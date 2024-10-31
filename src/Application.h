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
        GLFWwindow* window;
        
        // Handle initialization of GLFW and OpenGL for the constructor
        //
        void init();
        // Creates a new maximized GLFW window for the constructor
        //
        void newWindow();
        // Manages key press events for GLFW and updates the application accordingly
        //
        static void keyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
        // Manages resizing of openGL viewport to match window resizing
        //
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    public:
        //
        // run()
        //
        // This function starts the main rendering loop and handles user input and rendering objects
        // until the application is closed
        //
        void run();
        Text* text;
};