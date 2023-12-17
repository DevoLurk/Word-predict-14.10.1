#include "Trie.h"

Trie::Trie()
{
    root = getNewNode();
}

Trie::~Trie()
{
    delete root;
}

Trie::TrieNode* Trie::getNewNode()
{

    TrieNode* pNode = new TrieNode;         
    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    pNode->frequency = 0;

    return pNode;
}


void Trie::insert(std::string key)
{
    TrieNode* current = this->root;

    for (auto i{ 0 }; i < key.size(); i++)
    {
        char symb = key[i];
        int ind = key[i] - 'a';

        if (current->children[ind] == nullptr)
            current->children[ind] = getNewNode();

        current = current->children[ind];
        current->frequency++;
    }

    current->isEndOfWord = true;
}

bool Trie::search_(std::string key)
{
    TrieNode* node = this->root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';

        if (node->children[index] == nullptr)
            return false;

        node = node->children[index];
    }

    return ((node != nullptr) && (node->isEndOfWord));
}

void Trie::search(std::string key)
{
    if (search_(key))
        printf("%12s was found\n" , key.c_str());
    else
        printf("%12s was not found\n", key.c_str());
}

bool Trie::isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

Trie::TrieNode* Trie::remove(TrieNode* root, std::string key, int depth)
{

    if (!root)
        return nullptr;

    if (depth == key.size())
    {
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        if (isEmpty(root))
        {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    if (isEmpty(root) && root->isEndOfWord == false)
    {
        delete (root);
        root = nullptr;
    }

    return root;
}

void Trie::remove(std::string key)
{
    if (search_(key))
    {
        printf("%12s was removed\n", key.c_str());
        this->root = remove(this->root, key);
    }
    else
        printf("%12s was not removed\n", key.c_str());

}

void Trie::predict()
{
    std::string input;

    std::cout << std::endl << std::endl;
    std::cout << "input \\ex to out" << std::endl;

    while (true)
    {
        std::cout << "input beginning = ";
        std::cin >> input;

        if (input == "\\ex")
            break;

        TrieNode* node = this->root;
        int cnt = 0;

        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] < 'a' || input[i] > 'z') // if not a symbol we need
                break;

            int index = input[i] - 'a';

            if ((node->children[index] != nullptr) && !(node->isEndOfWord))
            {
                cnt++;
                node = node->children[index];
            }
            else
                break;
        }

        if (cnt != input.length()) // if we didnt find input
        {
            printf("%12s no such word start found\n", input.c_str());
            continue;
        }

        std::cout << "\033[32m";
        printFrom(node, input);
        std::cout << "\033[0m";
        std::cout << std::endl;
    }
}

void Trie::printFrom(TrieNode* node, std::string word)
{
    if (node->isEndOfWord)
    {
        printf("     %s", word.c_str());

        if(node->frequency == 1)
            return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i] != nullptr)
        {
            word.push_back((char)i + 'a');
            printFrom(node->children[i], word);
            word.pop_back();
        }
}