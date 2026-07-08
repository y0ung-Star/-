import imaplib, smtplib, mimetypes, time, os
from datetime import datetime
from tqdm import tqdm
import quopri
import base64

import email
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import decode_header
from email.message import EmailMessage
    
# Добавление почты и пароля для приложений
EMAIL = "eg89150319497@gmail.com"
PASSWD = "wfnm ywuo fzeo brwf"
RECIPIENT_EMAIL = "sawarinekodesu@gmail.com"
RECIPIENT_PASSWD = "jvtw fmya onec drey"

# IMAP сервер gmail
IMAP_SERVER = "imap.gmail.com"
IMAP_PORT = 993

# SMTP сервер gmail
SMTP_SERVER = "smtp.gmail.com"
SMTP_PORT = 587

# Настройки изображения для отправки
IMAGE_PATH = "image.png"
IMAGE_SIZE = os.path.getsize(IMAGE_PATH)

# Объем прогрузки файла за 1 итерацию цикла
CHUNK_SIZE = 1024 * 1024 # 1 MB


# Декодирование сообщения
def decode_header_value(header_value):
    decoded_parts = decode_header(header_value) # Разбиение заголовков на части
    result = ''
    for part, encoding in decoded_parts:
        if isinstance(part, bytes): # Если строка зашифрована
            result += part.decode(encoding or 'utf-8', errors='ignore') # Декодирование строки
        else:
            result += part
    return result


# Декодирование содержания письма (если оно закодировано)
def decode_body_part(body_part):
    content_transfer_encoding = body_part.get('Content-Transfer-Encoding') # Получаем заголовок
    if content_transfer_encoding == 'quoted-printable': # Если кодировка 'quoted-printable'
        return quopri.decodestring(body_part.get_payload()).decode('utf-8', 'ignore')
    elif content_transfer_encoding == 'base64': # Или 'base64'
        return base64.b64decode(body_part.get_payload()).decode('utf-8', 'ignore')
    else:
        return body_part.get_payload() # В противном случае просто возвращаем

# Сохранение файла
def save_attachment(part):
    filename = part.get_filename() # Получаем имя файла из сообщения
    if filename: # Если файл есть
        folder = 'attachments'
        if not os.path.exists(folder): # Если нет директории то создаём её
            os.makedirs(folder)

        filepath = os.path.join(folder, filename) # Заходим в директорию

        # Сохраняем файл
        with open(filepath, 'wb') as f: # Сохраняем файл
            f.write(part.get_payload(decode=True))

        print(f"Файл сохранён: {filepath}")

#####################
# SMTP SEND MESSAGE #
#####################

msg = EmailMessage() # Создаём экземпляр сообщения

# Передаём заголовки сообщению
msg["From"] = EMAIL
msg["To"] = RECIPIENT_EMAIL
msg["Subject"] = "Задание №6. Почтовый сервер"
msg.set_content(f"Отправил - Егоров Александр Владиславович М3О-125БВ-24, Принял - Егоров Александр Владиславович М3О-125БВ-24. Время отправки - {datetime.now()}.")

mime_type, _ = mimetypes.guess_type(IMAGE_PATH) # Присваиваем расширение файлу
if isinstance(mime_type, str):
    maintype, subtype = mime_type.split("/") # Разделяем раширение файла '/' для отправки
else:
    print("Error")
    exit(1)

file_data = bytearray() # Массив с данными файла

# Открываем файл в бинарном режиме и читаем его по частям
with open(IMAGE_PATH, 'rb') as file:
    # Создаём прогресс-бар
    with tqdm(total=IMAGE_SIZE, unit='B', unit_scale=True, desc="Загрузка файла") as pbar:
        while True:
            # Читаем файл по частям
            chunk = file.read(CHUNK_SIZE)
            if not chunk:
                break  # Выход из цикла, если файл прочитан полностью
            file_data.extend(chunk)  # Добавляем данные в массив
            pbar.update(len(chunk))  # Обновляем прогресс-бар
            time.sleep(0.1)  # Здесь можно сделать задержку для видимости процесса

print("Файл успешно загружен.")
print("Отправка файла.")

msg.add_attachment(file_data, maintype=maintype, subtype=subtype, filename=os.path.basename(IMAGE_PATH)) # Добавляем файл в письмо

with smtplib.SMTP(SMTP_SERVER, SMTP_PORT) as server: # Подключаемся к smtp серверу
    server.starttls()  # Устанавливаем TLS соединение
    server.login(EMAIL, PASSWD) # Логинимся
    server.send_message(msg) # Отправляем письмо

print("Файл отправлен.")

print('-' * 50)

#######################
# IMAP RECIVE MESSAGE #
######################

client = imaplib.IMAP4_SSL(IMAP_SERVER, IMAP_PORT) # Создание подключения к gmail imap серверу
client.login(RECIPIENT_EMAIL, RECIPIENT_PASSWD) # Логин

status_select, messages_count = client.select("INBOX") # Выбор ящика

if isinstance(messages_count[0], bytes): # Проверка на None
    print(f"Status: {status_select}\nMessages: {messages_count[0].decode()}") # Вывод статуса и количества сообщений
else:
    exit(1)

_, messages = client.search(None, 'ALL') # Подгрузка сообщений

message_ids = messages[0].split()[-5:][::-1] # Выбор 5 сообщений + реверс

print('-' * 50)

# Получение и обработка писем
for msg_id in message_ids:
    status, msg_data = client.fetch(msg_id, '(RFC822)') # Получение писем
    if status != 'OK':
        print(f'Не удалось получить письмо {msg_id.decode()}')
        continue

    raw_email = msg_data[0][1] # Получение сырых данных #type:ignore
    message = email.message_from_bytes(raw_email) # Преобразование байтов в объект 'email.message.Message' #type:ignore

    # Извлечение заголовков
    from_ = decode_header_value(message.get('From'))
    subject = decode_header_value(message.get('Subject'))
    date = message.get('Date')

    # Вывод заголовков
    print(f"From: {from_}")
    print(f"Subject: {subject}")
    print(f"Date: {date}")
    print('-' * 50)

# Поиск писем от отправителя
status_search, sender_messages = client.search(None, f'FROM "{EMAIL}"')

# Получаем список ID писем от этого отправителя
sender_message_ids = sender_messages[0].split()

print(f"Письмо от {EMAIL}:")

# Получение письма
if sender_message_ids:
    latest_msg_id = sender_message_ids[-1]  # Самое последнее письмо
    status, msg_data = client.fetch(latest_msg_id, '(RFC822)') # Получаем письмо
    
    if status != 'OK':
        print(f'Не удалось получить письмо {latest_msg_id.decode()}')
    else:
        raw_email = msg_data[0][1] # Получение сырых данных #type:ignore
        message = email.message_from_bytes(raw_email) # Преобразование байтов в объект 'email.message.Message' #type:ignore

        # Получение заголовков
        from_ = decode_header_value(message.get('From'))
        subject = decode_header_value(message.get('Subject'))
        date = message.get('Date')

        # Вывод заголовков
        print(f"From: {from_}")
        print(f"Subject: {subject}")
        print(f"Date: {date}")
        print("-" * 50)

        # Обрабатываем тело письма
        if message.is_multipart():
            # Если письмо многокомпонентное (с несколькими частями)
            for part in message.walk():
                content_type = part.get_content_type()
                content_disposition = str(part.get("Content-Disposition"))

                # Если это текстовое содержимое
                if "attachment" not in content_disposition:
                    if content_type == "text/plain":
                        body = decode_body_part(part)
                        print("Текстовое содержимое (plain):")
                        print(body)
                    elif content_type == "text/html":
                        body = decode_body_part(part)
                        print("Текстовое содержимое (HTML):")
                        print(body)
                else:
                    # Если это вложение, сохраняем его
                    save_attachment(part)
        else:
            # Если письмо состоит из одной части
            body = decode_body_part(message)
            print("Текстовое содержимое:")
            print(body)

        print("-" * 50)
else:
    print(f"Не найдено писем от {EMAIL}")

# Закрытие соединения
client.logout()

