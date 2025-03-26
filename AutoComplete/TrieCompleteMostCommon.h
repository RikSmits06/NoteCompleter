//
// Created by Thore on 24/03/2025.
//

#pragma once
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "autoComplete.h"

namespace autoComplete
{
    struct TrieNode
    {
        std::string word;
        std::unordered_map<char, TrieNode*> children;
        uint32_t weight;
    };


    class TrieCompleteMostCommon : public AutoComplete
    {
    public:
        ~TrieCompleteMostCommon() override;

        void addWord(std::string word) override;


        /// Adds a word to the autoComplete structure but with a weight for the word
        /// @param word The word to add.
        /// @param weight Weight of the word; the lower, the more common it is.
        void addWord(std::string word, uint32_t weight);

        std::vector<std::string> retrieveWords(std::string prefix, uint32_t max) override;

        /// Retrieves <max> words that best match the prefix.
        /// @param prefix The prefix to search for.
        /// @param max The max amount of words retrieved/returned.
        /// @param maxSearchLimit The max amount of words being searched. The higher, the more accurate the most common sort is.
        /// @return Returns a list of words matching the prefix.
        std::vector<std::string> retrieveWords(std::string prefix, uint32_t max, uint32_t maxSearchLimit);

    private:
        TrieNode root;
    };
}
