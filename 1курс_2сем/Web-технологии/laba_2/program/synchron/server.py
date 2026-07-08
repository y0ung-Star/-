import socket, time, json, os, logging

# Создание логгера
logger = logging.getLogger("logger")
logger.setLevel(logging.INFO)  # Уровень логирования (можно INFO, WARNING и т.д.)

# Формат логов
formatter = logging.Formatter(
    "%(asctime)s - %(levelname)s - %(message)s", 
    datefmt="%Y-%m-%d %H:%M:%S"
)

# Логгер для терминала
console_logger = logging.StreamHandler()
console_logger.setFormatter(formatter)
logger.addHandler(console_logger)

# Логгер для файла
file_log = logging.FileHandler("logs.log", mode="a", encoding="utf-8")
file_log.setFormatter(formatter)
logger.addHandler(file_log)


JSON_FILE = "config.json"

# Чтение конфига из файла
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

# Запись данных из файла в переменную
port = int(config.get("port"))
ip_addres = str(config.get("ip_addres"))
handler_delay = int(config.get("handler_delay"))
working_time = int(config.get("working_time"))

# Создание сокета
sock = socket.socket()
sock.bind((ip_addres, port))
sock.listen(1)

logger.info("Сервер запущен. Ожидание сообщений...")

def main():
    # Получение данных о подключенном клиенте
    conn, addr = sock.accept()
    conn.settimeout(1) # тайм-аут сокета
    logger.info(f"Установлено соединение с клиентом: {addr}")


    working_end_time = time.time() + working_time

    while time.time() < working_end_time:
        # Получение данных от клиента
        try:
            data = conn.recv(1024)
            data = data.decode()

            logger.info(f"Получено сообщение от клиента {addr}: '{data}'")

            # Эмуляция работы сервера
            time.sleep(handler_delay)

            # Отправка "обработанных" данных клиенту
            message = f"{data[::-1]}. Сервер написан Егоровым А.В. М3О-125БВ-24"
            conn.send((message).encode())

            logger.info(f"Сообщение отправлено клиенту {addr}: '{message}'")
        except socket.timeout:
            continue

    # Закрытие соединения
    # conn.send(("Клиент отключен от сервера.").encode())
    conn.close()

    logger.info(f"Клиент отключен от сервера: {addr}")

while True:
    main()
