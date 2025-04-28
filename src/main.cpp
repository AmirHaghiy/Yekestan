#include <iostream>
#include <string>
#include <limits>
#include <windows.h>
#include "../include/course.h"
#include "../include/enrollment.h"
#include "../include/grade.h"
#include "../include/homework.h"
#include "../include/user.h"

using namespace std;

// Color constants for Telegram theme
#define COLOR_WHITE 15    // Bright white
#define COLOR_GRAY 8     // Gray
#define COLOR_BLUE 9     // Blue
#define COLOR_LIGHTBLUE 11 // Light blue
#define COLOR_DEFAULT 7  // Light gray (default)

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printBanner(const string& text) {
    setColor(COLOR_LIGHTBLUE);
    cout << "\n+=" << string(44, '=') << "=+" << endl;
    cout << "| " << string(21, ' ') << text << string(21 - text.length(), ' ') << " |" << endl;
    cout << "+=" << string(44, '=') << "=+\n" << endl;
    setColor(COLOR_DEFAULT);
}

void printSubBanner(const string& text) {
    setColor(COLOR_LIGHTBLUE);
    cout << "\n+-" << string(48, '-') << "-+" << endl;
    cout << "| " << string(21, ' ') << text << string(21 - text.length(), ' ') << " |" << endl;
    cout << "+-" << string(48, '-') << "-+\n" << endl;
    setColor(COLOR_DEFAULT);
}

void printFooter() {
    setColor(COLOR_LIGHTBLUE);
    cout << "\n+-" << string(48, '-') << "-+" << endl;
    cout << "| " << string(15, ' ') << "© 2025 Yekestan LMS" << string(15, ' ') << " |" << endl;
    cout << "+-" << string(48, '-') << "-+" << endl;
    setColor(COLOR_DEFAULT);
}

void displayAdminMenu(Admin admin);
void displayStudentMenu(Student student);
void displayTeacherMenu(Teacher teacher);
int getValidInput(int min, int max);

int main() {
    string userRole;
    bool running = true;
    
    while(running) {
        system("cls");
        printBanner("Welcome to Yekestan");
        cout << "\nSelect your role:" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Student" << endl;
        cout << "4. Exit" << endl;
        cout << "\nEnter your choice (1-4): ";
        printFooter();
        
        int roleChoice = getValidInput(1, 4);
        
        if(roleChoice == 4) {
            break;
        }

        system("cls");
        printBanner("Login");
        cout << "Enter your Email: ";
        string email;
        cin >> email;
        
        cout << "Enter your PASSWORD: ";
        string password;
        cin >> password;
        
        try {
            switch(roleChoice) {
                case 1: {
                    Admin admin = Admin::loginAdmin(email, password);
                    displayAdminMenu(admin);
                    break;
                }
                case 2: {
                    Teacher teacher = Teacher::loginTeacher(email, password);
                    displayTeacherMenu(teacher);
                    break;
                }
                case 3: {
                    Student student = Student::loginStudent(email, password);
                    displayStudentMenu(student);
                    break;
                }
            }
        } catch (const std::exception& e) {
            cout << "\nError: " << e.what() << endl;
            system("pause");
        }
    }
    
    system("cls");
    printBanner("Goodbye!");
    cout << "Thank you for using Yekestan LMS" << endl;
    printFooter();
    system("pause");
    return 0;
}

int getValidInput(int min, int max) {
    int choice;
    while(!(cin >> choice) || choice < min || choice > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
    return choice;
}

void displayAdminMenu(Admin admin) {
    while(true) {
        system("cls");
        printBanner("Admin Dashboard");
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
        
        int choice = getValidInput(1, 8);
        
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
                system("pause");
                break;

            case 2:
                cout << "Enter the name of user you want to read: ";
                cin >> name;
                admin.viewUser(name);
                system("pause");
                break;

            case 3: {
                cout << "Enter user ID to update: ";
                int userId = getValidInput(1, 999);
                cin.ignore();
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "Enter new email: ";
                getline(cin, email);
                cout << "Enter new role (admin/teacher/student): ";
                getline(cin, role);
                admin.updateUser(userId, name, email, role);
                system("pause");
                break;
            }

            case 4:
                cout << "Enter user ID to delete: ";
                userId = getValidInput(1, 999);
                admin.deleteUser(userId);
                system("pause");
                break;

            case 5:
                admin.generateCourseReport();
                system("pause");
                break;

            case 6:
                cout << "Enter user ID to restore: ";
                userId = getValidInput(1, 999);
                admin.restorUser(userId);
                system("pause");
                break;

            case 7:
                admin.restorAllUsers();
                system("pause");
                break;

            case 8:
                if(admin.logout()) {
                    return;
                }
                break;

            default:
                cout << "Invalid choice!" << endl;
                system("pause");
        }
        
        printFooter();
    }
}

void displayTeacherMenu(Teacher teacher) {
    while(true) {
        system("cls");
        printBanner("Teacher Dashboard");
        cout << "\n=== Teacher Menu ===" << endl;
        cout << "1. View My Courses" << endl;
        cout << "2. Add Homework" << endl;
        cout << "3. Grade Homework" << endl;
        cout << "4. Create Course" << endl;
        cout << "5. Change Password" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        
        int choice = getValidInput(1, 6);
        
        switch(choice) {
            case 1: {
                while(true) {
                    system("cls");
                    printSubBanner("Course Management");
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
                    int option = getValidInput(1, 3);
                    
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
                            printSubBanner("Grade Management");
                            cout << "\n=== Student Grade Management ===" << endl;
                            teacher.viewEnrolledStudents(courseId);
                            
                            cout << "\nEnter student ID (0 to cancel): ";
                            int studentId;
                            cin >> studentId;
                            
                            if(studentId != 0) {
                                cout << "Enter grade (0-20): ";
                                int grade = getValidInput(0, 20);
                                
                                teacher.enterGrade(studentId, courseId, grade);
                                cout << "\nGrade entered successfully!" << endl;
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
                system("cls");
                printSubBanner("Homework Management");
                cout << "Enter course ID: ";
                cin >> courseId;
                
                cin.ignore();
                cout << "Enter homework description: ";
                getline(cin, homework);
                
                teacher.addHomework(courseId, homework);
                system("pause");
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
                grade = getValidInput(0, 20);
                
                teacher.addHomeworkGrades(homeworkId, courseId, studentId, grade);
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
                    return;
                }
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
                system("pause");
        }
        
        printFooter();
    }
}

void displayStudentMenu(Student student) {
    while(true) {
        system("cls");
        printBanner("Student Dashboard");
        cout << "\n=== Student Menu ===" << endl;
        cout << "1. View My Courses" << endl;
        cout << "2. View Available Courses" << endl;
        cout << "3. View Homeworks" << endl;
        cout << "4. View Homework Grades" << endl;
        cout << "5. Rate Course" << endl;
        cout << "6. Change Password" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        
        int choice = getValidInput(1, 7);
        
        switch(choice) {
            case 1: {
                while(true) {
                    system("cls");
                    cout << "\n=== My Courses ===" << endl;
                    student.viewEnrolledCourses();
                    
                    cout << "\nEnter course ID for details (0 to return): ";
                    int courseId;
                    cin >> courseId;
                    
                    if(courseId == 0) {
                        break;
                    }
                    
                    system("cls");
                    student.courseInfo(courseId);
                    system("pause");
                }
                break;
            }
            
            case 2: {
                while(true) {
                    system("cls");
                    cout << "\n=== Available Courses ===" << endl;
                    student.viewAvailableCourses();
                    
                    cout << "\nOptions:" << endl;
                    cout << "1. Enroll in Course" << endl;
                    cout << "2. Return to Main Menu" << endl;
                    cout << "\nEnter option (1-2): ";
                    
                    int option = getValidInput(1, 2);
                    
                    if(option == 1) {
                        cout << "Enter course ID to enroll (0 to cancel): ";
                        int courseId;
                        cin >> courseId;
                        
                        if(courseId != 0) {
                            student.enrollInCourse(courseId);
                        }
                    } else if(option == 2) {
                        break;
                    }
                    system("pause");
                }
                break;
            }
            
            case 3: {
                while(true) {
                    system("cls");
                    cout << "\n=== My Homeworks ===" << endl;
                    student.viewHomeworks();
                    
                    cout << "\nOptions:" << endl;
                    cout << "1. Submit Homework" << endl;
                    cout << "2. Return to Main Menu" << endl;
                    cout << "\nEnter option (1-2): ";
                    
                    int option = getValidInput(1, 2);
                    
                    if(option == 1) {
                        cout << "Enter course ID: ";
                        int courseId;
                        cin >> courseId;
                        
                        cout << "Enter homework ID: ";
                        int homeworkId;
                        cin >> homeworkId;
                        
                        cout << "Enter your submission: ";
                        cin.ignore();
                        string submission;
                        getline(cin, submission);
                        
                        student.submitHomework(courseId, homeworkId, submission);
                    } else if(option == 2) {
                        break;
                    }
                    system("pause");
                }
                break;
            }
            
            case 4: {
                system("cls");
                cout << "\n=== Homework Grades ===" << endl;
                student.viewHomeworksGrades();
                system("pause");
                break;
            }
            
            case 5: {
                system("cls");
                cout << "\n=== Rate Course ===" << endl;
                student.viewEnrolledCourses();
                
                cout << "\nEnter course ID to rate (0 to cancel): ";
                int courseId;
                cin >> courseId;
                
                if(courseId != 0) {
                    cout << "Enter rating (1-5): ";
                    int rating = getValidInput(1, 5);
                    
                    student.giveGradeToCourse(courseId, rating);
                }
                system("pause");
                break;
            }
            
            case 6: {
                string oldPassword, newPassword;
                cout << "\n=== Change Password ===" << endl;
                cout << "Enter old password: ";
                cin >> oldPassword;
                cout << "Enter new password: ";
                cin >> newPassword;
                
                student.changePassword(oldPassword, newPassword);
                system("pause");
                break;
            }
            
            case 7: {
                if(student.logout()) {
                    return;
                }
                break;
            }
            
            default:
                cout << "Invalid choice!" << endl;
                system("pause");
        }
        
        printFooter();
    }
}
