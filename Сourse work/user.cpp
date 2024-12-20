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
        cout << "������������ admin ������ � ����� ��������������.\n";
        saveUsersToFile();
    }
}

bool UserManager::isCurrentUserAdmin() const {
    return !currentUser.empty() && users.at(currentUser).isAdmin;
}

void UserManager::saveUsersToFile() {
    ofstream out(userFile, ios::out);
    if (!out) {
        cerr << "������ �������� ����� ��� ������ �������������.\n";
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
        cerr << "���� ������������� �� ������. ����� ������ �����.\n";
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
        cout << "������������ � ����� ������ ��� ����������.\n";
        return;
    }

    string salt = generateSalt();
    string hashedPassword = hashPassword(password, salt);
    string encryptedPassword = encryptPassword(password, key);

    users[username] = { username, hashedPassword, encryptedPassword, isAdmin, false };
    saveUsersToFile();
    cout << "������������ " << username << " ������� ���������������. �������� ������������� ��������������.\n";
}

bool UserManager::login(const string& username, const string& password) {
    auto it = users.find(username);
    if (it == users.end()) {
        cout << "������������ �� ������: " << username << "\n";
        return false;
    }
    // �������� decryptPassword �� encryptPassword
    string originalPassword = encryptPassword(it->second.encryptedPassword, key);
    if (password != originalPassword) {
        cout << "������������ ������ ��� ������������: " << username << "\n";
        return false;
    }
    if (!it->second.isActive) {
        cout << "������� ������ ������������ ��������� � ������� ������������� ��������������.\n";
        return false;
    }
    currentUser = username;
    cout << "����� ����������, " << username << "!\n";
    return true;
}

void UserManager::logout() {
    if (currentUser.empty()) {
        cout << "�� �� ����� � �������.\n";
        return;
    }
    cout << "������������ " << currentUser << " ����� �� �������.\n";
    currentUser.clear();
    saveUsersToFile();
}

void UserManager::changeUsername() {
    if (currentUser.empty()) {
        cout << "�� �� ����� � �������.\n";
        return;
    }

    string newUsername;
    cout << "������� ����� �����: ";
    cin >> newUsername;

    auto it = users.find(currentUser);
    if (it != users.end()) {
        User user = it->second;
        users.erase(it);
        user.username = newUsername;
        users[newUsername] = user;
        currentUser = newUsername;
        saveUsersToFile();
        cout << "����� ������� �������.\n";
    }
}

void UserManager::changePassword() {
    if (currentUser.empty()) {
        cout << "�� �� ����� � �������.\n";
        return;
    }

    string newPassword;
    cout << "������� ����� ������: ";
    cin >> newPassword;

    auto it = users.find(currentUser);
    if (it != users.end()) {
        string salt = generateSalt();
        it->second.password = hashPassword(newPassword, salt);
        it->second.encryptedPassword = encryptPassword(newPassword, key);
        saveUsersToFile();
        cout << "������ ������� �������.\n";
    }
}

void UserManager::confirmUserRegistration(const string& username) {
    auto it = users.find(username);
    if (it == users.end()) {
        cout << "������������ �� ������.\n";
        return;
    }

    it->second.isActive = true;
    saveUsersToFile();
    cout << "����������� ������������ " << username << " ������� ������������.\n";
}

void UserManager::confirmAllUserRegistrations() {
    for (auto& pair : users) {
        pair.second.isActive = true;
    }
    saveUsersToFile();
    cout << "����������� ���� ������������� ������� ������������.\n";
}

void UserManager::editUser() {
    string username;
    cout << "������� ��� ������������ ��� ��������������: ";
    cin >> username;
    auto it = users.find(username);
    if (it == users.end()) {
        cout << "������������ �� ������.\n";
        return;
    }
    cout << "������� ����� ������ ��� ������������ (��� �������� ������ ��� �������� ���������): ";
    string newPassword;
    cin.ignore();
    getline(cin, newPassword);
    if (!newPassword.empty()) {
        string salt = generateSalt();
        it->second.password = hashPassword(newPassword, salt);
        it->second.encryptedPassword = encryptPassword(newPassword, key);
    }
    cout << "�������� �� ������������ ��������������� (1 - ��, 0 - ���)? ";
    int isAdmin;
    cin >> isAdmin;
    it->second.isAdmin = isAdmin;
    saveUsersToFile();
    cout << "������������ ������� ��������������.\n";
}

void UserManager::deleteUser() {
    string username;
    cout << "������� ��� ������������ ��� ��������: ";
    cin >> username;
    auto it = users.find(username);
    if (it == users.end()) {
        cout << "������������ �� ������.\n";
        return;
    }
    users.erase(it);
    saveUsersToFile();
    cout << "������������ " << username << " ������� ������.\n";
}

void UserManager::listUsers() const {
    if (users.empty()) {
        cout << "������ ������������� ����.\n";
        return;
    }
    cout << left << setw(20) << "��� ������������" << setw(15) << "����" << setw(15) << "����������" << setw(20) << "������\n";
    cout << "------------------------------------------------------------------------------------\n";
    for (const auto& pair : users) {
        cout << left << setw(20) << pair.second.username
            << setw(15) << (pair.second.isAdmin ? "�������������" : "������������")
            << setw(15) << (pair.second.isActive ? "�������" : "���������")
            << setw(20) << "�����" << "\n"; // ������ �����
    }
}