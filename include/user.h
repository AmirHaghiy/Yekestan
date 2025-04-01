#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User
{
protected:
    int id;
    string password;
    string email;
    string name;
    string role;

public:
    User(const string &name, const string &password, const string &email, const int &id, const string &role);
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getRole() const;
    void login(const std::string &email, const std::string &password);
    void logout();
    void changePassword(const std::string &oldPassword, const std::string &newPassword);
};

#endif