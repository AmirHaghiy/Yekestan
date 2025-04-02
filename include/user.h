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
    int logout();
    void changePassword(const std::string &oldPassword, const std::string &newPassword);
};
class Admin : public User
{
public:
    Admin(int id, const std::string &name, const std::string &email, const std::string &password);

    void createUser(const std::string &name, const std::string &email, const std::string &password, const std::string &role);
    void viewUser(int userId);
    void updateUser(int userId, const std::string &name, const std::string &email, const std::string &role);
    void deleteUser(int userId);

    void viewInactiveUsers();
    void generateCourseReport();
};
class Teacher : public User
{
private:
    int teacherId;

public:
    Teacher(int id, const std::string &name, const std::string &email, const std::string &password);

    void createCourse(const std::string &title);
    void assignTest(int courseId, const std::string &testName);
    void enterGrades(int studentId, int courseId, int grade);
};
class Student : public User
{
private:
    int studentId;

public:
    Student(int id, const std::string &name, const std::string &email, const std::string &password);

    void enrollInCourse(int courseId);
    void takeTest(int testId);
    void viewGrades();
};

#endif