#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Максимальное количество рейсов, которые может обработать программа
const int MAX_RECORDS = 100;

// Размеры для строковых полей (включая завершающий нуль)
const int BOARD_NUM_SIZE = 20; // длина строки для бортового номера
const int AERO_SIZE = 10;      // длина строки для названия аэродрома
const int MARK_SIZE = 16;      // длина строки для марки самолета
const int LINE_SIZE = 64;      // максимальная длина строки при чтении из файла

// Структура для хранения информации о рейсе
struct Flight {
    char mark[MARK_SIZE];            // Марка самолёта, например "ТУ-154М"
    char boardNumber[BOARD_NUM_SIZE];// Бортовой номер, например "Б-3726"
    int landingHour;                 // Часы посадки (0-23)
    int landingMinute;               // Минуты посадки (0-59)
    char aerodrome[AERO_SIZE];       // Аэродром посадки, например "АП2"
};

// Копирует строку src в dest, не превышая maxLen (включая завершающий нуль).
// dest — массив символов, куда будет скопирована строка.
// src — исходная строка для копирования.
// maxLen — максимальный размер буфера dest, включая завершающий нуль.
void copyStr(char* dest, const char* src, int maxLen);

// Разбирает строку времени ("ЧЧ:ММ" или "Ч:ММ") на часы и минуты.
// str — строка времени для разбора (например, "09:45").
// hour — переменная для записи разобранных часов (по ссылке).
// minute — переменная для записи разобранных минут (по ссылке).
// Возвращает true, если разбор успешен и значения валидны; иначе false.
bool parseTime(const char* str, int& hour, int& minute);

// Возвращает время посадки в минутах от полуночи для данного рейса.
// f — структура Flight с данными рейса.
// Возвращает количество минут от полуночи.
int landingTimeToMinutes(const Flight& f);

// Проверяет корректность данных рейса.
// f — структура Flight для проверки.
// Возвращает true, если все поля валидны; иначе false.
bool isValidFlight(const Flight& f);

// Сравнивает две строки на равенство.
// a — первая строка (массив символов).
// b — вторая строка (массив символов).
// Возвращает true, если строки идентичны (по символам); иначе false.
bool areStringsEqual(const char* a, const char* b);

// Считывает данные рейсов из файла filename в массив flights (максимум maxRecords штук).
// filename — имя файла для чтения данных (например, "data.txt").
// flights — массив структур Flight, куда будут записаны считанные данные.
// maxRecords — максимальное количество записей для чтения (размер массива flights).
// Возвращает количество успешно считанных рейсов.
int readFlights(const char* filename, Flight flights[], int maxRecords);

// Выводит таблицу рейсов (n штук из массива flights).
// flights — массив структур Flight для вывода.
// n — количество рейсов для вывода.
void printFlights(const Flight flights[], int n);

// Сортирует индексы рейсов в массиве idx по времени посадки (пузырьковая сортировка).
// flights — массив структур Flight для сравнения времени посадки.
// idx — массив индексов, который будет отсортирован по времени посадки.
// n — количество рейсов/индексов для сортировки.
void indexBubbleSort(const Flight flights[], int idx[], int n);

// Выводит рейсы, приземлившиеся на targetAerodrome, в порядке времени посадки.
// flights — массив структур Flight.
// idx — массив отсортированных индексов рейсов.
// n — количество рейсов.
// targetAerodrome — название аэродрома, для которого нужно вывести рейсы.
void printFlightsByAerodrome(const Flight flights[], const int idx[], int n, const char* targetAerodrome);

// Точка входа в программу.
// argc — количество аргументов командной строки.
// argv — массив строк-аргументов командной строки.
int main(int argc, char* argv[]);



// Реализация функции копирования строки
void copyStr(char* dest, const char* src, int maxLen) {
    int i = 0;
    // Копируем символы по одному, пока не закончится исходная строка или не достигнут лимит
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    // Добавляем завершающий нуль
    dest[i] = '\0';
}

// Реализация функции разбора времени из строки формата "ЧЧ:ММ"
bool parseTime(const char* str, int& hour, int& minute) {
    hour = 0;
    minute = 0;
    int i = 0;
    // Считываем часы
    while (str[i] >= '0' && str[i] <= '9') {
        hour = hour * 10 + (str[i] - '0');
        ++i;
    }
    // Проверяем наличие разделителя ':'
    if (str[i] != ':') return false;
    ++i;
    // Считываем минуты
    if (!(str[i] >= '0' && str[i] <= '9')) return false;
    while (str[i] >= '0' && str[i] <= '9') {
        minute = minute * 10 + (str[i] - '0');
        ++i;
    }
    // Проверяем, что после минут нет лишних символов
    if (str[i] != '\0') return false;
    // Проверка диапазонов
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) return false;
    return true;
}

// Преобразует время посадки из часов и минут в общее количество минут от полуночи
int landingTimeToMinutes(const Flight& f) {
    return f.landingHour * 60 + f.landingMinute;
}

// Проверяет валидность данных о рейсе
bool isValidFlight(const Flight& f) {
    // Проверка, что бортовой номер не пустой
    if (f.boardNumber[0] == '\0') return false;
    // Проверка диапазонов времени
    if (f.landingHour < 0 || f.landingHour > 23 || f.landingMinute < 0 || f.landingMinute > 59) return false;
    // Проверка, что аэродром не пустой
    if (f.aerodrome[0] == '\0') return false;
    return true;
}

// Сравнивает две строки на идентичность посимвольно
bool areStringsEqual(const char* a, const char* b) {
    int i = 0;
    // Сравниваем символы по одному
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return false;
        ++i;
    }
    // Строки равны, если закончились одновременно
    return a[i] == b[i];
}

// Считывает данные о рейсах из текстового файла
int readFlights(const char* filename, Flight flights[], int maxRecords) {
    ifstream fin(filename); // Открываем файл для чтения
    int n = 0; // Счетчик успешно считанных записей
    if (!fin) {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }
    char line[LINE_SIZE];
    // Чтение файла построчно
    while (n < maxRecords && fin.getline(line, LINE_SIZE)) {
        if (line[0] == '\0') continue; // пропускаем пустые строки
        // Временные буферы для разбора строки
        char mark[MARK_SIZE] = {0}, boardNum[BOARD_NUM_SIZE] = {0}, timeStr[8] = {0}, aero[AERO_SIZE] = {0};
        int word = 0, li = 0, wi = 0;
        char* fields[4] = {mark, boardNum, timeStr, aero};
        int limits[4] = {MARK_SIZE, BOARD_NUM_SIZE, 8, AERO_SIZE};
        // Разбиваем строку на 4 слова
        while (line[li] && word < 4) {
            // Пропуск пробелов и табуляций
            while (line[li] == ' ' || line[li] == '\t') li++;
            wi = 0;
            // Копируем очередное слово в соответствующий буфер
            while (line[li] && line[li] != ' ' && line[li] != '\t' && wi < limits[word] - 1) {
                fields[word][wi++] = line[li++];
            }
            fields[word][wi] = '\0';
            word++;
        }
        // Если не хватает слов в строке — пропускаем строку
        if (word < 4) continue;

        Flight f;
        // Копируем разобранные данные в структуру
        copyStr(f.mark, mark, MARK_SIZE);
        copyStr(f.boardNumber, boardNum, BOARD_NUM_SIZE);
        copyStr(f.aerodrome, aero, AERO_SIZE);


        // Парсим время (часы и минуты)
        if (!parseTime(timeStr, f.landingHour, f.landingMinute)) {
            cout << "Ошибка парсинга времени для записи " << (n + 1) << endl;
            continue;
        }
        // Проверяем корректность данных, сохраняем запись, если все валидно
        if (isValidFlight(f)) {
            flights[n++] = f;
        } else {
            cout << "Некорректные данные в строке " << (n + 1) << endl;
        }
    }
    return n;
}

// Выводит таблицу рейсов в консоль
void printFlights(const Flight flights[], int n) {
    // Ширина столбцов для красивого вывода
    const int w1 = 10, w2 = 12, w3 = 8, w4 = 8;
    // Заголовки столбцов
    cout << left
         << setw(w1) << "Марка" << "  "
         << setw(w2) << "Бортовой №" << "  "
         << setw(w3) << "Время" << "  "
         << setw(w4) << "Аэродром"
         << endl;
    // Разделительная линия
    cout << setfill('-') << setw(w1 + w2 + w3 + w4 + 6) << "" << setfill(' ') << endl;
    // Вывод данных по каждому рейсу
    for (int i = 0; i < n; ++i) {
        cout << left << setw(w1) << flights[i].mark << "  "
             << left << setw(w2) << flights[i].boardNumber << "  "
             << right << setw(2) << setfill('0') << flights[i].landingHour << ":"
             << setw(2) << setfill('0') << flights[i].landingMinute << setfill(' ') << "  "
             << left << setw(w4) << flights[i].aerodrome << endl;
    }
}

// Сортирует индексы рейсов по времени посадки (от ранних к поздним)
void indexBubbleSort(const Flight flights[], int idx[], int n) {
    // Инициализация массива индексов
    for (int i = 0; i < n; ++i) idx[i] = i;
    // Пузырьковая сортировка по времени посадки
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            if (landingTimeToMinutes(flights[idx[j]]) > landingTimeToMinutes(flights[idx[j+1]])) {
                int tmp = idx[j];
                idx[j] = idx[j+1];
                idx[j+1] = tmp;
            }
        }
    }
}

// Выводит рейсы, приземлившиеся на указанный аэродром, отсортированные по времени посадки
void printFlightsByAerodrome(const Flight flights[], const int idx[], int n, const char* targetAerodrome) {
    cout << "\nСамолеты на аэродроме " << targetAerodrome << " (отсортировано по времени посадки):" << endl;
    // Ширина столбцов
    const int w1 = 10, w2 = 12, w3 = 8, w4 = 8;
    // Заголовки
    cout << left
         << setw(w1) << "Марка" << "  "
         << setw(w2) << "Бортовой №" << "  "
         << setw(w3) << "Время" << "  "
         << setw(w4) << "Аэродром"
         << endl;
    // Разделительная линия
    cout << setfill('-') << setw(w1 + w2 + w3 + w4 + 6) << "" << setfill(' ') << endl;
    bool found = false;
    // Проходим по отсортированным индексам и выводим только нужный аэродром
    for (int i = 0; i < n; ++i) {
        int k = idx[i];
        if (areStringsEqual(flights[k].aerodrome, targetAerodrome)) {
            cout << left << setw(w1) << flights[k].mark << "  "
                 << left << setw(w2) << flights[k].boardNumber << "  "
                 << right << setw(2) << setfill('0') << flights[k].landingHour << ":"
                 << setw(2) << setfill('0') << flights[k].landingMinute << setfill(' ') << "  "
                 << left << setw(w4) << flights[k].aerodrome << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Нет данных для этого аэродрома." << endl;
    }
}

// Точка входа в программу
int main(int argc, char* argv[]) {
    // Проверка наличия имени файла в аргументах командной строки
    if (argc < 2) {
        cout << "Использование: " << argv[0] << " <файл_данных>" << endl;
        return 1;
    }
    // Основной массив для хранения рейсов
    Flight flights[MAX_RECORDS];
    // Массив индексов для сортировки
    int idx[MAX_RECORDS];
    // Считываем рейсы из файла
    int n = readFlights(argv[1], flights, MAX_RECORDS);

    if (n == 0) {
        cout << "Нет данных для обработки." << endl;
        return 1;
    }


    // Выводим исходные данные
    cout << "Исходные данные:" << endl;
    printFlights(flights, n);
    // Сортируем индексы по времени посадки
    indexBubbleSort(flights, idx, n);

    // Выводим данные по каждому аэродрому
    printFlightsByAerodrome(flights, idx, n, "АП1");
    printFlightsByAerodrome(flights, idx, n, "АП2");
    printFlightsByAerodrome(flights, idx, n, "АП3");

    return 0;
}

