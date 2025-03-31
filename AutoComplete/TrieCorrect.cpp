//
// Created by Thore on 30/03/2025.
//

#include "TrieCorrect.h"

typedef autoComplete::TrieNodeCorrect Node;

autoComplete::TrieCorrect::~TrieCorrect()
{
}

void autoComplete::TrieCorrect::addWord(std::string word)
{
}

void autoComplete::TrieCorrect::addWord(std::string word, std::string correct)
{
    Node* current = &root;
    // Navigating to the words place.
    for (char c : word)
    {
        if (!current->children.count(c))
        {
            current->children[c] = new Node;
        }
        current = current->children[c];
    }

    // Setting the word and the correct word.
    current->word = word;
    current->correct = correct;
}

std::vector<std::string> autoComplete::TrieCorrect::retrieveWords(std::string prefix, uint32_t max)
{
    std::vector<std::string> ret;

    // Getting to the place of the prefix.
    Node* current = &root;
    for (char c : prefix)
    {
        if (!current->children.count(c))
        {
            return ret;
        }
        current = current->children[c];
    }
    // Going down the tree until a word is found.
    std::vector<Node*> toCheck;
    toCheck.push_back(current);

    while (!toCheck.empty() && ret.size() < max)
    {
        // Pops the first node to check for a word.
        Node* checkingNode = toCheck[0];
        toCheck.erase(toCheck.begin());

        // Check if it contains a word.
        if (!checkingNode->word.empty())
        {
            ret.push_back(checkingNode->correct);
        }

        // Adding children to check list.
        for (auto child : checkingNode->children)
        {
            toCheck.push_back(child.second);
        }
    }
    return ret;
}
