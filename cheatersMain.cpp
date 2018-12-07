#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int myExponent(int base, int power) {
    int result = 1;
    for (int i = 0; i < power; i++)
        result = result * base;
    return result;
}


int getdir (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


unsigned long int myHash (const string &input, int tableSize) {
    unsigned long int returnKey = 0;
    for (int i = 0; i < input.length(); i++)
        returnKey += (input[input.length() - i - 1] * 11) % tableSize;
    return returnKey;
}


/* class hashTable {
public:
    hashTable() {
        for (int i = 0; i < hashTSize; i++)
            map[i] = NULL;
    }

    int hashSize() {
        return hashTSize;
    }

private:
 */

int main(int argc, char *argv[]) {

    argc = 4;
    // argv[2] = "6";
    // argv[3] = "200";
    // argv[1] = "sm_doc_set";

    if (argc < 4)
        return 1;   // Only continue with program if proper number of arguments have been given

    typedef struct hashNode {
        hashNode *next;
        int data;
    } hashNode;

    const int hashTSize = 300000;
    hashNode *map[hashTSize];
    for (int i = 0; i < hashTSize; i++)
        map[i] = NULL;

    // hashTable HashTable;

    const string filePath = "sm_doc_set";
    const int chunkSize = atoi("6");
    const int cheatMin = atoi("200");


    // const int chunkSize = atoi(argv[2]);
    // const int cheatMin = atoi(argv[3]);
    // const int hashSize = HashTable.hashSize();

    vector<string> files;
    // getdir(argv[1], files);
    getdir(filePath, files);
    files.erase(files.begin(), files.begin() + 2);  // Take out . and .. from list
    for (int i = 0;i < files.size();i++)
        cout << i << files[i] << endl;

    for (int i = 0; i < files.size(); i++) {
        string fName = filePath + "/" + files[i];
        ifstream inFile;
        inFile.open(fName.c_str());
        vector<string> chunk;
        string temp;
        // read in file chunks and populate hash table
        while (inFile) {
            while (chunk.size() < chunkSize && inFile) {
                inFile >> temp;
                chunk.push_back(temp);
            }
            string wordChunk;
            for (int j = 0; j < chunk.size(); j++)
                wordChunk = wordChunk + chunk[j];
            unsigned long int key = myHash(wordChunk, hashTSize);
            if (map[key] != NULL) {
                if (map[key]->data == i)
                    break;
            }
            hashNode *before = NULL, *ptr = map[key];
            while (ptr != NULL) {
                before = ptr;
                ptr = ptr->next;
            }
            ptr = new hashNode;
            ptr->data = i;
            ptr->next = NULL;
            if (before != NULL)
                before->next = ptr;
            chunk.erase(chunk.begin());
            // hashTable[hash(chunk, hashTableSize)] = i;
            // insert into hash table now
        }
        inFile.close();
    }

    vector<int> collisions;

    for (int i = 0; i < 300000; i++) {
        if (map[i] != NULL) {
            if (map[i]->next != NULL) {
                collisions.push_back(map[i]->data);
                collisions.push_back((map[i]->next)->data);
                collisions.push_back(9999999);
            }
        }
    }

    return 0;
}