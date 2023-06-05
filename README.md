# OpenGLTemplate

Welcome !

This is a small template for starting new project with openGL.

## Compiling

You need to install [CMake](https://cmake.org/download/).

To use CMake I recommend this VS Code extension : [ms-vscode.cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools). You will need to setup the extension with a compiler. Here is [the tutorial](https://code.visualstudio.com/docs/cpp/cmake-linux). It is based on Linux but at the bottom of the page you will find the explanations to adapt it for [Windows](https://code.visualstudio.com/docs/cpp/config-msvc) and [Mac](https://code.visualstudio.com/docs/cpp/config-clang-mac).

Alternatively you can just create a *build* folder at the root of this project, open a terminal and run `cmake ..` ; chances are it will detect what compiler you have installed and generate the appropriate Makefile / Visual Studio solution / Xcode project.

## main.cpp

In here we initialize [*glfw*](https://www.glfw.org/docs/latest/) (the library that handles the window and user inputs), create a window and then start the app. You don't really need to modify this file, except to change your window name or initial size.

## User inputs

To learn more about the parameters you receive in the callbacks, read [glfw's documentation](https://www.glfw.org/docs/latest/input_guide.html).

## App

This is the actual root of your project. This is where your drawing code should go, as well as handling inputs from the user.

## Assets

As the asset paths are relative to the executable, we have two options: copy the asset folder next to the executable or use cmake's tricks to get the absolute project path to reference our assets.

 I chose the second option for my example (tips found [here](https://shot511.github.io/2018-05-29-how-to-setup-opengl-project-with-cmake/#:~:text=link_directories(%24%7BCMAKE_SOURCE_DIR%7D/lib)-,Resources,-Every%20OpenGL%20project))