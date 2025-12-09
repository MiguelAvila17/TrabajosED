#include "trie.h"
Trie::Trie(){root_=new TrieNode();}
Trie::~Trie(){}
void Trie::insert(const std::string& s){TrieNode* p=root_; for(char c:s){ if(!p->next.count(c)) p->next[c]=new TrieNode(); p=p->next[c]; } p->end=true; }
void Trie::collect(TrieNode* n,std::string cur,std::vector<std::string>& out) const{ if(!n) return; if(n->end) out.push_back(cur); for(auto& kv:n->next) collect(kv.second,cur+kv.first,out);} 
std::vector<std::string> Trie::suggest(const std::string& p) const{ TrieNode* n=root_; for(char c:p){ if(!n->next.count(c)) return {}; n=n->next.at(c);} std::vector<std::string> r; collect(n,p,r); return r; }