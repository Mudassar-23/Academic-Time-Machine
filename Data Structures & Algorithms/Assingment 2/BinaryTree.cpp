#include "BinaryTree.h"

#include <limits>
// BNode Implementation
template <class DT>
BNode<DT>::BNode() : leftchild(nullptr), rightchild(nullptr) {}

template <class DT>
void BNode<DT>::setLeftChild(BNode<DT>* n) { leftchild = n; }

template <class DT>
BNode<DT>* BNode<DT>::getLeftChild() { return leftchild; }

template <class DT>
void BNode<DT>::setRightChild(BNode<DT>* n) { rightchild = n; }

template <class DT>
BNode<DT>* BNode<DT>::getRightChild() { return rightchild; }

template <class DT>
void BNode<DT>::setData(DT data) { this->data = data; }

template <class DT>
DT BNode<DT>::getData() { return data; }

// BinaryTree Implementation
template <class DT>
BinaryTree<DT>::BinaryTree() : root(nullptr) {}


template <class DT>
void BinaryTree<DT>::BuildTree(DT* Arr, int Size)
{
    if (Size > 2)
    {
        BNode<DT>** nodes = new BNode<DT>*[Size];
        for (int i = 1; i < Size; ++i)
        {
            nodes[i] = new BNode<DT>();
            if (Arr[i] == 0)
            {
                nodes[i] = nullptr;
            }

            else
            {
                nodes[i]->setData(Arr[i]);
            }

            if (i != 1)
            {
                if (i % 2 == 0)
                {
                    nodes[i / 2]->setLeftChild(nodes[i]);
                }
                else
                {
                    nodes[i / 2]->setRightChild(nodes[i]);
                }
            }
        }
        root = nodes[1];
    }
    else
    {
        return;
    }
}



template <class DT>
void BinaryTree<DT>::insert(DT data) {
    BNode<DT>* newNode = new BNode<DT>();
    newNode->setData(data);

    if (!root) {
        root = newNode;
        return;
    }

    queue<BNode<DT>*> q;
    q.push(root);

    while (!q.empty()) {
        BNode<DT>* node = q.front();
        q.pop();

        if (!node->getLeftChild()) {
            node->setLeftChild(newNode);
            return;
        } else {
            q.push(node->getLeftChild());
        }

        if (!node->getRightChild()) {
            node->setRightChild(newNode);
            return;
        } else {
            q.push(node->getRightChild());
        }
    }
}

template <class DT>
void BinaryTree<DT>::PreOrder() { PreOrderHelper(root); }

template <class DT>
void BinaryTree<DT>::PreOrderHelper(BNode<DT>* node) {
    if (!node) return;
    cout << node->getData() << " ";
    PreOrderHelper(node->getLeftChild());
    PreOrderHelper(node->getRightChild());
}

template <class DT>
void BinaryTree<DT>::InOrder() { InOrderHelper(root); }

template <class DT>
void BinaryTree<DT>::InOrderHelper(BNode<DT>* node) {
    if (!node) return;
    InOrderHelper(node->getLeftChild());
    cout << node->getData() << " ";
    InOrderHelper(node->getRightChild());
}

template <class DT>
void BinaryTree<DT>::PostOrder() { PostOrderHelper(root); }

template <class DT>
void BinaryTree<DT>::PostOrderHelper(BNode<DT>* node) {
    if (!node) return;
    PostOrderHelper(node->getLeftChild());
    PostOrderHelper(node->getRightChild());
    cout << node->getData() << " ";
}

template <class DT>
void BinaryTree<DT>::PreOrderItr() {
    if (!root) return;
    stack<BNode<DT>*> s;
    s.push(root);

    while (!s.empty()) {
        BNode<DT>* node = s.top();
        s.pop();
        cout << node->getData() << " ";

        if (node->getRightChild()) s.push(node->getRightChild());
        if (node->getLeftChild()) s.push(node->getLeftChild());
    }
}

template <class DT>
void BinaryTree<DT>::InOrderItr() {
    stack<BNode<DT>*> s;
    BNode<DT>* current = root;

    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            current = current->getLeftChild();
        }
        current = s.top();
        s.pop();
        cout << current->getData() << " ";
        current = current->getRightChild();
    }
}

template <class DT>
void BinaryTree<DT>::PostOrderItr() {
    if (!root) return;
    stack<BNode<DT>*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        BNode<DT>* node = s1.top();
        s1.pop();
        s2.push(node);

        if (node->getLeftChild()) s1.push(node->getLeftChild());
        if (node->getRightChild()) s1.push(node->getRightChild());
    }

    while (!s2.empty()) {
        cout << s2.top()->getData() << " ";
        s2.pop();
    }
}

template <class DT>
void BinaryTree<DT>::LevelOrder() {
    if (!root) return;

    queue<BNode<DT>*> q;
    q.push(root);

    while (!q.empty()) {
        BNode<DT>* node = q.front();
        q.pop();
        cout << node->getData() << " ";

        if (node->getLeftChild()) q.push(node->getLeftChild());
        if (node->getRightChild()) q.push(node->getRightChild());
    }
}

template <class DT>
int BinaryTree<DT>::CountNodes() {
    if (!root) return 0;
    int count = 0;
    stack<BNode<DT>*> s;
    s.push(root);

    while (!s.empty()) {
        BNode<DT>* node = s.top();
        s.pop();
        ++count;

        if (node->getLeftChild()) s.push(node->getLeftChild());
        if (node->getRightChild()) s.push(node->getRightChild());
    }
    return count;
}

template <class DT>
int BinaryTree<DT>::calculateDepth() {
    return calculateDepthHelper(root);
}

template <class DT>
int BinaryTree<DT>::calculateDepthHelper(BNode<DT>* node) {
    if (!node) return 0;
    int leftDepth = calculateDepthHelper(node->getLeftChild());
    int rightDepth = calculateDepthHelper(node->getRightChild());
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

template <class DT>
bool BinaryTree<DT>::IsBST() {
    DT min = numeric_limits<DT>::min();
    DT max = numeric_limits<DT>::max();
    return isBSTHelper(root, min, max);
}

template <class DT>
bool BinaryTree<DT>::isBSTHelper(BNode<DT>* node, DT min, DT max) {
    if (!node) return true;
    if (node->getData() < min || node->getData() > max) return false;
    return isBSTHelper(node->getLeftChild(), min, node->getData()) &&
        isBSTHelper(node->getRightChild(), node->getData(), max);
}

template <class DT>
int BinaryTree<DT>::NodesAtLevel(int d) {
    return NodesAtLevelHelper(root, d);
}

template <class DT>
int BinaryTree<DT>::NodesAtLevelHelper(BNode<DT>* node, int level) {
    if (!node) return 0;
    if (level == 1) return 1;
    return NodesAtLevelHelper(node->getLeftChild(), level - 1) +
           NodesAtLevelHelper(node->getRightChild(), level - 1);
}

// Explicit instantiation
template class BNode<int>;
template class BinaryTree<int>;