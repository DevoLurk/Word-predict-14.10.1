#include <fstream>
#include "Trie.h"

using namespace std;

int main()
{
    string buf;
    string filename = "english.txt";
    ifstream fin(filename, std::ios::in);
    Trie trie;

    if (!fin.is_open())
    {
        cout << "\tcustom dictionary file was not found\n\n";
    }
    else
    {
        while (getline(fin, buf))
            trie.insert(buf);

        fin.close(); // no need to keep it open

        cout << "\tcustom dictionary loaded\n\n";

        trie.search("abuse");
        trie.search("below");
        trie.search("zoo");

        trie.remove("abuse");
        trie.search("abuse");

        trie.predict();
    }

    return 0;
}
