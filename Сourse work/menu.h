#ifndef MENU_H
#define MENU_H

#include "user.h"
#include "employee.h"

void showMainMenu();
void handleMainMenu(UserManager& userManager, EmployeeManager& employeeManager, bool& loggedIn);
void handleUserMenu(UserManager& userManager, EmployeeManager& employeeManager, bool& loggedIn);
void handleAdminMenu(UserManager& userManager, EmployeeManager& employeeManager, bool& loggedIn);

#endif // MENU_H