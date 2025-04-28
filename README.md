# Yekestan Learning Management System

A modern console-based Learning Management System (LMS) built with C++ that provides separate interfaces for administrators, teachers, and students. Features a Telegram-inspired UI with a clean, professional design.

## 🚀 Features

### 👑 Admin Dashboard
- Create, view, update, and delete users
- Manage system access and permissions
- View comprehensive course reports
- Restore deleted users
- Monitor system activities

### 👨‍🏫 Teacher Dashboard
- Create and manage courses
- Add and grade homework assignments
- Post course announcements
- View enrolled students
- Track student progress
- Manage course materials

### 👨‍🎓 Student Dashboard
- Browse and enroll in available courses
- Submit homework assignments
- View grades and progress
- Rate course experience
- Access course announcements
- Track enrolled courses

## 💻 Technical Details

### Prerequisites
- C++ 17 or higher
- nlohmann/json library
- Windows OS (for console colors)
- Visual Studio Code (recommended IDE)

### Project Structure
```
Yekestan/
├── src/
│   ├── main.cpp          # Main program logic
│   ├── admin.cpp         # Admin functionality
│   ├── teacher.cpp       # Teacher functionality
│   └── student.cpp       # Student functionality
├── include/
│   ├── user.h           # User class definitions
│   ├── course.h         # Course management
│   ├── homework.h       # Homework handling
│   ├── grade.h          # Grading system
│   └── enrollment.h     # Enrollment management
└── data/
    ├── users.json       # User database
    ├── courses.json     # Course information
    ├── homeworks.json   # Homework assignments
    ├── grades.json      # Student grades
    └── enrollments.json # Course enrollments
```

## 🛠️ Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/yekestan-lms.git
```

2. Install dependencies:
```bash
# Include nlohmann/json
vcpkg install nlohmann-json:x64-windows
```

3. Build the project:
```bash
cd yekestan-lms
g++ src/*.cpp -o yekestan.exe -std=c++17
```

## 🎮 Usage

Run the executable:
```bash
./yekestan.exe
```

Default login credentials:
- Admin: admin@gmail.com / admin
- Teacher: teacher@gmail.com / teacher
- Student: student@gmail.com / student

## 🎨 UI Features
- Telegram-inspired color scheme
- Clean and intuitive interface
- Professional banner design
- Color-coded menus
- Easy navigation

## 📝 License
This project is licensed under the MIT License - see the LICENSE file for details

## 🤝 Contributing
Contributions, issues, and feature requests are welcome! Feel free to check [issues page](https://github.com/yourusername/yekestan-lms/issues).

## 👥 Authors
- **Your Name** - *Initial work* - [YourGithub](https://github.com/yourusername)

## 🙏 Acknowledgments
- nlohmann/json library for JSON handling
- Telegram for UI inspiration
