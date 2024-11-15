#include <iostream>
#include <string>
using namespace std;

class Voter {
private:
    int voterID;
    string name;
    int age;
    Voter* next;
    Voter* prev;

public:
    Voter(int id, string n, int a) {
        setVoterID(id);
        setName(n);
        setAge(a);
        next = nullptr;
        prev = nullptr;
    }

    // Getters
    int getVoterID() {
        return voterID;
    }

    string getName() {
        return name;
    }

    int getAge() {
        return age;
    }

    Voter* getNext() {
        return next;
    }

    Voter* getPrev() {
        return prev;
    }

    // Setters
    void setVoterID(int id) {
        voterID = id;
    }

    void setName(string n) {
        name = n;
    }

    void setAge(int a) {
        age = a;
    }

    void setNext(Voter* n) {
        next = n;
    }

    void setPrev(Voter* p) {
        prev = p;
    }

    
};

class VoterList {
private:
    Voter* head;

public:
    VoterList() {
        head = nullptr;
    }

    // Add a voter to the list
    void addVoter(int id, string name, int age) {
        Voter* newVoter = new Voter(id, name, age);

        // If the list is empty, make newVoter the head
        if (head == nullptr) {
            head = newVoter;
        }
        else {
            newVoter->setNext(head);
            head->setPrev(newVoter);
            head = newVoter;
        }

        cout << "Voter with ID " << id << " added.\n";
    }

    // Delete a voter by voterID
    void deleteVoter(int id) {
        Voter* current = head;

        // If the list is empty
        if (head == nullptr) {
            cout << "No voters in the list to delete.\n";
            return;
        }

        // Search for the voter to delete
        while (current != nullptr && current->getVoterID() != id) {
            current = current->getNext();
        }

        // If the voter was not found
        if (current == nullptr) {
            cout << "Voter with ID " << id << " not found.\n";
            return;
        }

        // If the node to be deleted is the head
        if (current == head) {
            head = current->getNext();
            if (head != nullptr) {
                head->setPrev(nullptr);
            }
        }
        else {
            if (current->getPrev() != nullptr) {
                current->getPrev()->setNext(current->getNext());
            }
            if (current->getNext() != nullptr) {
                current->getNext()->setPrev(current->getPrev());
            }
        }

        delete current;
        cout << "Voter with ID " << id << " deleted.\n";
    }

    // Print the list of voters
    void printVoterList() {
        Voter* current = head;

        if (current == nullptr) {
            cout << "No voters in the list.\n";
            return;
        }

        cout << "Voter List:\n";
        while (current != nullptr) {
            cout << "Voter ID: " << current->getVoterID() << ", Name: " << current->getName() << ", Age: " << current->getAge() << endl;
            current = current->getNext();
        }
    }
};

int main() {
    VoterList voterList;

    voterList.addVoter(101, "Ahmed Ali", 30);
    voterList.addVoter(203, "Usman", 25);
    voterList.addVoter(309, "Asad", 23);
    voterList.addVoter(150, "Husnain", 29);

    voterList.printVoterList();

    cout << "\nDeleting Voter ID 203\n";
    voterList.deleteVoter(203);

    voterList.printVoterList();

    return 0;
}
