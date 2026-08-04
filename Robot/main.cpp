/*
 * ========================================================================
 * OPENGL ROBOT PROJECT - COMPUTER GRAPHICS ASSIGNMENT
 * ========================================================================
 *
 * Project Name: Interactive 3D Robot with Keyboard and Mouse Controls
 * IDE: CodeBlocks (Windows)
 * Graphics API: OpenGL with GLUT toolkit
 * Language: C++
 *
 * Description: This program creates a complete 3D robot that can be controlled
 * using keyboard keys and mouse input. The robot consists of multiple body parts
 * including head, torso, arms, and legs that can rotate independently.
 *
 * Controls:
 * - WASD: Move robot position
 * - Q/E: Rotate robot left/right (Y-axis)
 * - R/F: Rotate robot up/down (X-axis)
 * - T/G: Roll robot left/right (Z-axis)
 * - 1-8: Individual limb controls
 * - Mouse: Drag to rotate robot and camera
 * - SPACE: Toggle animation
 * - C: Reset to center
 * - ESC: Exit program
 *
 * Author: Computer Graphics Student
 * Date: August 2025
 * ========================================================================
 */

// ========================================================================
// HEADER INCLUDES - Required libraries for OpenGL and system functions
// ========================================================================
// Fix for GLUT wchar_t redeclaration error
#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #include <windows.h>
#endif

// Fix wchar_t redeclaration
#ifdef __MINGW32__
    #undef WINGDIAPI
    #define WINGDIAPI __declspec(dllimport)
#endif

// Now include GLUT headers
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Rest of your includes...
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/////////////////////////////////////////////////////////////////////////////////

#include <GL/glut.h>        // Main GLUT library for window management and OpenGL utilities
#include <GL/gl.h>          // Core OpenGL functions for graphics rendering
#include <GL/glu.h>         // OpenGL Utility Library for advanced functions like gluPerspective
#include <stdio.h>          // Standard input/output operations (printf, etc.)
#include <stdlib.h>         // Standard library functions (exit, etc.)
#include <math.h>           // Mathematical functions (sin, cos, etc.)
#include <windows.h>        // Windows-specific functions (required for some OpenGL operations)

// ========================================================================
// GLOBAL VARIABLES - Store robot state and control parameters
// ========================================================================

// Robot position in 3D world space
float robotX = 0.0f;        // X-coordinate (left/right position)
float robotY = 0.0f;        // Y-coordinate (up/down position)
float robotZ = 0.0f;        // Z-coordinate (forward/backward position)

// Whole robot rotation angles (in degrees)
float robotRotationX = 0.0f;    // Rotation around X-axis (pitch - up/down)
float robotRotationY = 0.0f;    // Rotation around Y-axis (yaw - left/right)
float robotRotationZ = 0.0f;    // Rotation around Z-axis (roll - tilt)

// Individual body part rotation angles
float headRotationY = 0.0f;     // Head turning left/right
float leftArmRotationX = 0.0f;  // Left arm up/down movement
float rightArmRotationX = 0.0f; // Right arm up/down movement
float leftLegRotationX = 0.0f;  // Left leg forward/backward
float rightLegRotationX = 0.0f; // Right leg forward/backward

// Mouse interaction variables
int lastMouseX = 0;         // Previous mouse X position
int lastMouseY = 0;         // Previous mouse Y position
bool mouseLeftPressed = false;   // Left mouse button state
bool mouseRightPressed = false;  // Right mouse button state

// Camera control variables
float cameraDistance = 10.0f;   // Distance from robot (zoom level)
float cameraAngleX = 20.0f;     // Camera elevation angle
float cameraAngleY = 0.0f;      // Camera rotation around robot

// Animation control
bool animationEnabled = false;   // Toggle for automatic animation
float animationTimer = 0.0f;    // Timer for animation calculations

// ========================================================================
// BASIC DRAWING FUNCTIONS - Primitive shape drawing utilities
// ========================================================================

/*
 * Function: drawColoredCube
 * Purpose: Draws a cube with specified dimensions and color
 * Parameters:
 *   - width, height, depth: Dimensions of the cube
 *   - red, green, blue: RGB color values (0.0 to 1.0)
 */
void drawColoredCube(float width, float height, float depth, float red, float green, float blue) {
    // Set the color for this cube using RGB values
    glColor3f(red, green, blue);

    // Save the current transformation matrix
    glPushMatrix();

    // Scale the unit cube to desired dimensions
    glScalef(width, height, depth);

    // Draw a solid cube using GLUT's built-in function
    glutSolidCube(1.0f);

    // Restore the previous transformation matrix
    glPopMatrix();
}

/*
 * Function: drawColoredSphere
 * Purpose: Draws a sphere with specified radius and color
 * Parameters:
 *   - radius: Size of the sphere
 *   - red, green, blue: RGB color values (0.0 to 1.0)
 */
void drawColoredSphere(float radius, float red, float green, float blue) {
    // Set the color for this sphere
    glColor3f(red, green, blue);

    // Save the current transformation matrix
    glPushMatrix();

    // Draw a solid sphere using GLUT's built-in function
    // Parameters: radius, slices (longitude divisions), stacks (latitude divisions)
    glutSolidSphere(radius, 20, 20);

    // Restore the previous transformation matrix
    glPopMatrix();
}

/*
 * Function: drawColoredCylinder
 * Purpose: Draws a cylinder using GLUT quadrics
 * Parameters:
 *   - radius: Cylinder radius
 *   - height: Cylinder height
 *   - red, green, blue: RGB color values
 */
void drawColoredCylinder(float radius, float height, float red, float green, float blue) {
    // Set the color for this cylinder
    glColor3f(red, green, blue);

    // Save the current transformation matrix
    glPushMatrix();

    // Create a quadric object for drawing cylinders
    GLUquadricObj* quadric = gluNewQuadric();

    // Rotate to make cylinder vertical (GLUT draws along Z-axis by default)
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    // Draw the cylinder
    // Parameters: quadric, base radius, top radius, height, slices, stacks
    gluCylinder(quadric, radius, radius, height, 12, 1);

    // Clean up the quadric object
    gluDeleteQuadric(quadric);

    // Restore the previous transformation matrix
    glPopMatrix();
}

// ========================================================================
// ROBOT BODY PART FUNCTIONS - Individual components of the robot
// ========================================================================

/*
 * Function: drawRobotHead
 * Purpose: Draws the robot's head including eyes and antenna
 */
void drawRobotHead() {
    // Save matrix state for head transformations
    glPushMatrix();

    // Position the head above the body
    glTranslatef(0.0f, 2.5f, 0.0f);

    // Apply head rotation (allows head to turn left/right)
    glRotatef(headRotationY, 0.0f, 1.0f, 0.0f);

    // Draw main head as a blue sphere
    drawColoredSphere(0.8f, 0.2f, 0.4f, 1.0f);  // Blue head

    // Draw left eye
    glPushMatrix();
        glTranslatef(-0.3f, 0.2f, 0.6f);  // Position left eye on face
        drawColoredSphere(0.15f, 1.0f, 1.0f, 1.0f);  // White eye
    glPopMatrix();

    // Draw right eye
    glPushMatrix();
        glTranslatef(0.3f, 0.2f, 0.6f);   // Position right eye on face
        drawColoredSphere(0.15f, 1.0f, 1.0f, 1.0f);   // White eye
    glPopMatrix();

    // Draw eye pupils
    glPushMatrix();
        glTranslatef(-0.3f, 0.2f, 0.72f); // Left pupil (slightly forward)
        drawColoredSphere(0.05f, 0.0f, 0.0f, 0.0f);   // Black pupil
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.3f, 0.2f, 0.72f);  // Right pupil
        drawColoredSphere(0.05f, 0.0f, 0.0f, 0.0f);   // Black pupil
    glPopMatrix();

    // Draw nose/mouth area
    glPushMatrix();
        glTranslatef(0.0f, -0.2f, 0.7f);  // Position below eyes
        drawColoredCube(0.3f, 0.1f, 0.1f, 1.0f, 0.5f, 0.0f);  // Orange mouth
    glPopMatrix();

    // Draw antenna on top of head
    glPushMatrix();
        glTranslatef(0.0f, 0.8f, 0.0f);   // Position on top of head
        drawColoredCylinder(0.05f, 0.4f, 0.7f, 0.7f, 0.7f);   // Gray antenna

        // Antenna tip
        glTranslatef(0.0f, 0.4f, 0.0f);
        drawColoredSphere(0.1f, 1.0f, 0.0f, 0.0f);    // Red tip
    glPopMatrix();

    // Restore matrix state
    glPopMatrix();
}

/*
 * Function: drawRobotTorso
 * Purpose: Draws the main body/torso of the robot
 */
void drawRobotTorso() {
    // Save matrix state for torso
    glPushMatrix();

    // Main torso positioned at origin
    glTranslatef(0.0f, 0.0f, 0.0f);

    // Draw main body as a red rectangular cube
    drawColoredCube(2.0f, 2.5f, 1.2f, 0.8f, 0.2f, 0.2f);  // Red torso

    // Draw chest control panel
    glPushMatrix();
        glTranslatef(0.0f, 0.5f, 0.61f);  // Position on front of torso
        drawColoredCube(1.2f, 1.5f, 0.05f, 0.0f, 0.8f, 0.0f);  // Green panel
    glPopMatrix();

    // Draw control buttons on chest panel
    for(int i = -1; i <= 1; i++) {
        for(int j = 0; j <= 2; j++) {
            glPushMatrix();
                glTranslatef(i * 0.3f, 0.8f - j * 0.3f, 0.65f);
                drawColoredSphere(0.08f, 1.0f, 1.0f, 0.0f);  // Yellow buttons
            glPopMatrix();
        }
    }

    // Draw power indicator (blinking light effect)
    glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.65f);
        // Simple blinking effect based on animation timer
        float brightness = (sin(animationTimer * 5.0f) + 1.0f) * 0.5f;
        drawColoredSphere(0.1f, brightness, 0.0f, 0.0f);  // Red power light
    glPopMatrix();

    // Restore matrix state
    glPopMatrix();
}

/*
 * Function: drawRobotArm
 * Purpose: Draws a complete robot arm with shoulder, elbow, and hand
 * Parameters: isLeftArm - true for left arm, false for right arm
 */
void drawRobotArm(bool isLeftArm) {
    // Save matrix state for entire arm assembly
    glPushMatrix();

    // Position arm at appropriate shoulder location
    float shoulderX = isLeftArm ? -1.3f : 1.3f;  // Left or right shoulder
    glTranslatef(shoulderX, 1.0f, 0.0f);

    // Apply arm rotation based on which arm this is
    if (isLeftArm) {
        glRotatef(leftArmRotationX, 1.0f, 0.0f, 0.0f);  // Left arm rotation
    } else {
        glRotatef(rightArmRotationX, 1.0f, 0.0f, 0.0f); // Right arm rotation
    }

    // Draw shoulder joint
    glPushMatrix();
        drawColoredSphere(0.3f, 0.6f, 0.6f, 0.6f);  // Gray shoulder joint
    glPopMatrix();

    // Draw upper arm
    glPushMatrix();
        glTranslatef(0.0f, -0.5f, 0.0f);  // Position upper arm below shoulder
        drawColoredCube(0.4f, 1.0f, 0.4f, 0.3f, 0.3f, 0.9f);  // Blue upper arm
    glPopMatrix();

    // Draw elbow joint
    glPushMatrix();
        glTranslatef(0.0f, -1.0f, 0.0f);  // Position at elbow
        drawColoredSphere(0.25f, 0.6f, 0.6f, 0.6f);  // Gray elbow joint
    glPopMatrix();

    // Draw forearm
    glPushMatrix();
        glTranslatef(0.0f, -1.4f, 0.0f);  // Position forearm below elbow
        drawColoredCube(0.35f, 0.8f, 0.35f, 0.2f, 0.7f, 0.2f);  // Green forearm
    glPopMatrix();

    // Draw wrist joint
    glPushMatrix();
        glTranslatef(0.0f, -1.9f, 0.0f);  // Position at wrist
        drawColoredSphere(0.2f, 0.6f, 0.6f, 0.6f);  // Gray wrist joint
    glPopMatrix();

    // Draw hand
    glPushMatrix();
        glTranslatef(0.0f, -2.2f, 0.0f);  // Position hand at end of arm
        drawColoredCube(0.3f, 0.4f, 0.2f, 1.0f, 0.8f, 0.0f);  // Yellow hand

        // Draw fingers
        for(int i = -1; i <= 1; i++) {
            glPushMatrix();
                glTranslatef(i * 0.08f, -0.3f, 0.0f);
                drawColoredCube(0.05f, 0.2f, 0.15f, 1.0f, 0.6f, 0.0f);  // Orange fingers
            glPopMatrix();
        }
    glPopMatrix();

    // Restore matrix state
    glPopMatrix();
}

/*
 * Function: drawRobotLeg
 * Purpose: Draws a complete robot leg with hip, knee, and foot
 * Parameters: isLeftLeg - true for left leg, false for right leg
 */
void drawRobotLeg(bool isLeftLeg) {
    // Save matrix state for entire leg assembly
    glPushMatrix();

    // Position leg at appropriate hip location
    float hipX = isLeftLeg ? -0.6f : 0.6f;  // Left or right hip
    glTranslatef(hipX, -1.25f, 0.0f);

    // Apply leg rotation based on which leg this is
    if (isLeftLeg) {
        glRotatef(leftLegRotationX, 1.0f, 0.0f, 0.0f);   // Left leg rotation
    } else {
        glRotatef(rightLegRotationX, 1.0f, 0.0f, 0.0f);  // Right leg rotation
    }

    // Draw hip joint
    glPushMatrix();
        drawColoredSphere(0.3f, 0.6f, 0.6f, 0.6f);  // Gray hip joint
    glPopMatrix();

    // Draw upper leg (thigh)
    glPushMatrix();
        glTranslatef(0.0f, -0.6f, 0.0f);  // Position thigh below hip
        drawColoredCube(0.5f, 1.2f, 0.5f, 0.7f, 0.3f, 0.7f);  // Purple thigh
    glPopMatrix();

    // Draw knee joint
    glPushMatrix();
        glTranslatef(0.0f, -1.2f, 0.0f);  // Position at knee
        drawColoredSphere(0.25f, 0.6f, 0.6f, 0.6f);  // Gray knee joint
    glPopMatrix();

    // Draw lower leg (shin)
    glPushMatrix();
        glTranslatef(0.0f, -1.7f, 0.0f);  // Position shin below knee
        drawColoredCube(0.4f, 1.0f, 0.4f, 0.0f, 0.6f, 0.6f);  // Cyan shin
    glPopMatrix();

    // Draw ankle joint
    glPushMatrix();
        glTranslatef(0.0f, -2.3f, 0.0f);  // Position at ankle
        drawColoredSphere(0.2f, 0.6f, 0.6f, 0.6f);  // Gray ankle joint
    glPopMatrix();

    // Draw foot
    glPushMatrix();
        glTranslatef(0.0f, -2.6f, 0.3f);  // Position foot (slightly forward)
        drawColoredCube(0.5f, 0.3f, 1.0f, 0.4f, 0.2f, 0.0f);  // Brown foot

        // Draw toe details
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.4f);  // Position at front of foot
            drawColoredCube(0.4f, 0.2f, 0.2f, 0.3f, 0.1f, 0.0f);  // Darker brown toe
        glPopMatrix();
    glPopMatrix();

    // Restore matrix state
    glPopMatrix();
}

// ========================================================================
// ROBOT ASSEMBLY FUNCTION - Combines all body parts
// ========================================================================

/*
 * Function: drawCompleteRobot
 * Purpose: Draws the entire robot by calling all body part functions
 * This function handles the overall robot positioning and rotation
 */
void drawCompleteRobot() {
    // Save matrix state for entire robot
    glPushMatrix();

    // Apply robot's world position
    glTranslatef(robotX, robotY, robotZ);

    // Apply whole robot rotations in proper order
    glRotatef(robotRotationY, 0.0f, 1.0f, 0.0f);  // Yaw (left/right turn)
    glRotatef(robotRotationX, 1.0f, 0.0f, 0.0f);  // Pitch (up/down tilt)
    glRotatef(robotRotationZ, 0.0f, 0.0f, 1.0f);  // Roll (side tilt)

    // Draw all robot body parts in logical order
    drawRobotTorso();       // Draw main body first (central reference)
    drawRobotHead();        // Draw head attached to body
    drawRobotArm(true);     // Draw left arm
    drawRobotArm(false);    // Draw right arm
    drawRobotLeg(true);     // Draw left leg
    drawRobotLeg(false);    // Draw right leg

    // Restore matrix state
    glPopMatrix();
}

// ========================================================================
// ANIMATION FUNCTIONS - Handle automatic robot movement
// ========================================================================

/*
 * Function: updateAnimation
 * Purpose: Updates robot limb positions for walking animation
 * This creates a realistic walking cycle using trigonometric functions
 */
void updateAnimation() {
    // Only update animation if it's enabled
    if (animationEnabled) {
        // Increment animation timer for smooth motion
        animationTimer += 0.004f;

        // Create walking cycle using sine waves with different phases
        // Arms swing opposite to legs for natural walking motion
        leftArmRotationX = 25.0f * sin(animationTimer);        // Left arm forward/back
        rightArmRotationX = -25.0f * sin(animationTimer);      // Right arm opposite

        // Legs move opposite to arms with phase offset for natural gait
        leftLegRotationX = 20.0f * sin(animationTimer + 3.14159f); // Left leg (180° phase)
        rightLegRotationX = -20.0f * sin(animationTimer + 3.14159f); // Right leg opposite

        // Add subtle head movement for realism
        headRotationY = 10.0f * sin(animationTimer * 0.7f);    // Slow head turn

        // Add slight vertical bobbing motion
        robotY = 0.15f * sin(animationTimer * 2.0f);
    }
}

// ========================================================================
// SCENE RENDERING FUNCTIONS - Display and camera management
// ========================================================================

/*
 * Function: drawEnvironment
 * Purpose: Draws background elements like ground plane and grid
 */
void drawEnvironment() {
    // Disable lighting for environment elements
    glDisable(GL_LIGHTING);

    // Draw ground plane
    glColor3f(0.3f, 0.5f, 0.3f);  // Dark green ground
    glBegin(GL_QUADS);
        glVertex3f(-20.0f, -4.0f, -20.0f);
        glVertex3f(20.0f, -4.0f, -20.0f);
        glVertex3f(20.0f, -4.0f, 20.0f);
        glVertex3f(-20.0f, -4.0f, 20.0f);
    glEnd();

    // Draw grid lines for reference
    glColor3f(0.4f, 0.4f, 0.4f);  // Gray grid lines
    glBegin(GL_LINES);
        // Horizontal lines
        for(int i = -20; i <= 20; i += 2) {
            glVertex3f(-20.0f, -3.99f, (float)i);
            glVertex3f(20.0f, -3.99f, (float)i);
        }
        // Vertical lines
        for(int i = -20; i <= 20; i += 2) {
            glVertex3f((float)i, -3.99f, -20.0f);
            glVertex3f((float)i, -3.99f, 20.0f);
        }
    glEnd();

    // Re-enable lighting for robot
    glEnable(GL_LIGHTING);
}

/*
 * Function: display
 * Purpose: Main display callback function - renders the entire scene
 * This function is called by GLUT whenever the screen needs to be redrawn
 */
void display() {
    // Clear both color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset the modelview matrix
    glLoadIdentity();

    // Calculate camera position using spherical coordinates
    float camX = cameraDistance * cos(cameraAngleX * 3.14159f / 180.0f) * sin(cameraAngleY * 3.14159f / 180.0f);
    float camY = cameraDistance * sin(cameraAngleX * 3.14159f / 180.0f);
    float camZ = cameraDistance * cos(cameraAngleX * 3.14159f / 180.0f) * cos(cameraAngleY * 3.14159f / 180.0f);

    // Position camera to look at the robot
    gluLookAt(camX, camY, camZ,         // Camera position
              0.0f, 0.0f, 0.0f,         // Look at point (robot center)
              0.0f, 1.0f, 0.0f);        // Up vector

    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Configure light properties
    GLfloat lightPos[] = {5.0f, 10.0f, 5.0f, 1.0f};   // Light position
    GLfloat lightAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f}; // Ambient light
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Diffuse light

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    // Update animation
    updateAnimation();

    // Draw the environment
    drawEnvironment();

    // Draw the robot
    drawCompleteRobot();

    // Swap front and back buffers (double buffering)
    glutSwapBuffers();
}

/*
 * Function: reshape
 * Purpose: Handle window resizing - maintains proper aspect ratio
 * Parameters: width, height - new window dimensions
 */
void reshape(int width, int height) {
    // Prevent division by zero
    if (height == 0) height = 1;

    // Set the viewport to cover the entire window
    glViewport(0, 0, width, height);

    // Switch to projection matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set up perspective projection
    // Parameters: field of view, aspect ratio, near plane, far plane
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

    // Switch back to modelview matrix mode
    glMatrixMode(GL_MODELVIEW);
}

// ========================================================================
// INPUT HANDLING FUNCTIONS - Keyboard and mouse interaction
// ========================================================================

/*
 * Function: keyboard
 * Purpose: Handle regular keyboard input
 * Parameters: key - the pressed key, x,y - mouse position when key was pressed
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // ============ WHOLE ROBOT ROTATION CONTROLS ============
        case 'q': case 'Q':
            robotRotationY -= 5.0f;  // Rotate robot left around Y-axis
            printf("Robot rotating left (Y-axis): %.1f degrees", robotRotationY);
            break;
        case 'e': case 'E':
            robotRotationY += 5.0f;  // Rotate robot right around Y-axis
            printf("Robot rotating right (Y-axis): %.1f degrees", robotRotationY);
            break;
        case 'r': case 'R':
            robotRotationX -= 5.0f;  // Tilt robot backward around X-axis
            printf("Robot tilting back (X-axis): %.1f degrees", robotRotationX);
            break;
        case 'f': case 'F':
            robotRotationX += 5.0f;  // Tilt robot forward around X-axis
            printf("Robot tilting forward (X-axis): %.1f degrees", robotRotationX);
            break;
        case 't': case 'T':
            robotRotationZ -= 5.0f;  // Roll robot left around Z-axis
            printf("Robot rolling left (Z-axis): %.1f degrees", robotRotationZ);
            break;
        case 'g': case 'G':
            robotRotationZ += 5.0f;  // Roll robot right around Z-axis
            printf("Robot rolling right (Z-axis): %.1f degrees", robotRotationZ);
            break;

        // ============ ROBOT POSITION CONTROLS ============
        case 'w': case 'W':
            robotY += 0.3f;          // Move robot up
            printf("Robot moving up: Y = %.1f", robotY);
            break;
        case 's': case 'S':
            robotY -= 0.3f;          // Move robot down
            printf("Robot moving down: Y = %.1f", robotY);
            break;
        case 'a': case 'A':
            robotX -= 0.3f;          // Move robot left
            printf("Robot moving left: X = %.1f", robotX);
            break;
        case 'd': case 'D':
            robotX += 0.3f;          // Move robot right
            printf("Robot moving right: X = %.1f", robotX);
            break;
        case 'z': case 'Z':
            robotZ += 0.3f;          // Move robot forward
            printf("Robot moving forward: Z = %.1f", robotZ);
            break;
        case 'x': case 'X':
            robotZ -= 0.3f;          // Move robot backward
            printf("Robot moving backward: Z = %.1f", robotZ);
            break;

        // ============ INDIVIDUAL LIMB CONTROLS ============
        case '1':
            leftArmRotationX += 15.0f;   // Left arm up
            printf("Left arm moving up: %.1f degrees", leftArmRotationX);
            break;
        case '2':
            leftArmRotationX -= 15.0f;   // Left arm down
            printf("Left arm moving down: %.1f degrees", leftArmRotationX);
            break;
        case '3':
            rightArmRotationX += 15.0f;  // Right arm up
            printf("Right arm moving up: %.1f degrees", rightArmRotationX);
            break;
        case '4':
            rightArmRotationX -= 15.0f;  // Right arm down
            printf("Right arm moving down: %.1f degrees", rightArmRotationX);
            break;
        case '5':
            leftLegRotationX += 15.0f;   // Left leg forward
            printf("Left leg moving forward: %.1f degrees", leftLegRotationX);
            break;
        case '6':
            leftLegRotationX -= 15.0f;   // Left leg backward
            printf("Left leg moving backward: %.1f degrees", leftLegRotationX);
            break;
        case '7':
            rightLegRotationX += 15.0f;  // Right leg forward
            printf("Right leg moving forward: %.1f degrees", rightLegRotationX);
            break;
        case '8':
            rightLegRotationX -= 15.0f;  // Right leg backward
            printf("Right leg moving backward: %.1f degrees", rightLegRotationX);
            break;
        case '9':
            headRotationY += 15.0f;      // Head turn right
            printf("Head turning right: %.1f degrees", headRotationY);
            break;
        case '0':
            headRotationY -= 15.0f;      // Head turn left
            printf("Head turning left: %.1f degrees", headRotationY);
            break;

        // ============ SPECIAL FUNCTION CONTROLS ============
        case ' ':  // Spacebar
            animationEnabled = !animationEnabled;  // Toggle animation
            printf("Animation %s", animationEnabled ? "ENABLED" : "DISABLED");
            break;

        case 'c': case 'C':
            // Reset all transformations to default values
            robotX = robotY = robotZ = 0.0f;
            robotRotationX = robotRotationY = robotRotationZ = 0.0f;
            leftArmRotationX = rightArmRotationX = 0.0f;
            leftLegRotationX = rightLegRotationX = 0.0f;
            headRotationY = 0.0f;
            animationTimer = 0.0f;
            printf("Robot reset to default position");
            break;

        case 27:  // Escape key
            printf("Exiting program...");
            exit(0);  // Exit the program
            break;

        default:
            // Print help message for unrecognized keys
            printf("Unknown key pressed. Available controls:");
            printf("Q/E: Rotate left/right, R/F: Tilt up/down, T/G: Roll left/right");
            printf("WASD: Move position, ZX: Move forward/back");
            printf("1-8: Individual limb control, 9/0: Head turn");
            printf("SPACE: Toggle animation, C: Reset, ESC: Exit");
            break;
    }

    // Request screen redraw after any key press
    glutPostRedisplay();
}

/*
 * Function: specialKeys
 * Purpose: Handle special keys (arrow keys, function keys, etc.)
 * Parameters: key - special key code, x,y - mouse position
 */
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            cameraAngleX += 5.0f;        // Tilt camera up
            printf("Camera tilt up: %.1f degrees", cameraAngleX);
            break;
        case GLUT_KEY_DOWN:
            cameraAngleX -= 5.0f;        // Tilt camera down
            printf("Camera tilt down: %.1f degrees", cameraAngleX);
            break;
        case GLUT_KEY_LEFT:
            cameraAngleY -= 5.0f;        // Rotate camera left
            printf("Camera rotate left: %.1f degrees", cameraAngleY);
            break;
        case GLUT_KEY_RIGHT:
            cameraAngleY += 5.0f;        // Rotate camera right
            printf("Camera rotate right: %.1f degrees", cameraAngleY);
            break;
        case GLUT_KEY_PAGE_UP:
            cameraDistance -= 1.0f;      // Zoom in
            if (cameraDistance < 3.0f) cameraDistance = 3.0f;  // Minimum distance
            printf("Camera zoom in: %.1f units", cameraDistance);
            break;
        case GLUT_KEY_PAGE_DOWN:
            cameraDistance += 1.0f;      // Zoom out
            if (cameraDistance > 25.0f) cameraDistance = 25.0f;  // Maximum distance
            printf("Camera zoom out: %.1f units", cameraDistance);
            break;
    }

    // Request screen redraw
    glutPostRedisplay();
}

/*
 * Function: mouse
 * Purpose: Handle mouse button press and release events
 * Parameters: button - which button, state - pressed or released, x,y - position
 */
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseLeftPressed = true;
            lastMouseX = x;
            lastMouseY = y;
            printf("Left mouse button pressed at (%d, %d)", x, y);
        } else {
            mouseLeftPressed = false;
            printf("Left mouse button released");
        }
    } else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseRightPressed = true;
            lastMouseX = x;
            lastMouseY = y;
            printf("Right mouse button pressed at (%d, %d)", x, y);
        } else {
            mouseRightPressed = false;
            printf("Right mouse button released");
        }
    }
}

/*
 * Function: mouseMotion
 * Purpose: Handle mouse movement while button is pressed (dragging)
 * Parameters: x, y - current mouse position
 */
void mouseMotion(int x, int y) {
    // Calculate how much the mouse moved
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;

    if (mouseLeftPressed) {
        // Left mouse drag: rotate the entire robot
        robotRotationY += deltaX * 0.5f;  // Horizontal movement rotates around Y-axis
        robotRotationX += deltaY * 0.5f;  // Vertical movement rotates around X-axis

        printf("Robot rotation: X=%.1f, Y=%.1f (mouse drag)", robotRotationX, robotRotationY);
    } else if (mouseRightPressed) {
        // Right mouse drag: control camera
        cameraAngleY += deltaX * 0.5f;    // Horizontal camera rotation
        cameraAngleX -= deltaY * 0.5f;    // Vertical camera rotation (inverted)

        // Limit vertical camera angle to reasonable range
        if (cameraAngleX > 85.0f) cameraAngleX = 85.0f;
        if (cameraAngleX < -85.0f) cameraAngleX = -85.0f;

        printf("Camera angles: X=%.1f, Y=%.1f (mouse drag)", cameraAngleX, cameraAngleY);
    }

    // Update last mouse position
    lastMouseX = x;
    lastMouseY = y;

    // Request screen redraw
    glutPostRedisplay();
}

/*
 * Function: idle
 * Purpose: Called when no events are pending - used for continuous animation
 * This function ensures smooth animation by constantly updating the display
 */
void idle() {
    // If animation is enabled, continuously update the display
    if (animationEnabled) {
        glutPostRedisplay();
    }
}

// ========================================================================
// INITIALIZATION AND MAIN PROGRAM
// ========================================================================

/*
 * Function: printInstructions
 * Purpose: Display control instructions in the console
 */
void printInstructions() {
    printf("");
    printf("========================================================");
    printf("         OPENGL ROBOT - CONTROL INSTRUCTIONS");
    printf("========================================================");
    printf(" ");
    printf("WHOLE ROBOT ROTATION:");
    printf("  Q/E - Rotate left/right (Y-axis yaw)");
    printf("  R/F - Tilt up/down (X-axis pitch)");
    printf("  T/G - Roll left/right (Z-axis roll)");
    printf(" ");
    printf("ROBOT POSITION MOVEMENT:");
    printf("  W/S - Move up/down");
    printf("  A/D - Move left/right");
    printf("  Z/X - Move forward/backward");
    printf(" ");
    printf("INDIVIDUAL LIMB CONTROL:");
    printf("  1/2 - Left arm up/down");
    printf("  3/4 - Right arm up/down");
    printf("  5/6 - Left leg forward/backward");
    printf("  7/8 - Right leg forward/backward");
    printf("  9/0 - Head turn right/left");
    printf(" ");
    printf("CAMERA CONTROL:");
    printf("  Arrow Keys - Move camera view");
    printf("  Page Up/Down - Zoom in/out");
    printf("  Right Mouse + Drag - Rotate camera");
    printf(" ");
    printf("MOUSE CONTROLS:");
    printf("  Left Mouse + Drag - Rotate entire robot");
    printf("  Right Mouse + Drag - Control camera view");
    printf(" ");
    printf("SPECIAL FUNCTIONS:");
    printf("  SPACEBAR - Toggle walking animation");
    printf("  C - Reset robot to center position");
    printf("  ESC - Exit program");
    printf(" ");
    printf("========================================================");
    printf(" ");
}

/*
 * Function: initializeOpenGL
 * Purpose: Set up OpenGL rendering parameters
 */
void initializeOpenGL() {
    // Set background color to dark blue
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

    // Enable depth testing for proper 3D rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable color material (allows glColor to affect lighting)
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Enable smooth shading
    glShadeModel(GL_SMOOTH);

    // Enable normalization of normals (important for lighting with scaling)
    glEnable(GL_NORMALIZE);

    // Set up material properties
    GLfloat materialShininess[] = {50.0f};
    GLfloat materialSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
}

/*
 * Function: main
 * Purpose: Main program entry point - initializes GLUT and starts the main loop
 * Parameters: argc - command line argument count, argv - command line arguments
 */
int main(int argc, char** argv) {
    // Print welcome message and instructions
    printf(" ");
    printf("####################################################");
    printf("#        OPENGL ROBOT PROJECT - CODEBLOCKS        #");
    printf("#              Computer Graphics Assignment         #");
    printf("####################################################");
    printf(" ");
    printf("Initializing OpenGL Robot Program...");
    printf("Graphics API: OpenGL with GLUT");
    printf("IDE: CodeBlocks");
    printf("Platform: Windows");
    printf(" ");

    // Initialize GLUT with command line arguments
    glutInit(&argc, argv);

    // Set display mode: double buffered, RGB color, depth buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Set initial window size
    glutInitWindowSize(1000, 700);

    // Set initial window position on screen
    glutInitWindowPosition(100, 50);

    // Create the main window with title
    glutCreateWindow("OpenGL Robot Project - CodeBlocks | Use Keyboard & Mouse to Control");

    // Initialize OpenGL settings
    initializeOpenGL();

    // Print control instructions
    printInstructions();

    // Register callback functions with GLUT
    glutDisplayFunc(display);       // Called when window needs redrawing
    glutReshapeFunc(reshape);       // Called when window is resized
    glutKeyboardFunc(keyboard);     // Called when normal key is pressed
    glutSpecialFunc(specialKeys);   // Called when special key is pressed
    glutMouseFunc(mouse);           // Called when mouse button is pressed/released
    glutMotionFunc(mouseMotion);    // Called when mouse moves with button down
    glutIdleFunc(idle);             // Called when no events are pending

    printf("Setup complete! Robot is ready for control.");
    printf("Use the controls listed above to interact with the robot.");
    printf(" ");

    // Start the GLUT event processing loop
    // This function never returns - the program ends when the window is closed
    glutMainLoop();

    return 0;  // This line is never reached, but included for completeness
}

/*
 * ========================================================================
 * END OF PROGRAM
 * ========================================================================
 *
 * This completes the OpenGL Robot project. The program creates a fully
 * interactive 3D robot with the following features:
 *
 * 1. Complete 3D robot model with head, torso, arms, and legs
 * 2. Keyboard controls for robot movement and rotation
 * 3. Mouse controls for interactive manipulation
 * 4. Individual limb control for detailed positioning
 * 5. Automatic walking animation with smooth motion
 * 6. Professional lighting and shading
 * 7. Camera system with zoom and rotation
 * 8. Ground plane and grid for spatial reference
 * 9. Console feedback for all user interactions
 * 10. Comprehensive error handling and user guidance
 *
 * The code is extensively commented to explain every function, variable,
 * and OpenGL operation, making it perfect for learning computer graphics
 * programming concepts.
 * ========================================================================
 */
