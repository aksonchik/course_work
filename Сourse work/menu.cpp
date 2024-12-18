#include "menu.h"
#include "getPassword.h"
#include "Checks.h"
#include <iostream>
#include "admin.h"
#include "employee.h"

using namespace std;

void showMainMenu() {
    cout << "\n=== Главное меню ===\n"
        << "1. Войти\n"
        << "2. Зарегистрироваться\n"
        << "3. Выход\n"
        << "Введите команду: ";
}

void handleMainMenu(UserManager& userManager, EmployeeManager& employeeManager, bool& loggedIn) {
    while (true) {
        if (!loggedIn) {
            showMainMenu();
            string command;
            getInputWithRange(command, 1, 3);

            if (command == "1") {
                string username;
                cout << "Имя пользователя: ";
                cin >> username;
                cin.ignore();
                cout << "Пароль: ";
                string password = getPassword();
                if (userManager.login(username, password)) {
                    loggedIn = true;
                }
            }
            else if (command == "2") {
                string username, password;
                cout << "Имя пользователя: ";
                cin >> username;
                cin.ignore();
                cout << "Пароль: ";
                password = getPassword();
                userManager.registerUser(username, password);
            }
            else if (command == "3") {
                cout << "Выход из программы.\n";
                break;
            }
            else {
                cout << "Неверная команда.\n";
            }
        }
        else {
            if (userManager.isCurrentUserAdmin()) {
                handleAdminMenu(userManager, employeeManager, loggedIn);
            }
            else {
                handleUserMenu(userManager, employeeManager, loggedIn);
            }
        }
    }
}

void handleUserMenu(UserManager& userManager, EmployeeManager& employeeManager, bool& loggedIn) {
    while (true) {
        cout << "\n=== Меню пользователя ===\n"
            << "1. Посмотреть очередность предоставления мест в общежитии\n"
            << "2. Изменить логин\n"
            << "3. Изменить пароль\n"
            << "4. Выйти из учетной записи\n"
            << "Введите команду: ";

        string command;
        getInputWithRange(command, 1, 4);

        if (command == "1") {
            const vector<EmployeeManager::Employee> sortedEmployees = employeeManager.getSortedEmployees();
            cout << "\n=== Очередность предоставления мест в общежитии ===\n";
            for (const auto& emp : sortedEmployees) {
                cout << "Ф.И.О.: " << emp.fullName
                    << ", Номер бригады: " << emp.teamNumber
                    << ", Средний доход: " << emp.averageIncome
                    << ", Участие в общественной деятельности: " << (emp.communityInvolvement ? "Да" : "Нет")
                    << ", Доход на одного члена семьи: " << emp.familyIncomePerCapita << "\n";
            }
        }
        else if (command == "2") {
            userManager.changeUsername();
        }
        else if (command == "3") {
            userManager.changePassword();
        }
        else if (command == "4") {
            userManager.logout();
            loggedIn = false;
            break;
        }
        else {
            cout << "Неверная команда.\n";
        }
    }
}
