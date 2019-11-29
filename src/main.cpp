#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw


#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);
void insertCheck(Dictionary& dict, set<string>& correct, const string& word);
void transposeCheck(Dictionary& dict, set<string>& correct, const string& word);
void replaceCheck(Dictionary& dict, set<string>& correct, const string& word);
void removeCheck(Dictionary& dict, set<string>& correct, const string& word);


// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char* argv[]) {
	
	// Output usage message if improper command line args were given.
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
        return EXIT_FAILURE;
    }

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}
	
	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);
    
	checkSpelling(inf, d);

	inf.close();

	return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict) {

	int line_number = 0;

	while (in) 
    {
		line_number++;
		set<string> totest;
		string line;
		getline(in, line);

  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;
		
		string word;
        set<string> correct;

		while (ss >> word) 
        {
            word = stripPunct(word);
            lower(word);

            if (!dict.search(word))
            {
                transposeCheck(dict, correct, word);
                removeCheck(dict, correct, word);
                replaceCheck(dict, correct, word);
                insertCheck(dict, correct, word);

                cout << "line " << line_number << ": '" << word << "'\n";
                cout << "\tsuggestions:\n";

                for (const string& cor : correct)
                {
                    cout << "\t\t" << cor << "\n";
                }

                correct.clear();
            }
		}
	}
}

void lower(string& s) {

    // Ensures that a word is lowercase
	for (int i = 0; i < s.length(); i++)
    {
		s[i] = tolower(s[i]);
	}
}

string stripPunct(const string& s) {

	// Remove any single trailing
	// punctuation character from a word.  
	if (ispunct(s[s.length() - 1]) ) 
    {
		return s.substr (0, s.length() - 1);
	}
	else 
    {
		return s;
	}
}

void transposeCheck(Dictionary& dict, set<string>& correct, const string& word)
{
    for (int i = 0; i < word.length() - 1; ++i)
    {
        string t(word);
        swap(t[i], t[i + 1]);

        if (dict.search(t))
        {
            correct.insert(t);
        }

    }
}

void removeCheck(Dictionary& dict, set<string>& correct, const string& word)
{
    for (int i = 0; i < word.length(); ++i)
    {
        string t(word);
        t.erase(i, 1);

        if (dict.search(t))
        {
            correct.insert(t);
        }
    }
}

void replaceCheck(Dictionary& dict, set<string>& correct, const string& word)
{
    for (int i = 0; i < word.length(); ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            string t(word);
            t[i] = c;

            if (dict.search(t))
            {
                correct.insert(t);
            }
        }
    }
}

void insertCheck(Dictionary& dict, set<string>& correct, const string& word)
{
    string t(word);
    string::const_iterator iter = t.begin();

    while (iter <= t.end())
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            iter = t.insert(iter, c);
            if (dict.search(t))
            {
                correct.insert(t);
            }

            iter = t.erase(iter);
        }

        ++iter;
    }
}
