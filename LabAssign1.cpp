#include <iostream>
#include <string>
using namespace std;

// Inventory Item ADT
class InventoryItem {
public:
    int itemID;
    string itemName;
    int quantity;
    float price;

    // Constructor
    InventoryItem(int id = 0, string name = "", int qty = 0, float pr = 0.0f) {
        itemID = id;
        itemName = name;
        quantity = qty;
        price = pr;
    }

    // Display item details
    void display() {
        cout << "Item ID: " << itemID
             << ", Name: " << itemName
             << ", Quantity: " << quantity
             << ", Price: " << price << endl;
    }
};

// Inventory Management System
class InventorySystem {
private:
    InventoryItem items[100]; // Array to store items
    int itemCount;

    // Multi-dimensional array (Price-Quantity Table)
    float priceQuantityTable[100][2]; // col[0] = price, col[1] = quantity

    // Sparse representation (store only non-zero quantities)
    int sparseMatrix[100][2]; // col[0] = itemID, col[1] = quantity

public:
    InventorySystem() {
        itemCount = 0;
    }

    // Insert new item
    // Time Complexity: O(1) → appending at the end
    // Space Complexity: O(1)
    void addItemRecord() {
        int id, qty;
        string name;
        float price;

        cout << "Enter Item ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Item Name: ";
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> qty;
        cout << "Enter Price: ";
        cin >> price;

        items[itemCount] = InventoryItem(id, name, qty, price);
        priceQuantityTable[itemCount][0] = price;
        priceQuantityTable[itemCount][1] = qty;

        if (qty != 0) { // store in sparse matrix only if non-zero
            sparseMatrix[itemCount][0] = id;
            sparseMatrix[itemCount][1] = qty;
        }
        itemCount++;

        cout << "Item added successfully!" << endl;
    }

    // Delete item by ID
    // Time Complexity: O(n) → worst case requires shifting all elements
    // Space Complexity: O(1)
    void removeItemRecord() {
        int id;
        cout << "Enter Item ID to delete: ";
        cin >> id;

        for (int i = 0; i < itemCount; i++) {
            if (items[i].itemID == id) {
                cout << "Item removed: " << items[i].itemName << endl;
                // Shift array elements left
                for (int j = i; j < itemCount - 1; j++) {
                    items[j] = items[j + 1];
                    priceQuantityTable[j][0] = priceQuantityTable[j + 1][0];
                    priceQuantityTable[j][1] = priceQuantityTable[j + 1][1];
                    sparseMatrix[j][0] = sparseMatrix[j + 1][0];
                    sparseMatrix[j][1] = sparseMatrix[j + 1][1];
                }
                itemCount--;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    // Search by ID or Name
    // Time Complexity: O(n) → linear search
    // Space Complexity: O(1)
    void searchByItem() {
        cin.ignore();
        string input;
        cout << "Enter Item ID or Name: ";
        getline(cin, input);

        for (int i = 0; i < itemCount; i++) {
            if (to_string(items[i].itemID) == input || items[i].itemName == input) {
                items[i].display();
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    // Manage price and quantity
    // Time Complexity: O(n) → iterates through all items
    // Space Complexity: O(1)
    void managePriceQuantity() {
        cout << "\nRow-Major Order (Item-wise):" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << "ItemID: " << items[i].itemID
                 << " | Price: " << priceQuantityTable[i][0]
                 << " | Quantity: " << priceQuantityTable[i][1] << endl;
        }

        cout << "\nColumn-Major Order (Attributes separately):" << endl;
        cout << "Prices: ";
        for (int i = 0; i < itemCount; i++) {
            cout << priceQuantityTable[i][0] << " ";
        }
        cout << "\nQuantities: ";
        for (int i = 0; i < itemCount; i++) {
            cout << priceQuantityTable[i][1] << " ";
        }
        cout << endl;
    }

    // Sparse representation
    // Time Complexity: O(n) → checks each item once
    // Space Complexity: O(k) → where k = number of non-zero items
    void optimizeSparseStorage() {
        cout << "Sparse Matrix (Non-zero quantities only):" << endl;
        for (int i = 0; i < itemCount; i++) {
            if (sparseMatrix[i][1] != 0) {
                cout << "ItemID: " << sparseMatrix[i][0]
                     << " | Quantity: " << sparseMatrix[i][1] << endl;
            }
        }
    }

    // Main Menu
    void menu() {
        int choice;
        while (true) {
            cout << "\n--- Inventory System ---" << endl;
            cout << "1. Add Item" << endl;
            cout << "2. Delete Item" << endl;
            cout << "3. Search Item" << endl;
            cout << "4. Manage Price & Quantity" << endl;
            cout << "5. Optimize Sparse Storage" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addItemRecord(); break;
                case 2: removeItemRecord(); break;
                case 3: searchByItem(); break;
                case 4: managePriceQuantity(); break;
                case 5: optimizeSparseStorage(); break;
                case 6: cout << "Exiting..." << endl; return;
                default: cout << "Invalid choice." << endl;
            }
        }
    }
};

// Main function
int main() {
    InventorySystem system;
    system.menu();
    return 0;
}
