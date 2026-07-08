# Отчет по курсовой работе «Основы эксплуатации ЭВМ» (Typst)

Данный репозиторий содержит исходный код отчета, оформленного по ГОСТу с использованием системы верстки **Typst**. Работа выполнена для студентов МАИ (Вариант №1).

## 📋 Требования

Для компиляции документа вам понадобятся:
1.  **Typst CLI** (версия 0.11.0 или выше).
2.  Шрифт **Linux Libertine** (входит в стандартные репозитории большинства дистрибутивов).

---

## 🛠 Установка

### 1. Установка Typst

#### Arch Linux
```bash
sudo pacman -S typst
```

#### Ubuntu / Debian / Mint
Скачайте актуальный `.deb` пакет со страницы [релизов GitHub](https://github.com/typst/typst/releases) или установите через Cargo (требуется Rust):
```bash
cargo install --locked typst-cli
```

#### Fedora
```bash
sudo dnf install typst
```

### 2. Установка шрифтов
Документ использует шрифт `Linux Libertine`, так как он является метрическим аналогом Times New Roman и отлично поддерживает кириллицу.

**Ubuntu/Debian:**
```bash
sudo apt install fonts-linuxlibertine
```

**Arch Linux:**
```bash
sudo pacman -S ttf-linux-libertine
```

---

## 🚀 Компиляция и работа

### Обычная компиляция в PDF
```bash
typst compile main.typ
```
Результатом будет файл `main.pdf`.

### Режим «Живого просмотра» (Рекомендуется)
Typst мгновенно пересобирает документ при каждом сохранении файла:
```bash
typst watch main.typ
```
*Запустите эту команду, откройте PDF в любом просмотрщике (например, Zathura или Evince) и редактируйте `.typ` файл. Изменения будут видны сразу.*

### Если шрифты не установлены в систему
Если вы скачали шрифты в папку `fonts/` внутри проекта, используйте флаг `--font-path`:
```bash
typst compile --font-path ./fonts main.typ
```

