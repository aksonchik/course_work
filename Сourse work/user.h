#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>
#include "employee.h"

using namespace std;

class UserManager {
public:
    struct User {
        string username;
        string password;
        string encryptedPassword;
        bool isAdmin = false;
        bool isActive = false;
    };

private:
    unordered_map<string, User> users;
    string currentUser;
    const string userFile = "users.txt";
    const char key = 'K';

    void saveUsersToFile();
    void loadUsersFromFile();

public:
    UserManager();
    void registerUser(const string& username, const string& password, bool isAdmin = false);
    bool login(const string& username, const string& password);
    void logout();
    bool isCurrentUserAdmin() const;
    void showUserMenu(EmployeeManager& employeeManager);
    void showAdminMenu(EmployeeManager& employeeManager);
    void editUser();
    void assignRole();
    void toggleUserActivation();
    void deleteUser();
    void listUsers() const;
    void changeUsername();
    void changePassword();
    void confirmUserRegistration(const string& username);
    void confirmAllUserRegistrations();
};

#endif // USER_H
