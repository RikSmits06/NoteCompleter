#include "EditField.h"

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "AutoCompleteBox.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "../AutoComplete/trieComplete.h"
#include "GLFW/glfw3.h"

// For each file we create a buffer of a standard size.
// The caller first has to register the file before rendering it.
namespace
{
    // Flags for creating the window.
    constexpr ImGuiWindowFlags FLAGS = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoResize;
    constexpr uint32_t STANDARD_BUFFER_SIZE = 10000;
    std::unordered_map<std::string, char*> buffers;


    /// Gets the word the person is currently typing.
    /// @param buffer The buffer of the current file.
    /// @param bufferSize The size of this buffer.
    /// @param cursorPosition Where in the buffer to search for the word.
    /// @return Returns the word the user is currently typing.
    std::string extractCurrentWord(const char* buffer, int bufferSize, int cursorPosition)
    {
        // We go left and right of the current position and append the letters.
        std::string ret;
        int i = cursorPosition - 1;
        while (i >= 0 && std::isalpha(buffer[i]))
        {
            ret.insert(ret.begin(), buffer[i]);
            i--;
        }

        i = cursorPosition;
        while (i < bufferSize && std::isalpha(buffer[i]))
        {
            ret.push_back(buffer[i]);
            i++;
        }

        return ret;
    }

    int editCallback(ImGuiInputTextCallbackData* data)
    {
        std::string currentWord = extractCurrentWord(data->Buf, data->BufSize, data->CursorPos);
        AutoCompleteWidget::setAutoCompleteWord(currentWord);
        return 0;
    }
}


void EditWidget::registerFile(const std::string& title)
{
    buffers[title] = static_cast<char*>(calloc(STANDARD_BUFFER_SIZE, 1));
}

void EditWidget::addEditField(const std::string& title)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin(title.c_str(), nullptr, FLAGS);
    ImGui::PushItemWidth(io.DisplaySize.x);
    ImGui::InputTextMultiline("##", buffers[title], STANDARD_BUFFER_SIZE,
                              ImGui::GetContentRegionAvail(),
                              ImGuiInputTextFlags_AllowTabInput |
                              ImGuiInputTextFlags_CallbackEdit,
                              editCallback);
    ImGui::PopItemWidth();
    ImGui::End();
}


void EditWidget::deregisterFile(const std::string& title)
{
    free(buffers[title]);
}
