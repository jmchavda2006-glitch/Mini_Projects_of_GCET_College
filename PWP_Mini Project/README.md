# 🪪 Automated Student ID Card Generating System

A practical web platform that automates institutional asset generation. Students can fill out a dynamic web form with their profile details and portrait images, and the system instantly maps the data onto a template to produce a crisp, download-ready student identification card.

---

## 🛠️ Tech Stack & Frameworks

* **Backend Framework:** Python (Django)
* **Frontend:** HTML5, CSS3, JavaScript
* **Image Processing Engine:** Pillow (PIL)
* **Database:** SQLite3 (Local development)

---

## 💡 Core Features

* **Dynamic Media Composition:** Blends uploaded user portraits cleanly into target identification badge layouts.
* **Canvas Coordinates Mapping:** Programs absolute pixel locations onto a preset background identity card template grid.
* **Responsive Data Form:** Captures vital fields (Full Name, Registration Number, Course Path) with clean validation constraints.
* **Administrative Control Panel:** Built-in Django admin backend to manage submitted records, templates, and user logs.

---

## 🚀 Local Setup & Installation Guide

Follow these sequential steps to set up the development environment and run this project locally on your machine.

### 1. Prerequisites

Ensure you have Python installed on your system. Open your terminal or command prompt inside the project's root directory (where `manage.py` is located).

### 2. Activate the Virtual Environment (`venv`)

Turn on the pre-configured isolated environment so your terminal can access the project dependencies. Run the command that matches your operating system/terminal terminal type:

* **Windows (Command Prompt):**
```cmd
venv\Scripts\activate

```



```
* **Windows (PowerShell):**
  ```powershell
  .\venv\Scripts\activate

```

* **Mac / Linux:**
```bash

```



source venv/bin/activate

```
*(Once activated, you will see `(venv)` appear at the very beginning of your terminal command line).*

### 3. Install Dependencies
If you are setting this up fresh or ensuring packages are updated, install the required libraries:
```bash
pip install -r requirements.txt

```

*(Note: If you don't have a requirements file yet, you can generate it using `pip freeze > requirements.txt` while your environment is active).*

### 4. Apply Database Migrations

Initialize the local SQLite database schema configurations by running:

```bash
python manage.py migrate

```

### 5. Create an Administrative Account (Superuser)

To access the Django backend control panel (`/admin`), you must generate a local admin profile. Run the following command and follow the terminal prompts:

```bash
python manage.py createsuperuser

```

*Input your desired username, email, and choose a password. Note: The password characters will remain completely hidden in the terminal while typing for safety.*

### 6. Start the Development Server

Fire up the local host loop using:

```bash
python manage.py runserver

```

Once executed successfully, open your web browser and navigate to:

* **Web App Frontend:** `[http://127.0.0.1:8000/](http://127.0.0.1:8000/)`
* **Django Admin Backend:** `[http://127.0.0.1:8000/admin/](http://127.0.0.1:8000/admin/)`

---
