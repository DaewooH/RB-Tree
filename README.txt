Your text looks good! Here’s a slightly refined version for clarity and consistency:

---

The Red-Black (RB) tree is a type of Binary Search Tree with excellent self-balancing characteristics, making it ideal for storing a large number of sorted numeric data. For development convenience, my implementation currently supports only integers.

This project supports the following operations:

- **Initialization**: `RBT`
- **Key Insertion**: `.insert(key)`
- **Search for a Key**: `.find(key)`
- **Find the Minimum Key**: `.min()`
- **Find the Maximum Key**: `.max()`
- **Key Deletion**: `.remove(key)`
- **Data Size**: `.size()`
- **Print Tree Structure**: `.printTree()`
- **Check Tree Structure Integrity**: `.checkRBTIntegrity()`

I have also written a demo (test) code that performs all these operations while ensuring that the RB Tree characteristics are maintained. If you notice any anomalies in the results, please check the tree’s integrity. If the tree fails, let me know.

To run the test file, please follow these steps:
1. Change your directory to the `build` folder under the project root.
2. Compile the project by running `cmake ..` and `make` in the terminal.
3. Execute the test file by running `./run_test`.

The test will warn you if any operations fail.

---

Feel free to adjust any details as needed!