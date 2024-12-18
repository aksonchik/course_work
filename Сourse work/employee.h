#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class EmployeeManager {
public:
    struct Employee {
        string fullName;
        string teamNumber;
        double averageIncome;
        bool communityInvolvement;
        double familyIncomePerCapita;
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
    void listEmployeeNames() const;  // Новая функция для вывода имен и фамилий сотрудников
    void deleteEmployee(const string& fullName);
};

#endif // EMPLOYEE_H
