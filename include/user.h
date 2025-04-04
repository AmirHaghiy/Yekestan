#ifndef USER_H
#define USER_H
#include <string>
#include "course.h"

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
    // Constructor
    Teacher(int id, const std::string &name, const std::string &email, const std::string &password);

    // Course management methods
    void createCourse(const std::string &title, int capacity, const std::string &startTime, const int &vahed);
    void updateCourse(int courseId, const int &teacherId, const std::string &title, int capacity, const std::string &startTime, const std::string &timing);

    // Announcement methods
    void addAnnouncementToCourse(int courseId, const std::string &announcement);

    // Homework methods
    void assignHomeworkToCourse(int courseId, const std::string &homework);
    void enterGrades(int studentId, int homeworkId, int grade);
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