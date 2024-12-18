#ifndef CHECKS_H
#define CHECKS_H

#include <string>

// Объявление функций проверки
bool isValidNumber(const std::string& str);
void getInput(std::string& input);
void getInputWithRange(std::string& input, int min, int max);
bool isValidDate(const std::string& date);  // Объявление функции проверки даты
void getDateInput(std::string& input);  // Объявление функции получения даты

// Новая функция проверки на пробелы
bool isValidProductName(const std::string& name);

#endif // CHECKS_H
