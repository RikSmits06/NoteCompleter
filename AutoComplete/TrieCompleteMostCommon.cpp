//
// Created by Thore on 24/03/2025.
//

#include "TrieCompleteMostCommon.h"

#include <mutex>
#include <ostream>
#include <unordered_map>
#include <vector>
#include <map>

typedef autoComplete::TrieNode Node;


autoComplete::TrieCompleteMostCommon::~TrieCompleteMostCommon()
{
    // Makes an array with nodes which should be deleted. Gets all nodes from the root.
    std::vector<Node*> nodesToDelete;
    for (auto child : root.children)
    {
        nodesToDelete.push_back(child.second);
    }

    // Goes through all nodes which should be deleted.
    while (!nodesToDelete.empty())
    {
        // Grabs first node, we are deleting this.
        const Node* current = nodesToDelete[0];
        nodesToDelete.erase(nodesToDelete.begin());

        // Schedule children for deletion.
        for (auto child : current->children)
        {
            nodesToDelete.push_back(child.second);
        }

        // Finally delete the allocated node.
        delete current;
    }
}

void autoComplete::TrieCompleteMostCommon::addWord(std::string word)
{
    // call addWord with weight, but make it an arbitrarily high weight.
    addWord(word, 9999999);
}

void autoComplete::TrieCompleteMostCommon::addWord(std::string word, uint32_t weight)
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

    // Setting the word.
    current->word = word;
    current->weight = weight;
}

std::vector<std::string> autoComplete::TrieCompleteMostCommon::retrieveWords(std::string prefix, uint32_t max)
{
    std::vector<std::string> retOrdered;
    std::map<uint32_t, std::string> retWeight;
    
    // Getting to the place of the prefix.
    Node *current = &root;

    for (char c : prefix)
    {
        if (!current->children.count(c))
        {
            return retOrdered;
        }
        current = current->children[c];
    }
    
    // Going down the tree until a word is found.
    std::vector<Node *> toCheck;
    toCheck.push_back(current);

    while (!toCheck.empty() && retWeight.size() < max) {
        // Pops the first node to check for a word.
        Node *checkingNode = toCheck[0];
        toCheck.erase(toCheck.begin());
        // Check if it contains a word that is larger than the current prefix.
        if (!checkingNode->word.empty() && !(prefix.length() >= checkingNode->word.length())) {
            retWeight.insert({checkingNode->weight, checkingNode->word});
        }
        // Add all children nodes to the checklist.
        for (std::pair<const char, TrieNode *> child: checkingNode->children) {
            toCheck.push_back(child.second);
        }
    }
    // Extract words from retWeight in sorted order (smallest weight first).
    for (const auto &pair: retWeight) {
        retOrdered.push_back(pair.second);
    }
    
    return retOrdered;
}
