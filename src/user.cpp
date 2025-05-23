#include "../include/user.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

User::User(const string &name1, const string &password1, const string &email1, const int &id1, const string &role1)
{
    id = id1;
    name = name1;
    email = email1;
    password = password1;
    role = role1;
}
int User::getId() const
{
    return id;
}

string User::getName() const
{
    return name;
}

string User::getEmail() const
{
    return email;
}

string User::getRole() const
{
    return role;
}

std::string User::login(const std::string &email, const std::string &password, int &loggedIn)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();
    
    for (const auto &user : users["users"])
    {
        if (user["email"] == email && user["password"] == password)
        {
            std::cout << "User " << user["name"] << " logged in successfully!" << std::endl;
            loggedIn = 1;
            return user["role"];
        }
    }
    
    std::cout << "Invalid email or password." << std::endl;
    return "";  // Add default return value for failed login
}
int User::logout()
{
    system("cls");  // Clear terminal on Windows
    std::cout << "User logged out successfully!" << std::endl;
    return 1;
}
void User::changePassword(const std::string &oldPassword, const std::string &newPassword)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users; // Parse the JSON data
    inputFile.close();
    bool passwordUpdated = false;
    for (auto &user : users["users"])
    {
        if (user["email"] == email && user["password"] == oldPassword)
        {
            user["password"] = newPassword;
            passwordUpdated = true;
            break;
        }
    }
    if (passwordUpdated)
    {
        std::ofstream outputFile("../data/users.json");
        outputFile << users.dump(4); // Pretty-print JSON with 4 spaces
        outputFile.close();

        std::cout << "Password changed successfully!" << std::endl;
    }
    else
    {
        std::cout << "Incorrect old password. Password change failed." << std::endl;
    }
}
