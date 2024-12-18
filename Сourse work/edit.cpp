#include "edit.h"
#include "getPassword.h"  // Включаем заголовочный файл для использования generateSalt
#include <iostream>
#include <algorithm>
#include <limits>

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
   int isAdmin;
   cin >> isAdmin;
   it->second.isAdmin = isAdmin;
   cout << "Пользователь успешно отредактирован.\n";
}

