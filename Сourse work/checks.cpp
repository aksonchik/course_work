#include "checks.h"
#include <iostream>
#include <regex>
#include <cctype>

using namespace std;

bool isValidNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

void getInput(string& input) {
    while (true) {
        getline(cin, input);
        if (isValidNumber(input)) {
            break;
        }
        else {
            cout << "Введите только цифровые значения: ";
        }
    }
}

void getInputWithRange(string& input, int min, int max) {
    while (true) {
        getline(cin, input);
        if (isValidNumber(input) && stoi(input) >= min && stoi(input) <= max) {
            break;
        }
        else {
            cout << "Неверная команда (вводите только цифры от " << min << " до " << max << "): ";
        }
    }
}

bool isValidDate(const string& date) {
    regex datePattern(R"(\d{2}\.\d{2}\.\d{4})");
    if (regex_match(date, datePattern)) {
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));

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
