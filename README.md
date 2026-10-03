# 🏠 CampusNest – Smart Hostel Management System

<p align="center">
  <strong>A Console-Based Smart Hostel Management System developed using C</strong>
</p>

<p align="center">
  IN1101 – Programming Fundamentals | 1st Year | 1st Semester
</p>

---

## 📌 About the Project

**CampusNest** is a console-based Smart Hostel Management System developed as a group project for **IN1101 – Programming Fundamentals**.

The project was created during our **1st Year, 1st Semester** of Computer Science to apply fundamental C programming concepts to a practical software application.

CampusNest provides a menu-driven system for managing different areas of hostel operations, including students, rooms, fees, visitors, and maintenance requests.

---

## 🎯 Project Objectives

The main objectives of CampusNest are to:

* Apply fundamental C programming concepts to a practical application.
* Develop a structured, menu-driven console application.
* Manage student and hostel-related records.
* Manage room information and availability.
* Record and track hostel fee information.
* Manage visitor records.
* Handle maintenance requests.
* Implement searching and sorting operations.
* Practice input validation and error handling.
* Develop teamwork and collaborative programming skills.
* Gain experience presenting and explaining a software project.

---

# ⚙️ System Modules

CampusNest consists of **five main management modules**.

## 👨‍🎓 1. Student Management

The Student Management module provides functionality for managing student records.

### Features

* Student registration
* View all student records
* Search students by ID
* Search students by name
* Update student room information
* Delete student records
* Sort student records by ID
* Validate student information

---

## 🏠 2. Room Management

The Room Management module handles hostel room-related information.

### Features

* Add room records
* View room information
* Search rooms
* Track room availability
* Update room status
* Manage room-related information
* Sort room records
* Delete room records
* Manage room allocation-related information

---

## 💰 3. Fee Management

The Fee Management module handles hostel fee records and payment information.

### Features

* Record fee information
* View fee records
* Search fees by student
* Update payment status
* Generate fee summaries
* Sort fee records by amount
* Validate student IDs and fee amounts

---

## 👥 4. Visitor Management

The Visitor Management module manages visitor records associated with hostel students.

### Features

* Register visitors
* View visitor records
* Search visitors by student
* Generate visitor count reports
* Sort visitor records by date
* Delete visitor records
* Validate visitor information

---

## 🔧 5. Maintenance Management

The Maintenance Management module handles hostel maintenance requests.

### Features

* Add maintenance requests
* View maintenance requests
* Update request status
* Search requests by room
* Manage request priorities
* Generate maintenance summaries
* Sort requests by priority
* Delete maintenance requests

---

# 🛠️ Technologies & Concepts

## Programming Language

* **C**

## Programming Concepts Used

* Structures
* Arrays
* Functions
* Pointers
* Strings
* Character handling
* Input validation
* Searching
* Sorting
* Modular programming
* Menu-driven programming
* Data validation
* Function-based program organization

## Algorithms & Techniques

* Linear searching
* Bubble sorting
* String comparison
* Input validation
* Record management using arrays of structures

---

# 🖥️ Application Interface

CampusNest is a **console-based application** operated through a menu-driven interface.

## Main Menu

![Main Menu](docs/screenshots/01-main-menu.png)

## Student Management

![Student Management](docs/screenshots/02-student-management.png)

## Room Management

![Room Management](docs/screenshots/03-room-management.png)

## Fee Management

![Fee Management](docs/screenshots/04-fee-management.png)

## Visitor Management

![Visitor Management](docs/screenshots/05-visitor-management.png)

## Maintenance Management

![Maintenance Management](docs/screenshots/06-maintenance-management.png)

---

# 👨‍💻 My Contribution

I worked as the **Group Leader** and was responsible for developing the **Room Management module**.

### My responsibilities included:

* Room record management
* Room allocation-related functionality
* Room availability tracking
* Room status updates
* Room searching
* Room sorting
* Room-related data validation
* Supporting the integration of individual modules into the final application
* Coordinating the team during the project development process

---

# 👥 Team Members

| Team Member          | Responsibility                     |
| -------------------- | ---------------------------------- |
| **Perera O. S. G**   | **Room Management / Group Leader** |
| **Perera M. I. P**   | Student Management                 |
| **Perera P.B.H.N.S** | Fee Management                     |
| **Perera P.S.K**     | Visitor Management                 |
| **Perera R.K.O.C**   | Maintenance Management             |

---

# 🎓 Academic Information

| Category                 | Details                           |
| ------------------------ | --------------------------------- |
| **Course**               | IN1101 – Programming Fundamentals |
| **Year**                 | 1st Year                          |
| **Semester**             | 1st Semester                      |
| **Project Type**         | Group Assignment                  |
| **Programming Language** | C                                 |
| **Application Type**     | Console Application               |
| **Project Status**       | Completed                         |

After completing the development phase, our team also participated in a **project presentation and viva**, where we demonstrated the system and explained our implementation.

---

# 🚀 Getting Started

## Prerequisites

To compile and run CampusNest, you need:

* A C compiler
* GCC recommended
* A terminal or command prompt

You can use environments such as:

* GCC
* MinGW
* Code::Blocks
* Visual Studio Code with a C compiler
* Other C development environments

---

## 📥 Clone the Repository

Clone the repository using:

```bash
git clone https://github.com/YOUR-USERNAME/CampusNest-Smart-Hostel-Management-System.git
```

Navigate into the project directory:

```bash
cd CampusNest-Smart-Hostel-Management-System
```

---

# 🔨 Compilation

Navigate to the `src` directory:

```bash
cd src
```

Compile the program using GCC:

```bash
gcc campusnest.c -o campusnest
```

---

# ▶️ Running the Application

## Windows

```bash
campusnest.exe
```

## Linux / macOS

```bash
./campusnest
```

---

# 📂 Project Structure

```text
CampusNest-Smart-Hostel-Management-System/
│
├── 📁 assets/
│   └── campusnest-banner.png
│
├── 📁 docs/
│   ├── project-report.pdf
│   ├── presentation.pdf
│   │
│   └── 📁 screenshots/
│       ├── 01-main-menu.png
│       ├── 02-student-management.png
│       ├── 03-room-management.png
│       ├── 04-fee-management.png
│       ├── 05-visitor-management.png
│       └── 06-maintenance-management.png
│
├── 📁 src/
│   └── campusnest.c
│
├── .gitignore
└── README.md
```

> **Note:** Documentation files such as the project report and presentation should only be included if public sharing is permitted by the university/course.

---

# 📚 Learning Outcomes

This project provided practical experience in applying programming fundamentals to a complete software application.

Through the development of CampusNest, we gained experience with:

* Applying C programming fundamentals
* Working with structures and arrays
* Creating reusable functions
* Using pointers
* Handling strings
* Validating user input
* Implementing searching operations
* Implementing sorting operations
* Debugging and testing
* Integrating multiple modules
* Working as a team
* Presenting and explaining software functionality

---

# 🧪 Testing

The application was tested through different user-input scenarios during development.

Testing included:

* Valid and invalid numeric input
* Empty input validation
* Student record operations
* Room record operations
* Fee record operations
* Visitor record operations
* Maintenance request operations
* Search operations
* Sorting operations
* Update operations
* Delete operations
* Menu navigation

The system was also demonstrated during the project presentation and viva.

---

# 🔮 Future Improvements

Although CampusNest was developed as a Programming Fundamentals project, several improvements could be made in future versions.

Possible improvements include:

* 💾 File-based data persistence
* 🗄️ Database integration
* 🔐 User authentication and role management
* 🏠 More automated room allocation and occupancy management
* 📊 Advanced reporting
* 🖥️ Graphical user interface
* 🌐 Web-based version
* 📱 Mobile application
* 🔍 More advanced search and filtering
* 📈 Improved data visualization
* 🛡️ More advanced validation and error handling

---

# 📄 Documentation

Additional project documentation can be found in the `docs/` directory.

Available documentation may include:

* Project report
* Presentation
* Application screenshots

---

# 📌 Project Status

**Completed – Academic Group Project**

CampusNest was developed as part of our **IN1101 – Programming Fundamentals** coursework during the first semester of our Computer Science degree.

---

# 🙏 Acknowledgement

We would like to thank our lecturer for the guidance provided throughout the project and our team members for their collaboration and contribution to the development of CampusNest.

This project provided us with valuable practical experience in applying C programming fundamentals to a complete console-based application.

---

# 👨‍💻 Developed By

### CampusNest Development Team

**Perera O. S. G — Group Leader & Room Management**

**Perera M. I. P — Student Management**

**Perera P.B.H.N.S — Fee Management**

**Perera P.S.K — Visitor Management**

**Perera R.K.O.C — Maintenance Management**

---

⭐ **Thank you for visiting the CampusNest project repository!**
