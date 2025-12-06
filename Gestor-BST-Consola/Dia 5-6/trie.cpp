#include "trie.h"

Trie::Trie() { root_ = new TrieNode(); }
Trie::~Trie() { /* no destructor profundo por simplicidad */ }

void Trie::insert(const std::string& s) {
    TrieNode* p = root_;
    for (char c : s) {
        if (!p->next.count(c)) p->next[c] = new TrieNode();
        p = p->next[c];
    }
    p->end = true;
}

void Trie::collect(TrieNode* node, std::string cur, std::vector<std::string>& out) const {
    if (!node) return;
    if (node->end) out.push_back(cur);
    for (auto& kv : node->next) collect(kv.second, cur + kv.first, out);
}

std::vector<std::string> Trie::suggest(const std::string& prefix) const {
    TrieNode* p = root_;
    for (char c : prefix) {
        if (!p->next.count(c)) return {};
        p = p->next.at(c);
    }
    std::vector<std::string> res; collect(p, prefix, res); return res;
}