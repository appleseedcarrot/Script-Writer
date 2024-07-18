//
// application.h
//
// Main application lifetime and GUI interfaces

// For Rendering
#include "SDL.h"

// For TTF Font Loading
#include "ft2build.h"

// Standard Libraries
#include <iostream>

#pragma once

class Application {

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool init;

    public:
        Application(int height, int width);
        ~Application();
        bool isInit() const;
        void run();
};