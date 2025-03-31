#include "AutoCompleteBox.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "EditField.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "../AutoComplete/TrieCompleteMostCommon.h"

#include "imgui_impl_opengl3_loader.h"
#include "../AutoComplete/TrieCorrect.h"

namespace
{
    bool showing = false;
    autoComplete::TrieCompleteMostCommon completer = autoComplete::TrieCompleteMostCommon();
    autoComplete::TrieCorrect correcter = autoComplete::TrieCorrect();
    std::string prefix;
    std::vector<std::string> suggestions;
    uint32_t suggestionIndex = 0;
    bool completerFilled = false;
}

void AutoCompleteWidget::renderAutoComplete()
{
    if (!completerFilled)
    {
        completerFilled = true;
        std::ifstream file("../Words/wordsMostCommon.txt");
        std::string line;
        // Counter to increase the weight of each word (only works if the words in the file are ordered from most common to least common!)
        uint32_t counter = 0;
        while (std::getline(file, line))
        {
            line.erase(remove_if(line.begin(), line.end(), isspace));
            completer.addWord(line, counter);
            counter++;
        }
        file.close();
        file.open("../Words/wordAutoCorrect.csv");
        while (std::getline(file, line))
        {
            std::stringstream stream(line);
            std::string wrongWord;
            std::string correctWord;
            std::getline(stream, wrongWord, ',');
            std::getline(stream, correctWord, ',');
            correcter.addWord(wrongWord, correctWord);
        }
        file.close();
    }

    if (!showing)
    {
        return;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(io.Ctx->PlatformImeData.InputPos);
    ImGui::Begin("##", nullptr,
                 ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_AlwaysAutoResize |
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    for (std::size_t i = 0; i < suggestions.size(); i++)
    {
        std::string suggestion = suggestions[i];
        if (i == suggestionIndex)
        {
            ImGui::ButtonEx(suggestion.c_str());
        }
        else
        {
            ImGui::Text(suggestion.c_str());
        }
    }
    ImGui::End();
}

bool AutoCompleteWidget::isShowing()
{
    return showing;
}

std::string AutoCompleteWidget::getCurrentSuggestion()
{
    return suggestions[suggestionIndex];
}

void AutoCompleteWidget::setAutoCompleteWord(std::string word)
{
    prefix = word;
    // Increase max count in function to find the more common words higher in the tree.
    suggestions = completer.retrieveWords(prefix, 5, 40);
    //suggestions = correcter.retrieveWords(prefix, 5);
    if (suggestions.empty())
    {
        suggestions = correcter.retrieveWords(prefix, 5);
    }
    showing = (word.size() >= MIN_CHAR_COUNT) && !suggestions.empty();
}
