#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include "ScanTable.h"
#include "SortTable.h"
#include "TreeTable.h"
#include "HashTable.h"

int main()
{
    Table<std::vector<int>> scan_table(10);
    SortTable<std::vector<int>> sort_table(1);
    TreeTable<std::vector<int>> tree_table;
    HashList<std::vector<int>> hash_table;
    int switch_on, exit = 1, temp, elem;
    std::vector<int> value;
    std::string key;
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите 1 для работы с ScanTable" << std::endl;
    std::cout << "Введите 2 для работы с SortTable" << std::endl;
    std::cout << "Введите 3 для работы с TreeTable" << std::endl;
    std::cout << "Введите 4 для работы с HashTable" << std::endl;
    std::cin >> switch_on;
    switch (switch_on)
    {
    case 1:
        while (exit) {
            std::cout << "Введите 1, чтобы добавить элемент (нужно ввести пару ключ-значение)" << std::endl;
            std::cout << "Введите 2, чтобы удалить элемент (нужно ввести ключ)" << std::endl;
            std::cout << "Введите 0, чтобы закончить работу" << std::endl;
            std::cin >> exit;
            if (exit == 1) {
                std::cout << "Введите ключ" << std::endl;
                std::cin >> key;
                std::cout << "Введите размерность вектора" << std::endl;
                std::cin >> temp;
                value = {};
                std::cout << "Введите данные" << std::endl;
                for (int i = 0; i < temp; i++) {
                    std::cin >> elem;
                    value.push_back(elem);
                }
                scan_table.Put(key, value);
                std::cout << std::endl;
                std::cout << scan_table << std::endl;
            }
            else if (exit == 2) {
                std::cout << "Введите ключ" << std::endl;
                std::cin >> key;
                scan_table.Del(key);
                std::cout << scan_table << std::endl;
            }
            else if (exit != 0) {
                std::cout << "Вводите цифру от 0 до 3, пожалуйста" << std::endl;
            }
        }
    case 2:
        while (exit) {
            std::cout << "Введите 1, чтобы добавить элемент (нужно ввести пару ключ-значение)" << std::endl;
            std::cout << "Введите 2, чтобы удалить элемент (нужно ввести ключ)" << std::endl;
            std::cout << "Введите 0, чтобы закончить работу" << std::endl;
            std::cin >> exit;
            if (exit == 1) {
                std::cout << "Введите ключ" << std::endl;
                std::cin >> key;
                std::cout << "Введите размерность вектора" << std::endl;
                std::cin >> temp;
                value = {};
                std::cout << "Введите данные" << std::endl;
                for (int i = 0; i < temp; i++) {
                    std::cin >> elem;
                    value.push_back(elem);
                }
                sort_table.Put(key, value);
                std::cout << std::endl;
                std::cout << sort_table << std::endl;
            }
            else if (exit == 2) {
                std::cout << "Введите ключ" << std::endl;
                std::cin >> key;
                sort_table.Del(key);
                std::cout << sort_table << std::endl;
            }
            else if (exit != 0) {
                std::cout << "Вводите цифру от 0 до 3, пожалуйста" << std::endl;
            }
        }
    case 3:
        while (exit) {
            std::cout << "Введите 1, чтобы добавить элемент (нужно ввести пару ключ-значение)" << std::endl;
            std::cout << "Введите 2, чтобы удалить элемент (нужно ввести ключ)" << std::endl;
            std::cout << "Введите 0, чтобы закончить работу" << std::endl;
            std::cin >> exit;
            if (exit == 1) {
                std::cout << "Введите ключ" << std::endl;
                std::cin >> key;
                std::cout << "Введите размерность вектора" << std::endl;
                std::cin >> temp;
                value = {};
                std::cout << "Введите данные" << std::endl;
                for (int i = 0; i < temp; i++) {
                    std::cin >> elem;
                    value.push_back(elem);
                }
                tree_table.Put(value, key);
                std::cout << std::endl;
                tree_table.Print();
            }
            else if (exit == 2) {
                std::cout << "Введите ключ" << std::endl;
                std::cin >> key;
                tree_table.Del(key);
                tree_table.Print();
            }
            else if (exit != 0) {
                std::cout << "Вводите цифру от 0 до 3, пожалуйста" << std::endl;
            }
        }
    case 4:
        while (exit) {
            std::cout << "Введите 1, чтобы добавить элемент (нужно ввести пару ключ-значение)" << std::endl;
            std::cout << "Введите 2, чтобы удалить элемент (нужно ввести ключ)" << std::endl;
            std::cout << "Введите 0, чтобы закончить работу" << std::endl;
            std::cin >> exit;
            if (exit == 1) {
                std::cout << "Введите ключ" << std::endl;
                std::cin >> key;
                std::cout << "Введите размерность вектора" << std::endl;
                std::cin >> temp;
                value = {};
                std::cout << "Введите данные" << std::endl;
                for (int i = 0; i < temp; i++) {
                    std::cin >> elem;
                    value.push_back(elem);
                }
                hash_table.Put(key, value);
                std::cout << std::endl;
                std::cout << hash_table << std::endl;
            }
            else if (exit == 2) {
                std::cout << "Введите ключ" << std::endl;
                std::cin >> key;
                hash_table.Del(key);
                std::cout << hash_table << std::endl;
            }
            else if (exit != 0) {
                std::cout << "Вводите цифру от 0 до 3, пожалуйста" << std::endl;
            }
        }
    default:
        break;
    }
    return 0;
}
