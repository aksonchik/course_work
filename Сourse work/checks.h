#ifndef CHECKS_H
#define CHECKS_H

#include <string>

// ���������� ������� ��������
bool isValidNumber(const std::string& str);
void getInput(std::string& input);
void getInputWithRange(std::string& input, int min, int max);
bool isValidDate(const std::string& date);  // ���������� ������� �������� ����
void getDateInput(std::string& input);  // ���������� ������� ��������� ����

// ����� ������� �������� �� �������
bool isValidProductName(const std::string& name);

#endif // CHECKS_H
