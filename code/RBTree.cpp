#include "RBTree.h"


RBT::RBT() : root(nullptr){}

// deconstructor
RBT::~RBT(){}

// initialize a new node
node* RBT::init_node(int key){
    // create a new node
    node* new_node = new node;
    // a new 
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;
    new_node->data = key;
    new_node->color = RED;
    return new_node;
}

//
// insert a new node to the tree with a key
void RBT::insert(int key){
    node* new_node = init_node(key);
    // if the tree is empty
    if(!root){
        root = new_node;
        root->color = BLACK;
        return;
    }
    // find the node to insert
    node* cursor = root;
    node* parent = root;
    bool left = true;  // determine if the node is left or right child of parent
    while(cursor){
        // update the parent node to the cursor
        parent = cursor;
        if(key <= cursor->data){
            cursor = cursor->left;
            left = true;
        }
        else{
            cursor = cursor->right;
            left = false;
        }
    }
    if(left){
        parent->left = new_node;
    }
    else{
        parent->right = new_node;
    }
    new_node->parent = parent;
    fix(new_node);
}

// check and fix the balance of the tree
void RBT::fix(node* issue_node){
    // check if the current node is at root
    if(issue_node == root){
        root->color = BLACK;
        return;
    }
    // check the parent node color, if black, tree is balanced. Exit the tree
    if(issue_node->parent->color == BLACK){
        return;
    }
    /*if (!issue_node->parent || !issue_node->parent->parent) {
    // No grandparent, hence no need to fix
    return;
    }*/
    bool left = true;  // check the parent node location to the grandpa node
    node* grandpa = issue_node->parent->parent;
    node* uncle;
    node* parent = issue_node->parent;
    if(grandpa->left == issue_node->parent){
        left = true;
        uncle = grandpa->right;
    }
    else{
        left = false;
        uncle = grandpa->left;
    }

    // checking the color of the uncle node color, if red, perform color change
    /// issues
    if(uncle && uncle->color == RED){
        grandpa->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        fix(grandpa);
        return;
    }
    // if the unbalanced node is LL type
    if(issue_node == issue_node->parent->left && left){ 
        LL(issue_node);
    }
    // if the unbalanced node is LR type
    else if(issue_node == issue_node->parent->right && left){
        LR(issue_node);
    }
    // the unbalanced node is RL type
    else if(issue_node == issue_node->parent->left && !left){
        RL(issue_node);
    }
    // the unbalanced node is RR type
    else{
        RR(issue_node);
    }

    return;
}

//
void RBT::LL(node* cursor){
    node* parent = cursor->parent;
    node* grandpa = parent->parent;
    node* grandgrandpa = grandpa->parent;
    // perform one right rotation
    // move the parent node to the grandpa node location
    parent->parent = grandpa->parent;
    bool left = true;
    if(grandgrandpa && grandgrandpa->right == grandpa){
        left = false;
    }
    // link the right child of parent to the left child of grandpa
    grandpa->left = parent->right;
    // link the grandpa to the right child of parent
    parent->right = grandpa;
    grandpa->parent = parent;
    // coloring the parent node and grandpa node
    grandpa->color = RED;
    parent->color = BLACK;

    // if the grandpa node is at root, update the root to parent
    if(root == grandpa){
        root = parent;
    }
    // linking the parent node to the grandgrandpa node
    else if(left){
        grandgrandpa->left = parent;
    }
    else{
        grandgrandpa->right = parent;
    }

}

//
void RBT::RR(node* cursor){
    node* parent = cursor->parent;
    node* grandpa = parent->parent;
    node* grandgrandpa = grandpa->parent;
    // perform the left rotation
    bool left = true;
    // move the parent node to the grandpa node location
    parent->parent = grandpa->parent;
    if(grandgrandpa && grandgrandpa->right == grandpa){
        left = false;
    }
    
    // link the left child of parent to the right child of grandpa
    grandpa->right = parent->left;
    // link the grandpa node to the left of parent node
    parent->left = grandpa;
    grandpa->parent = parent;
    // coloring the grandpa node and parent node
    grandpa->color = RED;
    parent->color = BLACK;
    // if grandpa node is at root, make the parent to be new root
    if(root == grandpa){
        root = parent;
    }
    // linking the parent node to grandgrandpa node
    else if(left){
        grandgrandpa->left = parent;
    }
    else{
        grandgrandpa->right = parent;
    }
}


// right to the grandpa and left to the parent
void RBT::RL(node* cursor){
    node* parent = cursor->parent;
    node* grandpa = parent->parent;
    node* uncle = grandpa->left;
    node* grandgrandpa = grandpa->parent;
    // perform a left rotation first
    // need to add a checker make sure grandpa at root is ok
    bool left = true;
    if(grandgrandpa && grandgrandpa->right == grandpa){
        left = false;
    }
    //exchange parent and cursor node location (R)
    parent->left = cursor->right;
    if(cursor->right){
        cursor->right->parent = parent;
    }
    cursor->right = parent;
    parent->parent = cursor;  // set parent's parent node
    // exchange grandpa and cursor node location (L)
    grandpa->right = cursor->left;
    if(cursor->left){
        cursor->left->parent = grandpa;
    }
    cursor->left = grandpa;
    grandpa->parent = cursor;  // set grandpa's parent node
    // coloring the nodes
    cursor->color = BLACK;
    grandpa->color = RED;
    // link the cursor to the grandgrandpa node
    // if the grandpa node is at root, change to cursor
    if(root == grandpa){
        root = cursor;
        cursor->parent = nullptr;  // set cursor's parent node
    }
    else if(left){
        grandgrandpa->left = cursor;
        cursor->parent = grandgrandpa;
    }
    else{
        grandgrandpa->right = cursor;
        cursor->parent = grandgrandpa;
    }
}


//
void RBT::LR(node* cursor){
    node* parent = cursor->parent;
    node* grandpa = parent->parent;
    node* uncle = grandpa->right;
    node* grandgrandpa = grandpa->parent;
    bool left = true;
    if(grandgrandpa && grandgrandpa->right == grandpa){
        left = false;
    }
    // exchange parent and cursor node location (L)
    parent->right = cursor->left;
    if(cursor->left){
        cursor->left->parent = parent;
    }
    cursor->left = parent;
    parent->parent = cursor;  // set parent's parent node
    // exchange grandpa and cursor node location (R)
    grandpa->left = cursor->right;
    if(cursor->right){
        cursor->right->parent = grandpa;
    }
    cursor->right = grandpa;
    grandpa->parent = cursor;  // set grandpa's parent node
    // coloring the nodes
    cursor->color = BLACK;
    grandpa->color = RED;
    // link the cursor to the grandgrandpa node
    // if the grandpa node is at root, change to cursor
    if(root == grandpa){
        root = cursor;  //reset root to cursor
        cursor->parent = nullptr;  // set cursor's parent node
    }
    else if(left){
        grandgrandpa->left = cursor;
        cursor->parent = grandgrandpa;
    }
    else{
        grandgrandpa->right = cursor;
        cursor->parent = grandgrandpa;
    }
}


// find the node location containing the key
node* RBT::findNode(int key){
    node* cursor = root;
    while(cursor){
        if(key < cursor->data){
            cursor = cursor->left;
        }
        else if(key > cursor->data){
            cursor = cursor->right;
        }
        else{
            return cursor;
        }
    }
    return NULL;
}

// a public find function to see if a value is already in the tree
bool RBT::find(int key){
    node* res = findNode(key);
    if(res){
        return true;
    }
    else{
        return false;
    }
}


// remove a value from the tree
// with three cases: 1, left child is leaf, 2, right child is leaf, 3, neither is leaf
bool RBT::remove(int key) {
    // Find the node to be deleted
    node* z = findNode(key);
    if (z == nullptr) {
        cout << "Key not found in the tree.\n";
        return false; // Node with the key doesn't exist
    }

    node* y = z; // Node to be actually deleted
    int yOriginalColor = y->color; // Save the original color of y
    node* x = nullptr; // Node that will replace y in the tree
    node* xParent = nullptr; // Parent of x

    if (z->left == nullptr) {
        x = z->right;
        xParent = z->parent;
        transplant(z, z->right); // Replace z with its right child
    } else if (z->right == nullptr) {
        x = z->left;
        xParent = z->parent;
        transplant(z, z->left); // Replace z with its left child
    } else {
        // If z has two children, find its successor y
        y = findMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr)
                x->parent = y;
            xParent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
            xParent = y->parent;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z; // Free the memory occupied by the deleted node

    // If the original color of y was black, fix the tree to maintain the Red-Black properties
    if (yOriginalColor == BLACK)
        delete_fix(x, xParent);

    return true;
}

void RBT::delete_fix(node* x, node* xParent) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == xParent->left) {
            node* w = xParent->right;
            // Case 1: x's sibling w is red
            if (w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                rotateL(xParent);
                w = xParent->right;
            }
            // Case 2: x's sibling w is black, and both of w's children are black
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = xParent;
                xParent = xParent->parent;
            } else {
                // Case 3: x's sibling w is black, and w's right child is black
                if (w->right == nullptr || w->right->color == BLACK) {
                    if (w->left != nullptr)
                        w->left->color = BLACK;
                    w->color = RED;
                    rotateR(w);
                    w = xParent->right;
                }
                // Case 4: x's sibling w is black, and w's right child is red
                w->color = xParent->color;
                xParent->color = BLACK;
                if (w->right != nullptr)
                    w->right->color = BLACK;
                rotateL(xParent);
                x = root;
            }
        } else {
            node* w = xParent->left;
            // Symmetric cases for when x is the right child
            if (w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                rotateR(xParent);
                w = xParent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = xParent;
                xParent = xParent->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right != nullptr)
                        w->right->color = BLACK;
                    w->color = RED;
                    rotateL(w);
                    w = xParent->left;
                }
                w->color = xParent->color;
                xParent->color = BLACK;
                if (w->left != nullptr)
                    w->left->color = BLACK;
                rotateR(xParent);
                x = root;
            }
        }
    }
    if (x != nullptr)
        x->color = BLACK;
}

// find the min node of a tree
node* RBT::findMin(node* target){
    // Traverse the left subtree until the smallest node is found
    while (target->left != nullptr)
        target = target->left;
    return target;
}

// linking the the target node to the grandpa node, 
// the link of sibling node to the target node is done before calling.
// the parent node is the one to be removed, and the target node is the one
// to transplant to the parent node location
void RBT::transplant(node* u, node* v) {
    if (u == root)
        root = v;  // If u is the root, replace it with v
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != nullptr)
        v->parent = u->parent;
}

void RBT::rotateR(node* target) {
    node* left = target->left;  // Left child of the target node
    node* parent = target->parent; // Parent of the target node

    // Move the right child of left to the left of the target
    target->left = left->right;
    if (left->right != nullptr) {
        left->right->parent = target;
    }

    // Update the parent of left
    left->parent = parent;
    if (parent == nullptr) {
        root = left;  // If target was the root, update the root to left
    } else if (target == parent->right) {
        parent->right = left; // If target was a right child, update parent's right child to left
    } else {
        parent->left = left;  // If target was a left child, update parent's left child to left
    }

    // Set target as the right child of left
    left->right = target;
    target->parent = left;
}

void RBT::rotateL(node* target) {
    node* right = target->right;  // Right child of the target node
    node* parent = target->parent; // Parent of the target node

    // Move the left child of right to the right of the target
    target->right = right->left;
    if (right->left != nullptr) {
        right->left->parent = target;
    }

    // Update the parent of right
    right->parent = parent;
    if (parent == nullptr) {
        root = right;  // If target was the root, update the root to right
    } else if (target == parent->left) {
        parent->left = right;  // If target was a left child, update parent's left child to right
    } else {
        parent->right = right; // If target was a right child, update parent's right child to right
    }

    // Set target as the left child of right
    right->left = target;
    target->parent = right;
}

// Function to print the entire tree structure
void RBT::printTree() {
    if (root == NULL) {
        cout << "The tree is empty." << endl;
    } else {
        printTreeHelper(root, "", true);
    }
}

// Helper function to print the tree structure.
void RBT::printTreeHelper(node* root, string indent, bool last) {
    if (root != NULL) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "     ";
        } else {
            cout << "L----";
            indent += "|    ";
        }

        string color = (root->color == RED) ? "RED" : "BLACK";
        cout << root->data << "(" << color << ")" << endl;

        printTreeHelper(root->left, indent, false);
        printTreeHelper(root->right, indent, true);
    }
}


// Function to check the integrity of the Red-Black Tree
bool RBT::checkRBTIntegrity() {
    if (root == nullptr) {
        return true; // An empty tree is a valid RBT
    }

    // Rule 2: The root must be black
    if (root->color != BLACK) {
        cout << "Root node is not black." << endl;
        return false;
    }

    // Recursively check the integrity of the tree
    int blackNodeCount = 0;
    return checkNodeIntegrity(root, blackNodeCount, 0);
}


// helper function for checking the node integrity. 
bool RBT::checkNodeIntegrity(node* n, int& blackNodeCount, int currentBlackCount) {
    if (n == nullptr) {
        // If this is a NIL node (null), check if the black node count is consistent
        if (blackNodeCount == 0) {
            blackNodeCount = currentBlackCount;
        } else if (currentBlackCount != blackNodeCount) {
            cout << "Black node count mismatch." << endl;
            return false;
        }
        return true;
    }

    // Rule 1: Every node is either red or black (implicitly true since we only have two colors)

    // Rule 4: If a node is red, both its children must be black
    if (n->color == RED) { // RED
        if ((n->left && n->left->color == RED) || (n->right && n->right->color == RED)) {
            cout << "Red node has a red child at node " << n->data << endl;
            return false;
        }
    }

    // If the current node is black, increment the black node count
    if (n->color == BLACK) { // BLACK
        currentBlackCount++;
    }

    // Check the parent-child link
    if (n->left) {
        if (n->left->parent != n) {
            cout << "Parent-child link error: Left child of node " << n->data << " does not point back to the parent correctly." << endl;
            cout<< "Node "<<n->left->data<<" is point to node"<<n->left->parent->data<<endl;
            return false;
        }
    }

    if (n->right) {
        if (n->right->parent != n) {
            cout << "Parent-child link error: Right child of node " << n->data << " does not point back to the parent correctly." << endl;
            cout<< "Node "<<n->right->data<<" is point to node"<<n->right->parent->data<<endl;
            return false;
        }
    }

    // Recursively check the left and right subtrees
    if (!checkNodeIntegrity(n->left, blackNodeCount, currentBlackCount) ||
        !checkNodeIntegrity(n->right, blackNodeCount, currentBlackCount)) {
        return false;
    }

    return true;
}

// count the total size of the tree. to help find out issues in the dev. and for the test.
int RBT::size() const {
    return sizeHelper(root);
}


// helper function for size()
int RBT::sizeHelper(node* n) const {
    if (n == nullptr) {
        return 0;
    }
    return 1 + sizeHelper(n->left) + sizeHelper(n->right);
}

int RBT::min(){
    node* cursor = root;
    while(cursor->left){
        cursor = cursor->left;
    }
    return cursor->data;
}

int RBT::max(){
    node* cursor = root;
    while(cursor->right){
        cursor = cursor->right;
    }
    return cursor->data;
}

