//
// application.cpp
//
// Application window, handles lifetime and GUI interface of main window.

#include "application.h"

//
// Constructor
//
Application::Application(int height, int width) {

    // Create Window
    this->window = SDL_CreateWindow("Text Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, width, SDL_WINDOW_RESIZABLE);

    if (this->window == NULL) {
        std::cout << "Window could not be created. SDL error " << SDL_GetError() << std::endl;
        this->init = false;
    }

    // Initialize Renderer
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (this->renderer == NULL) {
        std::cout << "Renderer could not be created. SDL error " << SDL_GetError() << std::endl;
        this->init = false;
    }

    this->init = true;
}

//
// Destructor
//
Application::~Application() {
    // Close Renderer
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        std::cout << "renderer closed\n";
    }

    // Close Window
    if (this->window) {
        SDL_DestroyWindow(this->window);
        std::cout << "window closed\n";
    }
}

//
// isInit()
//
// Checks if window and renderer have been properly initialized
//
bool Application::isInit() const {
    return this->init;
}

void Application::run() {
    if (!window || !renderer) {
        std::cerr << "SDL not properly initialized!" << std::endl;
        return;
    }

    // Run Program
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

    }
}