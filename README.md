# 🤖 Interactive 3D Robot using OpenGL & C++

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B" alt="C++">
  <img src="https://img.shields.io/badge/Graphics-OpenGL-red?style=for-the-badge&logo=opengl" alt="OpenGL">
  <img src="https://img.shields.io/badge/Toolkit-GLUT%2FFreeGLUT-orange?style=for-the-badge" alt="GLUT">
  <img src="https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows" alt="Windows">
  <img src="https://img.shields.io/badge/IDE-Code%3A%3ABlocks-brightgreen?style=for-the-badge" alt="Code::Blocks">
</p>

<p align="center">
  <b>An interactive 3D robot built from OpenGL primitives with keyboard controls, mouse interaction, camera manipulation, individual limb control, lighting, and procedural walking animation.</b>
</p>

---

## 📌 Overview

This project is an **interactive 3D robot simulation developed using C++ and OpenGL** as a Computer Graphics project.

Instead of using a pre-built 3D model, the robot is constructed programmatically from basic geometric primitives such as:

* Cubes
* Spheres
* Cylinders

The project demonstrates important concepts from **3D Computer Graphics**, including:

* 3D object modeling
* Hierarchical transformations
* Translation
* Rotation
* Scaling
* Camera positioning
* Perspective projection
* Lighting
* Depth buffering
* Mouse interaction
* Keyboard interaction
* Animation using trigonometric functions
* GLUT event-driven programming

The robot can be moved around the 3D environment, rotated along all three axes, manipulated limb-by-limb, and animated with a procedural walking motion.

---

## ✨ Features

### 🤖 3D Robot Model

The robot is composed of multiple independently rendered components:

* Head
* Torso
* Left arm
* Right arm
* Left leg
* Right leg
* Shoulder joints
* Elbow joints
* Wrist joints
* Hip joints
* Knee joints
* Ankle joints
* Hands
* Fingers
* Feet
* Eyes
* Pupils
* Mouth/control element
* Antenna
* Antenna tip
* Chest control panel
* Chest buttons
* Power indicator

Each body section is created using OpenGL/GLUT primitives and positioned using transformation matrices.

---

### 🎮 Interactive Robot Controls

The robot can be controlled in real time using the keyboard.

#### Whole Robot Rotation

| Key | Action                            |
| --- | --------------------------------- |
| `Q` | Rotate robot left around Y-axis   |
| `E` | Rotate robot right around Y-axis  |
| `R` | Tilt robot backward around X-axis |
| `F` | Tilt robot forward around X-axis  |
| `T` | Roll robot left around Z-axis     |
| `G` | Roll robot right around Z-axis    |

---

### 🧭 Robot Movement

| Key | Action              |
| --- | ------------------- |
| `W` | Move robot upward   |
| `S` | Move robot downward |
| `A` | Move robot left     |
| `D` | Move robot right    |
| `Z` | Move robot forward  |
| `X` | Move robot backward |

The movement is performed by modifying the robot's 3D world coordinates:

```text
robotX
robotY
robotZ
```

---

### 🦾 Individual Limb Controls

Each major limb can be controlled independently.

| Key | Action                  |
| --- | ----------------------- |
| `1` | Move left arm up        |
| `2` | Move left arm down      |
| `3` | Move right arm up       |
| `4` | Move right arm down     |
| `5` | Move left leg forward   |
| `6` | Move left leg backward  |
| `7` | Move right leg forward  |
| `8` | Move right leg backward |
| `9` | Turn head right         |
| `0` | Turn head left          |

This demonstrates **hierarchical modeling and independent joint transformations**.

---

## 🎥 Camera Controls

The project includes a controllable 3D camera.

### Arrow Keys

| Key | Action                         |
| --- | ------------------------------ |
| `↑` | Move camera elevation upward   |
| `↓` | Move camera elevation downward |
| `←` | Rotate camera left             |
| `→` | Rotate camera right            |

### Zoom

| Key         | Action   |
| ----------- | -------- |
| `Page Up`   | Zoom in  |
| `Page Down` | Zoom out |

The camera distance is constrained to prevent excessive zooming:

```text
Minimum distance: 3 units
Maximum distance: 25 units
```

---

## 🖱️ Mouse Controls

The project also supports interactive mouse manipulation.

### Left Mouse + Drag

Rotates the entire robot.

```text
Horizontal drag → Y-axis rotation
Vertical drag   → X-axis rotation
```

### Right Mouse + Drag

Controls the camera.

```text
Horizontal drag → Camera horizontal rotation
Vertical drag   → Camera vertical rotation
```

The vertical camera angle is restricted to a reasonable range to prevent extreme camera positioning.

---

## 🚶 Walking Animation

Press:

```text
SPACEBAR
```

to toggle the automatic walking animation.

The animation is generated mathematically using sine functions rather than using pre-recorded animation frames.

### Animation Components

The animation controls:

* Left arm movement
* Right arm movement
* Left leg movement
* Right leg movement
* Head movement
* Vertical body bobbing

The arms and legs use opposite phases to create a walking-like motion.

Conceptually:

```text
Arm Movement
     ↓
sin(animationTimer)

Leg Movement
     ↓
sin(animationTimer + π)

Head Movement
     ↓
sin(animationTimer × 0.7)

Body Bobbing
     ↓
sin(animationTimer × 2.0)
```

This demonstrates how **trigonometric functions can be used to generate smooth procedural animation**.

---

## 🔄 Reset

Press:

```text
C
```

to reset the robot.

The reset operation restores:

* Robot position
* Robot rotation
* Arm rotations
* Leg rotations
* Head rotation
* Animation timer

to their default values.

---

## ❌ Exit

Press:

```text
ESC
```

to close the application.

---

# 🎨 Robot Design

The robot is created using a combination of basic geometric primitives.

### Head

The head contains:

* Blue spherical body
* White eyes
* Black pupils
* Orange mouth element
* Gray antenna
* Red antenna tip

### Torso

The torso contains:

* Red rectangular body
* Green chest control panel
* Yellow control buttons
* Animated red power indicator

### Arms

Each arm contains:

```text
Shoulder
   ↓
Upper Arm
   ↓
Elbow
   ↓
Forearm
   ↓
Wrist
   ↓
Hand
   ↓
Fingers
```

### Legs

Each leg contains:

```text
Hip
 ↓
Thigh
 ↓
Knee
 ↓
Shin
 ↓
Ankle
 ↓
Foot
 ↓
Toe Detail
```

This structure allows the robot to behave like a simple articulated character.

---

# 🧩 Hierarchical Modeling

One of the main Computer Graphics concepts demonstrated by this project is **hierarchical modeling**.

The complete robot is assembled from multiple components:

```text
Robot
│
├── Torso
│
├── Head
│   ├── Eyes
│   ├── Pupils
│   ├── Mouth
│   └── Antenna
│
├── Left Arm
│   ├── Shoulder
│   ├── Upper Arm
│   ├── Elbow
│   ├── Forearm
│   ├── Wrist
│   └── Hand
│
├── Right Arm
│   ├── Shoulder
│   ├── Upper Arm
│   ├── Elbow
│   ├── Forearm
│   ├── Wrist
│   └── Hand
│
├── Left Leg
│   ├── Hip
│   ├── Thigh
│   ├── Knee
│   ├── Shin
│   ├── Ankle
│   └── Foot
│
└── Right Leg
    ├── Hip
    ├── Thigh
    ├── Knee
    ├── Shin
    ├── Ankle
    └── Foot
```

OpenGL's matrix stack is used extensively through:

```cpp
glPushMatrix();
glTranslatef(...);
glRotatef(...);
glScalef(...);
...
glPopMatrix();
```

This allows transformations applied to a parent component to affect its child components.

For example, rotating an arm around its shoulder also moves the upper arm, elbow, forearm, wrist, hand, and fingers together.

---

# 🧱 OpenGL Primitives

The project defines reusable helper functions for creating geometric objects.

### Cube

```cpp
drawColoredCube(width, height, depth, red, green, blue);
```

Used for:

* Torso
* Arms
* Legs
* Hands
* Feet
* Chest panel
* Buttons/details

### Sphere

```cpp
drawColoredSphere(radius, red, green, blue);
```

Used for:

* Head
* Eyes
* Pupils
* Joints
* Antenna tip
* Buttons

### Cylinder

```cpp
drawColoredCylinder(radius, height, red, green, blue);
```

Used for:

* Antenna

The cylinder is rendered using a GLU quadric object.

---

# 💡 Lighting and Rendering

The application uses OpenGL's fixed-function lighting pipeline.

The scene enables:

```cpp
GL_LIGHTING
GL_LIGHT0
GL_COLOR_MATERIAL
GL_NORMALIZE
GL_DEPTH_TEST
```

The main light source contains:

* Ambient lighting
* Diffuse lighting
* A defined 3D position

Material properties are also configured with:

* Specular reflection
* Shininess
* Smooth shading

This gives the robot a more three-dimensional appearance compared with completely unlit primitives.

---

# 🌍 3D Environment

The robot is placed inside a simple 3D environment.

The environment includes:

* Large ground plane
* Grid lines
* Perspective camera
* Dark blue background

The ground plane provides a spatial reference that makes robot movement and camera manipulation easier to observe.

---

# 📷 Camera System

The camera position is calculated using spherical coordinates.

The main camera parameters are:

```cpp
cameraDistance
cameraAngleX
cameraAngleY
```

The resulting camera position is passed to:

```cpp
gluLookAt();
```

This allows the camera to orbit around the robot.

The project also uses perspective projection:

```cpp
gluPerspective(
    45.0f,
    aspectRatio,
    0.1f,
    100.0f
);
```

This produces a more realistic 3D viewing experience.

---

# 🖥️ Rendering Pipeline

The main rendering process follows this sequence:

```text
Application Start
       ↓
Initialize GLUT
       ↓
Create OpenGL Window
       ↓
Initialize OpenGL State
       ↓
Register GLUT Callbacks
       ↓
Enter GLUT Main Loop
       ↓
       ┌───────────────────────┐
       │      Display()        │
       └───────────┬───────────┘
                   ↓
            Clear Buffers
                   ↓
            Setup Camera
                   ↓
            Setup Lighting
                   ↓
          Update Animation
                   ↓
          Draw Environment
                   ↓
          Draw Complete Robot
                   ↓
            Swap Buffers
                   ↓
              Repeat
```

---

# 🧠 Program Architecture

The entire application is currently implemented in a single C++ source file:

```text
main.cpp
```

The major functional sections are:

```text
Global State
│
├── Drawing Utilities
│
├── Robot Head
├── Robot Torso
├── Robot Arms
├── Robot Legs
│
├── Complete Robot Assembly
│
├── Animation
│
├── Environment
├── Display
├── Reshape
│
├── Keyboard Input
├── Special-Key Input
├── Mouse Input
├── Mouse Motion
├── Idle Callback
│
├── Instructions
├── OpenGL Initialization
│
└── main()
```

---

# 📁 Project Structure

```text
Robot-Project/
│
└── Robot/
    │
    ├── main.cpp
    ├── Robot.cbp
    ├── Robot.depend
    ├── Robot.layout
    │
    ├── bin/
    │   └── Debug/
    │       └── Robot.exe
    │
    └── obj/
        └── Debug/
            └── main.o
```

### Important Files

| File           | Purpose                                   |
| -------------- | ----------------------------------------- |
| `main.cpp`     | Main C++ source code                      |
| `Robot.cbp`    | Code::Blocks project configuration        |
| `Robot.depend` | Generated dependency information          |
| `Robot.layout` | Code::Blocks workspace/layout information |
| `Robot.exe`    | Compiled Windows executable               |
| `main.o`       | Compiled object file                      |

For a cleaner GitHub repository, generated build files such as `.exe` and `.o` can optionally be excluded using `.gitignore`.

---

# 🛠️ Technologies Used

| Technology          | Purpose                            |
| ------------------- | ---------------------------------- |
| **C++**             | Application programming            |
| **OpenGL**          | 3D graphics rendering              |
| **GLUT / FreeGLUT** | Window creation and input handling |
| **GLU**             | Utility functions and quadrics     |
| **MinGW/GCC**       | C++ compilation                    |
| **Code::Blocks**    | Development environment            |
| **Windows API**     | Windows-specific OpenGL support    |

---

# ⚙️ Requirements

To build the project from source, you need a Windows environment with:

* Code::Blocks
* MinGW/GCC compiler
* OpenGL development libraries
* GLUT or FreeGLUT
* GLU
* A system capable of running OpenGL applications

The project configuration was created for a Windows/MinGW environment.

---

# 🚀 How to Run

## Option 1 — Run the Existing Executable

If the compiled executable is available:

```text
Robot/bin/Debug/Robot.exe
```

Double-click the executable to launch the application.

> The executable is Windows-specific.

---

## Option 2 — Build from Source using Code::Blocks

### Step 1 — Install Code::Blocks

Install Code::Blocks with a MinGW compiler.

### Step 2 — Install GLUT/FreeGLUT

Make sure the OpenGL/GLUT development files are available to the compiler and linker.

Required libraries include:

```text
freeglut
opengl32
glu32
winmm
gdi32
```

### Step 3 — Open the Project

Open:

```text
Robot/Robot.cbp
```

using Code::Blocks.

### Step 4 — Verify Library Paths

The original project configuration contains machine-specific paths such as:

```text
C:/Program Files (x86)/CodeBlocks/MinGW/
```

If Code::Blocks or MinGW is installed in a different directory, update the compiler and linker paths accordingly.

### Step 5 — Build

Use:

```text
Build → Build
```

or:

```text
Ctrl + F9
```

### Step 6 — Run

Use:

```text
Build → Run
```

or:

```text
Ctrl + F10
```

---

# 🎮 Complete Controls Reference

| Input                | Function                 |
| -------------------- | ------------------------ |
| `W`                  | Move up                  |
| `S`                  | Move down                |
| `A`                  | Move left                |
| `D`                  | Move right               |
| `Z`                  | Move forward             |
| `X`                  | Move backward            |
| `Q`                  | Rotate left              |
| `E`                  | Rotate right             |
| `R`                  | Tilt backward            |
| `F`                  | Tilt forward             |
| `T`                  | Roll left                |
| `G`                  | Roll right               |
| `1`                  | Left arm up              |
| `2`                  | Left arm down            |
| `3`                  | Right arm up             |
| `4`                  | Right arm down           |
| `5`                  | Left leg forward         |
| `6`                  | Left leg backward        |
| `7`                  | Right leg forward        |
| `8`                  | Right leg backward       |
| `9`                  | Head right               |
| `0`                  | Head left                |
| `↑`                  | Camera up                |
| `↓`                  | Camera down              |
| `←`                  | Camera left              |
| `→`                  | Camera right             |
| `Page Up`            | Zoom in                  |
| `Page Down`          | Zoom out                 |
| `Left Mouse + Drag`  | Rotate robot             |
| `Right Mouse + Drag` | Rotate camera            |
| `Space`              | Toggle walking animation |
| `C`                  | Reset robot              |
| `ESC`                | Exit                     |

---

# 📚 Computer Graphics Concepts Demonstrated

This project demonstrates several fundamental concepts commonly covered in a Computer Graphics course.

### 1. 3D Transformation

Translation:

```cpp
glTranslatef();
```

Rotation:

```cpp
glRotatef();
```

Scaling:

```cpp
glScalef();
```

---

### 2. Hierarchical Modeling

Robot parts are organized as parent-child components.

```text
Robot
 └── Arm
      └── Forearm
           └── Hand
```

Transformations can therefore be applied to entire groups of components.

---

### 3. Perspective Projection

The project uses:

```cpp
gluPerspective();
```

to create a perspective view.

---

### 4. Camera Transformation

The camera is positioned using:

```cpp
gluLookAt();
```

---

### 5. Depth Testing

Depth buffering is enabled using:

```cpp
glEnable(GL_DEPTH_TEST);
```

This ensures that objects closer to the camera correctly appear in front of objects behind them.

---

### 6. Lighting

The project demonstrates OpenGL lighting using:

```cpp
GL_LIGHTING
GL_LIGHT0
GL_AMBIENT
GL_DIFFUSE
GL_SPECULAR
```

---

### 7. Animation

Smooth movement is generated using trigonometric functions such as:

```cpp
sin()
```

This is used for the walking cycle, head movement, and body bobbing.

---

### 8. Event-Driven Interaction

GLUT callback functions handle user interaction:

```cpp
glutKeyboardFunc()
glutSpecialFunc()
glutMouseFunc()
glutMotionFunc()
glutIdleFunc()
```

---

# 🔬 How the Animation Works

The walking animation does not rely on external animation files.

Instead, joint rotations are calculated continuously.

For example:

```cpp
leftArmRotationX = 25.0f * sin(animationTimer);
rightArmRotationX = -25.0f * sin(animationTimer);
```

The legs use an opposite phase:

```cpp
leftLegRotationX =
    20.0f * sin(animationTimer + 3.14159f);
```

This creates alternating limb movement.

The robot also receives a small vertical movement:

```cpp
robotY = 0.15f * sin(animationTimer * 2.0f);
```

Together, these calculations produce the appearance of a simple walking robot.

---

# 🧪 Learning Objectives

This project can be used to understand:

* How 3D objects are constructed from primitives
* How OpenGL transformation matrices work
* How hierarchical transformations are implemented
* How cameras are positioned in 3D space
* How perspective projection works
* How lighting affects 3D objects
* How keyboard and mouse input can control graphics
* How procedural animation can be created
* How GLUT manages an interactive graphics application
* How multiple objects can be assembled into a complete 3D model

---

# 🔮 Possible Future Improvements

The current project provides a strong foundation for further development.

Potential improvements include:

### 🎨 Better Visual Design

* Add textures
* Add metallic materials
* Improve lighting
* Add shadows
* Add more detailed robot components
* Add a skybox or richer environment

### 🦾 Advanced Robot Controls

* Independent elbow and knee controls
* Wrist rotation
* Hand/finger animation
* More realistic joint constraints
* Multiple predefined robot poses

### 🚶 Advanced Animation

* Improved walking cycle
* Running animation
* Idle animation
* Jumping
* Dancing
* Wave animation
* Animation state machine

### 🌎 Environment

* Obstacles
* Platforms
* Buildings
* Terrain
* Interactive objects

### 🎮 User Interface

A graphical control panel could be added to display:

* Robot coordinates
* Rotation values
* Current animation state
* Camera position
* Current limb angles

### 🖥️ Modern OpenGL

The project currently uses the traditional fixed-function OpenGL pipeline.

A future version could migrate to:

* Modern OpenGL
* Vertex Buffer Objects
* Vertex Array Objects
* GLSL shaders
* Texture mapping
* Normal mapping
* Modern lighting models

---

# ⚠️ Current Project Notes

This repository is an educational Computer Graphics project.

The current implementation uses **legacy/fixed-function OpenGL**, including functions such as:

```cpp
glBegin()
glEnd()
glColor3f()
glPushMatrix()
glPopMatrix()
glRotatef()
glTranslatef()
```

These APIs are useful for learning fundamental graphics concepts but are not the preferred approach for modern production-level OpenGL applications.

The Code::Blocks project file also contains **machine-specific Windows paths** for MinGW and OpenGL libraries. When building on another machine, these paths may need to be changed.

---

# 🧹 Recommended Repository Cleanup

For a cleaner GitHub repository, generated files can be excluded:

```gitignore
# Build output
bin/
obj/

# Compiled executable
*.exe

# Code::Blocks generated files
*.layout
*.depend
```

The main source file that needs to be preserved is:

```text
main.cpp
```

along with the project configuration if Code::Blocks is intended to remain the primary IDE.

---

# 📸 Project Preview

Add screenshots or a short demonstration GIF/video here after capturing the application.

Example:

```markdown
![3D Robot Preview](screenshots/robot-preview.png)
```

For an interactive project, a short GIF demonstrating the robot walking and responding to keyboard/mouse controls would make the repository significantly more attractive.

---

# 🎓 Academic Context

**Project Type:** Computer Graphics Project
**Application:** Interactive 3D Robot Simulation
**Programming Language:** C++
**Graphics API:** OpenGL
**Toolkit:** GLUT / FreeGLUT
**Development Environment:** Code::Blocks + MinGW
**Platform:** Windows

This project was developed to demonstrate practical implementation of fundamental **3D Computer Graphics concepts** through an interactive application.

---

# 👨‍💻 Author

**Ganesh Prasad**

Computer Science & Engineering Student

Interested in:

* Full Stack Development
* Software Development
* Computer Graphics
* Artificial Intelligence & Machine Learning
* Building practical software projects

---

# ⭐ If You Like This Project

If you found this project useful for learning OpenGL and Computer Graphics, consider giving the repository a ⭐ on GitHub.

---

<p align="center">
  <b>Built with C++, OpenGL & GLUT ❤️</b>
</p>
