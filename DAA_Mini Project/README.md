# 📚 Optimal Library Book Arrangement System

An intelligent library data manager developed to optimize manual book tracking and search efficiencies. This system maps real-world frequencies to evaluate performance tradeoffs between standard **Greedy Heuristics** and complex **Dynamic Programming (DP)** solutions.

## 🛠️ Tech Stack & Core Concepts
* **Language:** C (C99 Standard)
* **Algorithms:** Bottom-up Dynamic Programming, Greedy Approach, Tree Traversals (In-order), Array Sorting Heuristics
* **Database Layer:** Persistent flat-file logging (`library.txt`)

## 💡 Core Features
* **Optimal Arrangement (DP):** Implements the **Optimal Binary Search Tree (OBST)** concept. It evaluates frequency-weighted node distributions to construct an optimal topological layout that mathematically minimizes the average search cost.
* **Greedy Arrangement:** Applies a classic greedy layout paradigm by sorting active entries strictly based on search counts in descending order ($O(N \log N)$ complexity metrics).
* **Faux Access Transactions:** Simulates check-outs and structural updates, dynamically updating raw access counts on a persistent configuration log (`library.txt`).
* **Persistent Cache Streams:** Integrates native file I/O operations to save and parse library structures across active system runtimes.

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
## 🎯 Connect & Collaborate

* **LinkedIn:** [Jigar Chavda](linkedin.com/in/jigar-chavda-6b8322281)

---

### 👨‍💻 Maintained By
**Jigar Chavda** 
*Undergraduate Student, Computer Science and Design (2023–2027) under Department of Computer Engineering* <br>
**G H Patel College of Engineering and Technology (GCET)** 

