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

class SchoolList {
private:
    School* head;

public:
    SchoolList() : head(nullptr) {}

    void insertFirst(const School& school) {
        School* newSchool = new School(school);
        newSchool->next = head;
        head = newSchool;
    }

    void insertLast(const School& school) {
        School* newSchool = new School(school);
        if (!head) {
            head = newSchool;
            return;
        }
        School* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newSchool;
    }

    void deleteByName(const string& name) {
        if (!head) return;
        if (head->name == name) {
            School* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        School* temp = head;
        while (temp->next && temp->next->name != name) {
            temp = temp->next;
        }
        if (temp->next) {
            School* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
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

    void display() {
        School* temp = head;
        while (temp) {
            cout << temp->name << ", " << temp->address << ", " 
                 << temp->city << ", " << temp->state << ", " 
                 << temp->county << endl;
            temp = temp->next;
        }
    }
};

