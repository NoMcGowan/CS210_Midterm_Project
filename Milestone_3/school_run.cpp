#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct School {
    string name, address, city, state, county;
    School* left = nullptr, *right = nullptr, *next = nullptr;

    School(string n, string a, string c, string s, string co)
        : name(n), address(a), city(c), state(s), county(co) {}
};

// ---------------- Linked List ----------------
class SchoolList {
    School* head = nullptr;
public:
    void insertLast(const School& school) {
        School* newNode = new School(school);
        if (!head) head = newNode;
        else {
            School* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }
    School* findByName(const string& name) {
        School* temp = head;
        while (temp) {
            if (temp->name == name) return temp;
            temp = temp->next;
        }
        return nullptr;
    }
    void deleteByName(const string& name) {
        if (!head) return;
        if (head->name == name) {
            School* del = head;
            head = head->next;
            delete del;
            return;
        }
        School* temp = head;
        while (temp->next && temp->next->name != name) temp = temp->next;
        if (temp->next) {
            School* del = temp->next;
            temp->next = del->next;
            delete del;
        }
    }
};

// ---------------- Binary Search Tree ----------------
class SchoolBST {
    School* root = nullptr;

    School* insertHelper(School* node, const School& school) {
        if (!node) return new School(school);
        if (school.name < node->name) node->left = insertHelper(node->left, school);
        else node->right = insertHelper(node->right, school);
        return node;
    }

    School* findHelper(School* node, const string& name) {
        if (!node || node->name == name) return node;
        if (name < node->name) return findHelper(node->left, name);
        return findHelper(node->right, name);
    }

    School* deleteHelper(School* node, const string& name) {
        if (!node) return nullptr;
        if (name < node->name) node->left = deleteHelper(node->left, name);
        else if (name > node->name) node->right = deleteHelper(node->right, name);
        else {
            if (!node->left) {
                School* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                School* temp = node->left;
                delete node;
                return temp;
            }
            School* minNode = node->right;
            while (minNode->left) minNode = minNode->left;
            node->name = minNode->name;
            node->right = deleteHelper(node->right, minNode->name);
        }
        return node;
    }

public:
    void insert(const School& school) { root = insertHelper(root, school); }
    School* findByName(const string& name) { return findHelper(root, name); }
    void deleteByName(const string& name) { root = deleteHelper(root, name); }
};

// ---------------- Hash Table ----------------
class SchoolHashTable {
    static const int SIZE = 100;
    vector<list<School> > table;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) hash += c;
        return hash % SIZE;
    }

public:
    SchoolHashTable() : table(SIZE) {}

    void insert(const School& school) {
        table[hashFunction(school.name)].push_back(school);
    }

    School* findByName(const string& name) {
        int idx = hashFunction(name);
        for (auto& s : table[idx])
            if (s.name == name) return &s;
        return nullptr;
    }

    void deleteByName(const string& name) {
        int idx = hashFunction(name);
        auto& chain = table[idx];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->name == name) {
                chain.erase(it);
                return;
            }
        }
    }
};

// ---------------- Data Loader ----------------
vector<School> loadCSV(const string& filename) {
    vector<School> schools;
    ifstream file(filename);
    string line, word;
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        while (getline(ss, word, ',')) row.push_back(word);
        if (row.size() == 5) schools.emplace_back(row[0], row[1], row[2], row[3], row[4]);
    }
    return schools;
}

// ---------------- Main: Runtime Testing ----------------
int main() {
    string filename = "Illinois_Schools.csv";
    vector<School> data = loadCSV(filename);
    string target = data[data.size() / 2].name; 

    // Linked List
    SchoolList ll;
    auto start = high_resolution_clock::now();
    for (const auto& s : data) ll.insertLast(s);
    auto end = high_resolution_clock::now();
    cout << "Linked List Insertion: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    ll.findByName(target);
    end = high_resolution_clock::now();
    cout << "Linked List Search: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    start = high_resolution_clock::now();
    ll.deleteByName(target);
    end = high_resolution_clock::now();
    cout << "Linked List Deletion: " << duration_cast<microseconds>(end - start).count() << " µs\n\n";

    // Binary Search Tree
    SchoolBST bst;
    start = high_resolution_clock::now();
    for (const auto& s : data) bst.insert(s);
    end = high_resolution_clock::now();
    cout << "BST Insertion: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    bst.findByName(target);
    end = high_resolution_clock::now();
    cout << "BST Search: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    start = high_resolution_clock::now();
    bst.deleteByName(target);
    end = high_resolution_clock::now();
    cout << "BST Deletion: " << duration_cast<microseconds>(end - start).count() << " µs\n\n";

    // Hash Table
    SchoolHashTable ht;
    start = high_resolution_clock::now();
    for (const auto& s : data) ht.insert(s);
    end = high_resolution_clock::now();
    cout << "Hash Table Insertion: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    ht.findByName(target);
    end = high_resolution_clock::now();
    cout << "Hash Table Search: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    start = high_resolution_clock::now();
    ht.deleteByName(target);
    end = high_resolution_clock::now();
    cout << "Hash Table Deletion: " << duration_cast<microseconds>(end - start).count() << " µs\n";

    return 0;
}
