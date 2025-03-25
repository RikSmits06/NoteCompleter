#include "AutoCompleteBox.h"

#include <fstream>
#include <iostream>

#include "EditField.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "../AutoComplete/TrieCompleteMostCommon.h"

#include "imgui_impl_opengl3_loader.h"

namespace
{
    bool showing = true;
    autoComplete::TrieCompleteMostCommon completer = autoComplete::TrieCompleteMostCommon();
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
        std::ifstream file("../NoteCompleter/Words/wordsMostCommon.txt");
        std::string line;
        // Counter to increase the weight of each word (only works if the words in the file are ordered from most common to least common!)
        uint32_t counter = 0;
        while (std::getline(file, line))
        {
            completer.addWord(line, counter);
            counter++;
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
