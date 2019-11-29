#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"

Dictionary::Dictionary(string filename)
{
    ifstream fin;
    fin.open(filename);

    if (!fin.good())
    {
        throw invalid_argument("file is unavailable");
    }

    while (fin.good() && !fin.eof())
    {
        string word;
        fin >> word;
        this -> insert(word);
    }
}