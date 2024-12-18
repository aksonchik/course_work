#ifndef EDIT_H
#define EDIT_H

#include <string>
#include <unordered_map>
#include "user.h"  // ¬ключаем заголовок дл€ работы с пользовател€ми

using namespace std;

void editUser(unordered_map<string, UserManager::User>& users);

#endif // EDIT_H
