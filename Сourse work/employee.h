#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class EmployeeManager {
public:
    struct Employee {
        string fullName;
        string teamNumber;
        double averageIncome = 0.0;
        bool communityInvolvement = false;
        double familyIncomePerCapita = 0.0;
    };

private:
    unordered_map<string, Employee> employees;
    const string employeeFile = "employees.txt";

    void saveEmployeesToFile();
    void loadEmployeesFromFile();

public:
    EmployeeManager();
    void addEmployee(const string& fullName, const string& teamNumber, double averageIncome, bool communityInvolvement, double familyIncomePerCapita);
    const vector<Employee> getSortedEmployees() const;
    void listEmployees() const;
    void listEmployeeNames() const;
    void deleteEmployee(const string& fullName);
};