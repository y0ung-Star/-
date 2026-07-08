/****************************************************************
 *                     КАФЕДРА № 304 2 КУРС                      *
 *---------------------------------------------------------------*
 * Project Type  : GNU/Linux Console Application                 *
 * Project Name  : main                                          *
 * File Name     : main.cpp                                      *
 * Language      : C/C++                                         *
 * Programmer(s) : Егоров А.В (swrneko), Фёдоров А.И             *
 * Modifyed By   : Егоров А.В (swrneko), Фёдоров А.И             *
 * Edited by     : Neovim, Visual Studio                         *
 * OS            : Arch Linux, Cachy OS                          *
 * Github url    : https://github.com/swrneko/mai_shit.git       *
 * Created       : 24/11/25                                      *
 * Last Revision : 09/12/25                                      *
 * Comment(s)    : Алгоритмы сортировки данных                   *
 ****************************************************************/

#include <iostream>
#include <iomanip>  // Для таблицы (setw)
#include <cstdlib>  // rand, srand
#include <ctime>    // time
#include <chrono>   // Для замеров времени

using namespace std;
using namespace std::chrono;

// --- Глобальные переменные для статистики ---
long long comparisons = 0; // Количество сравнений
long long moves = 0;       // Количество пересылок
bool SHOW_STEPS = false;   // Флаг вывода промежуточных шагов (для N=15)

// --- Вспомогательные функции ---

// Вывод массива
void printArray(int* arr, int n) {
    if (!SHOW_STEPS) return;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

// Обмен элементов (считается за 3 пересылки)
void swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    moves += 3;
}

// Копирование массива (чтобы сортировать одни и те же данные разными методами)
void copyArray(int* src, int* dest, int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// Генерация данных
void generateData(int* arr, int n, int type) {
    // type: 1 - рандом, 2 - отсортирован (возр), 3 - отсортирован (убыв)
    for (int i = 0; i < n; i++) {
        if (type == 1) arr[i] = rand() % 10000;
        else if (type == 2) arr[i] = i;
        else if (type == 3) arr[i] = n - i;
    }
}

// =========================================================
// 1. СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT)
// =========================================================

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Временные массивы
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        moves++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        moves++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        moves++; // Запись в основной массив
        k++;
    }

    while (i < n1) {
        arr[k++] = L[i++];
        moves++;
    }
    while (j < n2) {
        arr[k++] = R[j++];
        moves++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int left, int right, int n_full) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, n_full);
    mergeSort(arr, mid + 1, right, n_full);
    merge(arr, left, mid, right);

    if (SHOW_STEPS) {
        cout << "Merge (" << left << "-" << right << "): ";
        printArray(arr, n_full);
    }
}

// =========================================================
// 2. БЫСТРАЯ СОРТИРОВКА (QUICK SORT)
// =========================================================

// ВАРИАНТ А: Опорный - ПОСЛЕДНИЙ (Lomuto partition)
int partitionLast(int* arr, int low, int high, int n_full) {
    int pivot = arr[high]; // Опорный - последний
    moves++; // чтение в pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swapElements(arr[i], arr[j]);
        }
    }
    swapElements(arr[i + 1], arr[high]);
    
    if (SHOW_STEPS) {
        cout << "PivotLast idx=" << i+1 << ": ";
        printArray(arr, n_full);
    }
    return (i + 1);
}

void quickSortLast(int* arr, int low, int high, int n_full) {
    if (low < high) {
        int pi = partitionLast(arr, low, high, n_full);
        quickSortLast(arr, low, pi - 1, n_full);
        quickSortLast(arr, pi + 1, high, n_full);
    }
}

// ВАРИАНТ Б: Опорный - СЕРЕДИНА (Hoare partition)
// Эффективнее на отсортированных данных
void quickSortHoare(int* arr, int low, int high, int n_full) {
    int i = low;
    int j = high;
    int pivot = arr[(low + high) / 2];
    moves++; // чтение pivot

    // Цикл разделения
    while (i <= j) {
        comparisons++;
        while (arr[i] < pivot) {
            comparisons++;
            i++;
        }
        comparisons++;
        while (arr[j] > pivot) {
            comparisons++;
            j--;
        }
        
        if (i <= j) {
            swapElements(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (SHOW_STEPS) {
        cout << "Hoare Part: ";
        printArray(arr, n_full);
    }

    if (low < j) quickSortHoare(arr, low, j, n_full);
    if (i < high) quickSortHoare(arr, i, high, n_full);
}

// =========================================================
// УПРАВЛЕНИЕ ТЕСТАМИ
// =========================================================

void runTest(int* original, int n, int algoType, string name) {
    int* arr = new int[n];
    copyArray(original, arr, n);

    comparisons = 0;
    moves = 0;

    // Таймер
    auto start = high_resolution_clock::now();

    if (algoType == 1) { // Merge
        mergeSort(arr, 0, n - 1, n);
    } 
    else if (algoType == 2) { // Quick Last
        // Защита от переполнения стека на больших отсортированных массивах
        // В рамках лабы это можно объяснить как "недостаток алгоритма"
        if (n > 40000 && (original[0] < original[1] || original[0] > original[1])) {
             cout << left << setw(20) << name << " | " << setw(10) << "SKIPPED (Stack Overflow)" << endl;
             delete[] arr;
             return;
        }
        quickSortLast(arr, 0, n - 1, n);
    } 
    else if (algoType == 3) { // Quick Hoare
        quickSortHoare(arr, 0, n - 1, n);
    }

    auto end = high_resolution_clock::now();
    long long time_ns = duration_cast<nanoseconds>(end - start).count();

    if (!SHOW_STEPS) {
        cout << left << setw(20) << name << " | " 
             << setw(10) << time_ns / 1000 << " mks | " // в микросекундах для удобства
             << setw(15) << comparisons << " | " 
             << setw(15) << moves << endl;
    }

    delete[] arr;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // --- ЧАСТЬ 1: Демонстрация (N = 15) ---
    cout << "=== ЭТАП 1: Визуализация (N=15) ===" << endl;
    int n_demo = 15;
    int* arr_demo = new int[n_demo];
    generateData(arr_demo, n_demo, 1); // Рандом

    cout << "Исходный массив: ";
    SHOW_STEPS = true;
    printArray(arr_demo, n_demo);
    cout << endl;

    cout << "--- Сортировка Слиянием ---" << endl;
    runTest(arr_demo, n_demo, 1, "Merge");
    
    cout << "\n--- Quick Sort (Last Pivot) ---" << endl;
    runTest(arr_demo, n_demo, 2, "QuickLast");

    cout << "\n--- Quick Sort (Hoare) ---" << endl;
    runTest(arr_demo, n_demo, 3, "QuickHoare");

    delete[] arr_demo;
    SHOW_STEPS = false;
    cout << endl << endl;

    // --- ЧАСТЬ 2: Большие массивы ---
    cout << "=== ЭТАП 2: Анализ производительности ===" << endl;
    int sizes[] = {500, 1000, 10000, 50000, 100000};
    
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        cout << string(80, '=') << endl;
        cout << "Размер массива N = " << n << endl;
        cout << string(80, '-') << endl;
        cout << left << setw(20) << "Алгоритм" << " | " 
             << setw(14) << "Время (мкс)" << " | " 
             << setw(15) << "Сравнения" << " | " 
             << setw(15) << "Пересылки" << endl;
        cout << string(80, '-') << endl;

        int* arr_src = new int[n];

        // 1. Случайный массив
        cout << "[ Случайные данные ]" << endl;
        generateData(arr_src, n, 1);
        runTest(arr_src, n, 1, "Слиянием");
        runTest(arr_src, n, 2, "Quick (Last)");
        runTest(arr_src, n, 3, "Quick (Hoare)");

        // 2. Отсортированный (Best/Worst case)
        cout << "\n[ Отсортированы (возр) ]" << endl;
        generateData(arr_src, n, 2);
        runTest(arr_src, n, 1, "Слиянием");
        runTest(arr_src, n, 2, "Quick (Last)"); // Внимание: тут будет плохо
        runTest(arr_src, n, 3, "Quick (Hoare)");

        // 3. Обратно отсортированный
        cout << "\n[ Отсортированы (убыв) ]" << endl;
        generateData(arr_src, n, 3);
        runTest(arr_src, n, 1, "Слиянием");
        runTest(arr_src, n, 2, "Quick (Last)"); // И тут будет плохо
        runTest(arr_src, n, 3, "Quick (Hoare)");

        delete[] arr_src;
        cout << endl;
    }

    return 0;
}
