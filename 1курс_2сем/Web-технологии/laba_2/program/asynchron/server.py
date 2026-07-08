import socket, time, json, os, logging, asyncio

# Логгер
logger = logging.getLogger("logger")
logger.setLevel(logging.INFO)
formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s", datefmt="%Y-%m-%d %H:%M:%S")

console_logger = logging.StreamHandler()
console_logger.setFormatter(formatter)
logger.addHandler(console_logger)

file_log = logging.FileHandler("logs.log", mode="a", encoding="utf-8")
file_log.setFormatter(formatter)
logger.addHandler(file_log)

# Чтение конфигурации
JSON_FILE = "config.json"
if os.path.exists(JSON_FILE):
    with open(JSON_FILE) as file:
        try:
            config = json.load(file)
        except Exception as e:
            logger.error(f"Ошибка: произошла ошибка при чтении конфигурационного файла: {e}. Выход.")
            exit()
else:
    logger.error("Ошибка: конфигурационный файл не найден. Выход.")
    exit()

# Настройки
port = int(config.get("port"))
ip_address = str(config.get("ip_addres"))
handler_delay = int(config.get("handler_delay"))
working_time = int(config.get("working_time"))

# Создание сокета
sock = socket.socket()
sock.bind((ip_address, port))
sock.listen()
sock.setblocking(False)

logger.info("Сервер запущен. Ожидание сообщений...")

async def handle_client(conn, addr):
    logger.info(f"Установлено соединение с клиентом: {addr}")
    conn.setblocking(False)

    loop = asyncio.get_running_loop()
    working_end_time = time.time() + working_time

    while time.time() < working_end_time:
        try:
            data = await asyncio.wait_for(loop.sock_recv(conn, 1024), timeout=1.0)
            data = data.decode()
            logger.info(f"Получено сообщение от клиента {addr}: '{data}'")

            await asyncio.sleep(handler_delay)

            message = f"{data[::-1]}. Сервер написан Егоровым А.В. М3О-125БВ-24"
            await loop.sock_sendall(conn, message.encode())
            logger.info(f"Сообщение отправлено клиенту {addr}: '{message}'")
        except asyncio.TimeoutError:
            continue
        except ConnectionResetError:
            logger.warning(f"Клиент {addr} разорвал соединение.")
            break
        except Exception as e:
            logger.error(f"Ошибка при обработке клиента {addr}: {e}")
            break

    conn.close()
    logger.info(f"Клиент отключен от сервера: {addr}")

async def main():
    loop = asyncio.get_running_loop()

    while True:
        conn, addr = await loop.sock_accept(sock)
        asyncio.create_task(handle_client(conn, addr))

# Запуск
if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        logger.info("Сервер остановлен вручную.")

