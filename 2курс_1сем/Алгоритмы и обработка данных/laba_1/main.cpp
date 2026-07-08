/****************************************************************
 *                     КАФЕДРА № 304 2 КУРС                      *
 *---------------------------------------------------------------*
 * Project Type  : GNU/Linux Console Application                 *
 * Project Name  : main                                          *
 * File Name     : main.cpp                                      *
 * Language      : C/C++                                         *
 * Programmer(s) : Егоров А.В (swrneko)                          *
 * Modifyed By   : Егоров А.В (swrneko)                          *
 * Edited by     : Neovim, Visual Studio                         *
 * OS            : Arch Linux                                    *
 * Github url    : https://github.com/swrneko/mai_shit.git       *
 * Created       : 5/11/25                                       *
 * Last Revision : 12/11/25                                      *
 * Comment(s)    : Алгоритм поиска                               *
 ****************************************************************/

// --- ПОДКЛЮЧЕНИЕ НЕОБХОДИМЫХ БИБЛИОТЕК ---
#include <chrono> // Дает доступ к высокоточному "секундомеру".
#include <cstdlib> // rand, srand
#include <ctime> // time
#include <iomanip> // setw
#include <iostream> // cout, cin
#include <string> // string

// --- ИСПОЛЬЗОВАНИЕ ПРОСТРАНСТВ ИМЕН ---
using namespace std;
using namespace std::chrono;

// --- Структура для хранения результатов ---
struct SearchResult {
    int index; // Индекс найденного элемента (или -1).
    long long time_ns;           // ВРЕМЯ В НАНОСЕКУНДАХ (изменено)
    long long counter1;          // Счетчик сравнений ключа (данных).
    long long counter2;          // Счетчик сравнений индексов (циклов).
};

// --- БЫСТРАЯ СОРТИРОВКА СЛИЯНИЕМ (MERGE SORT) ---
void merge(int *arr, int left, int mid, int right) {
    int left_half_size = mid - left + 1;
    int right_half_size = right - mid;

    int *left_array = new int[left_half_size];
    int *right_array = new int[right_half_size];

    for (int i = 0; i < left_half_size; i++)
        left_array[i] = arr[left + i];
    for (int j = 0; j < right_half_size; j++)
        right_array[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < left_half_size && j < right_half_size) {
        if (left_array[i] <= right_array[j]) {
            arr[k] = left_array[i];
            i++;
        } else {
            arr[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < left_half_size)
        arr[k++] = left_array[i++];
    while (j < right_half_size)
        arr[k++] = right_array[j++];

    delete[] left_array;
    delete[] right_array;
}

void mergeSort(int *arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// --- РЕАЛИЗАЦИЯ АЛГОРИТМОВ ПОИСКА ---

// Алгоритм 1: BLS (Simple Linear Search)
SearchResult BLS(const int *arr, int n, int key) {
    long long c1 = 0, c2 = 0;
    auto begin = steady_clock::now(); // Старт таймера

    for (int i = 0; i < n; ++i) {
        c2++; 
        c1++; 
        if (arr[i] == key) {
            auto end = steady_clock::now(); // Стоп таймера
            // duration_cast<nanoseconds> переводит разницу во времени в наносекунды
            return {i, duration_cast<nanoseconds>(end - begin).count(), c1, c2};
        }
    }
    c2++; 

    auto end = steady_clock::now();
    return {-1, duration_cast<nanoseconds>(end - begin).count(), c1, c2};
}

// Алгоритм 2: SLS (Sentinel Linear Search)
SearchResult SLS(int *arr, int n, int key) {
    long long c1 = 0, c2 = 0;
    if (n == 0) return {-1, 0, 0, 0};

    auto begin = steady_clock::now();
    
    int last = arr[n - 1]; 
    c1++;
    if (last == key) { 
        auto end = steady_clock::now();
        return {n - 1, duration_cast<nanoseconds>(end - begin).count(), c1, c2};
    }

    arr[n - 1] = key; 

    int i = 0;
    while (arr[i] != key) { 
        c1++; 
        i++;
    }
    c1++; 

    arr[n - 1] = last; 
    
    auto end = steady_clock::now();

    c2++; 
    if (i < n - 1) { 
        return {i, duration_cast<nanoseconds>(end - begin).count(), c1, c2}; 
    } else {
        return {-1, duration_cast<nanoseconds>(end - begin).count(), c1, c2}; 
    }
}

// Алгоритм 3: OAS (Ordered Array Search)
SearchResult OAS(const int *arr, int n, int key) {
    long long c1 = 0, c2 = 0;
    auto begin = steady_clock::now();

    for (int i = 0; i < n; ++i) {
        c2++; 
        c1++; 
        if (arr[i] == key) {
            auto end = steady_clock::now();
            return {i, duration_cast<nanoseconds>(end - begin).count(), c1, c2};
        }

        c1++; 
        if (arr[i] > key) {
            break; 
        }
    }
    if (c1 % 2 != 0) c2++; 

    auto end = steady_clock::now();
    return {-1, duration_cast<nanoseconds>(end - begin).count(), c1, c2};
}

// Алгоритм 4: BS (Binary Search)
SearchResult BS(const int *arr, int n, int key) {
    long long c1 = 0, c2 = 0;
    auto begin = steady_clock::now();

    int left = 0, right = n - 1;

    while (left <= right) {
        c2++; 
        int mid = left + (right - left) / 2;

        c1++;
        if (arr[mid] == key) { 
            auto end = steady_clock::now();
            return {mid, duration_cast<nanoseconds>(end - begin).count(), c1, c2};
        }

        c1++;
        if (arr[mid] < key) { 
            left = mid + 1;     
        } else {              
            right = mid - 1;    
        }
    }
    c2++; 

    auto end = steady_clock::now();
    return {-1, duration_cast<nanoseconds>(end - begin).count(), c1, c2};
}

// --- ФУНКЦИЯ ДЛЯ ВЫВОДА РЕЗУЛЬТАТОВ ---
void run_test_scenario(const string &scenario_name, 
                       int *unsorted_arr, int key_unsorted, 
                       const int *sorted_arr, int key_sorted, 
                       int n) {
    
    cout << "  Сценарий: " << scenario_name << "\n";
    cout << "  (Ключ несорт.: " << key_unsorted << ", Ключ сорт.: " << key_sorted << ")\n";
    cout << "  " << string(95, '-') << "\n";
    // Изменили заголовок колонки времени и немного расширили её
    cout << "  | Алгоритм |   Индекс   | Время (нс)  | Сравнения ключа (c1) | Сравнения индекса (c2) |\n";
    cout << "  " << string(95, '-') << "\n";

    SearchResult res_bls = BLS(unsorted_arr, n, key_unsorted);
    cout << "  | BLS      | " << setw(10) << res_bls.index << " | " << setw(11)
         << res_bls.time_ns << " | " << setw(20) << res_bls.counter1
         << " | " << setw(22) << res_bls.counter2 << " |\n";

    SearchResult res_sls = SLS(unsorted_arr, n, key_unsorted);
    cout << "  | SLS      | " << setw(10) << res_sls.index << " | " << setw(11)
         << res_sls.time_ns << " | " << setw(20) << res_sls.counter1
         << " | " << setw(22) << res_sls.counter2 << " |\n";

    SearchResult res_oas = OAS(sorted_arr, n, key_sorted);
    cout << "  | OAS      | " << setw(10) << res_oas.index << " | " << setw(11)
         << res_oas.time_ns << " | " << setw(20) << res_oas.counter1
         << " | " << setw(22) << res_oas.counter2 << " |\n";

    SearchResult res_bs = BS(sorted_arr, n, key_sorted);
    cout << "  | BS       | " << setw(10) << res_bs.index << " | " << setw(11)
         << res_bs.time_ns << " | " << setw(20) << res_bs.counter1
         << " | " << setw(22) << res_bs.counter2 << " |\n";

    cout << "  " << string(95, '-') << "\n\n";
}

int main() {
    setlocale(LC_ALL, ""); 
    srand(time(0)); 

    const int num_sizes = 6;
    int sizes[num_sizes] = {50000, 100000, 150000, 200000, 250000, 300000};

    for (int s = 0; s < num_sizes; ++s) {
        int n = sizes[s];

        cout << string(90, '=') << "\n";
        cout << "Тесты для массива размером " << n << " элементов\n";
        cout << string(90, '=') << "\n\n";

        int *unsorted_array = new int[n];
        int *sorted_array = new int[n];

        for (int i = 0; i < n; ++i) {
            unsorted_array[i] = rand() % (n * 10); 
            sorted_array[i] = unsorted_array[i]; 
        }

        auto sort_begin = steady_clock::now();
        mergeSort(sorted_array, 0, n - 1);
        auto sort_end = steady_clock::now();
        // Сортировку можно оставить в миллисекундах, она долгая
        cout << "  (Время сортировки: " << duration_cast<milliseconds>(sort_end - sort_begin).count() << " мс)\n\n";

        // --- 1. Лучший случай ---
        run_test_scenario("Элемент в начале массива", 
                          unsorted_array, unsorted_array[0],
                          sorted_array, sorted_array[0],
                          n);

        // --- 2. Средний случай ---
        int mid_val = sorted_array[n / 2];
        run_test_scenario("Элемент со значением медианы", 
                          unsorted_array, mid_val, 
                          sorted_array, mid_val, 
                          n);

        // --- 3. Худший случай ---
        int key_not_found = -1; 
        run_test_scenario("Ключ отсутствует", 
                          unsorted_array, key_not_found, 
                          sorted_array, key_not_found, 
                          n);

        delete[] unsorted_array;
        delete[] sorted_array;
    }

    return 0;
}
