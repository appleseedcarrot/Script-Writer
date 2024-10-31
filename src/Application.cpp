// Header Files
#include "Application.h"

// Standard Libraries
#include <iostream>
#include <string>

#include <chrono>


// Constructor
//
// Initializes GLFW3 with an OpenGL Context Version 4.1 Core. OpenGL function pointers
// are loaded using GLAD, and a fullscreen window is opened.
//
Application::Application() {
    init();
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
    // Set blending modes
    //
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Create new Text object for rendering text and point instance to window
    //
    this->text = new Text("assets/fonts/cour.ttf");
    glfwSetWindowUserPointer(window, this->text);
    // Setup GLFW key callback and window resize callback
    //
    glfwSetKeyCallback(window, keyPress);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
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
    // Initialize variables for cursor
    //
    auto lastTime = std::chrono::steady_clock::now();
    bool cursorVisible = true;
    const float blinkInterval = 0.5f;  // 500ms blink interval

    while (!glfwWindowShouldClose(window))
    {
        // Clear screen
        // 
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        text->renderText(100, 500, 1.0f, glm::vec3(0.0, 0.0f, 0.0f), "");

        // Check if cursor should blink
        //
        auto currentTime = std::chrono::steady_clock::now();
        float elapsedTime = std::chrono::duration<float>(currentTime - lastTime).count();
        if (elapsedTime >= blinkInterval) {
            cursorVisible = !cursorVisible;  // Toggle cursor visibility
            lastTime = currentTime;
        }
        
        // Get the cursor position at the end of the text
        float cursorX = text->getTextWidth() + 100; // Assume getTextWidth() gives width of current text
        float cursorY = 500;  // Same Y position as text

        // Render the cursor if visible
        if (cursorVisible) {
            text->renderText(cursorX, cursorY, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), "|");  // Render cursor as "|"
        }

        // Swap buffer and check for incoming events
        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::keyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // On key press...
    //
    if (action == GLFW_PRESS) {
        // Retrieve pointer to current instance of Application
        //
        Text* text = static_cast<Text*>(glfwGetWindowUserPointer(window));
        
        // Handle Escape (Closes Window)
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE); // Close the window if ESC is pressed
        }
        // Handle Backspace (Deletes last character)
        else if (key == GLFW_KEY_BACKSPACE) {
            text->delChar();
        }
        // Handle Spacebar
        else if (key == GLFW_KEY_SPACE) {
            text->addChar(' ');
        }
        else if ((key >= GLFW_KEY_A && key <= GLFW_KEY_Z) || (key >= GLFW_KEY_0 && key <= GLFW_KEY_9) ||
                 (key == GLFW_KEY_GRAVE_ACCENT || key == GLFW_KEY_MINUS ||  key == GLFW_KEY_EQUAL || 
                 key == GLFW_KEY_LEFT_BRACKET || key == GLFW_KEY_RIGHT_BRACKET  || key == GLFW_KEY_BACKSLASH ||
                 key == GLFW_KEY_SEMICOLON || key == GLFW_KEY_APOSTROPHE || key == GLFW_KEY_COMMA ||
                 key == GLFW_KEY_PERIOD || key == GLFW_KEY_SLASH)) {
            // Stores character to add to text structure
            char character;
            // If the shift modifier is pressed, handle uppercase and special characters
            if (mods & GLFW_MOD_SHIFT) {
                if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
                    // Uppercase letters
                    character = static_cast<char>(key);  // GLFW key codes for A-Z match ASCII directly
                } else {
                    // Handle shifted special characters (punctuation, etc.)
                    switch (key) {
                        case GLFW_KEY_1: character = '!'; break;
                        case GLFW_KEY_2: character = '@'; break;
                        case GLFW_KEY_3: character = '#'; break;
                        case GLFW_KEY_4: character = '$'; break;
                        case GLFW_KEY_5: character = '%'; break;
                        case GLFW_KEY_6: character = '^'; break;
                        case GLFW_KEY_7: character = '&'; break;
                        case GLFW_KEY_8: character = '*'; break;
                        case GLFW_KEY_9: character = '('; break;
                        case GLFW_KEY_0: character = ')'; break;
                        case GLFW_KEY_GRAVE_ACCENT: character = '~'; break;
                        case GLFW_KEY_MINUS: character = '_'; break;
                        case GLFW_KEY_EQUAL: character = '+'; break;
                        case GLFW_KEY_LEFT_BRACKET: character = '{'; break;
                        case GLFW_KEY_RIGHT_BRACKET: character = '}' ; break;
                        case GLFW_KEY_BACKSLASH: character = '|'; break;
                        case GLFW_KEY_SEMICOLON: character = ':'; break;
                        case GLFW_KEY_APOSTROPHE: character = '"'; break;
                        case GLFW_KEY_COMMA: character = '<'; break;
                        case GLFW_KEY_PERIOD: character = '>'; break;
                        case GLFW_KEY_SLASH: character = '?'; break;
                        
                        default: return;  // Unhandled key
                    }
                }
            } else {
                // Without shift, use lowercase letters and normal numbers/special characters
                if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
                    character = static_cast<char>(key + 32);  // Convert to lowercase ASCII
                } else {
                    // Handle non-shifted numbers and special characters
                    switch (key) {
                        case GLFW_KEY_1: character = '1'; break;
                        case GLFW_KEY_2: character = '2'; break;
                        case GLFW_KEY_3: character = '3'; break;
                        case GLFW_KEY_4: character = '4'; break;
                        case GLFW_KEY_5: character = '5'; break;
                        case GLFW_KEY_6: character = '6'; break;
                        case GLFW_KEY_7: character = '7'; break;
                        case GLFW_KEY_8: character = '8'; break;
                        case GLFW_KEY_9: character = '9'; break;
                        case GLFW_KEY_0: character = '0'; break;
                        case GLFW_KEY_GRAVE_ACCENT: character = '`'; break;
                        case GLFW_KEY_MINUS: character = '-'; break;
                        case GLFW_KEY_EQUAL: character = '='; break;
                        case GLFW_KEY_LEFT_BRACKET: character = '['; break;
                        case GLFW_KEY_RIGHT_BRACKET: character = ']'; break;
                        case GLFW_KEY_BACKSLASH: character = '\\'; break;
                        case GLFW_KEY_SEMICOLON: character = ';'; break;
                        case GLFW_KEY_APOSTROPHE: character = '\''; break;
                        case GLFW_KEY_COMMA: character = ','; break;
                        case GLFW_KEY_PERIOD: character = '.'; break;
                        case GLFW_KEY_SLASH: character = '/'; break;
                        
                        default: return;  // Unhandled key
                    }
                }
            }

            // Add the character to the text object
            text->addChar(character);
        }
    }   
}

void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}