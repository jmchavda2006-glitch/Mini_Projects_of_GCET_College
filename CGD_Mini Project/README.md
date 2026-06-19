# 🚀 2D Retro Space Shooting Game

An interactive, high-performance 2D retro arcade-style game built to explore real-time graphics rendering loops, viewport coordinate mapping, and continuous keyboard input tracking.

## 🛠️ Tech Stack & Core Concepts
* **Language:** C (C99 Standard)
* **Graphics API:** OpenGL / GLUT (FreeGLUT wrapper)
* **Mathematical Utilities:** Absolute coordinate boundary calculations (`fabs`)

## 💡 Core Features
* **Dynamic Particle Pipeline:** Renders an animated space field of 100 independent stars running at variable speed states to mimic vertical parallax depth.
* **Fluid Animation Loops:** Uses persistent OpenGL interval timers (16ms refresh caps targeting a responsive ~60 FPS environment).
* **Advanced Trail Renderers:** Projectiles trace custom multi-quad alpha gradient trails mapped directly to their historical coordinate paths.
* **Algorithmic Tweaks:** Features a randomized, scaling difficulty slider (`enemySpeed`) that increases velocity variables every time an active enemy is struck.

---

## ⚙️ Environment & OpenGL Setup Guide

Before compiling the game on Windows, you must download and configure the **FreeGLUT** development libraries to give your C compiler access to OpenGL headers.

### Step 1: Download FreeGLUT
1. Go to the official Transmission Zero directory: [FreeGLUT Windows Development Packages](https://www.transmissionzero.co.uk/software/freeglut-devel/)
2. Under the MSVC section, download the **"freeglut MSVC development package"** zip archive.

### Step 2: Extract and Move Files to MinGW/GCC
Extract the downloaded zip archive. You need to copy specific files into your local MinGW C compiler environment folder (usually located at `C:\MinGW\` or `C:\msys64\`):

1. **Include Headers:** Go to `freeglut\include\GL\` $\rightarrow$ Copy all `.h` files $\rightarrow$ Paste them into `C:\MinGW\include\GL\`
2. **Library Linkers:** Go to `freeglut\lib\` $\rightarrow$ Copy all `.a` / `.lib` files $\rightarrow$ Paste them into `C:\MinGW\lib\`
3. **System Runtime:** Go to `freeglut\bin\` $\rightarrow$ Copy the **`freeglut.dll`** file $\rightarrow$ Paste it into your Windows system directory `C:\Windows\System32\` (or keep it directly inside the same folder as your game's source code file).

---

## 🚀 How to Run Locally

Once your environment paths have OpenGL development headers mapped, you can build and launch the game directly from the command line.

### 1. Prerequisite
Ensure your terminal paths can access your configured C compiler workspace.

### 2. Compilation

Open your terminal inside this project directory and compile the program:

```cmd
gcc space_game.c -o space_game.exe -lfreeglut -lglu32 -lopengl32

```

### 3. Execution

Run the compiled execution program: 



 Windows:

```dos
space_game.exe

```

---

## 🎯 Connect & Collaborate

* **LinkedIn:** [Jigar Chavda](linkedin.com/in/jigar-chavda-6b8322281)

---

### 👨‍💻 Maintained By

**Jigar Chavda** *Undergraduate Student, Computer Science and Design (2023–2027) under Department of Computer Engineering* 




**G H Patel College of Engineering and Technology (GCET)**

---
