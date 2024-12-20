#include "getPassword.h"
#include <iostream>
#include <sstream>
#include <functional>
#include <iomanip>
#include <random>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

string getPassword() {
    string password;
    char ch;

#ifdef _WIN32
    while ((ch = _getch()) != 13) { // 13 - ��� Enter �� Windows
        if (ch == '\b') { // ��������� ������� Backspace
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n') {
        if (ch == '\b' || ch == 127) { // ��������� ������� Backspace �� Linux/Unix
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    cout << endl;
    return password;
}

string generateSalt() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t max_index = (sizeof(charset) - 1);
    string salt;

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, max_index);

    for (size_t i = 0; i < 16; ++i) {
        salt += charset[distribution(generator)];
    }
    return salt;
}

string hashPassword(const string& password, const string& salt) {
    hash<string> hasher;
    size_t hashed = hasher(password + salt);
    stringstream ss;
    ss << salt << " " << hex << hashed; // ��������� ���� � �������� ����� �����
    return ss.str();
}

string encryptPassword(const string& plaintext, char key) {
    string ciphertext = plaintext;
    for (char& c : ciphertext) {
        c ^= key; // ���������� XOR-���������� � ������
    }
    return ciphertext;
}

string decryptPassword(const string& ciphertext, char key) {
    return encryptPassword(ciphertext, key); // �������� ���������� XOR-���������� � ��� �� ������
}