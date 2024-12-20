#ifndef GETPASSWORD_H
#define GETPASSWORD_H

#include <string>

std::string getPassword();
std::string generateSalt();
std::string hashPassword(const std::string& password, const std::string& salt);
std::string encryptPassword(const std::string& plaintext, char key);

#endif // GETPASSWORD_H