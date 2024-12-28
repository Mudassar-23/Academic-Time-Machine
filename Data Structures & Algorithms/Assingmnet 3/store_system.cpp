#include "store_system.h"

// Implementation of GroceryItem methods
void GroceryItem::setDetails(const string& b, const string& t, double u, int q) {
    barcode = b;
    title = t;
    unitPrice = u;
    quantity = q;
}

string GroceryItem::getBarcode() const { return barcode; }
string GroceryItem::getTitle() const { return title; }
double GroceryItem::getUnitPrice() const { return unitPrice; }
int GroceryItem::getQuantity() const { return quantity; }
void GroceryItem::reduceQuantity(int amount) { quantity -= amount; }

// CustomerBST Node constructor
CustomerBST::Node::Node(const Customer& customer) : data(customer), left(nullptr), right(nullptr) {}

// CustomerBST methods
CustomerBST::CustomerBST() : root(nullptr) {}

CustomerBST::Node* CustomerBST::insert(Node* node, const Customer& customer) {
    if (!node) return new Node(customer);
    if (customer.cnic < node->data.cnic)
        node->left = insert(node->left, customer);
    else
        node->right = insert(node->right, customer);
    return node;
}

CustomerBST::Node* CustomerBST::findMin(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

CustomerBST::Node* CustomerBST::remove(Node* node, const string& cnic) {
    if (!node) return nullptr;
    if (cnic < node->data.cnic)
        node->left = remove(node->left, cnic);
    else if (cnic > node->data.cnic)
        node->right = remove(node->right, cnic);
    else {
        if (!node->left) {
            Node* right = node->right;
            delete node;
            return right;
        }
        else if (!node->right) {
            Node* left = node->left;
            delete node;
            return left;
        }
        Node* minRight = findMin(node->right);
        node->data = minRight->data;
        node->right = remove(node->right, minRight->data.cnic);
    }
    return node;
}

void CustomerBST::inOrder(Node* node) {
    if (!node) return;
    inOrder(node->left);
    cout << node->data.name << " (" << node->data.cnic << ")\n";
    inOrder(node->right);
}

void CustomerBST::insert(const Customer& customer) {
    root = insert(root, customer);
}

void CustomerBST::remove(const string& cnic) {
    root = remove(root, cnic);
}

void CustomerBST::display() {
    inOrder(root);
}

// GroceryStore methods
void GroceryStore::addItem(const GroceryItem& item) {
    groceries[item.barcode] = item;
}

void GroceryStore::removeItem(const string& barcode) {
    groceries.erase(barcode);
}

void GroceryStore::updateQuantity(const string& barcode, int quantity) {
    if (groceries.find(barcode) != groceries.end()) {
        groceries[barcode].quantity -= quantity;
        if (groceries[barcode].quantity < 0) groceries[barcode].quantity = 0;
    }
    else {
        cout << "Item not found!\n";
    }
}

void GroceryStore::searchByBarcode(const string& barcode) {
    if (groceries.find(barcode) != groceries.end()) {
        const auto& item = groceries[barcode];
        cout << "Item Found: " << item.title
            << ", Quantity: " << item.quantity
            << ", Unit Price: $" << item.unitPrice << "\n";
    }
    else {
        cout << "Item not found!\n";
    }
}

void GroceryStore::displayAll() {
    cout << "Groceries:\n";
    for (const auto& pair : groceries) {
        const auto& item = pair.second;
        cout << "Barcode: " << item.barcode
            << ", Title: " << item.title
            << ", Quantity: " << item.quantity
            << ", Unit Price: $" << item.unitPrice << "\n";
    }
}

bool GroceryStore::purchaseItem(const string& barcode, int quantity) {
    if (groceries.find(barcode) != groceries.end()) {
        auto& item = groceries[barcode];
        if (item.quantity >= quantity) {
            item.quantity -= quantity;
            cout << "Purchased " << quantity << " of " << item.title << ".\n";
            return true;
        }
        else {
            cout << "Not enough quantity available for " << item.title << ".\n";
            return false;
        }
    }
    else {
        cout << "Item not found!\n";
        return false;
    }
}

// DeliveryGraph Node constructor
DeliveryGraph::Node::Node(const string& name, int weight) : name(name), weight(weight), next(nullptr) {}

// DeliveryGraph methods
void DeliveryGraph::addEdge(const string& u, const string& v, int weight) {
    Node* nodeU = new Node(v, weight);
    nodeU->next = adjList[u];
    adjList[u] = nodeU;

    Node* nodeV = new Node(u, weight);
    nodeV->next = adjList[v];
    adjList[v] = nodeV;
}

void DeliveryGraph::shortestPath(const string& src, const string& dest) {
    const int INF = 9999999;
    map<string, int> dist;
    map<string, string> parent;

    for (const auto& pair : adjList) dist[pair.first] = INF;
    dist[src] = 0;

    for (int i = 0; i < adjList.size(); i++) {
        for (const auto& pair : adjList) {
            string u = pair.first;
            for (Node* neighbor = adjList[u]; neighbor != nullptr; neighbor = neighbor->next) {
                if (dist[u] + neighbor->weight < dist[neighbor->name]) {
                    dist[neighbor->name] = dist[u] + neighbor->weight;
                    parent[neighbor->name] = u;
                }
            }
        }
    }

    if (dist[dest] == INF) {
        cout << "No path found.\n";
        return;
    }

    string path = dest;
    for (string cur = dest; cur != src; cur = parent[cur]) {
        path = parent[cur] + " -> " + path;
    }
    cout << "Shortest path: " << path << " (Distance: " << dist[dest] << "km)\n";
}
