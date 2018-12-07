// Jared Vochoska - jiv329

#include <vector>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#ifndef _HASH_H
#define _HASH_H

using namespace std;

class hashTable {

private:
    // defined size for hash table (prime number)
    static const int hashTSize = 1000003;

    struct hashNode {
        int data;
        hashNode *next;
    };

    hashNode *map[hashTSize];

    // recursive function to delete all hashNodes in a hashNode linked list
    void clearHashNodes(hashNode *ptr) {
        if (ptr != NULL)
            clearHashNodes(ptr->next);
        delete ptr;
    }

public:
    hashTable();

    int getTableSize();

    void myHash (const string &input, int fileIndex);

    vector<string> traverseMap(const vector<string> &files, int min);

    ~hashTable();
};

#endif