#include "admin.h"
#include "getPassword.h"
#include "checks.h"
#include <iostream>

using namespace std;

void showAdminMenu() {
    cout << "\n=== ���� �������������� ===\n"
        << "1. ���������� ������������\n"
        << "2. ����������� ����������� ������������\n"
        << "3. ����������� ����������� ���� �������������\n"
        << "4. ����������� ����������� �������������� ���� � ���������\n"
        << "5. ����� �� ������� ������\n"
        << "������� �������: ";
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
            cout << "������� ��� ������������ ��� ������������� �����������: ";
            cin >> username;
            userManager.confirmUserRegistration(username);
        }
        else if (command == "3") {
            userManager.confirmAllUserRegistrations();
        }
        else if (command == "4") {
            employeeManager.listEmployees(); // ������� ��� ������ ��� ��������������
        }
        else if (command == "5") {
            userManager.logout();
            loggedIn = false;
            break;
        }
        else {
            cout << "�������� ������� (������� ������ ����� �� 1 �� 5).\n";
        }
    }
}

void showAdminEmployeeMenu() {
    cout << "=== ���� ���������� ������������ ===\n"
        << "1. ����������� �����������\n"
        << "2. �������� ����������\n"
        << "3. ������� ����������\n"
        << "4. �����\n"
        << "������� �������: ";
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

            cout << "�.�.�. ����������: ";
            getline(cin, fullName);

            teamNumber = employeeManager.getValidTeamNumber();

            cout << "������� ����� �� ��������� 3 ������: ";
            cin >> averageIncome;

            cout << "������� � ������������ ������������ (1 - ��, 0 - ���): ";
            cin >> communityInvolvement;

            cout << "����� �� ������ ����� �����: ";
            cin >> familyIncomePerCapita;

            employeeManager.addEmployee(fullName, teamNumber, averageIncome, communityInvolvement, familyIncomePerCapita);
        }
        else if (command == "3") {
            string fullName;
            cout << "�.�.�. ����������: ";
            cin.ignore();
            getline(cin, fullName);
            employeeManager.deleteEmployee(fullName);
        }
        else if (command == "4") {
            break;
        }
        else {
            cout << "�������� ������� (������� ������ ����� �� 1 �� 4).\n";
        }
    }
}