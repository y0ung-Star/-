# Промпт и готовые задания для лаб

## Промпт
```md
Ты — эксперт-преподаватель по цифровой схемотехнике и мастер верстки в Typst. Твоя задача — генерировать идеальные отчеты по лабораторным работам "под ключ" на основе заданного варианта. 

Я предоставлю тебе условия логической задачи (функции, наборы, схемы). Ты должен провести полный математический расчет (минимизация, перевод в базисы, синтез на мультиплексорах/дешифраторах) и выдать ГОТОВЫЙ КОД для Typst.

КРИТИЧЕСКИЕ ТРЕБОВАНИЯ К TYPST-КОДУ:
1. Только ЧЕРНО-БЕЛЫЙ формат (используй `luma()`, `gray`, `black`). Никаких цветных элементов — документ пойдет на ЧБ-принтер. Выделяй элементы таблиц полужирным шрифтом `[*text*]`, а не цветом.
2. ЗАПРЕЩЕНО использовать функцию `path()` или `curve()`. Для отрисовки линий и диаграмм используй только `line(start: (x,y), end: (x,y))`.
3. ЗАПРЕЩЕНО использовать блок `context` в `header` и `footer` `page()`, чтобы избежать конфликтов версий. Используй простую нумерацию `numbering: "1"`.
4. ЗАПРЕЩЕНО использовать внешние пакеты. Все схемы должны быть нарисованы внутренними средствами (векторно).
5. Чтобы схемы, формулы и таблицы не разрывались между страницами, ОБЯЗАТЕЛЬНО оборачивай их в `#block(breakable: false)[ ... ]`.
6. Не ломай межстрочный интервал. Глобальные настройки абзаца: `#set par(justify: true, first-line-indent: 1.25cm, leading: 1.5em)`.

ОБЯЗАТЕЛЬНЫЙ ШАБЛОН ДОКУМЕНТА (используй его как базу):
```typst
#set page(
  paper: "a4",
  margin: (top: 2cm, bottom: 2cm, left: 2.5cm, right: 1.5cm),
  header: align(right, text(size: 9pt, fill: luma(100))[Лабораторная работа: Вариант №X]),
  numbering: "1"
)
#set text(font: "Linux Libertine", size: 14pt, lang: "ru")
#set par(justify: true, first-line-indent: 1.25cm, leading: 1.5em)
#set heading(numbering: "1.")
#show table: set block(breakable: false)

// --- ВЕКТОРНЫЙ ДВИЖОК ДЛЯ ЛОГИЧЕСКИХ СХЕМ ---
#let node_dot(x, y) = place(dx: x - 2.5pt, dy: y - 2.5pt, circle(radius: 2.5pt, fill: black))
#let wire(..pts) = {
  let p = pts.pos()
  for i in range(p.len() - 1) {
    place(line(start: p.at(i), end: p.at(i+1), stroke: 1.2pt))
  }
}
#let lbl(x, y, txt) = place(dx: x, dy: y, text(size: 13pt, txt))
#let gost_gate(x, y, sym) = {
  place(dx: x, dy: y, rect(width: 30pt, height: 40pt, stroke: 1.2pt)[
    #set align(center + horizon)
    #set par(first-line-indent: 0pt)
    #text(size: 14pt, weight: "bold", font: "monospace")[#sym]
  ])
}
#let inv_circle(x, y) = place(dx: x, dy: y - 3pt, circle(radius: 3pt, stroke: 1.2pt))

// ТИТУЛЬНЫЙ ЛИСТ
#align(center)[
  #set par(first-line-indent: 0pt)
  #text(weight: "bold")[МИНИСТЕРСТВО ОБРАЗОВАНИЯ И НАУКИ РОССИЙСКОЙ ФЕДЕРАЦИИ \ МАИ]
  #v(4cm)
  #text(size: 16pt, weight: "bold")[ОТЧЕТ]\
  #text(size: 14pt)[по лабораторной работе]\
  #v(1cm)
  #text(size: 14pt)[Вариант X]
]
#v(3cm)
#align(right)[
  #box(width: 8cm)[
    #set align(left)
    #set par(first-line-indent: 0pt)
    *Выполнил студент:* ФИО \
    *Проверил:* ФИО
  ]
]
#v(1fr)
#align(center)[Москва, 2026]
#pagebreak()
// --- ДАЛЕЕ ИДЕТ РЕШЕНИЕ ---
```

АЛГОРИТМ ТВОЕЙ РАБОТЫ:
1. Сначала в скрытом блоке мыслей (или просто текстом перед кодом) реши задачу математически. Если это Лаба №3 (Синтез на мультиплексорах), подставь заданные переменные в базовое уравнение мультиплексора и дешифратора, раскрой скобки и приведи к целевой функции.
2. Оформи ход решения текстом в Typst. 
3. Нарисуй итоговую схему (Дешифратор + Мультиплексор или базовые элементы) используя векторный движок из шаблона (`rect`, `wire`, `lbl`). Для Дешифратора и Мультиплексора рисуй большие прямоугольники `rect()` с подписями входов слева и выходов справа.
4. Выведи только полный, готовый к компиляции блок кода Typst.

Жду твоей готовности. После твоего ответа я пришлю номер лабораторной и конкретное условие варианта.
```

## Готовая лаба №2
```typst
#set page(
  paper: "a4",
  margin: (top: 2cm, bottom: 2cm, left: 2.5cm, right: 1.5cm),
  header: align(right, text(size: 9pt, fill: luma(100))[Лабораторная работа №2: Вариант №5]),
  numbering: "1"
)

#set text(font: "Linux Libertine", size: 14pt, lang: "ru")
#set par(justify: true, first-line-indent: 1.25cm, leading: 1.5em)
#set heading(numbering: "1.")

#show table: set block(breakable: false)

// ==========================================
// ВЕКТОРНЫЙ ДВИЖОК ДЛЯ ЛОГИЧЕСКИХ СХЕМ
// ==========================================
#let node_dot(x, y) = place(dx: x - 2.5pt, dy: y - 2.5pt, circle(radius: 2.5pt, fill: black))
#let wire(..pts) = {
  let p = pts.pos()
  for i in range(p.len() - 1) { place(line(start: p.at(i), end: p.at(i+1), stroke: 1.2pt)) }
}
#let lbl(x, y, txt) = place(dx: x, dy: y, text(size: 13pt, txt))

#let gost_gate(x, y, sym) = {
  place(dx: x, dy: y, rect(width: 30pt, height: 40pt, stroke: 1.2pt)[
    #set align(center + horizon)
    #set par(first-line-indent: 0pt)
    #text(size: 14pt, weight: "bold", font: "monospace")[#sym]
  ])
  place(dx: x + 30pt, dy: y + 17pt, circle(radius: 3pt, stroke: 1.2pt))
}

// ==========================================
// ВЕКТОРНЫЙ ДВИЖОК ДЛЯ ВРЕМЕННЫХ ДИАГРАММ
// ==========================================
#let draw_timing_diagram() = {
  set par(first-line-indent: 0pt)
  let step = 40pt
  let h_lines = 5
  let h_spacing = 45pt

  align(center)[
    #box(width: 40pt + 8 * step, height: h_lines * h_spacing)[
      #for i in range(9) {
        place(dx: 40pt + i * step, dy: 0pt, line(start: (0pt,0pt), end: (0pt, h_lines * h_spacing - 15pt), stroke: (dash: "dotted", paint: luma(120))))
        if i < 8 { place(dx: 40pt + i * step + step/2 - 4pt, dy: h_lines * h_spacing - 5pt, text(size: 10pt, fill: luma(100))[#i]) }
      }
      #let draw_sig(name, data, idx) = {
         place(dx: 0pt, dy: idx * h_spacing + 5pt, text(weight: "bold")[#name])
         let cur_y = if data.at(0) == 1 { 0pt } else { 20pt }
         for (i, val) in data.enumerate() {
            let start_x = 40pt + i * step
            let end_x = 40pt + (i + 1) * step
            let target_y = if val == 1 { 0pt } else { 20pt }
            let base_y = idx * h_spacing
            if target_y != cur_y {
                place(line(start: (start_x, base_y + cur_y), end: (start_x, base_y + target_y), stroke: 1.5pt))
                cur_y = target_y
            }
            place(line(start: (start_x, base_y + cur_y), end: (end_x, base_y + cur_y), stroke: 1.5pt))
         }
      }
      #draw_sig("x", (0,0,0,0, 1,1,1,1), 0)
      #draw_sig("y", (0,0,1,1, 0,0,1,1), 1)
      #draw_sig("z", (0,1,0,1, 0,1,0,1), 2)
      #draw_sig($S_1$, (1,0,1,1, 1,0,1,1), 3)
      #draw_sig("f", (1,1,1,1, 0,1,0,0), 4)
    ]
  ]
}

// --- ТИТУЛЬНЫЙ ЛИСТ ---
#align(center)[
  #set par(first-line-indent: 0pt)
  #text(weight: "bold")[
    МИНИСТЕРСТВО ОБРАЗОВАНИЯ И НАУКИ РОССИЙСКОЙ ФЕДЕРАЦИИ \
    ФЕДЕРАЛЬНОЕ ГОСУДАРСТВЕННОЕ БЮДЖЕТНОЕ ОБРАЗОВАТЕЛЬНОЕ \ УЧРЕЖДЕНИЕ ВЫСШЕГО ОБРАЗОВАНИЯ \
    «МОСКОВСКИЙ АВИАЦИОННЫЙ ИНСТИТУТ \
    (национальный исследовательский университет)» (МАИ)
  ]
  #v(2cm)
  #text(size: 16pt, weight: "bold")[ОТЧЕТ]\
  #text(size: 14pt)[по лабораторной работе №2]\
  #text(size: 14pt, weight: "bold")[«Синтез комбинационных схем на элементах И-НЕ, ИЛИ-НЕ»]\
  #v(0.5cm)
  #text(size: 14pt)[Вариант 5]
]

#v(3cm)
#align(right)[
  #box(width: 9cm)[
    #set align(left)
    #set par(first-line-indent: 0pt)
    *Выполнил студент:* \
    Егоров Александр Владиславович \
    *Группа:* \
    М3О-225БВ-24 \
    *Проверил преподаватель:* \
    Ходоровский Александр Зиновьевич
  ]
]
#v(1fr)
#align(center)[#set par(first-line-indent: 0pt); Москва, 2026]
#pagebreak()

= Задание
Минимизировать и реализовать на элементах И-НЕ, ИЛИ-НЕ неполностью определенную логическую функцию трех переменных: $f = 1$ на наборах 1, 3, 5; $f = 0$ на наборах 4, 7. На остальных наборах (0, 2, 6) функция не определена (обозначается как «-»).

= Таблица истинности и диаграмма Карно
Составим таблицу истинности для заданной функции, где входные переменные $x, y, z$ представляют собой двоичные наборы от 0 до 7. На базе таблицы заполним диаграмму Карно.

#v(1em)
#align(center)[
  #set par(first-line-indent: 0pt)
  #grid(
    columns: (1fr, 1fr),
    align: (center, center),
    table(
      columns: (30pt, 30pt, 30pt, 30pt, 40pt), align: center,
      [*№*], [*x*], [*y*], [*z*], [*f*],
      [0], [0], [0], [0], [-],
      [1], [0], [0], [1], [1],
      [2], [0], [1], [0], [-],
      [3], [0], [1], [1], [1],
      [4], [1], [0], [0], [0],
      [5], [1], [0], [1], [1],
      [6], [1], [1], [0], [-],
      [7], [1], [1], [1], [0]
    ),
    [
      #v(2em)
      *Диаграмма Карно заданной функции:*
      #v(1em)
      #table(
        columns: (40pt, 30pt, 30pt, 30pt, 30pt), align: center,
        [x \\ yz], [00], [01], [11], [10],
        [0], [—], [1], [1], [—],
        [1], [0], [1], [0], [—]
      )
    ]
  )
]

#pagebreak()

= Отыскание МДНФ и МКНФ

== 2.1 Формальный (аналитический) метод
*Поиск МДНФ:* \
Составим Совершенную ДНФ для рабочих (единичных) наборов:
$ f(1) = Sigma(1, 3, 5) = overline(x) overline(y) z + overline(x) y z + x overline(y) z $
СДНФ для неопределенных наборов (допустимых для склеивания):
$ f(-) = Sigma(0, 2, 6) = overline(x) overline(y) overline(z) + overline(x) y overline(z) + x y overline(z) $

Проведем операцию неполного попарного склеивания (по методу Квайна) между рабочими и неопределенными наборами для нахождения простых импликант:
1. Склеивая наборы (0,1,2,3), получаем импликанту: $overline(x)$.
2. Склеивая наборы (1,5), получаем импликанту: $overline(y) z$.

Составим импликантную матрицу покрытия рабочих наборов $f(1)$:
#v(1em)
#align(center)[
  #set par(first-line-indent: 0pt)
  #table(
    columns: (100pt, 40pt, 40pt, 40pt), align: center,
    [*Импликанты*], [*1*], [*3*], [*5*],
    [$overline(x)$], [X], [X], [],
    [$overline(y) z$], [X], [], [X]
  )
]
Для покрытия всех рабочих наборов необходимы обе простые импликанты. \
*МДНФ:* $ f = overline(x) + overline(y)z $

#v(1em)
*Поиск МКНФ:* \
Составим Совершенную КНФ для нулевых наборов (наборы 4 и 7):
$ f(0) = Pi(4, 7) = (overline(x) + y + z)(overline(x) + overline(y) + overline(z)) $
СКНФ для неопределенных наборов:
$ f(-) = Pi(0, 2, 6) = (x + y + z)(x + overline(y) + z)(overline(x) + overline(y) + z) $

Склеиваем макситермы:
1. Наборы (4,6) дают макситерм: $(overline(x) + z)$.
2. Наборы (6,7) дают макситерм: $(overline(x) + overline(y))$.

Составим импликантную матрицу покрытия нулевых наборов $f(0)$:
#v(1em)
#align(center)[
  #set par(first-line-indent: 0pt)
  #table(
    columns: (150pt, 40pt, 40pt), align: center,
    [*Макситермы*], [*4*], [*7*],
    [$(overline(x) + z)$], [X], [],
    [$(overline(x) + overline(y))$], [], [X]
  )
]
*МКНФ:* $ f = (overline(x) + z)(overline(x) + overline(y)) $

#pagebreak()

== 2.2 Инженерный метод (по диаграммам Карно)
Для проверки результатов формального метода проведем минимизацию по диаграмме Карно.

*Отыскание МДНФ (по 1):* \
Дополняем контуры неопределенными наборами до размеров $2^n$.
- Контур 1 (объединяет всю верхнюю строку $x=0$) дает импликанту $overline(x)$.
- Контур 2 (объединяет столбец $y=0, z=1$) дает импликанту $overline(y)z$.

#v(1em)
#align(center)[
  #set par(first-line-indent: 0pt)
  #table(
    columns: 5, align: center,
    [x \\ yz], [00], [01], [11], [10],
    [0], [*—*], [*1*], [*1*], [*—*],
    [1], [0], [*1*], [0], [-]
  )
]
*Результат МДНФ совпадает:* $ f = overline(x) + overline(y)z $

#v(1em)
*Отыскание МКНФ (по 0):* \
- Контур 1 (края нижней строки: наборы 100 и 110) дает макситерм $(overline(x) + z)$.
- Контур 2 (соседние клетки 111 и 110) дает макситерм $(overline(x) + overline(y))$.

#v(1em)
#align(center)[
  #set par(first-line-indent: 0pt)
  #table(
    columns: 5, align: center,
    [x \\ yz], [00], [01], [11], [10],
    [0], [-], [1], [1], [-],
    [1], [*0*], [1], [*0*], [*—*]
  )
]
*Результат МКНФ совпадает:* $ f = (overline(x) + z)(overline(x) + overline(y)) $

#pagebreak()

= Перевод в базисы И-НЕ, ИЛИ-НЕ
Для перевода полученных минимальных форм в заданные базисы применяется закон двойного отрицания и правила де Моргана.

*1. Из МДНФ в базис И-НЕ (штрих Шеффера):*
$ f = overline(x) + overline(y)z = overline(overline(overline(x) + overline(y)z)) = overline(x dot overline(overline(y)z)) $

*2. Из МДНФ в базис ИЛИ-НЕ (стрелка Пирса):*
$ f = overline(x) + overline(y)z = overline(x) + overline(overline(overline(y)z)) = overline(x) + overline(y + overline(z)) = overline(overline(overline(x) + overline(y + overline(z)))) $

*3. Из МКНФ в базис ИЛИ-НЕ (стрелка Пирса):*
$ f = (overline(x) + z)(overline(x) + overline(y)) = overline(overline((overline(x) + z)(overline(x) + overline(y)))) = overline(overline(overline(x) + z) + overline(overline(x) + overline(y))) $

*4. Из МКНФ в базис И-НЕ (штрих Шеффера):*
$ overline(x) + z = overline(overline(overline(x) + z)) = overline(x overline(z)) $
$ overline(x) + overline(y) = overline(overline(overline(x) + overline(y))) = overline(x y) $
$ f = (overline(x) + z)(overline(x) + overline(y)) = overline(x overline(z)) dot overline(x y) = overline(overline(overline(x overline(z)) dot overline(x y))) $

= Оценка сложности реализаций (цена по Квайну)
Сложность схемы оценивается как суммарное число входов используемых элементов (прямые и инверсные сигналы доступны изначально).

- МДНФ в И-НЕ: 1 эл. (2 вх.) + 1 эл. (2 вх.) = *4 у.е.* (Оптимальная схема)
- МДНФ в ИЛИ-НЕ: 1 эл. (2 вх.) + 1 эл. (2 вх.) + инвертор (1 вх.) = *5 у.е.*
- МКНФ в ИЛИ-НЕ: 2 эл. (по 2 вх.) + 1 эл. (2 вх.) = *6 у.е.*
- МКНФ в И-НЕ: 2 эл. (по 2 вх.) + 1 эл. (2 вх.) + инвертор (1 вх.) = *7 у.е.*

#pagebreak()

= Построение логических схем

Ниже представлены структурные схемы для всех четырех реализаций. Обозначения согласно ГОСТ: элемент с символом & — логическое И-НЕ, с символом 1 — логическое ИЛИ-НЕ.

#v(2em)
#block(breakable: false)[
  *Схема 1: МДНФ в И-НЕ (Оптимальная, цена 4)*
  #align(center)[
    #box(width: 250pt, height: 70pt)[
      #lbl(0pt, 12pt, $overline(y)$); #wire((20pt, 20pt), (60pt, 20pt))
      #lbl(0pt, 32pt, $z$); #wire((20pt, 40pt), (60pt, 40pt))
      #gost_gate(60pt, 10pt, "&")
      #wire((96pt, 30pt), (140pt, 30pt))
      #lbl(0pt, 42pt, $x$); #wire((20pt, 50pt), (140pt, 50pt))
      #gost_gate(140pt, 20pt, "&")
      #wire((176pt, 40pt), (210pt, 40pt)); #lbl(215pt, 32pt, $f$)
    ]
  ]
]

#v(2em)
#block(breakable: false)[
  *Схема 2: МДНФ в ИЛИ-НЕ (цена 5)*
  #align(center)[
    #box(width: 320pt, height: 70pt)[
      #lbl(0pt, 12pt, $y$); #wire((20pt, 20pt), (60pt, 20pt))
      #lbl(0pt, 32pt, $overline(z)$); #wire((20pt, 40pt), (60pt, 40pt))
      #gost_gate(60pt, 10pt, "1")
      #wire((96pt, 30pt), (140pt, 30pt))
      #lbl(0pt, 42pt, $overline(x)$); #wire((20pt, 50pt), (140pt, 50pt))
      #gost_gate(140pt, 20pt, "1")
      #wire((176pt, 40pt), (200pt, 40pt), (200pt, 30pt), (220pt, 30pt))
      #wire((200pt, 40pt), (200pt, 50pt), (220pt, 50pt)); #node_dot(200pt, 40pt)
      #gost_gate(220pt, 20pt, "1")
      #wire((256pt, 40pt), (290pt, 40pt)); #lbl(295pt, 32pt, $f$)
      #place(dx: 235pt, dy: 70pt, text(size: 11pt)[(инвертор)])
    ]
  ]
]

#v(2em)
#block(breakable: false)[
  *Схема 3: МКНФ в ИЛИ-НЕ (цена 6)*
  #align(center)[
    #box(width: 250pt, height: 110pt)[
      #lbl(0pt, 2pt, $overline(x)$)
      #wire((20pt, 10pt), (60pt, 10pt)); #wire((40pt, 10pt), (40pt, 70pt), (60pt, 70pt)); #node_dot(40pt, 10pt)
      #lbl(0pt, 22pt, $z$); #wire((20pt, 30pt), (60pt, 30pt))
      #gost_gate(60pt, 0pt, "1")
      #lbl(0pt, 82pt, $overline(y)$); #wire((20pt, 90pt), (60pt, 90pt))
      #gost_gate(60pt, 60pt, "1")
      #wire((96pt, 20pt), (120pt, 20pt), (120pt, 40pt), (140pt, 40pt))
      #wire((96pt, 80pt), (120pt, 80pt), (120pt, 60pt), (140pt, 60pt))
      #gost_gate(140pt, 30pt, "1")
      #wire((176pt, 50pt), (210pt, 50pt)); #lbl(215pt, 42pt, $f$)
    ]
  ]
]

#v(2em)
#block(breakable: false)[
  *Схема 4: МКНФ в И-НЕ (цена 7)*
  #align(center)[
    #box(width: 320pt, height: 110pt)[
      #lbl(0pt, 2pt, $x$)
      #wire((20pt, 10pt), (60pt, 10pt)); #wire((40pt, 10pt), (40pt, 70pt), (60pt, 70pt)); #node_dot(40pt, 10pt)
      #lbl(0pt, 22pt, $overline(z)$); #wire((20pt, 30pt), (60pt, 30pt))
      #gost_gate(60pt, 0pt, "&")
      #lbl(0pt, 82pt, $y$); #wire((20pt, 90pt), (60pt, 90pt))
      #gost_gate(60pt, 60pt, "&")
      #wire((96pt, 20pt), (120pt, 20pt), (120pt, 40pt), (140pt, 40pt))
      #wire((96pt, 80pt), (120pt, 80pt), (120pt, 60pt), (140pt, 60pt))
      #gost_gate(140pt, 30pt, "&")
      #wire((176pt, 50pt), (200pt, 50pt), (200pt, 40pt), (220pt, 40pt))
      #wire((200pt, 50pt), (200pt, 60pt), (220pt, 60pt)); #node_dot(200pt, 50pt)
      #gost_gate(220pt, 30pt, "&")
      #wire((256pt, 50pt), (290pt, 50pt)); #lbl(295pt, 42pt, $f$)
      #place(dx: 235pt, dy: 80pt, text(size: 11pt)[(инвертор)])
    ]
  ]
]

#pagebreak()

= Временные диаграммы работы

#block(breakable: false)[
  Временная диаграмма построена для выбранной оптимальной схемы (МДНФ в базисе И-НЕ), описываемой уравнением $f = overline(x dot S_1)$, где промежуточный сигнал $S_1 = overline(overline(y)z)$.

  #v(2em)
  #draw_timing_diagram()
]```

## Готовая лаба №3
```typst
#set page(
  paper: "a4",
  margin: (top: 2cm, bottom: 2cm, left: 2.5cm, right: 1.5cm),
  header: align(right, text(size: 9pt, fill: luma(100))[Лабораторная работа №3: Вариант №13]),
  numbering: "1"
)

#set text(font: "Linux Libertine", size: 14pt, lang: "ru")
#set par(justify: true, first-line-indent: 1.25cm, leading: 1.5em)
#set heading(numbering: "1.")
#show table: set block(breakable: false)

// ==========================================
// ВЕКТОРНЫЙ ДВИЖОК ДЛЯ ЛОГИЧЕСКИХ СХЕМ
// ==========================================
#let node_dot(x, y) = place(dx: x - 2.5pt, dy: y - 2.5pt, circle(radius: 2.5pt, fill: black))
#let wire(..pts) = {
  let p = pts.pos()
  for i in range(p.len() - 1) { place(line(start: p.at(i), end: p.at(i+1), stroke: 1.2pt)) }
}
#let lbl(x, y, txt) = place(dx: x, dy: y, text(size: 13pt, txt))

#let dc_box(x, y) = {
  place(dx: x, dy: y, rect(width: 50pt, height: 100pt, stroke: 1.2pt)[
    #place(dx: 12pt, dy: 5pt, text(size: 11pt, weight: "bold", "DC"))
    #place(dx: 2pt, dy: 15pt, text(size: 9pt, "x1")); #place(dx: 40pt, dy: 15pt, text(size: 9pt, "0"))
    #place(dx: 2pt, dy: 35pt, text(size: 9pt, "x0")); #place(dx: 40pt, dy: 35pt, text(size: 9pt, "1"))
                                                      #place(dx: 40pt, dy: 55pt, text(size: 9pt, "2"))
    #place(dx: 2pt, dy: 75pt, text(size: 9pt, "E"));  #place(dx: 40pt, dy: 75pt, text(size: 9pt, "3"))
  ])
  wire((x - 15pt, y + 20pt), (x, y + 20pt)); wire((x - 15pt, y + 40pt), (x, y + 40pt))
  wire((x - 15pt, y + 80pt), (x, y + 80pt))
  wire((x + 50pt, y + 20pt), (x + 65pt, y + 20pt)); wire((x + 50pt, y + 40pt), (x + 65pt, y + 40pt))
  wire((x + 50pt, y + 60pt), (x + 65pt, y + 60pt)); wire((x + 50pt, y + 80pt), (x + 65pt, y + 80pt))
}

#let ms_box(x, y) = {
  place(dx: x, dy: y, rect(width: 50pt, height: 100pt, stroke: 1.2pt)[
    #place(dx: 12pt, dy: 5pt, text(size: 11pt, weight: "bold", "MS"))
    #place(dx: 2pt, dy: 15pt, text(size: 9pt, "0")); #place(dx: 2pt, dy: 35pt, text(size: 9pt, "1"))
    #place(dx: 2pt, dy: 55pt, text(size: 9pt, "2")); #place(dx: 2pt, dy: 75pt, text(size: 9pt, "3"))
    #place(dx: 10pt, dy: 85pt, text(size: 9pt, "Z1")); #place(dx: 30pt, dy: 85pt, text(size: 9pt, "Z0"))
  ])
  wire((x - 15pt, y + 20pt), (x, y + 20pt)); wire((x - 15pt, y + 40pt), (x, y + 40pt))
  wire((x - 15pt, y + 60pt), (x, y + 60pt)); wire((x - 15pt, y + 80pt), (x, y + 80pt))
  wire((x + 15pt, y + 100pt), (x + 15pt, y + 115pt)); wire((x + 35pt, y + 100pt), (x + 35pt, y + 115pt))
  wire((x + 50pt, y + 50pt), (x + 65pt, y + 50pt))
}

// ==========================================
// ВЕКТОРНЫЙ ДВИЖОК ДЛЯ ВРЕМЕННЫХ ДИАГРАММ (16 ТАКТОВ)
// ==========================================
#let draw_timing_diagram() = {
  set par(first-line-indent: 0pt)
  let step = 25pt
  let h_lines = 6
  let h_spacing = 35pt

  align(center)[
    #box(width: 30pt + 16 * step, height: h_lines * h_spacing)[
      #for i in range(17) {
        place(dx: 30pt + i * step, dy: 0pt, line(start: (0pt,0pt), end: (0pt, h_lines * h_spacing - 10pt), stroke: (dash: "dotted", paint: luma(120))))
        if i < 16 { place(dx: 30pt + i * step + step/2 - 4pt, dy: h_lines * h_spacing - 5pt, text(size: 9pt, fill: luma(100))[#i]) }
      }
      #let draw_sig(name, data, idx) = {
         place(dx: 0pt, dy: idx * h_spacing + 2pt, text(weight: "bold")[#name])
         let cur_y = if data.at(0) == 1 { 0pt } else { 15pt }
         for (i, val) in data.enumerate() {
            let start_x = 30pt + i * step
            let end_x = 30pt + (i + 1) * step
            let target_y = if val == 1 { 0pt } else { 15pt }
            let base_y = idx * h_spacing
            if target_y != cur_y {
                place(line(start: (start_x, base_y + cur_y), end: (start_x, base_y + target_y), stroke: 1.5pt))
                cur_y = target_y
            }
            place(line(start: (start_x, base_y + cur_y), end: (end_x, base_y + cur_y), stroke: 1.5pt))
         }
      }
      #draw_sig("a", (0,0,0,0, 0,0,0,0, 1,1,1,1, 1,1,1,1), 0)
      #draw_sig("b", (0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1), 1)
      #draw_sig("c", (0,0,1,1, 0,0,1,1, 0,0,1,1, 0,0,1,1), 2)
      #draw_sig("d", (0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1), 3)
      #draw_sig("f", (0,0,0,0, 0,0,0,0, 0,0,0,1, 1,1,1,0), 4)
    ]
  ]
}

// --- ТИТУЛЬНЫЙ ЛИСТ ---
#align(center)[
  #set par(first-line-indent: 0pt)
  #text(weight: "bold")[
    МИНИСТЕРСТВО ОБРАЗОВАНИЯ И НАУКИ РОССИЙСКОЙ ФЕДЕРАЦИИ \
    ФЕДЕРАЛЬНОЕ ГОСУДАРСТВЕННОЕ БЮДЖЕТНОЕ ОБРАЗОВАТЕЛЬНОЕ \ УЧРЕЖДЕНИЕ ВЫСШЕГО ОБРАЗОВАНИЯ \
    «МОСКОВСКИЙ АВИАЦИОННЫЙ ИНСТИТУТ \
    (национальный исследовательский университет)» (МАИ)
  ]
  #v(2cm)
  #text(size: 16pt, weight: "bold")[ОТЧЕТ]\
  #text(size: 14pt)[по лабораторной работе №3]\
  #text(size: 14pt, weight: "bold")[«Анализ и синтез схем на дешифраторах и мультиплексорах»]\
  #v(1cm)
  #text(size: 14pt)[Вариант 13]
]

#v(2cm)
#align(right)[
  #box(width: 9cm)[
    #set align(left)
    #set par(first-line-indent: 0pt)
    *Выполнил студент:* \
    Егоров Александр Владиславович \
    *Группа:* \
    М3О-225БВ-24 \
    *Проверил преподаватель:* \
    Ходоровский Александр Зиновьевич
  ]
]
#v(1fr)
#align(center)[#set par(first-line-indent: 0pt); Москва, 2026]
#pagebreak()


= Задание 1: Анализ логической схемы

*Исходные данные (Вариант 13):* \
Дана схема: последовательно соединенные дешифратор 2/4 (DC) и мультиплексор 4/1 (MS).
- Входы DC: $x_1 = c, x_0 = overline(b), E = a$.
- Входы MS: $Z_1 = y_0, Z_0 = d, D_0 = y_2, D_1 = y_3, D_2 = a, D_3 = 1$.

== 1. Определение логической функции
Дешифратор 2/4 формирует следующие минтермы:
$ y_0 = overline(c) dot overline(overline(b)) dot a = a b overline(c) $
$ y_1 = overline(c) dot overline(b) dot a = a overline(b) overline(c) $
$ y_2 = c dot overline(overline(b)) dot a = a b c $
$ y_3 = c dot overline(b) dot a = a overline(b) c $

Уравнение мультиплексора 4/1:
$ f = overline(Z_1) overline(Z_0) D_0 + overline(Z_1) Z_0 D_1 + Z_1 overline(Z_0) D_2 + Z_1 Z_0 D_3 $

Подставим исходные значения:
$ f = overline(y_0) dot overline(d) dot y_2 + overline(y_0) dot d dot y_3 + y_0 dot overline(d) dot a + y_0 dot d dot 1 $

Подставим найденные значения $y_i$ и раскроем инверсию $overline{(a b overline(c))} = overline(a) + overline(b) + c$:
$ f = (overline(a) + overline(b) + c) overline(d) a b c + (overline(a) + overline(b) + c) d a overline(b) c + a b overline(c) overline(d) a + a b overline(c) d $
$ f = a b c overline(d) + a overline(b) c d + a b overline(c) overline(d) + a b overline(c) d $

Сгруппируем слагаемые и упростим функцию:
$ f = a b c overline(d) + a overline(b) c d + a b overline(c) (overline(d) + d) = a b c overline(d) + a overline(b) c d + a b overline(c) $
Применим правило склеивания $x + overline(x)y = x + y$:
$ a b c overline(d) + a b overline(c) = a b (c overline(d) + overline(c)) = a b (overline(c) + overline(d)) = a b overline(c) + a b overline(d) $

*Аналитическая функция:* $ f = a b overline(c) + a b overline(d) + a overline(b) c d $

== 2. Отыскание МДНФ и МКНФ (по Диаграмме Карно)
Для найденной функции четырех переменных построим диаграмму Карно. Функция равна 1 на наборах: 1011 (11), 1100 (12), 1101 (13), 1110 (14).

#v(1em)
#align(center)[
  #table(
    columns: 5, align: center,
    [ab \\ cd], [00], [01], [11], [10],
    [00], [0], [0], [0], [0],
    [01], [0], [0], [0], [0],
    [11], [*1*], [*1*], [0], [*1*],
    [10], [0], [0], [*1*], [0]
  )
]

*Отыскание МДНФ:*
Обводим единицы: контур 1100-1101 дает $a b overline(c)$, контур 1100-1110 дает $a b overline(d)$, обособленная клетка 1011 дает $a overline(b) c d$. \
*МДНФ:* $ f = a b overline(c) + a b overline(d) + a overline(b) c d $

*Отыскание МКНФ:*
Обводим нули:
1. Восемь нулей в строках 00 и 01 дают макситерм $a$.
2. Квадрат нулей 0000, 0001, 1000, 1001 дает макситерм $(b+c)$.
3. Квадрат нулей 0000, 0010, 1000, 1010 дает макситерм $(b+d)$.
4. Пара нулей 0111, 1111 дает макситерм $(overline(b) + overline(c) + overline(d))$.

*МКНФ:* $ f = a(b+c)(b+d)(overline(b) + overline(c) + overline(d)) $

#pagebreak()

== 3. Временные диаграммы работы схемы
Временная диаграмма построена для полного цикла из 16 комбинаций входных переменных (от 0000 до 1111).

#v(2em)
#block(breakable: false)[
  #draw_timing_diagram()
]

#v(3em)
= Задание 2: Синтез логической схемы

*Исходные данные (Вариант 13):* \
Дана целевая логическая функция:
$ y = a overline(b) c d h + c overline(d) + a b overline(c) overline(d) h + a overline(b) overline(c) d overline(h) $
Требуется реализовать данную функцию на DC 2/4 и MS 4/1.

*Распределение переменных:* \
Назначим управляющие входы мультиплексора: $Z_1 = c$, $Z_0 = d$. \
Представим функцию $y$ в базовом виде мультиплексора, сгруппировав слагаемые:
$ y = overline(c) overline(d) (a b h) + overline(c) d (a overline(b) overline(h)) + c overline(d) (1) + c d (a overline(b) h) $
Информационные входы мультиплексора: $D_0 = a b h$, $D_1 = a overline(b) overline(h)$, $D_2 = 1$, $D_3 = a overline(b) h$.

Назначим входы дешифратора: $E = a$, $x_1 = b$, $x_0 = h$. \
Выходы дешифратора:
$ y_0 = a overline(b) overline(h) quad y_1 = a overline(b) h quad y_2 = a b overline(h) quad y_3 = a b h $

Сопоставим входы MS и выходы DC: $D_0 = y_3$, $D_1 = y_0$, $D_2 = 1$, $D_3 = y_1$.

#v(2em)
#block(breakable: false)[
  *Принципиальная схема к Заданию 2*
  #align(center)[
    #box(width: 400pt, height: 160pt)[
      #lbl(30pt, 12pt, $b$); #wire((50pt, 20pt), (85pt, 20pt))
      #lbl(30pt, 32pt, $h$); #wire((50pt, 40pt), (85pt, 40pt))
      #lbl(30pt, 72pt, $a$); #wire((50pt, 80pt), (85pt, 80pt))

      #dc_box(100pt, 0pt)
      #ms_box(250pt, 0pt)

      #wire((165pt, 20pt), (185pt, 20pt), (185pt, 40pt), (235pt, 40pt)) // y0 -> D1
      #wire((165pt, 40pt), (195pt, 40pt), (195pt, 80pt), (235pt, 80pt)) // y1 -> D3
      #wire((165pt, 80pt), (205pt, 80pt), (205pt, 20pt), (235pt, 20pt)) // y3 -> D0
      #lbl(220pt, 52pt, $1$); #wire((230pt, 60pt), (235pt, 60pt)) // 1 -> D2
      
      #lbl(260pt, 142pt, $c$); #wire((265pt, 140pt), (265pt, 115pt))
      #lbl(280pt, 142pt, $d$); #wire((285pt, 140pt), (285pt, 115pt))
      #lbl(325pt, 42pt, $y$)
    ]
  ]
]

#pagebreak()

= Дополнительное задание
*Задание:* На последовательно соединенных дешифраторе 2/4 и мультиплексоре 4/1 реализовать схему одноразрядного полусумматора.

*Теоретическое обоснование:* \
Одноразрядный полусумматор складывает два бита $A$ и $B$, формируя на выходе сумму $S$ и перенос $C$. Логические уравнения полусумматора:
- Сумма: $S = A overline(B) + overline(A) B = A plus.circle B$
- Перенос: $C = A B$

В нашем распоряжении микросхемы DC 2/4 и MS 4/1. \
Подадим входные сигналы на дешифратор: $x_1 = A, x_0 = B, E = 1$. \
Дешифратор сформирует минтермы:
$ y_0 = overline(A) overline(B) quad y_1 = overline(A) B quad y_2 = A overline(B) quad y_3 = A B $

Заметим, что сигнал $y_3$ полностью соответствует функции переноса $C$. Следовательно, выход $y_3$ можно использовать как готовый выход переноса $C$, минуя мультиплексор.

Осталось реализовать функцию суммы $S = y_1 + y_2$. \
Используем мультиплексор 4/1 для реализации логического ИЛИ. Подадим на его управляющие входы сигналы с дешифратора: $Z_1 = y_1, Z_0 = y_2$. \
Так как $y_1$ и $y_2$ никогда не равны единице одновременно (свойство дешифратора), на адресных входах мультиплексора возможны только три комбинации: 00, 01, 10. \
Чтобы на выходе MS получить функцию ИЛИ ($y_1 + y_2$), настроим информационные входы:
- При адресе 00 ($y_1=0, y_2=0$), сумма должна быть 0 $arrow.r$ $D_0 = 0$.
- При адресе 01 ($y_1=0, y_2=1$), сумма должна быть 1 $arrow.r$ $D_1 = 1$.
- При адресе 10 ($y_1=1, y_2=0$), сумма должна быть 1 $arrow.r$ $D_2 = 1$.
- Адрес 11 невозможен, поэтому $D_3$ может быть любым (подключим к 0).

#v(2em)
#block(breakable: false)[
  *Принципиальная схема полусумматора*
  #align(center)[
    #box(width: 400pt, height: 160pt)[
      #lbl(30pt, 12pt, $A$); #wire((50pt, 20pt), (85pt, 20pt))
      #lbl(30pt, 32pt, $B$); #wire((50pt, 40pt), (85pt, 40pt))
      #lbl(30pt, 72pt, $1$); #wire((50pt, 80pt), (85pt, 80pt))

      #dc_box(100pt, 0pt)
      #ms_box(250pt, 0pt)

      // y1 к Z1, y2 к Z0
      #wire((165pt, 40pt), (185pt, 40pt), (185pt, 135pt), (265pt, 135pt), (265pt, 115pt))
      #wire((165pt, 60pt), (200pt, 60pt), (200pt, 150pt), (285pt, 150pt), (285pt, 115pt))
      
      // y3 напрямую на выход C
      #wire((165pt, 80pt), (315pt, 80pt)); #lbl(325pt, 72pt, $C ("Перенос")$)

      // Информационные входы MS
      #lbl(220pt, 12pt, $0$); #wire((230pt, 20pt), (235pt, 20pt)) // D0 = 0
      #lbl(220pt, 32pt, $1$); #wire((230pt, 40pt), (235pt, 40pt)) // D1 = 1
      #lbl(220pt, 52pt, $1$); #wire((230pt, 60pt), (235pt, 60pt)) // D2 = 1
      #lbl(220pt, 72pt, $0$); #wire((230pt, 80pt), (235pt, 80pt)) // D3 = 0

      #lbl(325pt, 42pt, $S ("Сумма")$)
    ]
  ]
]
```

## Лаба №4
```typst
#set page(
  paper: "a4",
  margin: (top: 2cm, bottom: 2cm, left: 2.5cm, right: 1.5cm),
  header: align(right, text(size: 9pt, fill: luma(100))[Лабораторная работа №4: Вариант №13]),
  numbering: "1"
)

// Глобальные настройки текста по ГОСТ
#set text(font: "Linux Libertine", size: 14pt, lang: "ru")
#set par(justify: true, first-line-indent: 1.25cm, leading: 1em)
#set heading(numbering: "1.")

// Защита таблиц от разрывов и сброс текстовых отступов внутри них
#show table: set block(breakable: false)
#show table: set par(leading: 1em, first-line-indent: 0pt)

// ==========================================
// ВЕКТОРНЫЙ ДВИЖОК ДЛЯ ЛОГИЧЕСКИХ СХЕМ
// ==========================================
#let node_dot(x, y) = place(dx: x - 2.5pt, dy: y - 2.5pt, circle(radius: 2.5pt, fill: black))
#let wire(..pts) = {
  let p = pts.pos()
  for i in range(p.len() - 1) { place(line(start: p.at(i), end: p.at(i+1), stroke: 1.2pt)) }
}
#let lbl(x, y, txt) = place(dx: x, dy: y, text(size: 11pt, txt))

#let block_dc24(x, y, name) = {
  place(dx: x, dy: y, rect(width: 45pt, height: 80pt, stroke: 1.2pt)[
    #place(dx: 12pt, dy: 5pt, text(size: 11pt, weight: "bold", "DC"))
    #place(dx: 2pt, dy: 20pt, text(size: 9pt, "x1")); #place(dx: 35pt, dy: 20pt, text(size: 9pt, "0"))
    #place(dx: 2pt, dy: 40pt, text(size: 9pt, "x0")); #place(dx: 35pt, dy: 35pt, text(size: 9pt, "1"))
    #place(dx: 2pt, dy: 60pt, text(size: 9pt, "E"));  #place(dx: 35pt, dy: 50pt, text(size: 9pt, "2"))
                                                      #place(dx: 35pt, dy: 65pt, text(size: 9pt, "3"))
  ])
  place(dx: x + 15pt, dy: y - 12pt, text(size: 10pt, fill: gray, name))
}

#let block_cd42(x, y, name) = {
  place(dx: x, dy: y, rect(width: 45pt, height: 80pt, stroke: 1.2pt)[
    #place(dx: 12pt, dy: 5pt, text(size: 11pt, weight: "bold", "CD"))
    #place(dx: 2pt, dy: 20pt, text(size: 9pt, "0")); #place(dx: 28pt, dy: 30pt, text(size: 9pt, "y1"))
    #place(dx: 2pt, dy: 35pt, text(size: 9pt, "1")); #place(dx: 28pt, dy: 50pt, text(size: 9pt, "y0"))
    #place(dx: 2pt, dy: 50pt, text(size: 9pt, "2"))
    #place(dx: 2pt, dy: 65pt, text(size: 9pt, "3"))
  ])
  place(dx: x + 5pt, dy: y - 12pt, text(size: 10pt, fill: gray, name))
}

// --- ТИТУЛЬНЫЙ ЛИСТ ---
#align(center)[
  #set par(first-line-indent: 0pt)
  #text(weight: "bold")[
    МИНИСТЕРСТВО ОБРАЗОВАНИЯ И НАУКИ РОССИЙСКОЙ ФЕДЕРАЦИИ \
    ФЕДЕРАЛЬНОЕ ГОСУДАРСТВЕННОЕ БЮДЖЕТНОЕ ОБРАЗОВАТЕЛЬНОЕ \ УЧРЕЖДЕНИЕ ВЫСШЕГО ОБРАЗОВАНИЯ \
    «МОСКОВСКИЙ АВИАЦИОННЫЙ ИНСТИТУТ \
    (национальный исследовательский университет)» (МАИ)
  ]
  #v(3cm)
  #text(size: 16pt, weight: "bold")[ОТЧЕТ]\
  #text(size: 14pt)[по лабораторной работе №4]\
  #text(size: 14pt, weight: "bold")[«Преобразователи кодов на основе дешифраторов и шифраторов»]\
  #v(1cm)
  #text(size: 14pt)[Вариант 13]
]

#v(4cm)
#align(right)[
  #box(width: 9cm)[
    #set align(left)
    #set par(first-line-indent: 0pt)
    *Выполнил студент:* \
    Егоров Александр Владиславович \
    *Группа:* \
    М3О-225БВ-24 \
    *Проверил преподаватель:* \
    Ходоровский Александр Зиновьевич
  ]
]
#v(1fr)
#align(center)[#set par(first-line-indent: 0pt); Москва, 2026]
#pagebreak()

= Основное задание (Вариант 13)
Составить схему преобразователя 4-х разрядного двоичного слова ($x_3 x_2 x_1 x_0$) в 3-х разрядное ($y_2 y_1 y_0$) по следующим правилам:
- $y_2 = 1$, если число единиц во входном слове $>= 3$.
- $y_1 = 1$, если число из двух старших разрядов ($x_3 x_2$) строго меньше числа из двух младших разрядов ($x_1 x_0$).
- $y_0$ представляет собой свертку входного кода по модулю 2 (сумма $mod 2$, проверка на нечетность единиц).
Элементная база: дешифраторы 2/4 и элементы ИЛИ.

= Таблица истинности и аналитические выражения
Составим таблицу состояний для всех возможных 16 комбинаций входного кода.

#v(1em)
#align(center)[
  #table(
    columns: (30pt, 50pt, 50pt, 40pt, 40pt, 30pt, 30pt, 30pt), align: center,
    [*№*], [*Вход*], [*Единиц*], [*$x_3 x_2$*], [*$x_1 x_0$*], [*$y_2$*], [*$y_1$*], [*$y_0$*],
    [0], [0000], [0], [0], [0], [0], [0], [0],
    [1], [0001], [1], [0], [1], [0], [*1*], [*1*],
    [2], [0010], [1], [0], [2], [0], [*1*], [*1*],
    [3], [0011], [2], [0], [3], [0], [*1*], [0],
    [4], [0100], [1], [1], [0], [0], [0], [*1*],
    [5], [0101], [2], [1], [1], [0], [0], [0],
    [6], [0110], [2], [1], [2], [0], [*1*], [0],
    [7], [0111], [3], [1], [3], [*1*], [*1*], [*1*],
    [8], [1000], [1], [2], [0], [0], [0], [*1*],
    [9], [1001], [2], [2], [1], [0], [0], [0],
    [10], [1010], [2], [2], [2], [0], [0], [0],
    [11], [1011], [3], [2], [3], [*1*], [*1*], [*1*],
    [12], [1100], [2], [3], [0], [0], [0], [0],
    [13], [1101], [3], [3], [1], [*1*], [0], [*1*],
    [14], [1110], [3], [3], [2], [*1*], [0], [*1*],
    [15], [1111], [4], [3], [3], [*1*], [0], [0]
  )
]

Функции в Совершенной ДНФ (номера активных выходов дешифратора):
- $y_2 = Sigma(7, 11, 13, 14, 15)$
- $y_1 = Sigma(1, 2, 3, 6, 7, 11)$
- $y_0 = Sigma(1, 2, 4, 7, 8, 11, 13, 14)$

#v(1cm)

= Синтез логической схемы

Поскольку в задании требуется преобразовать 4-разрядный код, нам необходим дешифратор 4/16. Согласно элементной базе, мы располагаем только дешифраторами 2/4. Полный дешифратор 4/16 реализуется путем каскадного соединения пяти дешифраторов 2/4.

Первый дешифратор (DC0) принимает старшие биты $x_3, x_2$ и активирует один из четырех дешифраторов второго уровня (DC1-DC4) через их входы разрешения $E$. Дешифраторы второго уровня принимают младшие биты $x_1, x_0$ и формируют 16 уникальных минтермов.

Для реализации функций $y_2, y_1, y_0$ выходы дешифратора 4/16 объединяются элементами ИЛИ в виде коммутационной матрицы.

#v(1em)
#block(breakable: false)[
  *Каскадная реализация полного дешифратора 4/16*
  #align(center)[
    #set par(first-line-indent: 0pt)
    #box(width: 350pt, height: 200pt)[
      #block_dc24(20pt, 50pt, "DC0")
      #lbl(0pt, 64pt, $x_3$); #wire((15pt, 74pt), (20pt, 74pt))
      #lbl(0pt, 84pt, $x_2$); #wire((15pt, 94pt), (20pt, 94pt))
      #lbl(0pt, 104pt, "1");  #wire((15pt, 114pt), (20pt, 114pt))

      #block_dc24(140pt, 0pt, "DC1 (0..3)")
      #block_dc24(140pt, 100pt, "DC2 (4..7)")
      #block_dc24(260pt, 0pt, "DC3 (8..11)")
      #block_dc24(260pt, 100pt, "DC4 (12..15)")

      // Выходы DC0 ко входам E других DC
      #wire((65pt, 74pt), (140pt, 64pt))
      #wire((65pt, 89pt), (105pt, 89pt), (105pt, 164pt), (140pt, 164pt))
      #wire((65pt, 104pt), (115pt, 104pt), (115pt, 64pt), (260pt, 64pt))
      #wire((65pt, 119pt), (125pt, 119pt), (125pt, 164pt), (260pt, 164pt))
      
      // Шина x1, x0 (упрощенно)
      #place(dx: 130pt, dy: -20pt, text(size: 10pt, fill: gray)[Входы $x_1, x_0$ подаются параллельно на DC1-DC4])
    ]
  ]
]

#v(1em)
#block(breakable: false)[
  *Матрица элементов ИЛИ (подключение выходов дешифратора 4/16)*
  #align(center)[
    #set par(first-line-indent: 0pt)
    #box(width: 400pt, height: 230pt)[
      // Дешифратор как единый блок
      #place(dx: 0pt, dy: 10pt, rect(width: 50pt, height: 160pt)[
        #place(dx: 15pt, dy: 5pt, text(weight: "bold", "DC"))
        #place(dx: 10pt, dy: 20pt, text(weight: "bold", "4/16"))
        #place(dx: 5pt, dy: 70pt, text($X[3..0]$))
      ])

      // Вертикальные шины выходов
      #for i in range(16) {
        let vx = 70pt + i * 16pt
        let hy = 20pt + i * 9pt
        wire((50pt, hy), (vx, hy), (vx, 220pt))
        place(dx: vx - 4pt, dy: 5pt, text(size: 9pt, str(i)))
      }

      // Горизонтальные шины входов ИЛИ
      #let or_y = (165pt, 185pt, 205pt)
      #wire((60pt, or_y.at(0)), (340pt, or_y.at(0)))
      #wire((60pt, or_y.at(1)), (340pt, or_y.at(1)))
      #wire((60pt, or_y.at(2)), (340pt, or_y.at(2)))
      
      #place(dx: 340pt, dy: or_y.at(0) - 15pt, rect(width: 25pt, height: 30pt)[#set align(center+horizon); *1*])
      #place(dx: 340pt, dy: or_y.at(1) - 15pt, rect(width: 25pt, height: 30pt)[#set align(center+horizon); *1*])
      #place(dx: 340pt, dy: or_y.at(2) - 15pt, rect(width: 25pt, height: 30pt)[#set align(center+horizon); *1*])

      #wire((365pt, or_y.at(0)), (380pt, or_y.at(0))); #lbl(385pt, or_y.at(0) - 10pt, $y_2$)
      #wire((365pt, or_y.at(1)), (380pt, or_y.at(1))); #lbl(385pt, or_y.at(1) - 10pt, $y_1$)
      #wire((365pt, or_y.at(2)), (380pt, or_y.at(2))); #lbl(385pt, or_y.at(2) - 10pt, $y_0$)

      // Точки соединений (матрица)
      #let y2_nodes = (7, 11, 13, 14, 15)
      #let y1_nodes = (1, 2, 3, 6, 7, 11)
      #let y0_nodes = (1, 2, 4, 7, 8, 11, 13, 14)

      #for i in y2_nodes { node_dot(70pt + i*16pt, or_y.at(0)) }
      #for i in y1_nodes { node_dot(70pt + i*16pt, or_y.at(1)) }
      #for i in y0_nodes { node_dot(70pt + i*16pt, or_y.at(2)) }
    ]
  ]
]

#pagebreak()

= Дополнительное задание 13
*Задание:* Построить постоянное запоминающее устройство (ПЗУ) с организацией 4х4 (четыре четырехразрядных ячейки), используя дешифратор 2/4 и шифраторы 4/2.

*Анализ архитектуры:* \
ПЗУ размерностью 4х4 имеет 2 адресных входа ($A_1, A_0$) для выбора одной из четырех ячеек и 4 выхода данных ($D_3, D_2, D_1, D_0$).
1. *Адресный дешифратор (DC 2/4)* принимает адрес и активирует одну из 4-х словарных линий ($W_0, W_1, W_2, W_3$).
2. *Матрица памяти на шифраторах:* Стандартный шифратор 4/2 при подаче сигнала на один из своих входов выдает 2-разрядный двоичный код номера этого входа. Использование двух параллельных шифраторов (CD1 и CD0) позволяет сформировать 4 разряда данных.

Соединяя активную словарную линию $W_i$ со специфическими входами шифраторов, мы «прошиваем» информацию в ПЗУ. Для примера зададим следующую карту прошивки памяти:

#v(1em)
#align(center)[
  #table(
    columns: (60pt, 60pt, 80pt, 180pt), align: center,
    [*Адрес*], [*Линия*], [*Данные*], [*Подключение шифраторов*],
    [00], [$W_0$], [00 00], [К входам "0" обоих CD],
    [01], [$W_1$], [01 10], [К входу "1" CD1, входу "2" CD0],
    [10], [$W_2$], [10 11], [К входу "2" CD1, входу "3" CD0],
    [11], [$W_3$], [11 01], [К входу "3" CD1, входу "1" CD0],
  )
]

#v(1em)
#block(breakable: false)[
  *Принципиальная схема ПЗУ 4х4*
  #align(center)[
    #set par(first-line-indent: 0pt)
    #box(width: 350pt, height: 180pt)[
      #lbl(0pt, 34pt, $A_1$); #wire((15pt, 44pt), (30pt, 44pt))
      #lbl(0pt, 54pt, $A_0$); #wire((15pt, 64pt), (30pt, 64pt))
      #lbl(0pt, 74pt, "1");   #wire((15pt, 84pt), (30pt, 84pt))

      #block_dc24(30pt, 20pt, "DC 2/4 (Адрес)")
      
      #block_cd42(180pt, 0pt, "CD1 (Данные 3..2)")
      #block_cd42(180pt, 90pt, "CD0 (Данные 1..0)")

      // Линии W0 - W3 (выходы DC)
      #wire((75pt, 44pt), (135pt, 44pt)); #lbl(85pt, 30pt, $W_0$)
      #wire((75pt, 59pt), (145pt, 59pt)); #lbl(85pt, 45pt, $W_1$)
      #wire((75pt, 74pt), (155pt, 74pt)); #lbl(85pt, 60pt, $W_2$)
      #wire((75pt, 89pt), (165pt, 89pt)); #lbl(85pt, 75pt, $W_3$)

      // Прошивка W0 (00 00)
      #wire((135pt, 44pt), (135pt, 24pt), (180pt, 24pt)); #node_dot(135pt, 44pt)
      #wire((135pt, 44pt), (135pt, 114pt), (180pt, 114pt))

      // Прошивка W1 (01 10)
      #wire((145pt, 59pt), (145pt, 39pt), (180pt, 39pt)); #node_dot(145pt, 59pt)
      #wire((145pt, 59pt), (145pt, 144pt), (180pt, 144pt))

      // Прошивка W2 (10 11)
      #wire((155pt, 74pt), (155pt, 54pt), (180pt, 54pt)); #node_dot(155pt, 74pt)
      #wire((155pt, 74pt), (155pt, 159pt), (180pt, 159pt))

      // Прошивка W3 (11 01)
      #wire((165pt, 89pt), (165pt, 69pt), (180pt, 69pt)); #node_dot(165pt, 89pt)
      #wire((165pt, 89pt), (165pt, 129pt), (180pt, 129pt))

      // Выходы ПЗУ
      #wire((225pt, 34pt), (240pt, 34pt)); #lbl(245pt, 24pt, $D_3$)
      #wire((225pt, 54pt), (240pt, 54pt)); #lbl(245pt, 44pt, $D_2$)
      #wire((225pt, 124pt), (240pt, 124pt)); #lbl(245pt, 114pt, $D_1$)
      #wire((225pt, 144pt), (240pt, 144pt)); #lbl(245pt, 134pt, $D_0$)
    ]
  ]
]
```
