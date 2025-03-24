//
// Created by rikhj on 17/03/2025.
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
    };


    class TrieComplete : public AutoComplete
    {
    public:
        ~TrieComplete() override;

        void addWord(std::string word) override;

        std::vector<std::string> retrieveWords(std::string prefix, uint32_t max) override;

    private:
        TrieNode root;
    };
}
