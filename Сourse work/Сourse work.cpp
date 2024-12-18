#include <windows.h>
#include <iostream>
#include "menu.h"
#include "user.h"
#include "employee.h" // Включаем заголовок для работы с EmployeeManager

using namespace std;

int main() {
	// Устанавливаем кодировку для ввода и вывода
	SetConsoleCP(1251);        // Устанавливаем кодовую страницу ввода
	SetConsoleOutputCP(1251);  // Устанавливаем кодовую страницу вывода

	UserManager userManager;
	EmployeeManager employeeManager;  // Создаем экземпляр EmployeeManager
	bool loggedIn = false;

	handleMainMenu(userManager, employeeManager, loggedIn);  // Передаем три аргумента

	return 0;
}
