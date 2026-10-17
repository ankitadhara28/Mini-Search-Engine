# 🔎 Mini Search Engine in C++

A lightweight, command-line search engine built using **C++** that indexes text documents and retrieves relevant results based on user queries. The project demonstrates how an **inverted index**, hash maps, and vectors can be used to build a simple yet efficient keyword-based search system.

## 📌 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [How It Works](#-how-it-works)
- [Project Structure](#-project-structure)
- [Technologies Used](#-technologies-used)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Sample Output](#-sample-output)
- [Algorithm and Data Structures](#-algorithm-and-data-structures)
- [Time and Space Complexity](#-time-and-space-complexity)
- [Challenges Faced and Solutions](#-challenges-faced-and-solutions)
- [Limitations](#-limitations)
- [Future Improvements](#-future-improvements)
- [Learning Outcomes](#-learning-outcomes)

## 🎯 Overview

Searching through multiple text files manually can be inefficient, especially as the number of documents increases.

This project addresses that problem by building an inverted index of the words found in a collection of text files. When a user enters a search query, the application looks up the query words in the index, identifies matching documents, and ranks them according to the number of distinct query words they contain.

The application runs in the command line and uses C++ Standard Template Library (STL) containers, file handling, text preprocessing, and sorting.

## ✨ Features

- **Document Indexing:** Reads and indexes `.txt` files from a specified documents folder.
- **Case-Insensitive Search:** Converts text and search queries to lowercase for consistent matching.
- **Inverted Index:** Maps each unique word to the filenames containing it.
- **Keyword-Based Retrieval:** Finds documents containing one or more search terms.
- **Relevance Ranking:** Assigns scores based on the number of distinct query words matched.
- **Sorted Results:** Displays higher-scoring documents first.
- **Input Validation:** Handles empty or invalid queries.
- **No-Match Handling:** Displays a helpful message when no documents match the query.
- **Interactive CLI:** Supports multiple searches in a single session.

## ⚙️ How It Works

The search engine follows four main steps.

### 1. Document Indexing

The application reads `.txt` files from the `documents/` directory and extracts their contents.

### 2. Text Preprocessing

The extracted text is tokenized into lowercase terms. Punctuation and whitespace separate words, while `+` is preserved to support terms such as `C++`.

For example:

`C++ Uses Data Structures`

becomes:

`c++`, `uses`, `data`, `structures`

Repeated words within the same document are indexed only once.

### 3. Inverted Index Construction

Each word is stored as a key in an `unordered_map`, with a vector of filenames containing that word as its value.

Example:

```text
"c++"         -> ["doc1.txt", "doc3.txt"]
"data"        -> ["doc1.txt", "doc2.txt"]
"graphs"      -> ["doc2.txt"]
"programming" -> ["doc3.txt"]
```

This structure helps the application retrieve candidate documents without scanning every file for each query.

### 4. Search and Relevance Ranking

When the user enters a query, the application preprocesses it and looks up each distinct query word in the inverted index.

Each document receives one point for every distinct query word it contains. The matching documents are then sorted by descending relevance score. If two documents have equal scores, their filenames are sorted alphabetically.

## 📁 Project Structure

```text
MiniSearchEngine/
│
├── main.cpp
│   └── Entry point and interactive search loop
│
├── SearchEngine.h
│   └── SearchEngine class declaration
│
├── SearchEngine.cpp
│   └── Indexing, tokenization, searching, and ranking logic
│
├── documents/
│   ├── doc1.txt
│   ├── doc2.txt
│   └── doc3.txt
│
└── README.md
    └── Project documentation
```

## 🛠️ Technologies Used

- **Language:** C++
- **Compiler:** GCC (G++)
- **Language Standard:** C++17
- **Data Structures:** `unordered_map`, `vector`, `unordered_set`
- **File Handling:** `ifstream`
- **Text Processing:** Character classification and case normalization
- **Sorting:** STL `sort()` with a custom comparator
- **File Discovery:** Windows API (`FindFirstFileA` and `FindNextFileA`)

## 🚀 Getting Started

### Prerequisites

Make sure you have:

- Windows operating system
- GCC/G++ compiler installed and available in your terminal
- Visual Studio Code or another C++ editor

### 1. Clone the Repository

```bash
git clone <YOUR_GITHUB_REPOSITORY_URL>
```

Replace the placeholder with your actual repository URL.

### 2. Navigate to the Project Directory

```bash
cd MiniSearchEngine
```

Make sure the `documents/` folder is inside this directory and contains your `.txt` files.

### 3. Compile the Project

```bash
g++ -std=c++17 main.cpp SearchEngine.cpp -o search
```

### 4. Run the Application

In Windows Command Prompt or PowerShell:

```powershell
.\search.exe
```

## 💻 Usage

After starting the application, enter a keyword or phrase when prompted.

Example:

```text
Enter your search query (or type 'exit' to quit): data

Search Results:
File: doc1.txt | Relevance Score: 1
File: doc2.txt | Relevance Score: 1

Enter your search query (or type 'exit' to quit): python
No matching documents found.

Enter your search query (or type 'exit' to quit): exit
Exiting Mini Search Engine. Goodbye!
```

### Sample Documents

**doc1.txt**

```text
C++ uses data structures and algorithms.
```

**doc2.txt**

```text
Data structures include trees and graphs.
```

**doc3.txt**

```text
C++ supports object oriented programming.
```

### Example Queries

| Query | Expected behavior |
|---|---|
| `data` | Returns `doc1.txt` and `doc2.txt` |
| `C++` | Returns `doc1.txt` and `doc3.txt` |
| `data structures` | Returns `doc1.txt` and `doc2.txt`, both with score 2 |
| `python` | Displays no matching documents |
| Empty input | Requests a valid search query |

## 🧠 Algorithm and Data Structures

### Inverted Index

An inverted index stores a mapping from each term to the documents containing that term.

```cpp
unordered_map<string, vector<string>> invertedIndex;
```

- **Key:** A normalized word.
- **Value:** The list of document filenames containing the word.

### Supporting Data Structures

| Data structure | Purpose |
|---|---|
| `unordered_map` | Stores the inverted index and document relevance scores |
| `vector` | Stores tokenized words, document filenames, and sorted results |
| `unordered_set` | Removes duplicate words from each document and query |

### Relevance Scoring

For a document \(d\) and a query containing distinct terms \(Q\), the score is:

\[
\operatorname{Score}(d,Q)
=\sum_{q\in Q}\mathbf{1}[q\text{ occurs in }d]
\]

Here, the indicator contributes 1 when the query term is present in the document and 0 otherwise.

This is a basic keyword-overlap scoring method, not a semantic search or machine-learning ranking algorithm.

## ⏱️ Time and Space Complexity

Let:

- \(T\) = total number of characters processed during indexing.
- \(U\) = total number of distinct word-document pairs stored in the index.
- \(Q\) = number of distinct query words.
- \(P\) = total number of document entries visited across the query words' posting lists.
- \(M\) = number of matching documents returned.

| Operation | Approximate complexity |
|---|---|
| Index construction | Average-case \(O(T)\), excluding file-system overhead and hashing costs |
| Query lookup | Average-case \(O(Q + P)\), excluding result sorting |
| Sorting search results | \(O(M\log M)\) |
| Index storage | \(O(U)\) word-document associations, plus container overhead |

These are expected or approximate bounds under ordinary hash-table behavior. Actual performance depends on the input, tokenization, file I/O, and hash collisions.

## 🧩 Challenges Faced and Solutions

Building this project involved solving practical implementation and debugging problems.

### 1. Compiler Error with `<filesystem>`

**Challenge:** During the initial compilation, GCC reported:

```text
fatal error: filesystem: No such file or directory
```

**Cause:** The installed compiler environment did not provide the expected `<filesystem>` header support.

**Solution:** Replaced the `std::filesystem` directory traversal with Windows file-discovery functions, including `FindFirstFileA()` and `FindNextFileA()`.

**Learning:** Compiler and standard-library compatibility matter when choosing implementation techniques. The revised approach works specifically with Windows and is less portable than a standard-library solution.

### 2. Case-Insensitive Searching

**Challenge:** Words written with different capitalization, such as `Data` and `data`, should match the same query.

**Solution:** Added tokenization and lowercase normalization before indexing documents and processing queries.

**Learning:** Consistent preprocessing is essential for reliable keyword matching.

### 3. Handling Repeated Words

**Challenge:** Repeated occurrences of a word in one document should not create duplicate document entries in the inverted index.

**Solution:** Used `unordered_set` to collect unique words from each document before adding the filename to the index.

**Learning:** Choosing suitable data structures helps avoid duplicate entries and simplifies later processing.

### 4. Ranking Search Results

**Challenge:** Returning matching documents alone does not distinguish documents that match many query terms from those that match only one.

**Solution:** Introduced a score for each matching document, incrementing it for every distinct query word found. Used `sort()` to display higher-scoring results first.

**Learning:** A simple scoring system can make search results more useful without requiring complex ranking algorithms.

### 5. Handling Missing Results and Invalid Input

**Challenge:** Empty queries and terms absent from the index should not cause confusing output.

**Solution:** Added checks for empty tokenized queries and empty result sets, displaying appropriate messages instead.

**Learning:** Input validation and clear error messages improve the usability of command-line applications.

## ⚠️ Limitations

- Searches are based on exact normalized keywords rather than meaning or context.
- The application indexes plain-text `.txt` files only.
- File discovery uses the Windows API, so the current implementation is Windows-specific.
- Relevance scores count distinct query-term matches and do not account for term frequency, document length, or word importance.
- The current version does not support phrases, wildcards, stemming, or fuzzy matching.
- The index is built at startup and is not persisted between runs.

## 🔮 Future Improvements

- Add support for recursive directory indexing.
- Display snippets showing where a query matches within a document.
- Improve relevance ranking using TF-IDF or BM25.
- Add phrase searching and Boolean operators such as `AND` and `OR`.
- Support additional file formats.
- Save the index to disk so it can be loaded on subsequent runs.
- Introduce a graphical or web-based interface.
- Make file discovery cross-platform using a compatible standard-library implementation.

## 📚 Learning Outcomes

Through this project, I practised:

- Implementing an inverted index for keyword retrieval.
- Using C++ STL containers to organize and retrieve data.
- Reading and processing text files.
- Normalizing user input for case-insensitive matching.
- Ranking and sorting search results.
- Debugging compiler compatibility issues.
- Evaluating algorithmic time and space complexity.
- Structuring a small C++ project across header and implementation files.

## 👩‍💻 Author

**Ankita Dhara**

B.E. in Information Technology, Jadavpur University

---

*Built as a learning project to explore data structures, algorithms, and file handling in C++.*