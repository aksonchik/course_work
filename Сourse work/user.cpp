#include "user.h"
#include "getPassword.h"
#include "checks.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

UserManager::UserManager() {
    loadUsersFromFile();
    if (users.empty()) {
        string password = "admin";
        string salt = generateSalt();
        users["admin"] = { "admin", hashPassword(password, salt), encryptPassword(password, key), true, true };
        cout << "Пользователь admin создан с ролью администратора.\n";
        saveUsersToFile();
    }
}

bool UserManager::isCurrentUserAdmin() const {
    return !currentUser.empty() && users.at(currentUser).isAdmin;
}

void UserManager::saveUsersToFile() {
    ofstream out(userFile, ios::out);
    if (!out) {
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
}

void UserManager::loadUsersFromFile() {
    ifstream in(userFile);
    if (!in) {
        cerr << "Файл пользователей не найден. Будет создан новый.\n";
        return;
    }
    string username, salt, password, encryptedPassword;
    bool isAdmin, isActive;
    while (in >> username >> salt >> password >> encryptedPassword >> isAdmin >> isActive) {
        password = salt + " " + password;
        users[username] = { username, password, encryptedPassword, isAdmin, isActive };
    }
    in.close();
}

void UserManager::registerUser(const string& username, const string& password, bool isAdmin) {
    if (users.find(username) != users.end()) {
        cout << "Пользователь с таким именем уже существует.\n";
        return;
    }

    string salt = generateSalt();
    string hashedPassword = hashPassword(password, salt);
    string encryptedPassword = encryptPassword(password, key);

    users[username] = { username, hashedPassword, encryptedPassword, isAdmin, false };
    saveUsersToFile();
    cout << "Пользователь " << username << " успешно зарегистрирован. Ожидание подтверждения администратора.\n";
}

bool UserManager::login(const string& username, const string& password) {
    auto it = users.find(username);
    if (it == users.end()) {
        cout << "Пользователь не найден: " << username << "\n";
        return false;
    }
    // Заменяем decryptPassword на encryptPassword
    string originalPassword = encryptPassword(it->second.encryptedPassword, key);
    if (password != originalPassword) {
        cout << "Неправильный пароль для пользователя: " << username << "\n";
        return false;
    }
    if (!it->second.isActive) {
        cout << "Учетная запись пользователя неактивна и ожидает подтверждения администратора.\n";
        return false;
    }
    currentUser = username;
    cout << "Добро пожаловать, " << username << "!\n";
    return true;
}

void UserManager::logout() {
    if (currentUser.empty()) {
        cout << "Вы не вошли в систему.\n";
        return;
    }
    cout << "Пользователь " << currentUser << " вышел из системы.\n";
    currentUser.clear();
    saveUsersToFile();
}

void UserManager::changeUsername() {
    if (currentUser.empty()) {
        cout << "Вы не вошли в систему.\n";
        return;
    }

    string newUsername;
    cout << "Введите новый логин: ";
    cin >> newUsername;

    auto it = users.find(currentUser);
    if (it != users.end()) {
        User user = it->second;
        users.erase(it);
        user.username = newUsername;
        users[newUsername] = user;
        currentUser = newUsername;
        saveUsersToFile();
        cout << "Логин успешно изменен.\n";
    }
}

void UserManager::changePassword() {
    if (currentUser.empty()) {
        cout << "Вы не вошли в систему.\n";
        return;
    }

    string newPassword;
    cout << "Введите новый пароль: ";
    cin >> newPassword;

    auto it = users.find(currentUser);
    if (it != users.end()) {
        string salt = generateSalt();
        it->second.password = hashPassword(newPassword, salt);
        it->second.encryptedPassword = encryptPassword(newPassword, key);
        saveUsersToFile();
        cout << "Пароль успешно изменен.\n";
    }
}

void UserManager::confirmUserRegistration(const string& username) {
    auto it = users.find(username);
    if (it == users.end()) {
        cout << "Пользователь не найден.\n";
        return;
    }

    it->second.isActive = true;
    saveUsersToFile();
    cout << "Регистрация пользователя " << username << " успешно подтверждена.\n";
}

void UserManager::confirmAllUserRegistrations() {
    for (auto& pair : users) {
        pair.second.isActive = true;
    }
    saveUsersToFile();
    cout << "Регистрация всех пользователей успешно подтверждена.\n";
}

void UserManager::editUser() {
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
        it->second.encryptedPassword = encryptPassword(newPassword, key);
    }
    cout << "Является ли пользователь администратором (1 - да, 0 - нет)? ";
    int isAdmin;
    cin >> isAdmin;
    it->second.isAdmin = isAdmin;
    saveUsersToFile();
    cout << "Пользователь успешно отредактирован.\n";
}

void UserManager::deleteUser() {
    string username;
    cout << "Введите имя пользователя для удаления: ";
    cin >> username;
    auto it = users.find(username);
    if (it == users.end()) {
        cout << "Пользователь не найден.\n";
        return;
    }
    users.erase(it);
    saveUsersToFile();
    cout << "Пользователь " << username << " успешно удален.\n";
}

void UserManager::listUsers() const {
    if (users.empty()) {
        cout << "Список пользователей пуст.\n";
        return;
    }
    cout << left << setw(20) << "Имя пользователя" << setw(15) << "Роль" << setw(15) << "Активность" << setw(20) << "Пароль\n";
    cout << "------------------------------------------------------------------------------------\n";
    for (const auto& pair : users) {
        cout << left << setw(20) << pair.second.username
            << setw(15) << (pair.second.isAdmin ? "Администратор" : "Пользователь")
            << setw(15) << (pair.second.isActive ? "Активен" : "Неактивен")
            << setw(20) << "Скрыт" << "\n"; // Пароль скрыт
    }
}