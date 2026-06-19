# 🎓 Student Management System

A foundational Data Structures project implementing a robust student record organizer using dynamic memory allocation and linear data structures. This application handles basic student database workflows entirely within volatile memory using pointer chains.

## 🛠️ Tech Stack & Core Concepts
* **Language:** C (C99 Standard)
* **Data Structure:** Singly Linked List
* **Memory Management:** Dynamic Memory Allocation (`malloc`, `free`)

## 💡 Core Features
* **Dynamic Node Allocation:** Seamlessly adds student profiles (Roll No, Name, Marks) into an active runtime Linked List without arbitrary array limits.
* **Linear Search & Update:** Traverses structured memory addresses via pointers to update marks or search for specific entities.
* **Pointer Manipulation:** Safely handles head and middle pointer unlinking during record deletions.
* **Memory Leak Prevention:** Includes an explicit structural cleanup routine (`freeAllStudents`) to safely release heap fragments back to the OS before graceful application shutdown.

---

## 🚀 How to Run Locally

Since this project runs directly as a standalone C application, no heavy installation steps are required. 

### 1. Prerequisite
Ensure you have a standard C compiler installed (such as GCC, Clang, or MinGW for Windows).

### 2. Compilation

Open your terminal inside this project directory and compile the program:

```cmd

gcc main.c -o Optimal_Library_Book_Arrangement_System

```

### 2. Execution

Run the compiled execution program: <br> Windows: 

```dos

Optimal_Library_Book_Arrangement_System.exe

```
Mac / Linux:

```Bash

./Optimal_Library_Book_Arrangement_System

```

