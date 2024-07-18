#include "application.h"

bool appInit() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO < 0)) {
        std::cout << "SDL could not be initialized. SDL error " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

int main() {

    // Initialize SDL and SDL_TTF
    if (!appInit()) {
        return -1;
    }

    // Initialize Main Program
    Application editor = Application(1920,1080);
    if (!editor.isInit()) {
        return -1;
    }

    editor.run();

    // Quit SDL
    SDL_Quit();

    // End Program
    return 0;
}