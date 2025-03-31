//
// Created by Thore on 30/03/2025.
//

#pragma once
#include <unordered_map>

#include "autoComplete.h"

namespace autoComplete
{
    struct TrieNodeCorrect
    {
        std::string word;
        std::unordered_map<char, TrieNodeCorrect*> children;
        std::string correct;
    };
    
    class TrieCorrect : public AutoComplete
    {
    public:
        ~TrieCorrect() override;

        void addWord(std::string word) override;
        
        /// Add a word to the trie.
        /// @param word The word to add (the misspelled word).
        /// @param correct The correct word to replace {word} with.
        void addWord(std::string word, std::string correct);

        std::vector<std::string> retrieveWords(std::string prefix, uint32_t max) override;
    private:
        TrieNodeCorrect root;
    };
}

