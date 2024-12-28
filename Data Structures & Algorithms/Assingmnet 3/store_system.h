#ifndef STORE_SYSTEM_H
#define STORE_SYSTEM_H

#include <string>
#include <unordered_map>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Structure for customer
struct Customer {
    string cnic;
    string name;
    string mobile;
    string address;

    bool operator<(const Customer& other) const {
        return cnic < other.cnic;
    }
};

// Structure for grocery item
struct GroceryItem {
    string barcode;
    string title;
    double unitPrice;
    int quantity;

    void setDetails(const string& b, const string& t, double u, int q);
    string getBarcode() const;
    string getTitle() const;
    double getUnitPrice() const;
    int getQuantity() const;
    void reduceQuantity(int amount);
};

// Binary Search Tree for Customers
class CustomerBST {
private:
    struct Node {
        Customer data;
        Node* left, * right;
        Node(const Customer& customer);
    };

    Node* root;
    Node* insert(Node* node, const Customer& customer);
    Node* findMin(Node* node);
    Node* remove(Node* node, const string& cnic);
    void inOrder(Node* node);

public:
    CustomerBST();
    void insert(const Customer& customer);
    void remove(const string& cnic);
    void display();
};

// Groceries handled with unordered_map
class GroceryStore {
private:
    unordered_map<string, GroceryItem> groceries;

public:
    void addItem(const GroceryItem& item);
    void removeItem(const string& barcode);
    void updateQuantity(const string& barcode, int quantity);
    void searchByBarcode(const string& barcode);
    void displayAll();
    bool purchaseItem(const string& barcode, int quantity);
};

// Graph for delivery using adjacency list
class DeliveryGraph {
private:
    struct Node {
        string name;
        int weight;
        Node* next;
        Node(const string& name, int weight);
    };

    map<string, Node*> adjList;

public:
    void addEdge(const string& u, const string& v, int weight);
    void shortestPath(const string& src, const string& dest);
};

#endif
