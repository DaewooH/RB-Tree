## Red-Black Tree (RBT) Implementation

### Overview

The Red-Black Tree (RBT) is a type of self-balancing Binary Search Tree (BST) that maintains sorted order and ensures O(log n) time complexity for insertion, deletion, and search operations. This makes it highly efficient for storing and managing a large amount of sorted numeric data. For simplicity, this implementation supports integer values only.

### Supported Operations

- **Initialization**: `RBT`
- **Key Insertion**: `.insert(key)`
- **Search for a Key**: `.find(key)`
- **Find the Minimum Key**: `.min()`
- **Find the Maximum Key**: `.max()`
- **Key Deletion**: `.remove(key)`
- **Data Size**: `.size()`
- **Print Tree Structure**: `.printTree()`
- **Check Tree Integrity**: `.checkRBTIntegrity()`

### Running the Tests

To ensure that the Red-Black Tree operates correctly and maintains its properties, follow these steps to compile and run the test code:

1. **Navigate to the Build Directory**:

   cd build

2. **Compile the Project**:
   Run the following commands in the terminal:

   cmake ..
   make

3. **Execute the Test File**:

   ./run_tests


The test will verify all operations and alert you to any failures. If the tree fails the integrity check, please report any anomalies for further investigation.

### Project Data Structure

The project is organized as follows:


project-root/
│
├── code/
│   ├── RBTree.h
│   └── RBTree.cpp
│
├── test/
│   └── test.cpp
│
└── CMakeLists.txt


### References

- **Red-Black Tree Insertion**:
  - [YouTube](https://www.youtube.com/watch?v=Ij8-xX3PreE&t=377s)
- **Red-Black Tree Deletion**:
  - [YouTube](https://www.youtube.com/watch?v=lU99loSvD8s)
  - [YouTube](https://www.youtube.com/watch?v=iw8N1_keEWA)
  - [Bilibili](https://www.bilibili.com/video/BV16m421u7Tb/?spm_id_from=333.1007.0.0)

Feel free to adjust any details as needed!