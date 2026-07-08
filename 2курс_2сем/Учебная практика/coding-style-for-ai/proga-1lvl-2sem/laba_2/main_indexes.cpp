#include <iostream>
#include <fstream>
using namespace std;

// Получение размера квадратной матрицы из файла.
// Открывает файл, считывает первую строку (размер матрицы).
// Возвращает размер, если успешно, иначе -1.
int getMatrixSize(const char* filename);

// Чтение квадратной матрицы из файла и заполнение двумерного массива.
// filename — имя файла, matrix — двумерный массив, size — размерность матрицы.
// Возвращает true при успешном чтении, иначе false.
bool readMatrixFromFile(const char* filename, int matrix[][1000], int size);

// Обработка матрицы: поиск сумм в строках под главной диагональю без отрицательных элементов.
// matrix — матрица, size — размер, sums — массив для хранения сумм, minSum — минимальная из сумм.
// Возвращает количество подходящих строк.
int processMatrix(int matrix[][1000], int size, int* sums, int& minSum);

// Функция для вывода результатов анализа одной матрицы на экран.
// matrixName — название матрицы (для вывода), sums — массив сумм, count — количество, minSum — минимум.
void printResults(const char* matrixName, int* sums, int count, int minSum);

// Функция для вывода матрицы на экран.
// matrix — двумерный массив, size — размерность, matrixName — название матрицы.
void printMatrix(const char* matrixName, int matrix[][1000], int size);

int main() {
    // Массив имён файлов с матрицами (два файла)
    const char* files[2] = {"matrix1.txt", "matrix2.txt"};
    // Массив имён для вывода на экран
    const char* names[2] = {"Первая матрица", "Вторая матрица"};

    // Последовательно обрабатываем оба файла с матрицами
    for (int idx = 0; idx < 2; ++idx) {
        cout << "==== " << names[idx] << " ====" << endl;

        // Получаем размерность матрицы из файла
        int size = getMatrixSize(files[idx]);
        if (size <= 0 || size > 1000) {
            cerr << "Ошибка: некорректный размер матрицы в файле " << files[idx] << endl;
            continue;
        }

        // Объявляем статический двумерный массив (до 1000x1000)
        int matrix[1000][1000];
        // Динамически выделяем память под массив найденных сумм (не больше size-1, но для простоты size)
        int* sums = new int[size];

        // Читаем матрицу из файла
        if (!readMatrixFromFile(files[idx], matrix, size)) {
            cerr << "Ошибка чтения матрицы" << endl;
            delete[] sums;
            continue;
        }

        // Выводим исходную матрицу перед обработкой
        printMatrix(names[idx], matrix, size);

        // minSum — для хранения минимальной из найденных сумм
        int minSum;
        // count — количество подходящих строк (по условию задачи)
        int count = processMatrix(matrix, size, sums, minSum);

        // Выводим результаты на экран
        printResults(names[idx], sums, count, minSum);

        // Освобождаем память под массив найденных сумм
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

bool readMatrixFromFile(const char* filename, int matrix[][1000], int size) {
    // Открываем файл для чтения
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return false;
    }
    int tmp;
    // Пропускаем размер матрицы
    fin >> tmp;
    // Читаем элементы матрицы по строкам
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            if (!(fin >> matrix[i][j])) {
                cerr << "Ошибка чтения элемента матрицы [" << i << "][" << j << "]." << endl;
                fin.close();
                return false;
            }
        }
    fin.close();
    return true;
}

int processMatrix(int matrix[][1000], int size, int* sums, int& minSum) {
    // minSum — минимальная из найденных сумм, если нет строк — останется 0
    minSum = 0;
    // foundAny — количество строк, удовлетворяющих условию
    int foundAny = 0;
    // Проходим по всем строкам, находящимся ниже главной диагонали (i > 0)
    for (int i = 1; i < size; ++i) {
        bool hasNegative = false; // Флаг наличия отрицательного элемента в строке
        // Проверяем только элементы под главной диагональю (j < i)
        for (int j = 0; j < i; ++j) {
            if (matrix[i][j] < 0) {
                hasNegative = true;
                break; // Если встречен отрицательный элемент — строка не подходит
            }
        }
        // Если в строке нет отрицательных элементов — считаем сумму и сохраняем
        if (!hasNegative) {
            int sum = 0;
            for (int j = 0; j < i; ++j)
                sum += matrix[i][j];
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

// Функция для вывода матрицы на экран
void printMatrix(const char* matrixName, int matrix[][1000], int size) {
    cout << matrixName << " (исходная матрица):" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
