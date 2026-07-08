/****************************************************************
*                     КАФЕДРА № 304 1 КУРС                      *
*---------------------------------------------------------------*
* Project Type  : GNU/Linux Console Application                 *
* Project Name  : laba_1                                        *
* File Name     : main.cpp                                      *
* Language      : C/C++                                         * 
* Programmer(s) : Егоров А.В (swrneko), Федоров А.И.            *
* Modifyed By   : Егоров А.В (swrneko)                          *
* Edited by     : Neovim, Visual Studio                         *
* OS            : Arch Linux, Windows 11                        *
* Github url    : https://github.com/swrneko/mai_shit.git       *
* Created       : 04/04/25                                      *
* Last Revision : 23/04/25                                      *
* Comment(s)    : Символьные данные                             *
****************************************************************/

#include <iostream>
using namespace std;

/*************************
* Инициализация констант *
*************************/
const int SIZE = 100;

/********************
* Прототипы функций *
********************/

// Разбивает строку на слова
// Параметры:
// - str: входная строка, содержащая слова, разделённые пробелами
// - words: двумерный массив для хранения отдельных слов
// - count: ссылка на переменную, в которую будет записано количество найденных слов
void getWords(char str[], char words[][SIZE], int &count);

// Сравнивает два слова на равенство
// Параметры:
// - w1: первое слово
// - w2: второе слово
// Возвращает true, если слова одинаковые, иначе false
bool areEqual(char w1[], char w2[]);

// Считает количество вхождений символа в строке
// Параметры:
// - str: строка, в которой выполняется подсчёт
// - c: символ, который нужно посчитать
// Возвращает количество вхождений символа c в строке str
int countChar(char str[], char c);

/******************
* Главная функция *
******************/

// --- Главная функция программы ---
int main() {
    char c;                     // Заданный символ
    char str1[SIZE], str2[SIZE]; // Две строки, введённые пользователем

    // Двумерные массивы для хранения слов из каждой строки
    char words1[20][SIZE], words2[20][SIZE];
    int count1 = 0, count2 = 0; // Количество слов в каждой строке

    // Ввод данных
    cout << "Введите символ: ";
    cin >> c;
    cin.ignore(); // Убираем символ новой строки после ввода символа

    cout << "Введите первую строку: ";
    cin.getline(str1, SIZE);

    cout << "Введите вторую строку: ";
    cin.getline(str2, SIZE);

    // Разделение строк на слова
    getWords(str1, words1, count1);
    getWords(str2, words2, count2);

    // --- Поиск и вывод общих слов ---
    bool foundCommon = false; // флаг наличия общих слов

    cout << "\nОбщие слова:\n";
    for (int i = 0; i < count1; i++) {
        if (words1[i][0] == '\0') continue; // пропустить пустые

        for (int j = 0; j < count2; j++) {
            if (words2[j][0] == '\0') continue;

            if (areEqual(words1[i], words2[j])) {
                cout << words1[i] << endl;
                foundCommon = true;
                break;
            }
        }
    }

    if (!foundCommon) {
        cout << "Нет общих слов.\n";
    }

    // --- Подсчёт количества символов и вывод результата ---
    int freq1 = countChar(str1, c);
    int freq2 = countChar(str2, c);

    if (freq1 == 0 && freq2 == 0) {
        cout << "\nСимвол '" << c << "' не встречается ни в одной строке.\n";
    } else {
        cout << "\nСимвол '" << c << "' чаще встречается ";
        if (freq1 > freq2)
            cout << "в первой строке.\n";
        else if (freq2 > freq1)
            cout << "во второй строке.\n";
        else
            cout << "одинаково часто.\n";
    }   

    return 0;
}

/**********
* Функции *
**********/

// Разбивает строку на слова по пробелам
void getWords(char str[], char words[][SIZE], int &count) {
    int i = 0, j = 0, w = 0;
    count = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ') {
            words[w][j++] = str[i]; // добавляем символ в слово
        } else if (j > 0) {
            // Если j > 0, значит было накоплено хотя бы одно слово
            words[w][j] = '\0'; // закрываем слово
            w++;
            j = 0;
        }
        i++;
    }

    // Последнее слово (если было)
    if (j > 0) {
        words[w][j] = '\0';
        w++;
    }

    count = w; // сохраняем количество слов
}


// Сравнивает два слова символ за символом
bool areEqual(char w1[], char w2[]) {
    int i = 0;
    while (w1[i] != '\0' && w2[i] != '\0') {
        if (w1[i] != w2[i])
            return false; // Нашли несовпадение
        i++;
    }

    // Возвращаем true только если оба слова закончились одновременно
    return w1[i] == '\0' && w2[i] == '\0';
}

// Подсчёт количества вхождений символа в строку
int countChar(char str[], char c) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            count++;
    }
    return count;
}

