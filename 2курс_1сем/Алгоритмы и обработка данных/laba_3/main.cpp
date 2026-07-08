#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

struct Node {
    double data;
    Node* next;
};

// --- ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ (НОВАЯ) ---
// Проверяет, есть ли уже такое число в списке.
// Нужна, так как по заданию "повторное вхождение запрещено".
bool isDuplicate(Node* head, double value) {
    Node* temp = head;
    while (temp != nullptr) {
        // Сравниваем вещественные числа. 
        // Для лабы достаточно простого ==, но для double лучше так:
        if (temp->data == value) {
            return true; // Нашли дубликат
        }
        temp = temp->next;
    }
    return false; // Дубликатов нет
}

// --- ОСНОВНЫЕ ФУНКЦИИ ---

// 1. Создание/добавление (с проверкой на уникальность)
void append(Node*& head, double value) {
    // ПРОВЕРКА НА ЗАПРЕТ ПОВТОРОВ
    if (isDuplicate(head, value)) {
        cout << "Ошибка: Число " << value << " уже есть в списке! Повторы запрещены." << endl;
        return;
    }

    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Элемент " << value << " добавлен." << endl;
}

// 2. Вывод списка
void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }
    cout << "Список: [ ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "]" << endl;
}

// 3. Запись в файл
void saveToFile(Node* head) {
    ofstream file("list_output.txt");
    if (!file.is_open()) {
        cout << "Ошибка файла!" << endl;
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        file << temp->data << " ";
        temp = temp->next;
    }
    file.close();
    cout << "Записано в файл." << endl;
}

// 4. Удаление списка
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Список очищен." << endl;
}

// --- СПЕЦИФИЧЕСКИЕ ОПЕРАЦИИ (ВАРИАНТ 4) ---

// Операция 2: Поиск максимума
// (Так как повторы запрещены при вводе, максимум будет уникальным)
void findMax(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }

    Node* temp = head;
    double maxVal = temp->data;
    int maxIndex = 1;
    int currentIndex = 1;

    while (temp != nullptr) {
        if (temp->data > maxVal) {
            maxVal = temp->data;
            maxIndex = currentIndex;
        }
        temp = temp->next;
        currentIndex++;
    }

    cout << "Максимум: " << maxVal << " (Позиция: " << maxIndex << ")" << endl;
}

// Операция 5: Вставка в позицию (с проверкой на уникальность)
void insertAtPosition(Node*& head, int pos, double value) {
    if (pos < 1) {
        cout << "Ошибка: позиция >= 1." << endl;
        return;
    }

    // ПРОВЕРКА НА ЗАПРЕТ ПОВТОРОВ
    if (isDuplicate(head, value)) {
        cout << "Ошибка: Число " << value << " уже есть в списке! Повторы запрещены." << endl;
        return;
    }

    Node* newNode = new Node;
    newNode->data = value;

    if (pos == 1) {
        newNode->next = head;
        head = newNode;
        cout << "Вставлено в начало." << endl;
        return;
    }

    Node* temp = head;
    for (int i = 1; i < pos - 1; i++) {
        if (temp == nullptr) {
            cout << "Ошибка: позиция за пределами списка." << endl;
            delete newNode; 
            return;
        }
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Ошибка: позиция за пределами списка." << endl;
        delete newNode;
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
        cout << "Вставлено на позицию " << pos << "." << endl;
    }
}

// Операция 8: Удаление из позиции
void deleteAtPosition(Node*& head, int pos) {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }
    if (pos < 1) {
        cout << "Неверная позиция." << endl;
        return;
    }

    if (pos == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Удалено из начала." << endl;
        return;
    }

    Node* temp = head;
    for (int i = 1; i < pos - 1; i++) {
        if (temp == nullptr || temp->next == nullptr) {
            cout << "Нет такой позиции." << endl;
            return;
        }
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Нет такой позиции." << endl;
    } else {
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        cout << "Удалено с позиции " << pos << "." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Node* head = nullptr;
    int choice;

    while (true) {
        cout << "\n--- МЕНЮ (Вариант 4: Без повторов) ---" << endl;
        cout << "1. Добавить элемент (в конец)" << endl;
        cout << "2. Показать список" << endl;
        cout << "3. Сохранить в файл" << endl;
        cout << "4. Очистить список" << endl;
        cout << "5. [Доп] Найти МАКСИМУМ" << endl;
        cout << "6. [Доп] Вставить в позицию" << endl;
        cout << "7. [Доп] Удалить из позиции" << endl;
        cout << "0. Выход" << endl;
        cout << "> ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: {
                double v;
                cout << "Число: ";
                cin >> v;
                append(head, v);
                break;
            }
            case 2: printList(head); break;
            case 3: saveToFile(head); break;
            case 4: deleteList(head); break;
            case 5: findMax(head); break;
            case 6: {
                int p; double v;
                cout << "Позиция: "; cin >> p;
                cout << "Число: "; cin >> v;
                insertAtPosition(head, p, v);
                break;
            }
            case 7: {
                int p;
                cout << "Позиция: "; cin >> p;
                deleteAtPosition(head, p);
                break;
            }
            case 0: deleteList(head); return 0;
            default: cout << "Неверный ввод." << endl;
        }
    }
}
