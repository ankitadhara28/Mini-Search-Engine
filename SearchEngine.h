
#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class SearchEngine {
private:
    // Maps each word to the documents containing it
    unordered_map<string, vector<string>> invertedIndex;

public:
    // Index all text files in the documents folder
    void indexDocuments(const string& folderPath);

    // Search documents using a user's query
    void search(const string& query) const;
};

#endif
