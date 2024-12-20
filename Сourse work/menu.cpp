#include "menu.h"
#include "getPassword.h"
#include "checks.h"
#include <iostream>

using namespace std;

void showMainMenu() {
    cout << "\n=== ������� ���� ===\n"
        << "1. �����\n"
        << "2. ������������������\n"
        << "3. �����\n"
        << "������� �������: ";
}

void handleMainMenu(UserManager& userManager, EmployeeManager& employeeManager, bool& loggedIn) {
    while (true) {
        if (!loggedIn) {
            showMainMenu();
            string command;
            getInputWithRange(command, 1, 3);

            if (command == "1") {
                string username, password;
                cout << "��� ������������: ";
                cin >> username;
                cin.ignore();
                cout << "������: ";
                password = getPassword();
                if (userManager.login(username, password)) {
                    loggedIn = true;
                }
            }
            else if (command == "2") {
                string username, password;
                cout << "��� ������������: ";
                cin >> username;
                cin.ignore();
                cout << "������: ";
                password = getPassword();
                userManager.registerUser(username, password);
            }
            else if (command == "3") {
                cout << "����� �� ���������.\n";
                break;
            }
            else {
                cout << "�������� �������.\n";
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
        cout << "\n=== ���� ������������ ===\n"
            << "1. ���������� ����������� �������������� ���� � ���������\n"
            << "2. �������� �����\n"
            << "3. �������� ������\n"
            << "4. ����� �� ������� ������\n"
            << "������� �������: ";

        string command;
        getInputWithRange(command, 1, 4);

        if (command == "1") {
            if (userManager.isCurrentUserAdmin()) {
                employeeManager.listEmployees(); // ����� ���� ������ ��� ��������������
            }
            else {
                employeeManager.listEmployeeNames(); // ����� ������ �.�.�. ��� �������� ������������
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
            cout << "�������� �������.\n";
        }
    }
}