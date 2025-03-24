//
// Created by rikhj on 18/03/2025.
//

#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace autoComplete {
    class AutoComplete {
    public:
        virtual ~AutoComplete() = default;


        /// Adds a word to the autoComplete structure.
        /// @param word The word to add.
        virtual void addWord(std::string word) = 0;

        ///
        /// @param prefix The prefix to search for.
        /// @param max The max amount of words retrieved.
        /// @return Returns a list of words matching the prefix.
        virtual std::vector<std::string> retrieveWords(std::string prefix, uint32_t max) =0;
    };
}
