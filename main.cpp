#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <map>

using namespace std;

// Функция для генерации случайного числа в пределах от 1 до num_faces
int roll_die(int num_faces) {
    random_device rd; // Создаем генератор случайных чисел
    mt19937 gen(rd()); // Мерсеннский твистер для случайных чисел
    uniform_int_distribution<> dis(1, num_faces); // Равномерное распределение
    return dis(gen); // Генерируем случайное число
}

// Функция для выполнения броска по строковому описанию
int dice(const string &dice_str) {
    int total = 0;

    stringstream ss(dice_str); // Стрим для обработки строки
    string part;

    while (getline(ss, part, ',')) { // Разделяем строку по запятой
        int num_dice = 0, num_faces = 0, bonus = 0;

        // Ищем позицию плюса, чтобы разделить на количество кубиков и бонус
        size_t plus_pos = part.find('+');
        if (plus_pos != string::npos) {
            bonus = stoi(part.substr(plus_pos + 1)); // Извлекаем бонус
            part = part.substr(0, plus_pos); // Убираем бонус из основной части
        }

        // Разделяем часть на количество кубиков и количество граней
        size_t d_pos = part.find('d');
        if (d_pos != string::npos) {
            num_dice = stoi(part.substr(0, d_pos)); // Количество кубиков
            num_faces = stoi(part.substr(d_pos + 1)); // Количество граней на кубике
        }

        // Подсчитываем результат броска
        int roll_sum = 0;
        for (int i = 0; i < num_dice; ++i) {
            roll_sum += roll_die(num_faces); // Бросаем кубик
        }

        // Добавляем бонус и прибавляем к общему результату
        total += roll_sum + bonus;
    }

    return total;
}

void printHistogram(const int a[], int size) {
    // Мапа для подсчета количества каждого результата
    map<int, int> histogram;

    // Подсчитываем количество каждого результата
    for (int i = 0; i < size; ++i) {
        histogram[a[i]]++;
    }

    // Находим максимальное значение для определения высоты столбцов
    int max_count = 0;
    for (const auto& pair : histogram) {
        if (pair.second > max_count) {
            max_count = pair.second;
        }
    }

    // Вывод гистограммы
    for (int i = max_count; i > 0; --i) {
        for (const auto& pair : histogram) {
            if (pair.second >= i) {
                cout << "  *  ";  // Столбик
            } else {
                cout << "     ";  // Пробел, если меньше
            }
        }
        cout << endl;
    }

    // Вывод оси X
    for (const auto& pair : histogram) {
        cout << "  " << setw(3) << pair.first << " ";
    }
    cout << endl;
}

int main() {
    string dice_input = "3d6"; // Пример строки с бросками

    cout<<"Result: "<<dice(dice_input)<<endl;

    int a[1000];
    for (int & i : a){
        i=dice(dice_input);
    }

    cout << "Histogram: " << endl;
    printHistogram(a, 1000);


    return 0;
}
