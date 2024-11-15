#include "BinaryTree.h"


int main() {
    BinaryTree<int> tree;
    int arr[] = { 0, 1, 2, 3, 4, 5, 6 };
    tree.BuildTree(arr, sizeof(arr) / sizeof(arr[0])); 

    cout << "\033[32m****************************************************\033[0m" << endl;  
    cout << "PreOrder: ";
    tree.PreOrder();
    cout << endl;

    cout << "InOrder: ";
    tree.InOrder();
    cout << endl;

    cout << "PostOrder: ";
    tree.PostOrder();
    cout << endl;

    cout << "\033[32m****************************************************\033[0m" << endl; 

    cout << "PreOrder (Iterative): ";
    tree.PreOrderItr();
    cout << endl;

    cout << "InOrder (Iterative): ";
    tree.InOrderItr();
    cout << endl;

    cout << "PostOrder (Iterative): ";
    tree.PostOrderItr();
    cout << endl;

    cout << "Level Order: ";
    tree.LevelOrder();
    cout << endl;
    cout << "\033[32m****************************************************\033[0m" << endl;

    cout << "Total Nodes: " << tree.CountNodes() << endl;
    cout << "Is BST: " << (tree.IsBST() ? "Yes" : "No") << endl;
    cout << "Depth of the tree: " << tree.calculateDepth() << endl;
    cout << "Node at Level: " << tree.NodesAtLevel(2) << endl;
    tree.insert(7);
    cout << "Node 7 Inserted" << endl;
    cout << "Total Nodes: " << tree.CountNodes() << endl;

    cout << "\033[32m****************************************************\033[0m" << endl;
    cout << "Level Order: ";
    tree.LevelOrder();
    cout << endl;

    cout << "\033[32m****************************************************\033[0m" << endl;
   
    return 0;
}
