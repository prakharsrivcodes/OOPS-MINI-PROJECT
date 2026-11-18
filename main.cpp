#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ==========================================
// BASE CLASS: EWaste (Demonstrates Abstraction)
// ==========================================
class EWaste {
protected:
    int id;
    string name;
    double weight;
    string status;

public:
    EWaste(int i, string n, double w, string s) 
        : id(i), name(n), weight(w), status(s) {}
    
    // Virtual destructor for proper cleanup in polymorphism
    virtual ~EWaste() {}

    // Pure Virtual Functions (Enforcing Polymorphism)
    virtual string getCategory() const = 0;
    virtual string getDisposalAdvice() const = 0;

    // Getters and Setters
    int getId() const { return id; }
    string getName() const { return name; }
    double getWeight() const { return weight; }
    string getStatus() const { return status; }
    void setStatus(string newStatus) { status = newStatus; }

    // Virtual display function
    virtual void display() const {
        cout << left << setw(5) << id
             << setw(20) << name
             << setw(15) << getCategory()
             << setw(10) << fixed << setprecision(2) << weight
             << setw(12) << status << endl;
    }
};

// ==========================================
// DERIVED CLASSES (Demonstrates Inheritance)
// ==========================================

class Mobile : public EWaste {
public:
    Mobile(int i, string n, double w, string s) : EWaste(i, n, w, s) {}

    string getCategory() const override {
        return "Mobile";
    }

    string getDisposalAdvice() const override {
        return "Remove battery & SIM, wipe personal data, and drop in certified e-waste bin.";
    }
};

class Laptop : public EWaste {
public:
    Laptop(int i, string n, double w, string s) : EWaste(i, n, w, s) {}

    string getCategory() const override {
        return "Laptop";
    }

    string getDisposalAdvice() const override {
        return "Backup data, format hard drive securely, donate if working or send to recycler.";
    }
};

class Battery : public EWaste {
public:
    Battery(int i, string n, double w, string s) : EWaste(i, n, w, s) {}

    string getCategory() const override {
        return "Battery";
    }

    string getDisposalAdvice() const override {
        return "HAZARDOUS! Tape terminals to prevent short circuits and hand over to specialists.";
    }
};

class Appliance : public EWaste {
public:
    Appliance(int i, string n, double w, string s) : EWaste(i, n, w, s) {}

    string getCategory() const override {
        return "Appliance";
    }

    string getDisposalAdvice() const override {
        return "Send to certified electronic recycling facility for metal/plastic extraction.";
    }
};

// ==========================================
// MANAGER CLASS (Handles Collection & Files)
// ==========================================
class EWasteManager {
private:
    vector<EWaste*> items; // Polymorphic container storing base class pointers
    int nextId;
    const string filename = "ewaste_records.txt";

public:
    EWasteManager() : nextId(1) {
        loadFromFile();
    }

    // Destructor to prevent memory leaks (clean up dynamic pointers)
    ~EWasteManager() {
        saveToFile();
        for (auto item : items) {
            delete item;
        }
        items.clear();
    }

    void addItem() {
        int choice;
        string name;
        double weight;

        cout << "\n--- Add New E-Waste Item ---\n";
        cout << "1. Mobile\n2. Laptop\n3. Battery\n4. Appliance/Other\n";
        cout << "Enter category choice (1-4): ";
        cin >> choice;
        cin.ignore();

        cout << "Enter item name/model: ";
        getline(cin, name);

        cout << "Enter weight (in kg): ";
        cin >> weight;

        EWaste* newItem = nullptr;

        switch (choice) {
            case 1: newItem = new Mobile(nextId, name, weight, "Registered"); break;
            case 2: newItem = new Laptop(nextId, name, weight, "Registered"); break;
            case 3: newItem = new Battery(nextId, name, weight, "Registered"); break;
            default: newItem = new Appliance(nextId, name, weight, "Registered"); break;
        }

        items.push_back(newItem);
        cout << "\n[Success] Item registered successfully! Assigned ID: " << nextId << endl;
        cout << "Disposal Advice: " << newItem->getDisposalAdvice() << endl;
        nextId++;
    }

    void viewAllItems() const {
        if (items.empty()) {
            cout << "\nNo e-waste records found.\n";
            return;
        }

        cout << "\n============================================================\n";
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Category"
             << setw(10) << "Weight" << setw(12) << "Status" << endl;
        cout << "============================================================\n";

        for (const auto& item : items) {
            item->display(); // Dynamic Polymorphism in action
        }
        cout << "============================================================\n";
    }

    void searchItem() const {
        if (items.empty()) {
            cout << "\nNo records to search.\n";
            return;
        }

        int id;
        cout << "Enter Item ID to search: ";
        cin >> id;

        for (const auto& item : items) {
            if (item->getId() == id) {
                cout << "\n[Record Found]\n";
                item->display();
                cout << "Advice: " << item->getDisposalAdvice() << endl;
                return;
            }
        }
        cout << "\nItem with ID " << id << " not found.\n";
    }

    void updateStatus() {
        int id;
        cout << "Enter Item ID to update status: ";
        cin >> id;

        for (auto& item : items) {
            if (item->getId() == id) {
                int statusChoice;
                cout << "\nCurrent Status: " << item->getStatus() << endl;
                cout << "Select new status:\n1. Collected\n2. Processing\n3. Recycled\n4. Reused\n5. Disposed\nChoice: ";
                cin >> statusChoice;

                string newStatus;
                switch (statusChoice) {
                    case 1: newStatus = "Collected"; break;
                    case 2: newStatus = "Processing"; break;
                    case 3: newStatus = "Recycled"; break;
                    case 4: newStatus = "Reused"; break;
                    default: newStatus = "Disposed"; break;
                }

                item->setStatus(newStatus);
                cout << "\n[Success] Status updated to: " << newStatus << endl;
                return;
            }
        }
        cout << "\nItem not found.\n";
    }

    void deleteItem() {
        int id;
        cout << "Enter Item ID to delete: ";
        cin >> id;

        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it; // Free memory
                items.erase(it);
                cout << "\n[Success] Record deleted successfully!\n";
                return;
            }
        }
        cout << "\nItem not found.\n";
    }

    void showStatistics() const {
        if (items.empty()) {
            cout << "\nNo statistics available.\n";
            return;
        }

        double totalWeight = 0;
        int recycledCount = 0;

        for (const auto& item : items) {
            totalWeight += item->getWeight();
            if (item->getStatus() == "Recycled" || item->getStatus() == "Reused") {
                recycledCount++;
            }
        }

        cout << "\n===== E-WASTE STATISTICS (SDG 12) =====\n";
        cout << "Total Registered Items: " << items.size() << endl;
        cout << "Total E-Waste Weight: " << fixed << setprecision(2) << totalWeight << " kg" << endl;
        cout << "Successfully Recycled/Reused: " << recycledCount << " items\n";
        cout << "=======================================\n";
    }

    // File Handling: Save
    void saveToFile() const {
        ofstream file(filename);
        if (!file.is_open()) return;

        for (const auto& item : items) {
            file << item->getCategory() << "|" << item->getId() << "|" 
                 << item->getName() << "|" << item->getWeight() << "|" 
                 << item->getStatus() << "\n";
        }
        file.close();
    }

    // File Handling: Load
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) return;

        string line;
        int maxId = 0;

        while (getline(file, line)) {
            stringstream ss(line);
            string cat, idStr, name, weightStr, status;

            getline(ss, cat, '|');
            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, weightStr, '|');
            getline(ss, status, '|');

            if (!idStr.empty()) {
                int id = stoi(idStr);
                double weight = stod(weightStr);
                EWaste* item = nullptr;

                if (cat == "Mobile") item = new Mobile(id, name, weight, status);
                else if (cat == "Laptop") item = new Laptop(id, name, weight, status);
                else if (cat == "Battery") item = new Battery(id, name, weight, status);
                else item = new Appliance(id, name, weight, status);

                items.push_back(item);
                if (id >= nextId) {
                    nextId = id + 1;
                }
            }
        }
        file.close();
    }
};

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    EWasteManager manager;
    int choice;

    do {
        cout << "\n============================================\n";
        cout << "     E-WASTE MANAGEMENT & RECYCLING SYSTEM  \n";
        cout << "     (Aligned with SDG 12)                  \n";
        cout << "============================================\n";
        cout << "1. Add New E-Waste Item\n";
        cout << "2. View All Records\n";
        cout << "3. Search Item by ID\n";
        cout << "4. Update Recycling Status\n";
        cout << "5. Show Statistics & Summary\n";
        cout << "6. Delete Record\n";
        cout << "0. Save & Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addItem(); break;
            case 2: manager.viewAllItems(); break;
            case 3: manager.searchItem(); break;
            case 4: manager.updateStatus(); break;
            case 5: manager.showStatistics(); break;
            case 6: manager.deleteItem(); break;
            case 0:
                cout << "\nSaving data and exiting. Thank you!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}