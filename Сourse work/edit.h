#ifndef EDIT_H
#define EDIT_H

#include <string>
#include <unordered_map>
#include "user.h"  // �������� ��������� ��� ������ � ��������������

using namespace std;

void editUser(unordered_map<string, UserManager::User>& users);

#endif // EDIT_H
