#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "employee.h"

void showAdminMenu();
void handleAdminMenu(UserManager& userManager, EmployeeManager& employeeManager, bool& loggedIn);
void showAdminEmployeeMenu();
void handleAdminEmployeeMenu(EmployeeManager& employeeManager);

#endif // ADMIN_H
