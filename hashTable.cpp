// Jared Vochoska - jiv329
#include "hashTable.h"
#include <algorithm>

using namespace std;


// Default constructor for hashTable class. initializes all locations to NULL
hashTable::hashTable() {
    for (int i = 0; i < hashTSize; i++)
        map[i] = NULL;
}


// return hashTable size
int hashTable::getTableSize() {
    return hashTSize;
}


// hashing function - inserts file index (in vector files) into corresponding location in hash table
void hashTable::myHash (const string &input, int fileIndex) {
    unsigned long int key = 0;
    int prime = 11;
    int exp = 1;

    for (int i = 0; i < input.size(); i++) {
        key += (exp * input[i]);
        exp = exp * prime;
    }

    key = (key % (2 * hashTSize)) % hashTSize;

    hashNode *ptr = map[key];
    if (map[key] != NULL) {
        if (map[key]->data != fileIndex) {
            ptr = new hashNode;
            ptr->data = fileIndex;
            ptr->next = map[key];
            map[key] = ptr;
        }
    } else {
        ptr = new hashNode;
        ptr->data = fileIndex;
        ptr->next = map[key];
        map[key] = ptr;
    }
}


vector<string> hashTable::traverseMap(const vector<string> &files, int min) {
    vector<string> retString;
    // Create and initialize 2D array used to store collisions
    int *collisionT[files.size()];
    for (int i = 0; i < files.size(); i++) {
        collisionT[i] = new int[files.size()];
        for (int j = 0; j < files.size(); j++)
            collisionT[i][j] = 0;
    }
    hashNode *ptr, *after;
    // Search for collisions and populate collision 2D array accordingly
    for (int i = 0; i < hashTSize; i++) {
        if (map[i] != NULL) {
            ptr = map[i];
            after = map[i]->next;

            while (after != NULL) {
                collisionT[ptr->data][after->data] += 1;
                after = after->next;
            }
        }
    }

    // use similarity min value passed by user to populate new, sorted array of collisions
    vector<int>sortedList;
    for(int i = 0; i < files.size();i++) {
        for(int j = 0; j < files.size();j++) {
            if(collisionT[i][j] > min) {
                sortedList.push_back(collisionT[i][j]);
            }
        }
    }

    // sort new array in descending order
    sort(sortedList.begin(), sortedList.end());
    reverse(sortedList.begin(), sortedList.end());

    // traverse final collision array and link file indeces to file names.
    // populate output vector with strings and return
    vector<int>::iterator iter = sortedList.begin();
    while (iter != sortedList.end()) {
        for (int i = 0; i < files.size(); i++) {
            for (int j = 0; j < files.size(); j++) {
                if (collisionT[i][j] == *iter) {
                    string printOut;
                    printOut += to_string(collisionT[i][j]);
                    printOut = printOut + ":" + files[i] + ", " + files[j];
                    retString.push_back(printOut);
                }
            }
        }
        iter++;
    }
    return retString;
}


// destructor for hashTable
hashTable::~hashTable() {
    for (int i = 0; i < hashTSize; i++) {
        if (map[i] != NULL)
            clearHashNodes(map[i]);
    }
}