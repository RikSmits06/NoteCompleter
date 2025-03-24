//
// Created by rikhj on 17/03/2025.
//

#include "trieComplete.h"

#include <mutex>
#include <ostream>
#include <unordered_map>
#include <vector>

typedef autoComplete::TrieNode Node;


autoComplete::TrieComplete::~TrieComplete()
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

void autoComplete::TrieComplete::addWord(std::string word)
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
}

std::vector<std::string> autoComplete::TrieComplete::retrieveWords(std::string prefix, uint32_t max)
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
            ret.push_back(checkingNode->word);
        }

        // Adding children to check list.
        for (auto child : checkingNode->children)
        {
            toCheck.push_back(child.second);
        }
    }

    return ret;
}
