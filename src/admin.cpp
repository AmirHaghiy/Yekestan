#include "../include/user.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

// Constructor
Admin::Admin(int id, const std::string &name, const std::string &email, const std::string &password)
    : User(name, password, email, id, "admin")
{
    std::cout << "Admin created: " << name << std::endl;
}

void Admin::createUser(const std::string &name, const std::string &email, const std::string &password, const std::string &role)
{
    std::ifstream inputFile("../data/users.json");
    json users;

    inputFile >> users;
    inputFile.close();

    int userId = users["users"].size() + 1;
    json newUser = {
        {"id", userId},
        {"name", name},
        {"email", email},
        {"password", password},
        {"role", role},
        {"status", "active"}};

    users["users"].push_back(newUser);

    std::ofstream outputFile("../data/users.json");
    outputFile << users.dump(4);
    outputFile.close();

    std::cout << "User created successfully!" << std::endl;
}

void Admin::viewUser(int userId)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    for (const auto &user : users["users"])
    {
        if (user["id"] == userId && user["status"] == "active")
        {
            std::cout << "ID: " << user["id"] << "\n"
                      << "Name: " << user["name"] << "\n"
                      << "Email: " << user["email"] << "\n"
                      << "Role: " << user["role"] << "\n"
                      << "Status: " << user["status"] << std::endl;
            return;
        }
    }

    std::cout << "User with ID " << userId << " not found or is inactive." << std::endl;
}

void Admin::updateUser(int userId, const std::string &name, const std::string &email, const std::string &role)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    bool updated = false;
    for (auto &user : users["users"])
    {
        if (user["id"] == userId && user["status"] == "active")
        {
            user["name"] = name;
            user["email"] = email;
            user["role"] = role;
            updated = true;
            break;
        }
    }

    if (updated)
    {
        std::ofstream outputFile("../data/users.json");
        outputFile << users.dump(4);
        outputFile.close();

        std::cout << "User updated successfully!" << std::endl;
    }
    else
    {
        std::cout << "User with ID " << userId << " not found or is inactive." << std::endl;
    }
}

void Admin::deleteUser(int userId)
{
    std::ifstream inputFile("../data/users.json");
    json users;
    inputFile >> users;
    inputFile.close();

    bool deleted = false;
    for (auto &user : users["users"])
    {
        if (user["id"] == userId && user["status"] == "active")
        {
            user["status"] = "inactive";
            deleted = true;
            break;
        }
    }

    if (deleted)
    {
        std::ofstream outputFile("data/users.json");
        outputFile << users.dump(4);
        outputFile.close();

        std::cout << "User deleted successfully!" << std::endl;
    }
    else
    {
        std::cout << "User with ID " << userId << " not found " << std::endl;
    }
}

void Admin::viewInactiveUsers()
{
    std::ifstream inputFile("../data/users.json");
    json users;

    inputFile >> users;
    inputFile.close();

    bool foundInactive = false;
    for (const auto &user : users["users"])
    {
        if (user["status"] == "inactive")
        {
            std::cout << "ID: " << user["id"] << "\n"
                      << "Name: " << user["name"] << "\n"
                      << "Email: " << user["email"] << "\n"
                      << "Role: " << user["role"] << "\n"
                      << "Status: " << user["status"] << "\n"
                      << "-----------------------------" << std::endl;
            foundInactive = true;
        }
    }

    if (!foundInactive)
    {
        std::cout << "No inactive users found." << std::endl;
    }
}