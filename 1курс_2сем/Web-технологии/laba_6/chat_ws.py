from flask import Flask, render_template_string, jsonify
from flask_socketio import SocketIO, emit
import json
import os

# Создаём Flask-приложение
app = Flask(__name__)

# Инициализируем SocketIO для поддержки WebSocket соединений
socketio = SocketIO(app, cors_allowed_origins="*")

# Имя файла для хранения сообщений
MESSAGES_FILE = "messages.json"

# Загрузка сообщений из файла
def load_messages():
    if os.path.exists(MESSAGES_FILE):
        try:
            with open(MESSAGES_FILE, "r", encoding="utf-8") as f:
                return json.load(f)
        except Exception:
            return []
    return []

# Сохранение сообщений в файл
def save_messages(msgs):
    # Создаём директорию, если её нет
    os.makedirs(os.path.dirname(MESSAGES_FILE), exist_ok=True)
    with open(MESSAGES_FILE, "w", encoding="utf-8") as f:
        json.dump(msgs, f, ensure_ascii=False, indent=2)

# Список для хранения последних 100 сообщений чата
messages = load_messages()

# HTML-шаблон страницы чата с подключением к WebSocket через Socket.IO
HTML = '''
<!DOCTYPE html>
<html>
<head>
    <title>WebSocket Chat</title>
    <script src="https://cdn.socket.io/4.0.1/socket.io.min.js"></script>
</head>
<body>
    <h2>WebSocket Chat</h2>
    <div id="chat" style="height:200px;overflow:auto;border:1px solid #ccc;margin-bottom:10px;"></div>
    <input id="msg" type="text" autofocus>
    <button onclick="sendMsg()">Send</button>
    <script>
        // Подключение к серверу через Socket.IO
        var socket = io();
        // Функция отправки сообщения на сервер
        function sendMsg() {
            var m = document.getElementById('msg').value;
            if (m.trim() === "") return;
            socket.emit('message', m);
            document.getElementById('msg').value = '';
        }
        // Обработка получения новых сообщений от сервера
        socket.on('messages', function(msgs){
            var chat = document.getElementById('chat');
            chat.innerHTML = msgs.map(m => '<div>'+m+'</div>').join('');
            chat.scrollTop = chat.scrollHeight;
        });
        // Первоначальная загрузка истории сообщений через fetch и запрос к серверу
        fetch('/messages.json')
            .then(r=>r.json())
            .then(msgs=>socket.emit('messages', msgs));
    </script>
</body>
</html>
'''

# Главная страница: отдаёт HTML с чатом
@app.route('/')
def index():
    return render_template_string(HTML)

# Эндпоинт для получения последних 100 сообщений в формате JSON
@app.route('/messages.json')
def get_messages():
    # Загружаем актуальные сообщения из файла
    msgs = load_messages()
    return jsonify(msgs[-100:])

# Обработка события "message" от клиента (новое сообщение)
@socketio.on('message')
def handle_message(msg):
    msg = str(msg).strip()
    if msg:
        msgs = load_messages()
        msgs.append(msg)
        # Ограничиваем историю 100 сообщениями
        if len(msgs) > 100:
            msgs = msgs[-100:]
        save_messages(msgs)
        # Рассылаем обновлённую историю всем подключённым клиентам
        socketio.emit('messages', msgs[-100:])

# При подключении клиента отправляем ему последние 100 сообщений
@socketio.on('connect')
def handle_connect():
    # Загружаем актуальные сообщения из файла при подключении клиента
    msgs = load_messages()
    emit('messages', msgs[-100:])

# Обработка события "messages" — отправка истории сообщений клиенту по запросу
@socketio.on('messages')
def send_messages(msgs):
    # Загружаем актуальные сообщения из файла по запросу клиента
    msgs = load_messages()
    emit('messages', msgs[-100:])

# Запуск сервера
if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=8080)
