// OpenGL Function Pointers
#include <glad/glad.h>

// GLFW Library
#include "GLFW/glfw3.h"

// Header Files
#include "Text.h"

#pragma once

class Application {

    public: 
        Application();
        ~Application();

    private:
        int windowWidth;
        int windowHeight;
        GLFWwindow* window;

        //
        // init()
        //
        // This function handles initialization of GLFW and OpenGL for the constructor
        //
        void init();
        //
        // newWindow()
        //
        // This function creates a new GLFW window with the inputted window mode in use for the constructor
        //
        void newWindow();

        //
        // keyPress()
        //
        // This function manages key press events for GLFW and updates the application accordingly
        //
        void keyPress(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
        //
        // run()
        //
        // This function starts the main rendering loop and handles user input and rendering objects
        // until the application is closed
        //
        void run();

    private:
        Text* text;
};