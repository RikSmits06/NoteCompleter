#pragma once
#include <string>

namespace AutoCompleteWidget
{
    // The minimum amount of chars that need to be typed before the box appears.
    constexpr uint8_t MIN_CHAR_COUNT = 3;

    /// Shows the auto complete box with sugestions.
    void renderAutoComplete();

    // Sets the prefix to autocomplete for.
    void setAutoCompleteWord(std::string word);
}
