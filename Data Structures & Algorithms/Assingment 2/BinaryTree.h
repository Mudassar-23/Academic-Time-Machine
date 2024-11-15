#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <stack>
#include <queue>
#include <climits> // For INT_MIN and INT_MAX

using namespace std;

template <class DT>
class BNode {
public:
    BNode();
    void setLeftChild(BNode<DT>* n);
    BNode<DT>* getLeftChild();
    void setRightChild(BNode<DT>* n);
    BNode<DT>* getRightChild();
    void setData(DT data);
    DT getData();

private:
    DT data;
    BNode<DT>* leftchild;
    BNode<DT>* rightchild;
};

template <class DT>
class BinaryTree {
public:
    BinaryTree();

    void BuildTree(DT* Arr, int Size);
    void PreOrder();
    void PostOrder();
    void InOrder();

    void PreOrderItr();
    void PostOrderItr();
    void InOrderItr();
    void LevelOrder();

    void insert(DT data);
    int CountNodes();
    bool IsBST();
    int NodesAtLevel(int d);
    int calculateDepth();

private:
    BNode<DT>* root;
    void PreOrderHelper(BNode<DT>* temp);
    void PostOrderHelper(BNode<DT>* temp);
    void InOrderHelper(BNode<DT>* temp);
  
    bool isBSTHelper(BNode<DT>* node, DT min, DT max);
    int NodesAtLevelHelper(BNode<DT>* node, int level);
    int calculateDepthHelper(BNode<DT>* node);
};

#endif 
