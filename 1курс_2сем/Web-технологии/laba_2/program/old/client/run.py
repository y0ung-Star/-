import socket, os, json, logging, time

JSON_FILE = "config.json"
MESSAGE = "Егоров Александр Владиславович М3О-125БВ-24"

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

port = int(config.get("port"))
ip_addres = str(config.get("ip_addres"))
time_to_wait = int(config.get("time_to_wait"))

sock = socket.socket()
sock.connect((ip_addres, port))

logger.info(f"Успешное подключение к серверу: {ip_addres}:{port}")

while True:
    time.sleep(time_to_wait)

    try:
        sock.send(MESSAGE.encode())
    except socket.error:
        break

    logger.info(f"Отправлено сообщение: '{MESSAGE}'")

    data = sock.recv(1024)

    print(data.decode())
    logger.info(f"Получено сообщение: '{data.decode()}'")

