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
    void restorUser(int userId);
    void restorAllUsers();
    void generateCourseReport();
};
class Teacher : public User
{
private:
    int teacherId;

public:
    Teacher(int id, const std::string &name, const std::string &email, const std::string &password);

    void createCourse(const std::string &title, int capacity, std::string startTime, int vahed);
    void enterGrade(int , int , int);
    void viewEnrolledStudents(int);
    void addHomework(int, std::string);
    void addHomeworkGrades(int,int, int , int);
    void addAnnouncment(int, std::string);


};
class Student : public User
{
private:
    int studentId;

public:
    Student(int id, const std::string &name, const std::string &email, const std::string &password);

    void viewEnrolledCourses();
    void viewAvailableCourses();
    void courseInfo(int courseId);
    void viewHomeworksGrades();
    void giveGradeToCourse(int courseId, int grade);
    void enrollInCourse(int courseId);
};

#endif