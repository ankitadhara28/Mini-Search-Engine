
#include "SearchEngine.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <cctype>
#include <windows.h>

using namespace std;

// Convert text into lowercase words
vector<string> tokenize(const string& text) {
    vector<string> words;
    string word;

    for (unsigned char ch : text) {
        if (isalnum(ch) || ch == '+') {
            word += static_cast<char>(tolower(ch));
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

// Read files and build the inverted index
void SearchEngine::indexDocuments(const string& folderPath) {
    string searchPath = folderPath + "\\*.txt";
    WIN32_FIND_DATAA fileData;

    HANDLE handle = FindFirstFileA(searchPath.c_str(), &fileData);

    if (handle == INVALID_HANDLE_VALUE) {
        cout << "Error: No text files found in the documents folder.\n";
        return;
    }

    int fileCount = 0;

    do {
        if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            string filename = fileData.cFileName;
            string fullPath = folderPath + "\\" + filename;

            ifstream file(fullPath);

            if (!file.is_open()) {
                continue;
            }

            string content;
            string line;

            while (getline(file, line)) {
                content += line + " ";
            }

            vector<string> words = tokenize(content);
            unordered_set<string> uniqueWords(
                words.begin(), words.end()
            );

            for (const string& word : uniqueWords) {
                invertedIndex[word].push_back(filename);
            }

            fileCount++;
        }
    } while (FindNextFileA(handle, &fileData));

    FindClose(handle);

    cout << "Indexing completed successfully!\n";
    cout << "Documents indexed: " << fileCount << "\n";
}

// Search documents and rank results by matching query words
void SearchEngine::search(const string& query) const {
    vector<string> queryWords = tokenize(query);

    if (queryWords.empty()) {
        cout << "Please enter a valid search query.\n";
        return;
    }

    unordered_map<string, int> scores;

    unordered_set<string> uniqueQueryWords(
        queryWords.begin(), queryWords.end()
    );

    for (const string& word : uniqueQueryWords) {
        auto it = invertedIndex.find(word);

        if (it != invertedIndex.end()) {
            for (const string& filename : it->second) {
                scores[filename]++;
            }
        }
    }

    if (scores.empty()) {
        cout << "No matching documents found.\n";
        return;
    }

    vector<pair<string, int>> results(
        scores.begin(), scores.end()
    );

    sort(results.begin(), results.end(),
         [](const auto& a, const auto& b) {
             if (a.second != b.second) {
                 return a.second > b.second;
             }

             return a.first < b.first;
         });

    cout << "\nSearch Results:\n";

    for (const auto& result : results) {
        cout << "File: " << result.first
             << " | Relevance Score: " << result.second
             << "\n";
    }
}
