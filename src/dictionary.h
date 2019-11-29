#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;

class hash_function
{
public:

    //FNV
    unsigned int operator()( const string& s )  const {

        unsigned int hashValue = 2166136261u;

        for (int i = 0; i < s.length(); ++i)
        {
            hashValue ^= s[i];
            hashValue *= 16777619u; // простое число
        }

        return hashValue;
    }
};

class equality
{
public:
    equality() {}
    bool  operator()( const string& A, const string& B )  const 
    {
        return  (A == B);
    }
};

class Dictionary: public HashSet<string, hash_function, equality> {

    // Complete definition
public:
	Dictionary(string filename);

};
#endif // _DICTIONARY_H_
