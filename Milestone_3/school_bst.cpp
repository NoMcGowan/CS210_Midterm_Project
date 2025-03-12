#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* left;
    School* right;

    School(string n, string a, string c, string s, string co)
        : name(n), address(a), city(c), state(s), county(co), left(nullptr), right(nullptr) {}
};

void loadCSVData(const string& filename, class SchoolBST& bst);

class SchoolBST {
    private:
        School* root;
    
        School* insertHelper(School* node, const School& school) {
            if (!node) return new School(school);
            if (school.name < node->name)
                node->left = insertHelper(node->left, school);
            else
                node->right = insertHelper(node->right, school);
            return node;
        }
    
        void inOrderHelper(School* node) {
            if (!node) return;
            inOrderHelper(node->left);
            cout << node->name << ", " << node->address << ", " << node->city
                 << ", " << node->state << ", " << node->county << endl;
            inOrderHelper(node->right);
        }
    
    public:
        SchoolBST() : root(nullptr) {}
    
        void insert(const School& school) {
            root = insertHelper(root, school);
        }
    
        void displayInOrder() {
            inOrderHelper(root);
        }
    };
    
