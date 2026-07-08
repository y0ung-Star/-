#include <iostream>  // Для ввода-вывода
#include <fstream>   // Для работы с файлами

using namespace std;

// ------------------ ПРОТОТИПЫ ФУНКЦИЙ ------------------

// Считывает матрицу из файла filename, возвращает через matrix,
// а размеры через rows и cols (передаются по ссылке)
void readMatrix(const char* filename, int**& matrix, int& rows, int& cols);

// Выводит матрицу matrix размером rows x cols на экран
void printMatrix(int** matrix, int rows, int cols);

// Сортирует столбцы матрицы matrix по возрастанию суммы элементов в столбцах
void sortColumnsBySum(int** matrix, int rows, int cols);

// Вычисляет сумму элементов в столбце colIndex матрицы matrix
int columnSum(int** matrix, int rows, int colIndex);

// Освобождает память, выделенную под матрицу (удаляет все строки и сам массив указателей)
void freeMatrix(int** matrix, int rows);

// ------------------ ОСНОВНАЯ ПРОГРАММА ------------------

int main() {
    int** matrix = nullptr; // Указатель на двумерный массив (будущая матрица)
    int rows = 0, cols = 0; // Переменные для хранения количества строк и столбцов

    // Считываем матрицу из файла
    readMatrix("matrix.txt", matrix, rows, cols);

    // Выводим исходную матрицу на экран
    cout << "Исходная матрица:\n";
    printMatrix(matrix, rows, cols);

    // Сортируем столбцы по возрастанию суммы их элементов
    sortColumnsBySum(matrix, rows, cols);

    // Выводим преобразованную (отсортированную) матрицу
    cout << "Матрица после сортировки столбцов по возрастанию суммы:\n";
    printMatrix(matrix, rows, cols);

    // Освобождаем память, выделенную под матрицу
    freeMatrix(matrix, rows);

    return 0;
}

// ------------------ РЕАЛИЗАЦИЯ ФУНКЦИЙ ------------------

// Функция для считывания матрицы из файла
void readMatrix(const char* filename, int**& matrix, int& rows, int& cols) {
    ifstream fin(filename); // Открываем файл для чтения
    if (!fin) {
        // Если файл не открылся, выводим ошибку и завершаем программу
        cout << "Не удалось открыть файл " << filename << endl;
        exit(1);
    }

    // Считываем количество строк и столбцов из файла
    fin >> rows >> cols;

    // Выделяем память для матрицы: массив указателей на строки
    matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        // Для каждой строки выделяем память под массив из cols элементов
        matrix[i] = new int[cols];
    }

    // Заполняем матрицу числами из файла (построчно)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fin >> matrix[i][j]; // Чтение очередного элемента
        }
    }

    // Закрываем файл после завершения чтения
    fin.close();
}

// Функция для вывода матрицы на экран
void printMatrix(int** matrix, int rows, int cols) {
    // Проходим по всем строкам
    for (int i = 0; i < rows; ++i) {
        // Проходим по всем столбцам в текущей строке
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t"; // Выводим элемент и табуляцию для выравнивания
        }
        cout << endl; // После строки переходим на новую строку
    }
}

// Функция для обмена двух столбцов матрицы местами
// col1 и col2 - индексы столбцов, которые нужно поменять
void swapColumns(int** matrix, int rows, int col1, int col2) {
    for (int i = 0; i < rows; ++i) {
        // Меняем элементы местами в каждой строке для этих столбцов
        int tmp = matrix[i][col1];
        matrix[i][col1] = matrix[i][col2];
        matrix[i][col2] = tmp;
    }
}

// Функция вычисляет сумму элементов в столбце colIndex
int columnSum(int** matrix, int rows, int colIndex) {
    int sum = 0; // Для хранения суммы элементов столбца
    for (int i = 0; i < rows; ++i) {
        sum += matrix[i][colIndex]; // Прибавляем очередной элемент столбца
    }
    return sum; // Возвращаем сумму
}

// Функция сортирует столбцы по возрастанию суммы их элементов
void sortColumnsBySum(int** matrix, int rows, int cols) {
    // Создаём массив для хранения сумм каждого столбца
    int* sums = new int[cols];
    for (int j = 0; j < cols; ++j) {
        sums[j] = columnSum(matrix, rows, j); // Запоминаем суммы
    }

    // Сортируем столбцы по возрастанию суммы (метод пузырька)
    for (int i = 0; i < cols - 1; ++i) {
        // Проходим по неотсортированной части столбцов
        for (int j = 0; j < cols - i - 1; ++j) {
            // Если сумма текущего столбца больше суммы следующего, меняем их местами
            if (sums[j] > sums[j+1]) {
                // Меняем суммы местами
                int tmp = sums[j];
                sums[j] = sums[j+1];
                sums[j+1] = tmp;
                // Меняем местами соответствующие столбцы в матрице
                swapColumns(matrix, rows, j, j+1);
            }
        }
    }

    // Освобождаем память, выделенную под массив сумм
    delete[] sums;
}

// Функция для освобождения памяти, выделенной под матрицу
void freeMatrix(int** matrix, int rows) {
    // Сначала удаляем каждую строку
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    // Затем удаляем массив указателей на строки
    delete[] matrix;
}

