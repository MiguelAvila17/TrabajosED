#pragma once
#include <vector>
#include <string>
#include <unordered_map>

struct TrieNode { bool end=false; std::unordered_map<char, TrieNode*> next; };

class Trie {
    TrieNode* root_;
    void collect(TrieNode* node, std::string cur, std::vector<std::string>& out) const;
public:
    Trie();
    ~Trie();
    void insert(const std::string& s);
    std::vector<std::string> suggest(const std::string& prefix) const;
};