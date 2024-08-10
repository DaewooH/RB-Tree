#include<iostream>

using namespace std;

#define RED -1
#define BLACK 1
struct node{
    int data;
    node* left;
    node* right;
    node* parent;
    int color;
};

class RBT {
public:
    RBT();

    ~RBT();

    // insert a new node to the tree
    void insert(int key);

    // search a value in the tree
    bool find(int key);

    // remove a value from the tree
    bool remove(int key);

    // Function to print the entire tree structure
    void printTree();

    // Function to check the integrity of the Red-Black Tree
    bool checkRBTIntegrity();

    // counting the numbers stored in the tree
    int size() const;

    // find the minimum number of the tree
    int min();

    // find the max number of the tree
    int max();
private:
    node* root;
    node* init_node(int key);

    // helper function for remove() to move subtrees within the tree
    void transplant(node* parent, node* target);

    // find the smallest node of a tree
    node* findMin(node* target);

    // helper function for remove() to fixup the unbalanced tree
    void delete_fix(node* target, node* parent);

    // check and fix the balance of RBT
    void fix(node* issue_node);

    // left left rotation to keep tree balance
    void LL(node* node);

    // right right rotation to keep tree balance
    void RR(node* node);

    // left right rotation to keep tree balance
    void LR(node* node);

    // right left rotation to keep tree balance
    void RL(node* node);

    // find the node containing the key
    node* findNode(int key);
    
    void printTreeHelper(node* root, string indent, bool last);

    // Function to check the integrity of the Red-Black Tree
    bool checkNodeIntegrity(node* n, int& blackNodeCount, int currentBlackCount);
    
    // helper function for size()
    int sizeHelper(node* n) const;

    // perform a rotation about a node. Similar to LL and RR.
    void rotateL(node* target);
    void rotateR(node* target);
};