#include<iostream>
#include<vector>
#include "RBTree.h"

using namespace std;

int main() {
    // Initialize the red-black tree
    RBT tree;

    // Checking insert operations. 
    vector<int> numbers = {20, 10, 5, 30, 40, 57, 3, 2, 4, 35, 25, 18, 22, 23, 24, 19, 18};
    //vector<int> numbers = {10,5,4,15,14};

    // Insert each number into the tree
    for(int num : numbers) {
        int ori_size = tree.size();
        tree.insert(num);
        if(!tree.checkRBTIntegrity() || tree.size()!=(ori_size+1)){
            cout<<"tree is wrong"<<endl;
            return 0;
        }
    }
    tree.printTree();  // print out the tree for visual benefit

    // Output a message indicating insertion is complete
    cout << "All numbers inserted into the tree." << endl;
    // Optionally, you can search for a number to test the find function
    for(int num: numbers){
        if(!tree.find(num)){
            cout<<num<<" was not found"<<endl;  // once a number is missing, exit loop and print error message.
            return 0;
        }
    }
    cout<<"All numbers are found in the tree as expected. Insert operation test passed\n\n"<<endl;


    // checking delete operation

    // remove each number from the tree
    for(int num:numbers){
        int ori_size = tree.size();
        tree.remove(num);
        if(!tree.checkRBTIntegrity() || tree.size()!=(ori_size-1)){
            cout<<"tree is wrong"<<endl;
            return 0;
        }
    }
    cout<<"All numbers are deleted without an issue. Deletion operation test passed\n\n"<<endl;

    return 0;
}