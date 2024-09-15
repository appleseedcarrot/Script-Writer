// Header Files
#include "Application.h"

// Standard Libraries
#include <iostream>
#include <string>

// Constructor
//
// Initializes GLFW3 with an OpenGL Context Version 4.1 Core. OpenGL function pointers
// are loaded using GLAD, and a fullscreen window is opened.
//
Application::Application() {
    std::cout << "Initializing Application" << std::endl;
    init();
    this->text = new Text("assets/fonts/cour.ttf");
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

//
// Destructor
//
// Frees the current window and GLFW program
//
Application::~Application() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

//
// init()
//
// Handles GLFW initialization and loading of OpenGL function pointers for the application constructor
//
// Args: N/A
// Return: N/A
//
void Application::init() {
    // Initialize GLFW and OpenGL Version 4.1
    //
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Create GLFW window
    //
    newWindow();

    // Load OpenGL Function Pointers
    //
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

//
// newWindow()
//
// Creates a new, maximized GLFW window and sets the current context to the newly created window. 
//
// Args: N/A
// Return: N/A
//
void Application::newWindow() {
    // Create the window with any dimension - window will be maximized regardless
    //
    this->window = glfwCreateWindow(800, 600, "Script Writer", NULL, NULL);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the context of the window current
    glfwMakeContextCurrent(window);
}

//
// run()
//
// Renders one loop cycle of the application with a white background color.
//
// Args: N/A
// Return: N/A
//
void Application::run() {
    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // courier.renderText(cursor_x, cursor_y, 0.5f, glm::vec3(0.0, 0.0f, 0.0f));
       
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::keyPress() {
    
}