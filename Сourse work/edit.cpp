#include "edit.h"
#include "getPassword.h"  // �������� ������������ ���� ��� ������������� generateSalt
#include <iostream>
#include <algorithm>
#include <limits>

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
   int isAdmin;
   cin >> isAdmin;
   it->second.isAdmin = isAdmin;
   cout << "������������ ������� ��������������.\n";
}

