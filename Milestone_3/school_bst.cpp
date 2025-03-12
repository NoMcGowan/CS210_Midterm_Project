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
