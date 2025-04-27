#include <iostream>
#include <string>
#include "../include/course.h"
#include "../include/enrollment.h"
#include "../include/grade.h"
#include "../include/homework.h"
#include "../include/user.h"

using namespace std;
void displayAdminMenu(Admin admin);
void displayStudentMenu(Student student);

void displayTeacherMenu(Teacher teacher);

int main() {
    static Admin admin(1, "admin", "admin@gmail.com", "admin");
    static Teacher teacher(2, "teacher", "teacher@gmail.com", "teacher");
    static Student student(3, "student", "student@gmail.com", "student");
    string userRole;
    bool running = true;
    
    while(running) {
        system("cls");
        cout << "=== Welcome to Yekestan Learning Management System ===" << endl;
        cout << "Please login to continue" << endl;
        cout << "Enter your Email: ";
        string email;
        cin >> email;
        cout << "Enter your PASSWORD: ";
        string password;
        cin >> password;
        
        int loggedIn = 0;
        userRole = User::login(email, password, loggedIn);
        
        if(loggedIn) {
            if(userRole == "admin") {
                displayAdminMenu(admin);
            }
            else if(userRole == "teacher") {
                displayTeacherMenu(teacher);
            }
            else if(userRole == "student") {
                displayStudentMenu(student);
            }
        }
    }
    return 0;
}

void displayAdminMenu(Admin admin) {
    while(true) {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. Create User" << endl;
        cout << "2. Read User" << endl;
        cout << "3. Update User" << endl;
        cout << "4. Delete User" << endl;
        cout << "5. View All Courses Report" << endl;
        cout << "6. Restore User" << endl;
        cout << "7. Restore All Users" << endl;
        cout << "8. Logout" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        string name, email, password, role;
        int userId;
        
        switch(choice) {
            case 1:
                cout << "Enter name for user: ";
                cin >> name;
                cout << "\nEnter Email for user: ";
                cin >> email;
                cout << "\nEnter password for user: ";
                cin >> password;
                cout << "\nEnter role for user: ";
                cin >> role;
                admin.createUser(name, email, password, role);
                break;

            case 2:
                cout << "Enter the name of user you want to read: ";
                cin >> name;
                admin.viewUser(name);
                break;

            case 3:
                cout << "Enter user ID to update: ";
                cin >> userId;
                cout << "Enter new name: ";
                cin >> name;
                cout << "Enter new email: ";
                cin >> email;
                cout << "Enter new role: ";
                cin >> role;
                admin.updateUser(userId, name, email, role);
                break;

            case 4:
                cout << "Enter user ID to delete: ";
                cin >> userId;
                admin.deleteUser(userId);
                break;

            case 5:
                admin.generateCourseReport();
                break;

            case 6:
                cout << "Enter user ID to restore: ";
                cin >> userId;
                admin.restorUser(userId);
                break;

            case 7:
                admin.restorAllUsers();
                break;

            case 8:
                if(admin.logout()) {
                    return;  // Return to main loop which will show login screen
                }
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    }
}
void displayTeacherMenu(Teacher teacher) {
    while(true) {
        cout << "\n=== Teacher Menu ===" << endl;
        cout << "1. View My Courses" << endl;
        cout << "2. Add Homework" << endl;
        cout << "3. Grade Homework" << endl;
        cout << "4. View Student Progress" << endl;
        cout << "5. Change Password" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1:
                // View courses implementation
                break;
            case 2:
                // Add homework implementation
                break;
            case 3:
                // Grade homework implementation
                break;
            case 4:
                // View progress implementation
                break;
            case 5:
                // Change password implementation
                break;
            case 6:
                // if(User::logout()) {
                //     return;  // Return to main loop which will show login screen
                // }
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void displayStudentMenu(Student student) {
    while(true) {
        cout << "\n=== Student Menu ===" << endl;
        cout << "1. View My Courses" << endl;
        cout << "2. View Homework" << endl;
        cout << "3. Submit Homework" << endl;
        cout << "4. View Grades" << endl;
        cout << "5. Change Password" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1:
                // View courses implementation
                break;
            case 2:
                // View homework implementation
                break;
            case 3:
                // Submit homework implementation
                break;
            case 4:
                // View grades implementation
                break;
            case 5:
                // Change password implementation
                break;
            case 6:
                // if(User::logout()) {
                //     return;  // Return to main loop which will show login screen
                // }
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}
