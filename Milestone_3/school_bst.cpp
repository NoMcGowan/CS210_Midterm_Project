#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

struct School{
    string name,address,city,state,county;
    School* left,* right;
    School(string n,string a,string c,string s,string co):name(n),address(a),city(c),state(s),county(co),left(nullptr),right(nullptr){}
};

void loadCSVData(const string& filename,class SchoolBST& bst);

class SchoolBST{
private:
    School* root;

    School* insertHelper(School* node,const School& school){
        if(!node)return new School(school);
        if(school.name<node->name)node->left=insertHelper(node->left,school);
        else node->right=insertHelper(node->right,school);
        return node;
    }

    void inOrderHelper(School* node){
        if(!node)return;
        inOrderHelper(node->left);
        cout<<node->name<<","<<node->address<<","<<node->city<<","<<node->state<<","<<node->county<<endl;
        inOrderHelper(node->right);
    }

    void preOrderHelper(School* node){
        if(!node)return;
        cout<<node->name<<","<<node->address<<","<<node->city<<","<<node->state<<","<<node->county<<endl;
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }

    void postOrderHelper(School* node){
        if(!node)return;
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout<<node->name<<","<<node->address<<","<<node->city<<","<<node->state<<","<<node->county<<endl;
    }

public:
    SchoolBST():root(nullptr){}

    void insert(const School& school){root=insertHelper(root,school);}
    void displayInOrder(){inOrderHelper(root);}
    void displayPreOrder(){preOrderHelper(root);}
    void displayPostOrder(){postOrderHelper(root);}

    School* findHelper(School* node,const string& name){
        if(!node||node->name==name)return node;
        if(name<node->name)return findHelper(node->left,name);
        return findHelper(node->right,name);
    }

    School* deleteHelper(School* node,const string& name){
        if(!node)return nullptr;
        if(name<node->name)node->left=deleteHelper(node->left,name);
        else if(name>node->name)node->right=deleteHelper(node->right,name);
        else{
            if(!node->left){School* temp=node->right;delete node;return temp;}
            else if(!node->right){School* temp=node->left;delete node;return temp;}
            School* minNode=node->right;while(minNode->left)minNode=minNode->left;
            node->name=minNode->name;
            node->right=deleteHelper(node->right,minNode->name);
        }
        return node;
    }

    School* findByName(const string& name){return findHelper(root,name);}
    void deleteByName(const string& name){root=deleteHelper(root,name);}
};

void loadCSVData(const string& filename,SchoolBST& bst){
    ifstream file(filename);string line,word;
    if(!file.is_open()){cerr<<"Error: Could not open file "<<filename<<endl;return;}
    getline(file,line);
    while(getline(file,line)){
        stringstream ss(line);vector<string> row;
        while(getline(ss,word,','))row.push_back(word);
        if(row.size()==5)bst.insert(School(row[0],row[1],row[2],row[3],row[4]));
    }
}

int main(){
    SchoolBST bst;string filename="schools.csv";
    loadCSVData(filename,bst);

    int choice;string name;
    do{
        cout<<"\nMenu:\n1. Display in-order\n2. Display pre-order\n3. Display post-order\n4. Search for a school\n5. Delete a school\n6. Exit\nEnter choice: ";
        cin>>choice;cin.ignore();

        switch(choice){
            case 1:bst.displayInOrder();break;
            case 2:bst.displayPreOrder();break;
            case 3:bst.displayPostOrder();break;
            case 4:
                cout<<"Enter school name: ";getline(cin,name);
                if(bst.findByName(name))cout<<"School found: "<<name<<endl;
                else cout<<"School not found.\n";break;
            case 5:
                cout<<"Enter school name to delete: ";getline(cin,name);
                bst.deleteByName(name);cout<<"School deleted.\n";break;
            case 6:cout<<"Exiting...\n";break;
            default:cout<<"Invalid choice.\n";
        }
    }while(choice!=6);

    return 0;
}
