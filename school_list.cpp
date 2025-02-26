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
    School* next; 

    School(string n, string a, string c, string s, string co) 
        : name(n), address(a), city(c), state(s), county(co), next(nullptr) {}
};
