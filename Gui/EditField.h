#pragma once
#include <string>

namespace EditWidget
{
    /// Reserves space for the file for the editor.
    /// @param title The name of the file.
    void registerFile(const std::string& title);

    /// Creates an ImGui widget
    /// @param title The name of the file.
    void addEditField(const std::string& title);

    /// free's the reserved space.
    /// @param title The name of the file.
    void deregisterFile(const std::string& title);
}
