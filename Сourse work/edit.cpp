#include "edit.h"
#include "getPassword.h"  // Включаем заголовочный файл для использования generateSalt
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>  // Добавлен для работы с файлами

using namespace std;

void editUser(unordered_map<string, UserManager::User>& users) {
    string username;
    cout << "Введите имя пользователя для редактирования: ";
    cin >> username;
    auto it = users.find(username);
    if (it == users.end()) {
        cout << "Пользователь не найден.\n";
        return;
    }
    cout << "Введите новый пароль для пользователя (или оставьте пустым для пропуска изменения): ";
    string newPassword;
    cin.ignore();
    getline(cin, newPassword);
    if (!newPassword.empty()) {
        string salt = generateSalt();
        it->second.password = hashPassword(newPassword, salt);
        it->second.encryptedPassword = encryptPassword(newPassword, 'K');
    }
    cout << "Является ли пользователь администратором (1 - да, 0 - нет)? ";
    int isAdmin;  // Инициализация переменной
    cin >> isAdmin;
    it->second.isAdmin = isAdmin;

    // Сохраняем изменения в файл
    ofstream out("users.txt", ios::out);
    if (!out.is_open()) { // Проверяем, открыт ли файл
        cerr << "Ошибка открытия файла для записи пользователей.\n";
        return;
    }
    for (const auto& pair : users) {
        out << pair.second.username << " "
            << pair.second.password << " "
            << pair.second.encryptedPassword << " "
            << pair.second.isAdmin << " "
            << pair.second.isActive << "\n";
    }
    out.close();

    cout << "Пользователь успешно отредактирован.\n";
}