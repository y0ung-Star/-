const net = require("net");
const fs = require("fs");
const os = require("os");

const CONFIG_FILE = "config.json";
const LOG_FILE = "logs.log";
const MESSAGE = "Егоров Александр Владиславович М3О-125БВ-24";

// Логирование
function log(message, level = "INFO") {
    const timestamp = new Date().toISOString().replace("T", " ").split(".")[0];
    const logMessage = `${timestamp} - ${level} - ${message}`;
    console.log(logMessage);
    try {
        fs.appendFileSync(LOG_FILE, logMessage + os.EOL, { encoding: "utf-8" });
    } catch (e) {
        console.error("Ошибка при записи в лог:", e.message);
    }
}

// Чтение конфигурации
if (!fs.existsSync(CONFIG_FILE)) {
    log("Ошибка: конфигурационный файл не найден. Выход.", "ERROR");
    process.exit(1);
}

let config;
try {
    const raw = fs.readFileSync(CONFIG_FILE);
    config = JSON.parse(raw);
} catch (e) {
    log(`Ошибка при чтении конфигурации: ${e.message}. Выход.`, "ERROR");
    process.exit(1);
}

// Проверка параметров
const PORT = parseInt(config.port);
const HOST = config.ip_addres;
const INTERVAL = parseInt(config.time_to_wait) * 1000;

if (!PORT || !HOST || !INTERVAL) {
    log("Ошибка: неверные параметры конфигурации. Выход.", "ERROR");
    process.exit(1);
}

// Создание сокета
const client = new net.Socket();

client.connect(PORT, HOST, () => {
    log(`Успешное подключение к серверу: ${HOST}:${PORT}`);

    setInterval(() => {
        if (!client.destroyed) {
            try {
                client.write(MESSAGE);
                log(`Отправлено сообщение: '${MESSAGE}'`);
            } catch (e) {
                log(`Ошибка при отправке данных: ${e.message}`, "ERROR");
                client.destroy();
            }
        }
        else {
            log("Отключен от сервера.")
            client.destroy();
        }
    }, INTERVAL);
});

client.on("data", (data) => {
    const text = data.toString().trim();
    console.log(text);
    log(`Получено сообщение: '${text}'`);
});

client.on("error", (err) => {
    log(`Ошибка соединения: ${err.message}`, "ERROR");
    process.exit(0);  // Завершение программы
});

client.on("close", () => {
    log("Соединение с сервером закрыто", "INFO");
    process.exit(0);  // Завершение программы
});

