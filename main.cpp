
#include <iostream>
#include <string>
#include "SearchEngine.h"

using namespace std;

int main() {
    SearchEngine engine;

    // Build the index from the documents folder
    engine.indexDocuments("documents");

    string query;

    while (true) {
        cout << "\nEnter your search query (or type 'exit' to quit): ";
        getline(cin, query);

        if (query == "exit" || query == "EXIT" || query == "Exit") {
            cout << "Exiting Mini Search Engine. Goodbye!\n";
            break;
        }

        engine.search(query);
    }

    return 0;
}
