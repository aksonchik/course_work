#include "edit.h"
#include "getPassword.h"  // �������� ������������ ���� ��� ������������� generateSalt
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>  // �������� ��� ������ � �������

using namespace std;

void editUser(unordered_map<string, UserManager::User>& users) {
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
        it->second.encryptedPassword = encryptPassword(newPassword, 'K');
    }
    cout << "�������� �� ������������ ��������������� (1 - ��, 0 - ���)? ";
    int isAdmin;  // ������������� ����������
    cin >> isAdmin;
    it->second.isAdmin = isAdmin;

    // ��������� ��������� � ����
    ofstream out("users.txt", ios::out);
    if (!out.is_open()) { // ���������, ������ �� ����
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

    cout << "������������ ������� ��������������.\n";
}