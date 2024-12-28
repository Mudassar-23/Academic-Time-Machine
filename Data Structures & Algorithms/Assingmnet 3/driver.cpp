#include "store_system.h"
using namespace std;

int main() {
    // Initialize data
    CustomerBST customerTree;
    GroceryStore store;
    DeliveryGraph graph;

    // Load customers
    ifstream customerFile("customers.txt");
    if (customerFile.is_open()) {
        string line;
        while (getline(customerFile, line)) {
            stringstream ss(line);
            Customer customer;
            getline(ss, customer.cnic, ',');
            getline(ss, customer.name, ',');
            getline(ss, customer.mobile, ',');
            getline(ss, customer.address, ',');
            customerTree.insert(customer);
        }
        customerFile.close();
    }

    // Load groceries
    ifstream groceryFile("groceries.txt");
    if (groceryFile.is_open()) {
        string line;
        while (getline(groceryFile, line)) {
            stringstream ss(line);
            GroceryItem item;
            string unitPriceStr, quantityStr;

            getline(ss, item.barcode, ',');
            getline(ss, item.title, ',');
            getline(ss, unitPriceStr, ',');
            getline(ss, quantityStr, ',');

            item.unitPrice = stod(unitPriceStr);
            item.quantity = stoi(quantityStr);

            store.addItem(item);
        }
        groceryFile.close();
    }

    // Add delivery routes
    graph.addEdge("Store", "Customer1", 10);
    graph.addEdge("Store", "Customer2", 15);
    graph.addEdge("Customer1", "Customer2", 5);

    // Display customers and groceries
    cout << "Customers:\n";
    customerTree.display();

    cout << "\nInitial Grocery Inventory:\n";
    store.displayAll();

    // Purchase interaction
    string barcode,title;
    int quantity,choice;
    double unitPrice;

    while (true) {
        
        cout << "\nMenu:\n";
        cout << "1. Add a new item\n";
        cout << "2. Remove an item\n";
        cout << "3. Update item quantity\n";
        cout << "4. Search item by barcode\n";
        cout << "5. Purchase an item\n";
        cout << "6. Display all items\n";
        cout << "7. Generate Bill\n";
        cout << "8. Delivered the Item to Customer\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: { // Add a new item
            cout << "Enter barcode: ";
            cin >> barcode;
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter unit price: ";
            cin >> unitPrice;
            cout << "Enter quantity: ";
            cin >> quantity;

            store.addItem({ barcode, title, unitPrice, quantity });
            cout << "Item added successfully.\n";
            break;
        }
        case 2: { // Remove an item
            cout << "Enter barcode of the item to remove: ";
            cin >> barcode;
            store.removeItem(barcode);
            cout << "Item removed successfully.\n";
            break;
        }
        case 3: { // Update item quantity
            cout << "Enter barcode of the item to update: ";
            cin >> barcode;
            cout << "Enter new quantity: ";
            cin >> quantity;
            store.updateQuantity(barcode, quantity);
            cout << "Item quantity updated successfully.\n";
            break;
        }
        case 4: { // Search item by barcode
            cout << "Enter barcode of the item to search: ";
            cin >> barcode;
            store.searchByBarcode(barcode);
            break;
        }
        case 5: { // Purchase an item
            cout << "Enter the barcode of the item to purchase: ";
            cin >> barcode;
            cout << "Enter quantity to purchase: ";
            cin >> quantity;

            store.purchaseItem(barcode, quantity);

            cout << "\nUpdated Grocery Inventory:\n";
            store.displayAll();
            break;
        }
        case 6: { // Display all items
            store.displayAll();
            break;
        }
        case 7: { // Generate Bill
           
            
            // Clear the bill after generation
            break;
        }
        case 8: {
            cout << "\nShortest Path:\n";
            graph.shortestPath("Store", "Customer1");
        }
        case 0: // Exit
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    
    }

    return 0;
}
