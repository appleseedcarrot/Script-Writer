# Script-Writer

Script Writer is a lightweight screenwriting application that you can use to write film scripts and plays. It is being developed by Christian Lee as an introduction to OpenGL developement and low-level graphics rendering.

# Dependencies

Script Writer requires these following libraries and packages

- SDL2
- Freetype2
- pkg-config

# Revisions

The following sections are dedicated to marking progress and key moments that helped me learn OpenGL.

### August 2, 2024

- Force OpenGL Core Version to work on MacOS
- M1 Macbook incorrectly loaded OpenGL 2.1 instead of the requested 4.1 -> Fixed by using Core Profile and Requesting 4.1 after SDL was initialized
- 
### August 1, 2024

- Added Freetype2 as a dependency
- Learned to Open .ttf type font files using Freetype2 and load individual character information onto a character map for future reference.
- Add glm as a dependency to handle font information and operations.
- Add GLAD as a dependency to link proper OpenGL function pointers to the graphics drivers implementations.
- Started to use implicit rules for the Makefile to generate build configuration.
- Fixed a problem where I used -I/include instead of -Iinclude, which meant the compiler was looking in the wrong place for GLAD and glm.

### July 18, 2024

Initial commit and project configuration:

- Learned how to setup a window using SDL2 properly close when finished
- Created a proper Makefile using basic syntax to configure the final executable