#include "employee.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <regex> // ��� �������� �����

using namespace std;

EmployeeManager::EmployeeManager() {
    loadEmployeesFromFile();
}

void EmployeeManager::saveEmployeesToFile() {
    ofstream out(employeeFile, ios::trunc);
    if (!out) {
        cerr << "������ �������� ����� ��� ������ �����������.\n";
        return;
    }
    for (const auto& pair : employees) {
        const Employee& emp = pair.second;
        out << emp.fullName << "\n" << emp.teamNumber << "\n" << emp.averageIncome << "\n"
            << emp.communityInvolvement << "\n" << emp.familyIncomePerCapita << "\n";
    }
    out.close();
}

void EmployeeManager::loadEmployeesFromFile() {
    ifstream in(employeeFile);
    if (!in) {
        cerr << "���� ����������� �� ������. ����� ������ �����.\n";
        return;
    }
    string fullName, teamNumber;
    double averageIncome, familyIncomePerCapita;
    bool communityInvolvement;
    while (getline(in, fullName) && getline(in, teamNumber) && (in >> averageIncome) && (in >> communityInvolvement) && (in >> familyIncomePerCapita)) {
        employees[fullName] = { fullName, teamNumber, averageIncome, communityInvolvement, familyIncomePerCapita };
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    in.close();
}

// ������� ��� ��������� ��������� 4-�������� ������ �������
string EmployeeManager::getValidTeamNumber() const {
    string teamNumber;
    regex pattern("^\\d{4}$"); // ���������� ��������� ��� 4 ����

    while (true) {
        cout << "������� ����� ������� (4 �����): ";
        cin >> teamNumber;

        // ���������, ������������� �� ���� �������
        if (regex_match(teamNumber, pattern)) {
            return teamNumber;
        }
        else {
            cout << "������: ����� ������� ������ �������� �� 4 ����. ���������� �����.\n";
        }
    }
}


void EmployeeManager::addEmployee(const string& fullName, const string& teamNumber, double averageIncome, bool communityInvolvement, double familyIncomePerCapita) {
    if (employees.find(fullName) != employees.end()) {
        cout << "��������� � ����� ������ ��� ����������.\n";
        return;
    }
    employees[fullName] = { fullName, teamNumber, averageIncome, communityInvolvement, familyIncomePerCapita };
    saveEmployeesToFile();
    cout << "��������� ������� ��������.\n";
}

const vector<EmployeeManager::Employee> EmployeeManager::getSortedEmployees() const {
    vector<Employee> sortedEmployees;
    for (const auto& pair : employees) {
        sortedEmployees.push_back(pair.second);
    }
    sort(sortedEmployees.begin(), sortedEmployees.end(), [](const Employee& a, const Employee& b) {
        if (a.familyIncomePerCapita == b.familyIncomePerCapita) {
            if (a.communityInvolvement == b.communityInvolvement) {
                return a.averageIncome < b.averageIncome;
            }
            return a.communityInvolvement > b.communityInvolvement;
        }
        return a.familyIncomePerCapita < b.familyIncomePerCapita;
        });
    return sortedEmployees;
}

void EmployeeManager::listEmployees() const {
    const vector<Employee> sortedEmployees = getSortedEmployees();
    if (sortedEmployees.empty()) {
        cout << "������ ����������� ����.\n";
        return;
    }
    cout << left << setw(25) << "�.�.�."
        << setw(15) << "�������"
        << setw(15) << "������� ����� �� 3 ������"
        << setw(30) << "������� � ������������ ������������"
        << setw(25) << "����� �� ����� �����" << "\n";
    cout << string(110, '-') << "\n";
    for (const auto& emp : sortedEmployees) {
        cout << left << setw(25) << emp.fullName
            << setw(15) << emp.teamNumber
            << setw(15) << emp.averageIncome
            << setw(30) << (emp.communityInvolvement ? "��" : "���")
            << setw(25) << emp.familyIncomePerCapita << "\n";
    }
}

void EmployeeManager::listEmployeeNames() const {
    const vector<Employee> sortedEmployees = getSortedEmployees();
    if (sortedEmployees.empty()) {
        cout << "������ ����������� ����.\n";
        return;
    }
    for (const auto& emp : sortedEmployees) {
        cout << "�.�.�.: " << emp.fullName << "\n";
    }
}

void EmployeeManager::deleteEmployee(const string& fullName) {
    if (employees.erase(fullName)) {
        saveEmployeesToFile();
        cout << "��������� " << fullName << " ������� ������.\n";
    }
    else {
        cout << "��������� �� ������.\n";
    }
}