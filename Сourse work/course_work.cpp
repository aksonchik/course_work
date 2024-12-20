#include <windows.h>
#include <iostream>
#include "menu.h"
#include "user.h"
#include "employee.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    UserManager userManager;
    EmployeeManager employeeManager;
    bool loggedIn = false;

    handleMainMenu(userManager, employeeManager, loggedIn);

    return 0;
}