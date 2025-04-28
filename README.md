# 🎓 Yekestan Learning Management System (LMS)

A modern, console-based Learning Management System developed in C++ for Isfahan University of Technology. Features a clean, Telegram-inspired interface and comprehensive functionality for administrators, teachers, and students.

## ✨ Features

### 👑 Admin Portal
- Complete user management (CRUD operations)
- Course report generation
- User restoration system
- Access control management
- System monitoring

### 👨‍🏫 Teacher Portal
- Course creation and management
- Homework assignment and grading
- Course announcements
- Student grade management
- Course roster viewing

### 👨‍🎓 Student Portal
- Course enrollment system
- Homework submission
- Grade viewing
- Course rating system
- Course announcement viewing

## 🛠️ Technical Stack

- **Language**: C++ 17
- **Data Storage**: JSON
- **UI**: Console-based with colored interface
- **Architecture**: Object-Oriented Design
- **Platform**: Windows

## 📁 Project Structure

```
Yekestan/
├── src/
│   ├── main.cpp          # Program entry point
│   ├── admin.cpp         # Admin functionality
│   ├── teacher.cpp       # Teacher functionality
│   └── student.cpp       # Student functionality
├── include/
│   ├── user.h           # User class definitions
│   ├── course.h         # Course management
│   ├── homework.h       # Homework system
│   ├── grade.h          # Grading system
│   └── enrollment.h     # Enrollment management
└── data/
    ├── users.json       # User data
    ├── courses.json     # Course information
    ├── homework.json    # Homework data
    └── grades.json      # Grade records
```

## 🚀 Getting Started

### Prerequisites
- Windows operating system
- C++ compiler (MinGW or MSVC)
- nlohmann/json library

### Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/yekestan-lms.git
```

2. Navigate to project directory:
```bash
cd yekestan-lms
```

3. Compile the project:
```bash
g++ src/*.cpp -o yekestan.exe -std=c++17
```

### Default Accounts

```
Admin:    admin@gmail.com / admin
Teacher:  ali@gmail.com / 1234
Student:  amir@gmail.com / 1234
```

## 🎨 Interface

- Telegram-inspired color scheme
- Color-coded menus

## 🤝 Contributing

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 🌟 Acknowledgments

- Isfahan University of Technology
- nlohmann/json library
- Telegram for UI inspiration

## 👥 Authors

- **Amir Mahdy Haghi**  - [Your GitHub Profile](https://github.com/AmirHaghiy)

## 📬 Contact

- Project Link:([https://github.com/yourusername/yekestan-lms](https://github.com/AmirHaghiy/Yekestan.git))
- Your Email: a.haghi2006@gmail.com

---
Made with ❤️ at Isfahan University of Technology
