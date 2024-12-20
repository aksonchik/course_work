#include "admin.h"
#include "getPassword.h"
#include "checks.h"
#include <iostream>

using namespace std;

void showAdminMenu() {
    cout << "\n=== Меню администратора ===\n"
        << "1. Управление сотрудниками\n"
        << "2. Подтвердить регистрацию пользователя\n"
        << "3. Подтвердить регистрацию всех пользователей\n"
        << "4. Просмотреть очередность предоставления мест в общежитии\n"
        << "5. Выйти из учетной записи\n"
        << "Введите команду: ";
}

void handleAdminMenu(UserManager& userManager, EmployeeManager& employeeManager, bool& loggedIn) {
    while (true) {
        showAdminMenu();
        string command;
        cin >> command;
        cin.ignore();

        if (command == "1") {
            handleAdminEmployeeMenu(employeeManager);
        }
        else if (command == "2") {
            string username;
            cout << "Введите имя пользователя для подтверждения регистрации: ";
            cin >> username;
            userManager.confirmUserRegistration(username);
        }
        else if (command == "3") {
            userManager.confirmAllUserRegistrations();
        }
        else if (command == "4") {
            employeeManager.listEmployees(); // Выводим все данные для администратора
        }
        else if (command == "5") {
            userManager.logout();
            loggedIn = false;
            break;
        }
        else {
            cout << "Неверная команда (вводите только цифры от 1 до 5).\n";
        }
    }
}

void showAdminEmployeeMenu() {
    cout << "=== Меню управления сотрудниками ===\n"
        << "1. Просмотреть сотрудников\n"
        << "2. Добавить сотрудника\n"
        << "3. Удалить сотрудника\n"
        << "4. Назад\n"
        << "Введите команду: ";
}

void handleAdminEmployeeMenu(EmployeeManager& employeeManager) {
    while (true) {
        showAdminEmployeeMenu();
        string command;
        cin >> command;
        cin.ignore();

        if (command == "1") {
            employeeManager.listEmployees();
        }
        else if (command == "2") {
            string fullName, teamNumber;
            double averageIncome, familyIncomePerCapita;
            bool communityInvolvement;

            cout << "Ф.И.О. сотрудника: ";
            getline(cin, fullName);

            teamNumber = employeeManager.getValidTeamNumber();

            cout << "Средний доход за последние 3 месяца: ";
            cin >> averageIncome;

            cout << "Участие в общественной деятельности (1 - да, 0 - нет): ";
            cin >> communityInvolvement;

            cout << "Доход на одного члена семьи: ";
            cin >> familyIncomePerCapita;

            employeeManager.addEmployee(fullName, teamNumber, averageIncome, communityInvolvement, familyIncomePerCapita);
        }
        else if (command == "3") {
            string fullName;
            cout << "Ф.И.О. сотрудника: ";
            cin.ignore();
            getline(cin, fullName);
            employeeManager.deleteEmployee(fullName);
        }
        else if (command == "4") {
            break;
        }
        else {
            cout << "Неверная команда (вводите только цифры от 1 до 4).\n";
        }
    }
}