#include "employee.h"
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

EmployeeManager::EmployeeManager() {
    loadEmployeesFromFile();
}

void EmployeeManager::saveEmployeesToFile() {
    ofstream out(employeeFile, ios::trunc);
    if (!out) {
        cerr << "Ошибка открытия файла для записи сотрудников.\n";
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
        cerr << "Файл сотрудников не найден. Будет создан новый.\n";
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

void EmployeeManager::addEmployee(const string& fullName, const string& teamNumber, double averageIncome, bool communityInvolvement, double familyIncomePerCapita) {
    if (employees.find(fullName) != employees.end()) {
        cout << "Сотрудник с таким именем уже существует.\n";
        return;
    }
    employees[fullName] = { fullName, teamNumber, averageIncome, communityInvolvement, familyIncomePerCapita };
    saveEmployeesToFile();
    cout << "Сотрудник успешно добавлен.\n";
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
        cout << "Список сотрудников пуст.\n";
        return;
    }
    for (const auto& emp : sortedEmployees) {
        cout << "Ф.И.О.: " << emp.fullName << ", Номер бригады: " << emp.teamNumber
            << ", Средний доход: " << emp.averageIncome << ", Участие в общественной деятельности: "
            << (emp.communityInvolvement ? "Да" : "Нет") << ", Доход на одного члена семьи: " << emp.familyIncomePerCapita << "\n";
    }
}

void EmployeeManager::listEmployeeNames() const {
    const vector<Employee> sortedEmployees = getSortedEmployees();
    if (sortedEmployees.empty()) {
        cout << "Список сотрудников пуст.\n";
        return;
    }
    for (const auto& emp : sortedEmployees) {
        cout << "Ф.И.О.: " << emp.fullName << "\n";
    }
}

void EmployeeManager::deleteEmployee(const string& fullName) {
    if (employees.erase(fullName)) {
        saveEmployeesToFile();
        cout << "Сотрудник " << fullName << " успешно удален.\n";
    }
    else {
        cout << "Сотрудник не найден.\n";
    }
}
