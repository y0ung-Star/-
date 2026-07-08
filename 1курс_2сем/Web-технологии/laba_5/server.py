import socket
import threading
import datetime

HOST = '127.0.0.1'
PORT = 65432
MAX_CLIENTS = 10
CHAT_LOG_FILE = 'chat_log.txt'
HISTORY_LINES = 10

clients = []
client_lock = threading.Lock()

def log_message(message):
    # Сохраняем сообщение в файл с датой и временем
    try:
        with open(CHAT_LOG_FILE, 'a', encoding='utf-8') as f:
            timestamp = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            f.write(f"[{timestamp}] {message}\n")
    except Exception as e:
        print(f"Ошибка записи в лог: {e}")

def get_chat_history():
    # Берём последние N сообщений из файла истории
    try:
        with open(CHAT_LOG_FILE, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        return "".join(lines[-HISTORY_LINES:])
    except FileNotFoundError:
        return "Истории чата еще нет.\n"
    except Exception as e:
        print(f"Ошибка чтения истории чата: {e}")
        return "Ошибка получения истории.\n"

def broadcast_message(message, sender_socket):
    # Рассылаем сообщение всем, кроме отправителя
    with client_lock:
        for client_socket, _, nickname in clients:
            if client_socket != sender_socket:
                try:
                    client_socket.sendall(message.encode('utf-8'))
                except socket.error as e:
                    print(f"Ошибка отправки {nickname}: {e}")

def handle_client(conn, addr):
    print(f"Подключен клиент: {addr}")
    nickname = ""
    try:
        # Сначала просим никнейм
        conn.sendall("NICKNAME_REQUEST".encode('utf-8'))
        nickname_data = conn.recv(1024)
        if not nickname_data:
            print(f"Клиент {addr} отключился до отправки никнейма.")
            return
        nickname = nickname_data.decode('utf-8').strip()

        # Проверяем, не занят ли никнейм
        with client_lock:
            for _, _, existing_nick in clients:
                if existing_nick == nickname:
                    conn.sendall(f"Никнейм '{nickname}' уже занят. Пожалуйста, переподключитесь с другим никнеймом.\n".encode('utf-8'))
                    print(f"Клиент {addr} попытался использовать занятый никнейм: {nickname}")
                    return

        # Добавляем клиента в общий список
        with client_lock:
            clients.append((conn, addr, nickname))

        print(f"Клиент {addr} идентифицирован как {nickname}")
        log_message(f"{nickname} присоединился к чату.")
        broadcast_message(f"--- {nickname} присоединился к чату. ---\n", conn)

        # Отправляем историю чата новому участнику
        history = get_chat_history()
        if history and history.strip() != "Истории чата еще нет.":
            conn.sendall(f"--- Последние {HISTORY_LINES} сообщений ---\n".encode('utf-8'))
            conn.sendall(history.encode('utf-8'))
            conn.sendall("--- Конец истории ---\n".encode('utf-8'))
        elif history.strip() == "Истории чата еще нет.":
            conn.sendall("Истории чата еще нет.\n".encode('utf-8'))

        # Основной цикл общения с клиентом
        while True:
            data = conn.recv(1024)
            if not data:
                break

            message_text = data.decode('utf-8').strip()
            full_message = f"{nickname}: {message_text}"
            print(f"Получено от {nickname}: {message_text}")

            log_message(full_message)
            broadcast_message(full_message + "\n", conn)

    except socket.error as e:
        print(f"Ошибка сокета с {nickname} ({addr}): {e}")
    except Exception as e:
        print(f"Ошибка обработки клиента {nickname} ({addr}): {e}")
    finally:
        # Удаляем клиента из списка при отключении
        with client_lock:
            clients[:] = [c for c in clients if c[0] != conn]

        if nickname:
            print(f"{nickname} ({addr}) отключился.")
            log_message(f"{nickname} покинул чат.")
            broadcast_message(f"--- {nickname} покинул чат. ---\n", conn)
        else:
            print(f"Клиент {addr} отключился (без никнейма).")

        conn.close()

def start_server():
    # Запускаем сервер и ждем подключения клиентов
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            s.bind((HOST, PORT))
        except socket.error as e:
            print(f"Ошибка привязки: {e}")
            return

        s.listen(MAX_CLIENTS)
        print(f"Сервер слушает на {HOST}:{PORT}")

        try:
            while True:
                conn, addr = s.accept()
                thread = threading.Thread(target=handle_client, args=(conn, addr))
                thread.daemon = True
                thread.start()
        except KeyboardInterrupt:
            print("\nСервер останавливается...")
        finally:
            print("Закрытие всех клиентских соединений...")
            with client_lock:
                for client_socket, _, _ in clients:
                    try:
                        client_socket.sendall("SERVER_SHUTDOWN".encode('utf-8'))
                        client_socket.close()
                    except socket.error:
                        pass
            s.close()
            print("Сервер остановлен.")

if __name__ == '__main__':
    start_server()
