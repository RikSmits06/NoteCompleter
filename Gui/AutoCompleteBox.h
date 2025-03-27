#pragma once
#include <string>

namespace AutoCompleteWidget
{
    // The minimum amount of chars that need to be typed before the box appears.
    constexpr uint8_t MIN_CHAR_COUNT = 2;

    /// Shows the auto complete box with suggestions.
    void renderAutoComplete();

    /// Checks wheter the autocomplete is rendered.
    /// @return Returns true if the autocomplete is showing.
    bool isShowing();


    /// Retrieves the currently marked sellection.
    /// @return Returns the current string the complete is suggesting.
    std::string getCurrentSuggestion();

    // Sets the prefix to autocomplete for.
    void setAutoCompleteWord(std::string word);
}
