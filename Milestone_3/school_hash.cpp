#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

struct School {
    string name;
    string address;
    string city;
    string state;
    string county;

    School(string n, string a, string c, string s, string co)
        : name(n), address(a), city(c), state(s), county(co) {}
};
class SchoolHashTable {
    private:
        static const int TABLE_SIZE = 100;
        vector<list<School>> table;
    
        int hashFunction(const string& key) {
            int hash = 0;
            for (char ch : key) {
                hash += ch;
            }
            return hash % TABLE_SIZE;
        }
    
    public:
        SchoolHashTable() : table(TABLE_SIZE) {}
    
        void insert(const School& school) {
            int index = hashFunction(school.name);
            table[index].push_back(school);
        }
    
        School* findByName(const string& name) {
            int index = hashFunction(name);
            for (auto& school : table[index]) {
                if (school.name == name) {
                    return &school;
                }
            }
            return nullptr; 
        }
    
        void deleteByName(const string& name) {
            int index = hashFunction(name);
            auto& chain = table[index];
    
            for (auto it = chain.begin(); it != chain.end(); ++it) {
                if (it->name == name) {
                    chain.erase(it);
                    cout << "School deleted: " << name << endl;
                    return;
                }
            }
            cout << "School not found for deletion.\n";
        }
    
        void display() {
            for (int i = 0; i < TABLE_SIZE; ++i) {
                if (!table[i].empty()) {
                    cout << "Index " << i << ":\n";
                    for (const auto& school : table[i]) {
                        cout << "  " << school.name << ", " << school.address << ", " 
                             << school.city << ", " << school.state << ", " << school.county << endl;
                    }
                }
            }
        }
    };
    