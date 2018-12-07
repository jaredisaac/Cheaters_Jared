// Jared Vochoska - jiv329
#include <iostream>
#include <dirent.h>
#include <vector>
#include <fstream>
#include "hashTable.h"

using namespace std;


// function getdir
// attempts to open specified directory path and populate passed vector with all file names in directory
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


int main(int argc, char *argv[]) {

    argc = 4;
    // argv[2] = "6";
    // argv[3] = "200";
    // argv[1] = "sm_doc_set";

    if (argc < 4)
        return 1;   // Only continue with program if proper number of arguments have been given

    hashTable *h = new hashTable;

    const string filePath = "sm_doc_set";
    const int chunkSize = atoi("6");
    const int cheatMin = atoi("200");
    const int tableSize = h->getTableSize();


    // const int chunkSize = atoi(argv[2]);
    // const int cheatMin = atoi(argv[3]);

    vector<string> files;
    // getdir(argv[1], files);
    getdir(filePath, files);
    files.erase(files.begin(), files.begin() + 2);  // Take out . and .. from list

    // Go through each file in directory and populate hash table with chunk instances
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
            // call hashing function
            h->myHash(wordChunk, i);

            chunk.erase(chunk.begin());   // move window
            // insert into hash table now
        }
        inFile.close();
    }

    // obtain results based on minimum similarity value set by user
    vector<string> results = h->traverseMap(files, cheatMin);
    // print results to console in descending order of similarities
    for (int i = 0; i < results.size(); i++)
        cout << results[i] << endl;
    return 0;
}