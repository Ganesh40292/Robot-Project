# 🤖 Interactive 3D Robot

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-OpenGL-blue?style=for-the-badge&logo=c%2B%2B" alt="C++ OpenGL">
  <img src="https://img.shields.io/badge/GLUT-Graphics-orange?style=for-the-badge" alt="GLUT">
  <img src="https://img.shields.io/badge/Code%3A%3ABlocks-IDE-brightgreen?style=for-the-badge" alt="Code::Blocks">
</p>

<p align="center">
  An interactive 3D robot built using <b>C++ and OpenGL</b>, featuring real-time movement, camera controls, individual limb manipulation, lighting, and walking animation.
</p>

---

## 📌 About

This project is a **3D Interactive Robot simulation** developed using C++ and OpenGL as a Computer Graphics project.

The robot is constructed using basic OpenGL/GLUT primitives such as cubes, spheres, and cylinders. It demonstrates fundamental 3D graphics concepts including **transformations, hierarchical modeling, camera control, lighting, user interaction, and procedural animation**.

---

## ✨ Features

* 🤖 Interactive 3D robot model
* 🎮 Keyboard-controlled robot movement
* 🦾 Individual arm and leg controls
* 🔄 Rotation and transformation along X, Y and Z axes
* 🚶 Procedural walking animation
* 🎥 Interactive 3D camera
* 🖱️ Mouse-based robot and camera rotation
* 💡 OpenGL lighting and depth testing
* 🌍 3D ground plane and grid environment
* 🔁 Robot position and rotation reset

---

## 🎮 Controls

| Key                   | Action                       |
| --------------------- | ---------------------------- |
| `W / S`               | Move Up / Down               |
| `A / D`               | Move Left / Right            |
| `Z / X`               | Move Forward / Backward      |
| `Q / E`               | Rotate Left / Right          |
| `R / F`               | Tilt Backward / Forward      |
| `T / G`               | Roll Left / Right            |
| `1 / 2`               | Left Arm Up / Down           |
| `3 / 4`               | Right Arm Up / Down          |
| `5 / 6`               | Left Leg Forward / Backward  |
| `7 / 8`               | Right Leg Forward / Backward |
| `9 / 0`               | Head Right / Left            |
| `Arrow Keys`          | Control Camera               |
| `Page Up / Page Down` | Zoom In / Out                |
| `Space`               | Toggle Walking Animation     |
| `C`                   | Reset Robot                  |
| `ESC`                 | Exit                         |

### 🖱️ Mouse

* **Left-click + Drag** → Rotate the robot
* **Right-click + Drag** → Rotate the camera

---

## 🛠️ Technologies Used

* **C++**
* **OpenGL**
* **GLUT / FreeGLUT**
* **GLU**
* **MinGW / GCC**
* **Code::Blocks**

---

## 🧠 Concepts Demonstrated

This project demonstrates:

* 3D transformations
* Translation, rotation and scaling
* Hierarchical modeling
* Perspective projection
* Camera positioning using `gluLookAt()`
* OpenGL lighting
* Depth buffering
* Keyboard and mouse interaction
* Procedural animation using trigonometric functions
* OpenGL matrix stack using `glPushMatrix()` and `glPopMatrix()`

---

## 📂 Project Structure

```text
Robot-Project/
│
└── Robot/
    ├── main.cpp
    ├── Robot.cbp
    ├── bin/
    │   └── Debug/
    │       └── Robot.exe
    └── obj/
        └── Debug/
            └── main.o
```

---

## 🚀 How to Run

### 1. Clone the repository

```bash
git clone <your-repository-url>
cd Robot-Project
```

### 2. Open the project

Open:

```text
Robot/Robot.cbp
```

using **Code::Blocks** with MinGW configured.

### 3. Build & Run

Build the project and run the generated executable.

> **Note:** The original Code::Blocks project contains Windows-specific MinGW/library paths. These may need to be updated depending on your local installation.

---

## 🎓 Project Information

**Project:** Interactive 3D Robot
**Language:** C++
**Graphics API:** OpenGL
**Toolkit:** GLUT / FreeGLUT
**Platform:** Windows
**Type:** Computer Graphics Project

---

## 👨‍💻 Author

**Ganesh Prasad**

Computer Science & Engineering Student

---

## 🙏 Credits

This repository is **forked from [Vijeth737](https://github.com/Vijeth737)**.

The project has been explored, customized, and maintained for learning and academic purposes.

---

<p align="center">
  ⭐ If you found this project interesting, consider starring the repository!
</p>
