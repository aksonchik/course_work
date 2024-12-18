#include <algorithm>
#include <iostream>
#include <regex>
#include <limits>
#include "checks.h"
#include <cctype>

bool isValidNumber(const std::string& str) {
   return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

void getInput(std::string& input) {
   while (true) {
      std::getline(std::cin, input);
      if (isValidNumber(input)) {
         break;
      }
      else {
         std::cout << "Введите только цифровые значения: ";
      }
   }
}

void getInputWithRange(std::string& input, int min, int max) {
   while (true) {
      std::getline(std::cin, input);
      if (isValidNumber(input) && std::stoi(input) >= min && std::stoi(input) <= max) {
         break;
      }
      else {
         std::cout << "Неверная команда (вводите только цифры от " << min << " до " << max << "): ";
      }
   }
}

bool isValidDate(const std::string& date) {
   std::regex datePattern(R"(\d{2}\.\d{2}\.\d{4})");
   if (std::regex_match(date, datePattern)) {
      // Дополнительная проверка на допустимость дня, месяца и года
      int day = std::stoi(date.substr(0, 2));
      int month = std::stoi(date.substr(3, 2));
      int year = std::stoi(date.substr(6, 4));

      if (month < 1 || month > 12) return false;
      if (day < 1 || day > 31) return false;
      if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
      if (month == 2) {
         bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
         if (day > (isLeap ? 29 : 28)) return false;
      }
      return true;
   }
   return false;
}

void getDateInput(std::string& input) {
   while (true) {
      std::getline(std::cin, input);
      if (isValidDate(input)) {
         break;
      }
      else {
         std::cout << "Неверный формат даты. Введите дату в формате ДД.ММ.ГГГГ: ";
      }
   }
}




bool isValidProductName(const std::string& name) {
   return name.find(' ') == std::string::npos;
}
