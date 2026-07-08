#include <iostream>
using namespace std;

// Прототипы функций
// СДЕЛАТЬ КОМЕНТАРИИ Ф-ЦИ И ПАРАМЕТРОВ
void printCommonWords(char* str1, char* str2);
int countCharOccurrences(char* str, char ch);
void findLineWithMoreChar(char* str1, char* str2, char ch);

int main() {
    char str1[100], str2[100];
    char ch;

    // Ввод данных с терминала
    cout << "Введите первую строку: ";
    cin.getline(str1, 100);
    cout << "Введите вторую строку: ";
    cin.getline(str2, 100);
    cout << "Введите символ: ";
    cin >> ch;

    // Вызов функций для выполнения задач
    printCommonWords(str1, str2);
    findLineWithMoreChar(str1, str2, ch);

    return 0;
}

void printCommonWords(char* str1, char* str2) {
    char word1[100], word2[100]; 
    int i = 0, j = 0; // i для str1, j для str2
    int k1 = 0, k2 = 0; // Отдельные счетчики для word1 и word2

    cout << "Общие слова: ";
    while (true) {
        // Извлекаем слово из первой строки
        if (str1[i] == ' ' || str1[i] == '\0') {
            word1[k1] = '\0'; // Завершаем слово в word1
                              
            if (k1 > 0) { // Если слово не пустое
                // Поиск этого слова во второй строке
                j = 0;
                k2 = 0; // Сбрасываем k2 перед началом записи слова из str2

                while (true) {
                    if (str2[j] == ' ' || str2[j] == '\0') {
                        word2[k2] = '\0'; // Завершаем слово в word2
                                          
                        if (k2 > 0) { // Если слово не пустое
                            bool match = true;

                            // Сравниваем слова
                            for (int l = 0; word1[l] != '\0' && word2[l] != '\0'; l++) {
                                if (word1[l] != word2[l]) {
                                    match = false;
                                    break;
                                }
                            }
                            // Проверяем, что слова полностью совпали
                            if (match && word1[k1] == '\0' && word2[k2] == '\0') {
                                cout << word1 << " "; // Выводим общее слово
                            }
                        }

                        k2 = 0; // Сбрасываем k2 для следующего слова
                        if (str2[j] == '\0') break; // Выход, если строка закончилась
                                                    
                    } 

                    else {
                        word2[k2++] = str2[j]; // Записываем символ в word2
                    }

                    j++;
                }
            }

            k1 = 0; // Сбрасываем k1 для следующего слова
            if (str1[i] == '\0') break; // Выход, если строка закончилась
                                    
        } 

        else {
            word1[k1++] = str1[i]; // Записываем символ в word1
        }

        i++;
    }
    cout << endl;
}

int countCharOccurrences(char* str, char ch) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            count++;
        }
    }
    return count;
}

void findLineWithMoreChar(char* str1, char* str2, char ch) {
    int count1 = countCharOccurrences(str1, ch);
    int count2 = countCharOccurrences(str2, ch);

    if (count1 > count2) {
        cout << "Символ '" << ch << "' чаще встречается в первой строке." << endl;
    } 
    else if (count2 > count1) {
        cout << "Символ '" << ch << "' чаще встречается во второй строке." << endl;
    } 
    else {
        cout << "Символ '" << ch << "' встречается одинаково часто в обеих строках." << endl;
    }
}
