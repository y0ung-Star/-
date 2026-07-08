import socket
import threading
import sys
import os

CACHE_FILE = 'client_chat_cache.txt'
CACHE_LINES = 5

def load_cache():
    # При запуске клиента выводим последние сообщения из локального кэша, чтобы пользователь видел историю прошлых сессий
    try:
        if os.path.exists(CACHE_FILE):
            with open(CACHE_FILE, 'r', encoding='utf-8') as f:
                lines = f.readlines()
            print("--- Последние сообщения из кэша ---")
            for line in lines:
                print(line.strip())
            print("--- Конец кэша ---")
    except Exception as e:
        print(f"Ошибка загрузки кэша: {e}")

def save_to_cache(message):
    # Сохраняем новое сообщение в кэш, чтобы при следующем запуске чата пользователь видел последние сообщения
    try:
        lines = []
        if os.path.exists(CACHE_FILE):
            with open(CACHE_FILE, 'r', encoding='utf-8') as f:
                lines = f.readlines()
        lines.append(message + '\n')
        # Оставляем только последние CACHE_LINES сообщений
        lines_to_write = lines[-CACHE_LINES:]
        with open(CACHE_FILE, 'w', encoding='utf-8') as f:
            f.writelines(lines_to_write)
    except Exception as e:
        print(f"Ошибка сохранения в кэш: {e}")

def receive_messages(client_socket):
    # Этот поток постоянно слушает сервер и выводит все входящие сообщения на экран
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if not message:
                print("Отключено от сервера (пустое сообщение).")
                break
            if message == "SERVER_SHUTDOWN":
                print("Сервер завершает работу. Отключение.")
                break
            if message == "NICKNAME_REQUEST":
                continue 
            print(message.strip())
        except socket.error as e:
            print(f"Ошибка соединения: {e}")
            break
        except Exception as e:
            print(f"Ошибка получения сообщения: {e}")
            break
    client_socket.close()
    print("Соединение закрыто.")
    os._exit(0) # Если этот поток завершился, выходим из всей программы

def start_client(host, port):
    # Основная функция клиента: подключение, ввод ника, отправка и получение сообщений
    load_cache()
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client_socket.connect((host, port))
        print(f"Подключено к серверу {host}:{port}")
    except socket.error as e:
        print(f"Не удалось подключиться к серверу: {e}")
        return
    except Exception as e:
        print(f"Непредвиденная ошибка при подключении: {e}")
        return

    nickname = ""
    try:
        # После подключения ждем от сервера запрос ника
        initial_data = client_socket.recv(1024).decode('utf-8')
        if initial_data.strip() == "NICKNAME_REQUEST":
            while not nickname:
                nickname = input("Введите ваш никнейм: ").strip()
                if not nickname:
                    print("Никнейм не может быть пустым.")
            client_socket.sendall(nickname.encode('utf-8'))
        else:
            print(initial_data.strip())
            if not nickname:
                while not nickname:
                    nickname = input("Введите ваш никнейм: ").strip()
                    if not nickname:
                        print("Никнейм не может быть пустым.")
                client_socket.sendall(nickname.encode('utf-8'))

        # Запускаем отдельный поток для получения сообщений от сервера
        receive_thread = threading.Thread(target=receive_messages, args=(client_socket,))
        receive_thread.daemon = True
        receive_thread.start()

        if nickname:
            print(f"Вы вошли как {nickname}. Вводите сообщения и нажимайте Enter. Введите 'выход' для завершения.")
        else:
            print("Вводите сообщения и нажимайте Enter. Введите 'выход' для завершения.")

        # Основной цикл: читаем ввод пользователя и отправляем на сервер
        while True:
            message_to_send = input()
            if message_to_send.lower() == 'выход':
                break
            if message_to_send:
                client_socket.sendall(message_to_send.encode('utf-8'))
                save_to_cache(f"Вы: {message_to_send}")

    except KeyboardInterrupt:
        print("\nОтключение...")
    except socket.error as e:
        print(f"Ошибка сокета во время связи: {e}")
    except Exception as e:
        print(f"Произошла ошибка: {e}")
    finally:
        print("Закрытие соединения.")
        client_socket.close()

if __name__ == '__main__':
    # Проверяем аргументы командной строки и запускаем клиент
    if len(sys.argv) != 3:
        print("Использование: python client.py <ip_адрес_хоста> <порт>")
        sys.exit(1)
    host_ip = sys.argv[1]
    try:
        port_num = int(sys.argv[2])
        if not (0 <= port_num <= 65535):
            raise ValueError("Номер порта должен быть от 0 до 65535.")
    except ValueError as e:
        print(f"Неверный номер порта: {e}")
        sys.exit(1)
    start_client(host_ip, port_num)
