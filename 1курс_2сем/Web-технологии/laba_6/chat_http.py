from flask import Flask, request, redirect, render_template_string
import json
import os

# Создаём экземпляр Flask-приложения
app = Flask(__name__)

# Имя файла для хранения сообщений
MESSAGES_FILE = "messages.json"

def load_messages():
    """Загружает сообщения из JSON-файла, если он существует."""
    if os.path.exists(MESSAGES_FILE):
        try:
            with open(MESSAGES_FILE, "r", encoding="utf-8") as f:
                return json.load(f)
        except Exception:
            return []
    return []

def save_messages(messages):
    """Сохраняет сообщения в JSON-файл."""
    os.makedirs(os.path.dirname(MESSAGES_FILE), exist_ok=True)
    with open(MESSAGES_FILE, "w", encoding="utf-8") as f:
        json.dump(messages, f, ensure_ascii=False)

# Список для хранения последних 100 сообщений чата
messages = load_messages()

# HTML-шаблон страницы чата с формой для ввода сообщений
HTML = '''
<!DOCTYPE html>
<html>
<head>
    <title>Chat</title>
    <style>
        body { font-family: Arial, sans-serif; }
        #chat-box { height: 250px; overflow-y: auto; border: 1px solid #ccc; padding: 8px; margin-bottom: 10px; background: #f9f9f9; }
        .msg { margin-bottom: 4px; }
        form { display: flex; gap: 8px; }
        input[type="text"] { flex: 1; padding: 6px; }
        button { padding: 6px 16px; }
    </style>
</head>
<body>
    <h2>HTTP Chat</h2>
    <div id="chat-box">
        {% for msg in messages %}
            <div class="msg">{{ msg }}</div>
        {% endfor %}
    </div>
    <form action="/send" method="post" autocomplete="off">
        <input type="text" name="message" placeholder="Type your message..." autofocus required maxlength="200">
        <button type="submit">Send</button>
    </form>
</body>
</html>
'''

@app.route('/', methods=['GET'])
def index():
    """
    Обрабатывает GET-запрос на главную страницу.
    Возвращает HTML-страницу с последними 100 сообщениями.
    """
    return render_template_string(HTML, messages=messages[-100:])

@app.route('/send', methods=['POST'])
def send():
    """
    Обрабатывает POST-запрос с новым сообщением.
    Добавляет сообщение в список, ограничивает список 100 сообщениями,
    сохраняет в JSON-файл, затем перенаправляет пользователя обратно на главную страницу.
    """
    msg = request.form.get('message', '').strip()
    if msg:
        messages.append(msg)
        if len(messages) > 100:
            messages.pop(0)
        save_messages(messages)
    return redirect('/')

if __name__ == '__main__':
    # При запуске сервера загружаем сообщения из файла (на случай изменений вне процесса)
    messages = load_messages()
    # Запуск сервера Flask на всех интерфейсах, порт 8080
    app.run(host='0.0.0.0', port=8080)
