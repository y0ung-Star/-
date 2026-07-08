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
    char mark[MARK_SIZE];            // Марка самолёта, например "TU-154M"
    char boardNumber[BOARD_NUM_SIZE];// Бортовой номер, например "B-3726"
    int landingHour;                 // Часы посадки (0-23)
    int landingMinute;               // Минуты посадки (0-59)
    char aerodrome[AERO_SIZE];       // Аэродром посадки, например "AP2"
};

// Индексная структура для сортировки и доступа по индексу
struct FlightIndex {
    int idx;    // Индекс рейса в массиве Flight
    int time;   // Время посадки в минутах (для сортировки)
};

// Собственная реализация функции определения длины строки (аналог strlen)
int strLength(const char* s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// Копирует строку src в dest, не превышая maxLen (включая завершающий нуль).
void copyStr(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Разбирает строку времени ("ЧЧ:ММ" или "Ч:ММ") на часы и минуты.
bool parseTime(const char* str, int& hour, int& minute) {
    hour = 0;
    minute = 0;
    int i = 0;
    if (!(str[i] >= '0' && str[i] <= '9')) return false;
    while (str[i] >= '0' && str[i] <= '9') {
        hour = hour * 10 + (str[i] - '0');
        ++i;
    }
    if (str[i] != ':') return false;
    ++i;
    if (!(str[i] >= '0' && str[i] <= '9')) return false;
    while (str[i] >= '0' && str[i] <= '9') {
        minute = minute * 10 + (str[i] - '0');
        ++i;
    }
    if (str[i] != '\0') return false;
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) return false;
    return true;
}

// Возвращает время посадки в минутах от полуночи
int landingTimeToMinutes(const Flight& f) {
    return f.landingHour * 60 + f.landingMinute;
}

// Проверяет, что символ - латинская буква или цифра
bool isLetterOrDigit(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return true;
    if (c >= '0' && c <= '9') return true;
    return false;
}

// Проверяет, что строка состоит только из латинских букв и цифр
bool isAlphaNumStr(const char* s) {
    int i = 0;
    while (s[i] != '\0') {
        if (!isLetterOrDigit(s[i])) return false;
        i++;
    }
    return i > 0;
}

// Проверяет, что строка состоит из латинских букв, цифр и дефиса (должен быть хотя бы один дефис)
bool isAlphaNumDashStr(const char* s) {
    int i = 0;
    bool hasDash = false;
    while (s[i] != '\0') {
        if (s[i] == '-') hasDash = true;
        else if (!isLetterOrDigit(s[i])) return false;
        i++;
    }
    return i > 0 && hasDash;
}

// Проверяет формат бортового номера: одна латинская буква, дефис, 4 цифры
bool isBoardNumberValid(const char* s) {
    if (!((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z'))) return false;
    if (s[1] != '-') return false;
    int i = 2, cnt = 0;
    while (s[i] >= '0' && s[i] <= '9') { ++i; ++cnt; }
    if (cnt != 4) return false;
    if (s[i] != '\0') return false;
    return true;
}

// Проверяет, что аэродром — только AP1, AP2 или AP3
bool isAerodromeValid(const char* s) {
    return (
        (s[0] == 'A' && s[1] == 'P' && s[2] == '1' && s[3] == '\0') ||
        (s[0] == 'A' && s[1] == 'P' && s[2] == '2' && s[3] == '\0') ||
        (s[0] == 'A' && s[1] == 'P' && s[2] == '3' && s[3] == '\0')
    );
}

// Главная функция проверки полей структуры Flight (кроме специфических проверок аэродрома)
bool isValidFlightData(const Flight& f) {
    if (!isBoardNumberValid(f.boardNumber)) return false;
    if (!isAlphaNumDashStr(f.mark)) return false;
    if (f.landingHour < 0 || f.landingHour > 23) return false;
    if (f.landingMinute < 0 || f.landingMinute > 59) return false;
    return true;
}

// Сравнивает две строки на полное совпадение
bool areStringsEqual(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return false;
        ++i;
    }
    return a[i] == b[i];
}

// Чтение данных о рейсах из текстового файла
int readFlights(const char* filename, Flight flights[], int maxRecords) {
    ifstream fin(filename);
    int n = 0;
    if (!fin) {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }
    
    char line[LINE_SIZE];
    int lineNumber = 0;
    while (n < maxRecords && fin.getline(line, LINE_SIZE)) {
        lineNumber++;
        if (line[0] == '\0') continue;
        char mark_buf[MARK_SIZE] = {0};
        char boardNum_buf[BOARD_NUM_SIZE] = {0};
        char timeStr_buf[8] = {0};
        char aero_buf[AERO_SIZE] = {0};
        int word = 0, li = 0, wi = 0;
        char* fields[4] = {mark_buf, boardNum_buf, timeStr_buf, aero_buf};
        int limits[4] = {MARK_SIZE, BOARD_NUM_SIZE, 8, AERO_SIZE};
        while (line[li] && word < 4) {
            while (line[li] == ' ' || line[li] == '\t') li++;
            if(line[li] == '\0' && word < 4) break;
            wi = 0;
            while (line[li] && line[li] != ' ' && line[li] != '\t' && wi < limits[word] - 1) {
                fields[word][wi++] = line[li++];
            }
            fields[word][wi] = '\0'; 
            word++; 
        }
        // ПРОВЕРКА 2: Поле аэродрома не пустое
        if (strLength(aero_buf) == 0) {
            cout << "Ошибка: отсутствует значение для аэродрома (пустое поле) в строке " << lineNumber << endl;
            continue;
        }
        // ПРОВЕРКА 3: Корректность значения аэродрома (AP1, AP2, AP3)
        if (!isAerodromeValid(aero_buf)) {
            cout << "Ошибка: некорректный код аэродрома '" << aero_buf 
                 << "' в строке " << lineNumber << ". Ожидался AP1, AP2 или AP3." << endl;
            continue;
        }
        Flight f;
        copyStr(f.mark, mark_buf, MARK_SIZE);
        copyStr(f.boardNumber, boardNum_buf, BOARD_NUM_SIZE);
        copyStr(f.aerodrome, aero_buf, AERO_SIZE);
        if (!parseTime(timeStr_buf, f.landingHour, f.landingMinute)) {
            cout << "Ошибка парсинга времени для записи '" << timeStr_buf << "' в строке " << lineNumber << endl;
            continue;
        }
        if (isValidFlightData(f)) {
            flights[n++] = f;
        } else {
            cout << "Ошибка: некорректные данные (марка или бортовой номер) в строке " << lineNumber << endl;
        }
    }
    return n;
}

// Выводит таблицу рейсов (без сортировки)
void printFlights(const Flight flights[], int n) {
    const int w1 = 10, w2 = 12, w3 = 8, w4 = 8;
    cout << left
         << setw(w1) << "Марка" << "  "
         << setw(w2) << "Бортовой №" << "  "
         << setw(w3) << "Время" << "  "
         << setw(w4) << "Аэродром"
         << endl;
    cout << setfill('-') << setw(w1 + w2 + w3 + w4 + 6) << "" << setfill(' ') << endl;
    for (int i = 0; i < n; ++i) {
        cout << left << setw(w1) << flights[i].mark << "  "
             << left << setw(w2) << flights[i].boardNumber << "  "
             << right << setw(2) << setfill('0') << flights[i].landingHour << ":"
             << setw(2) << setfill('0') << flights[i].landingMinute << setfill(' ') << "  "
             << left << setw(w4) << flights[i].aerodrome << endl;
    }
}

// Сортирует массив FlightIndex по времени посадки (от ранних к поздним)
void indexSort(FlightIndex indexes[], int n) {
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            if (indexes[j].time > indexes[j+1].time) {
                FlightIndex tmp = indexes[j];
                indexes[j] = indexes[j+1];
                indexes[j+1] = tmp;
            }
        }
    }
}

// Выводит рейсы по индексной структуре (отсортированные по времени)
void printFlightsByIndex(const Flight flights[], const FlightIndex indexes[], int n) {
    const int w1 = 10, w2 = 12, w3 = 8, w4 = 8;
    cout << left
         << setw(w1) << "Марка" << "  "
         << setw(w2) << "Бортовой №" << "  "
         << setw(w3) << "Время" << "  "
         << setw(w4) << "Аэродром"
         << endl;
    cout << setfill('-') << setw(w1 + w2 + w3 + w4 + 6) << "" << setfill(' ') << endl;
    for (int i = 0; i < n; ++i) {
        const Flight& f = flights[indexes[i].idx];
        cout << left << setw(w1) << f.mark << "  "
             << left << setw(w2) << f.boardNumber << "  "
             << right << setw(2) << setfill('0') << f.landingHour << ":"
             << setw(2) << setfill('0') << f.landingMinute << setfill(' ') << "  "
             << left << setw(w4) << f.aerodrome << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Использование: " << argv[0] << " <файл_данных>" << endl;
        return 1;
    }
    Flight flights[MAX_RECORDS];
    FlightIndex indexes[MAX_RECORDS];
    int n = readFlights(argv[1], flights, MAX_RECORDS);

    if (n == 0) {
        cout << "Нет данных для обработки (возможно, отсутствие файла)." << endl;
        return 1;
    }

    cout << "\nИсходные данные (только корректные записи):" << endl;
    printFlights(flights, n);

    // Заполнение индексной структуры
    for (int i = 0; i < n; ++i) {
        indexes[i].idx = i;
        indexes[i].time = landingTimeToMinutes(flights[i]);
    }
    // Сортировка индексной структуры по времени
    indexSort(indexes, n);

    cout << "\nДанные, отсортированные по времени посадки (через индексную структуру):" << endl;
    printFlightsByIndex(flights, indexes, n);

    // По каждому аэродрому вывод через индексную структуру:
    const char* aerodromes[3] = {"AP1", "AP2", "AP3"};
    for (int ad = 0; ad < 3; ++ad) {
        cout << "\nСамолеты на аэродроме " << aerodromes[ad] << " (отсортировано по времени посадки):" << endl;
        const int w1 = 10, w2 = 12, w3 = 8, w4 = 8;
        cout << left
             << setw(w1) << "Марка" << "  "
             << setw(w2) << "Бортовой №" << "  "
             << setw(w3) << "Время" << "  "
             << setw(w4) << "Аэродром"
             << endl;
        cout << setfill('-') << setw(w1 + w2 + w3 + w4 + 6) << "" << setfill(' ') << endl;
        bool found = false;
        for (int i = 0; i < n; ++i) {
            const Flight& f = flights[indexes[i].idx];
            if (areStringsEqual(f.aerodrome, aerodromes[ad])) {
                cout << left << setw(w1) << f.mark << "  "
                     << left << setw(w2) << f.boardNumber << "  "
                     << right << setw(w3-6) << setfill('0') << f.landingHour << ":"
                     << setw(2) << setfill('0') << f.landingMinute << setfill(' ') << "  "
                     << left << setw(w4) << f.aerodrome << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Нет данных для этого аэродрома." << endl;
        }
    }

    return 0;
}
