#include <fstream>
#include <iomanip>
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

        fin.close();

        cout << "\tcustom dictionary loaded\n\n";
    }

    trie.search("abuse");
    trie.search("below");
    trie.search("zoo");
    trie.remove("abuse");
    trie.search("abuse");

    trie.predict();

    cout << (int)'z' - 'a' << endl;
        
    return 0;
}
