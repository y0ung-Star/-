#include <iostream>
#include <fstream>
using namespace std;

// Получение размера квадратной матрицы из файла (размер — первая строка).
// Если файл не удаётся открыть или данные некорректны, возвращает -1.
int getMatrixSize(const char* filename);

// Чтение квадратной матрицы из файла и заполнение одномерного массива (размещённого динамически).
// filename — имя файла, matrix — указатель на массив, size — размерность.
// Возвращает true при успехе, иначе false.
bool readMatrixFromFile(const char* filename, int* matrix, int size);

// Обработка матрицы: поиск сумм в строках под главной диагональю без отрицательных элементов.
// matrix — указатель на массив, size — размер, sums — массив для хранения сумм, minSum — минимум.
// Возвращает количество подходящих строк.
int processMatrix(const int* matrix, int size, int* sums, int& minSum);

// Функция для вывода результатов анализа одной матрицы
// matrixName — имя для вывода, sums — массив сумм, count — количество, minSum — минимум
void printResults(const char* matrixName, int* sums, int count, int minSum);

int main() {
    // Массив имён файлов с матрицами (два файла)
    const char* files[2] = {"matrix1.txt", "matrix2.txt"};
    // Массив имён для вывода на экран
    const char* names[2] = {"Первая матрица", "Вторая матрица"};

    // Последовательно обрабатываем оба файла с матрицами с помощью арифметики указателей
    for (int idx = 0; idx < 2; ++idx) {
        cout << "==== " << names[idx] << " ====" << endl;

        // Получаем размерность матрицы из файла
        int size = getMatrixSize(files[idx]);
        if (size <= 0 || size > 1000) {
            cerr << "Ошибка: некорректный размер матрицы в файле " << files[idx] << endl;
            continue;
        }

        // Динамически выделяем память под одномерный массив для хранения матрицы
        int* matrix = nullptr;
        int* sums = nullptr;
        try {
            matrix = new int[size * size];
            sums = new int[size];
        } catch (bad_alloc&) {
            cerr << "Ошибка выделения памяти." << endl;
            delete[] matrix;
            delete[] sums;
            continue;
        }

        // Читаем матрицу из файла в одномерный массив
        if (!readMatrixFromFile(files[idx], matrix, size)) {
            cerr << "Ошибка чтения матрицы" << endl;
            delete[] matrix;
            delete[] sums;
            continue;
        }

        // minSum — для хранения минимальной из найденных сумм
        int minSum;
        // count — количество подходящих строк (по условию задачи)
        int count = processMatrix(matrix, size, sums, minSum);

        // Выводим результаты на экран
        printResults(names[idx], sums, count, minSum);

        // Освобождаем память под массивы
        delete[] matrix;
        delete[] sums;
        cout << endl;
    }
    return 0;
}

int getMatrixSize(const char* filename) {
    // Открываем файл для чтения
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return -1;
    }
    int size = -1;
    // Считываем размер матрицы (первое число в файле)
    fin >> size;
    // Проверка на ошибку чтения и корректность размера
    if (fin.fail() || size <= 0) {
        cerr << "Ошибка чтения размера матрицы или некорректный размер." << endl;
        fin.close();
        return -1;
    }
    fin.close();
    return size;
}

bool readMatrixFromFile(const char* filename, int* matrix, int size) {
    // Открываем файл для чтения
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return false;
    }
    int tmp;
    // Пропускаем размер матрицы
    fin >> tmp;
    // Заполняем одномерный массив, используя арифметику указателей
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            if (!(fin >> *(matrix + i*size + j))) {
                cerr << "Ошибка чтения элемента матрицы [" << i << "][" << j << "]." << endl;
                fin.close();
                return false;
            }
        }
    fin.close();
    return true;
}

int processMatrix(const int* matrix, int size, int* sums, int& minSum) {
    // minSum — минимальная из найденных сумм, если нет строк — останется 0
    minSum = 0;
    // foundAny — количество строк, удовлетворяющих условию
    int foundAny = 0;
    // Проходим по всем строкам, находящимся ниже главной диагонали (i > 0)
    for (int i = 1; i < size; ++i) {
        bool hasNegative = false; // Флаг наличия отрицательного элемента в строке
        // Проверяем только элементы под главной диагональю (j < i)
        for (int j = 0; j < i; ++j) {
            if (*(matrix + i*size + j) < 0) {
                hasNegative = true;
                break; // Если встречен отрицательный элемент — строка не подходит
            }
        }
        // Если в строке нет отрицательных элементов — считаем сумму и сохраняем
        if (!hasNegative) {
            int sum = 0;
            for (int j = 0; j < i; ++j)
                sum += *(matrix + i*size + j);
            sums[foundAny++] = sum;
            // Первый подходящий элемент — сразу пишем в minSum
            if (foundAny == 1) minSum = sum;
            // Для последующих — ищем минимум
            else if (sum < minSum) minSum = sum;
        }
    }
    // Если ни одной подходящей строки не найдено, minSum остаётся 0
    return foundAny;
}

void printResults(const char* matrixName, int* sums, int count, int minSum) {
    // Выводим все найденные суммы по условию задачи
    cout << matrixName << " — суммы элементов по условию: ";
    if (count == 0) {
        cout << "Нет подходящих строк";
    } else {
        for (int i = 0; i < count; ++i) {
            cout << sums[i];
            if (i + 1 != count) cout << ", ";
        }
    }
    cout << endl;
    // Выводим минимальную из этих сумм
    cout << matrixName << " — минимальная из этих сумм: " << minSum << endl;
}
