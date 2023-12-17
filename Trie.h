#ifndef TRIE
#define TRIE

#include<string>
#include<iostream>

const int ALPHABET_SIZE = 26; // english   lower case 

class Trie
{
    struct TrieNode
    {
        TrieNode* children[ALPHABET_SIZE];
        bool isEndOfWord;
        int frequency;
    };

private:
    TrieNode* root;

    bool isEmpty(TrieNode* root);
    bool search_(std::string key);   
    void printFrom(TrieNode* node, std::string word);
    TrieNode* remove(TrieNode* root, std::string key, int depth = 0);
    TrieNode* getNewNode();

public:
    Trie();
    ~Trie();

    void insert(std::string key);
    void search(std::string key);
    void remove(std::string key);
    void predict();
};

#endif // TRIE