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
  //  static Admin admin(1, "admin", "admin@gmail.com", "admin");
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
                try {
                    Admin admin = Admin::loginAdmin(email, password);
                    displayAdminMenu(admin);
                } catch (const std::exception& e) {
                    cout << "Error: " << e.what() << endl;
                    system("pause");
                }
            }
            else if(userRole == "teacher") {
                try {
                    Teacher teacher = Teacher::loginTeacher(email, password);
                    displayTeacherMenu(teacher);
                } catch (const std::exception& e) {
                    cout << "Error: " << e.what() << endl;
                    system("pause");
                }
            }
            else if(userRole == "student") {
                try {
                    Student student = Student::loginStudent(email, password);
                    displayStudentMenu(student);
                } catch (const std::exception& e) {
                    cout << "Error: " << e.what() << endl;
                    system("pause");
                }
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
        system("cls");
        cout << "\n=== Teacher Menu ===" << endl;
        cout << "1. View My Courses" << endl;
        cout << "2. Add Homework" << endl;
        cout << "3. Grade Homework" << endl;
        cout << "4. Create Course" << endl;
        cout << "5. Change Password" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        switch(choice) {
            case 1: {
                while(true) {
                    system("cls");
                    cout << "\n=== Course Management ===" << endl;
                    teacher.viewCourses();
                    
                    cout << "\nOptions:" << endl;
                    cout << "1. Make an Announcement" << endl;
                    cout << "2. Manage Student Grades" << endl;
                    cout << "3. Return to Main Menu" << endl;
                    cout << "\nEnter course ID (0 to return): ";
                    
                    int courseId;
                    cin >> courseId;
                    
                    if(courseId == 0) {
                        system("cls");
                        break;
                    }
                    
                    cout << "Select option (1-3): ";
                    int option;
                    cin >> option;
                    
                    switch(option) {
                        case 1: {
                            system("cls");
                            cout << "\n=== Make Announcement ===" << endl;
                            cout << "Enter announcement (end with Enter):" << endl;
                            cin.ignore();
                            string announcement;
                            getline(cin, announcement);
                            
                            teacher.addAnnouncment(courseId, announcement);
                            cout << "\nAnnouncement added successfully!" << endl;
                            system("pause");
                            break;
                        }
                        case 2: {
                            system("cls");
                            cout << "\n=== Student Grade Management ===" << endl;
                            teacher.viewEnrolledStudents(courseId);
                            
                            cout << "\nEnter student ID (0 to cancel): ";
                            int studentId;
                            cin >> studentId;
                            
                            if(studentId != 0) {
                                cout << "Enter grade (0-20): ";
                                int grade;
                                cin >> grade;
                                
                                if(grade >= 0 && grade <= 20) {
                                    teacher.enterGrade(studentId, courseId, grade);
                                    cout << "\nGrade entered successfully!" << endl;
                                } else {
                                    cout << "\nInvalid grade! Must be between 0-20" << endl;
                                }
                            }
                            system("pause");
                            break;
                        }
                        case 3:
                            system("cls");
                            break;
                        default:
                            cout << "\nInvalid option!" << endl;
                            system("pause");
                    }
                }
                break;
            }
            case 2: {
                int courseId;
                string homework;
                
                cout << "\n=== Add Homework ===" << endl;
                cout << "Enter course ID: ";
                cin >> courseId;
                
                cin.ignore(); // Clear input buffer
                cout << "Enter homework description: ";
                getline(cin, homework);
                
                teacher.addHomework(courseId, homework);
                break;
            }
            case 3: {
                int courseId, studentId, homeworkId, grade;
                cout << "\n=== Grade Homework ===" << endl;
                cout << "Enter course ID: ";
                cin >> courseId;
                cout << "Enter homework ID: ";
                cin >> homeworkId;
                cout << "Enter student ID: ";
                cin >> studentId;
                cout << "Enter grade (0-20): ";
                cin >> grade;
                
                if(grade >= 0 && grade <= 20) {
                    teacher.addHomeworkGrades(homeworkId, courseId, studentId, grade);
                } else {
                    cout << "\nInvalid grade! Must be between 0-20" << endl;
                }
                system("pause");
                break;
            }
            case 4: {
                string title, startTime;
                int capacity, vahed;
                
                cout << "\n=== Create Course ===" << endl;
                cout << "Enter course title: ";
                cin.ignore();
                getline(cin, title);
                
                cout << "Enter capacity: ";
                cin >> capacity;
                
                cout << "Enter start time (e.g., 9:00 AM): ";
                cin.ignore();
                getline(cin, startTime);
                
                cout << "Enter vahed (units): ";
                cin >> vahed;
                
                teacher.createCourse(title, capacity, startTime, vahed);
                system("pause");
                break;
            }
            case 5: {
                string oldPassword, newPassword;
                cout << "\n=== Change Password ===" << endl;
                cout << "Enter old password: ";
                cin >> oldPassword;
                cout << "Enter new password: ";
                cin >> newPassword;
                
                teacher.changePassword(oldPassword, newPassword);
                system("pause");
                break;
            }
            case 6: {
                if(teacher.logout()) {
                    return;  // Return to main loop which will show login screen
                }
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
                system("pause");
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
