#pragma once
#include <GLFW/glfw3.h>

#include "imgui.h"

/// Class encapsulating the main note-taking app.
class App
{
public:
    App();

    /// Starts running the app in a loop.
    void run();

    /// Destroys all allocated resources, should be called after run.
    void destroy();

private:
    GLFWwindow* window;
};
