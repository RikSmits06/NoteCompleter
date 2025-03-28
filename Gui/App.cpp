#include "App.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "AutoCompleteBox.h"
#include "Logging.h"
#include "EditField.h"
#include "imgui_internal.h"

namespace
{
    /// Function used by glfw to tell us an error occurs. Terminates the program.
    /// @param error The code used to identify the error.
    /// @param description Short message descriping the error.
    [[noreturn]] void appGlfwErrorCallback(int error, const char* description)
    {
        char msgBuffer[128];
        (void)sprintf_s(msgBuffer, "(%d) %s", error, description);
        logError(msgBuffer);
        exit(0);
    }
}


App::App()
{
    // This will make all glfw errors print to the console.
    glfwSetErrorCallback(appGlfwErrorCallback);

    // Initializing library and creating a window to draw to.
    glfwInit();
    this->window = glfwCreateWindow(640, 480, "NoteCompleter", nullptr, nullptr);
    glfwMakeContextCurrent(this->window);

    // Loading the OpenGL functions and checking if it went well.
    int version = gladLoadGL(glfwGetProcAddress);

    if (!version)
    {
        logError("Failed to initialize OpenGL context");
        return;
    }

    // OpenGl Loaded correctly, yippie!!!
    char buffMsg[30];
    (void)sprintf_s(buffMsg, "Loaded OpenGL version %d.%d.", GLAD_VERSION_MAJOR(version),
                    GLAD_VERSION_MINOR(version));
    logInfo(buffMsg);

    // Initializing ImGui.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // Add custom font.
    io.Fonts->AddFontFromFileTTF("segoeui.ttf", 23);
    io.Fonts->Build();
    
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    logInfo("Created app window.");
}

void App::run()
{
    // Make screen clear black.
    logInfo("Entered main loop.");
    glClearColor(0, 0, 0, 1);

    EditWidget::registerFile("test.txt");

    while (!glfwWindowShouldClose(this->window))
    {
        // Starting new frame.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Drawing windows should be done here.
        EditWidget::addEditField("test.txt");
        AutoCompleteWidget::renderAutoComplete();

        // Clearing screen and drawing the windows.
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(this->window);

        // Updating the events of the window.
        glfwPollEvents();
    }
}

void App::destroy()
{
    // Closing resources.
    logInfo("Destroying window.");
    EditWidget::deregisterFile("test.txt");
    glfwDestroyWindow(this->window);
}
