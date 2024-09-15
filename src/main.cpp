// OpenGL Function Pointers
#include <glad/glad.h>

// GLFW Library and OpenGL
#include "GLFW/glfw3.h"

// For TTF Font Loading
#include "ft2build.h"
#include FT_FREETYPE_H

// OpenGL Mathematics Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Header Files
#include "Shader.h"
#include "Text.h"
#include "Application.h"

// Standard Libraries
#include <iostream>
#include <map>
#include <utility>
#include <string>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        Text* text = static_cast<Text*>(glfwGetWindowUserPointer(window));
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE); // Close the window if ESC is pressed
        }
        else if (key == GLFW_KEY_BACKSPACE) {
            text->delChar();
        }
        else if (key != GLFW_KEY_LEFT_SHIFT && key != GLFW_KEY_RIGHT_SHIFT && key != GLFW_KEY_TAB && key != GLFW_KEY_ENTER) {
            if (mods == GLFW_MOD_SHIFT) {
                text->addChar(key);
            }
            else {
                text->addChar(key+32);
            }
        }
    }   
}

// settings
const unsigned int SCR_WIDTH= 1920;
const unsigned int SCR_HEIGHT = 1080;

int main() {

    // // Initialize GLFW
    // // ______________________________
    // glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // // Create GLFW Window
    // // ______________________________
    // GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Text", NULL, NULL);
    // if (window == NULL)
    // {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }
    // glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // Load OpenGL Function Pointers
    // // ______________________________
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }
    
    // // OpenGL state
    // // ______________________________
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// // find path to font
    // std::string font_name = "assets/fonts/cour.ttf";
    // Text courier = Text(font_name);

    // double cursor_x = 25.0;
    // double cursor_y = 1000.0;

    // glfwSetWindowUserPointer(window, &courier);
    // glfwSetKeyCallback(window, key_callback);

    // // render loop
    // // -----------
    // while (!glfwWindowShouldClose(window))
    // {
    //     // render
    //     // ------
    //     glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     courier.renderText(cursor_x, cursor_y, 0.5f, glm::vec3(0.0, 0.0f, 0.0f));
       
    //     // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    //     // -------------------------------------------------------------------------------
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }

    // glfwTerminate();

    Application app = Application();
    app.run();

    return 0;
}

