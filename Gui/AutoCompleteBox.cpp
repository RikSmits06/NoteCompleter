#include "AutoCompleteBox.h"

#include <fstream>
#include <iostream>

#include "EditField.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "../AutoComplete/trieComplete.h"

namespace
{
    bool showing = true;
    autoComplete::TrieComplete completer = autoComplete::TrieComplete();
    std::string prefix;
    bool completerFilled = false;
}

void AutoCompleteWidget::showAutoComplete()
{
    showing = true;
}

void AutoCompleteWidget::renderAutoComplete()
{
    if (!completerFilled)
    {
        completerFilled = true;
        std::ifstream file("../words.txt");
        std::string line;
        while (std::getline(file, line))
        {
            completer.addWord(line);
        }
        file.close();
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(io.Ctx->PlatformImeData.InputPos);
    ImGui::Begin("##", nullptr,
                 ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_AlwaysAutoResize |
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    for (std::string suggestion : completer.retrieveWords(prefix, 5))
    {
        ImGui::Text(suggestion.c_str());
    }
    ImGui::End();
}

void AutoCompleteWidget::setAutoCompleteWord(std::string word)
{
    prefix = word;
}

void AutoCompleteWidget::hideAutoComplete()
{
    showing = false;
}
