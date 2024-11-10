#include <iostream>
#include <string>
using namespace std;

class Address {
public:
    string streetNumber;
    string suburb;
    string city;
    string province;

    Address(string streetNumber, string suburb, string city, string province)
        : streetNumber(streetNumber), suburb(suburb), city(city), province(province) {}
};

class Person {
public:
    string name;
    string mobileNumber;
    Address address;
    //parametrized constructor
    Person(string name, string mobileNumber, Address address)
        : name(name), mobileNumber(mobileNumber), address(address) {}
};


class Package {
protected:
    Person sender;
    Person receiver;
    double weight;
    double standardCostPerKg;

public:
    // Parameterized constructor
    Package(Person sender, Person receiver, double weight, double standardCostPerKg)
        : sender(sender), receiver(receiver), weight(weight), standardCostPerKg(standardCostPerKg) {}

    virtual double calculateCost() {
        return weight * standardCostPerKg;
    }

    virtual string getType() {
        return "Normal Package";
    }

    void printDetails() {
        cout << "Sender: " << sender.name << " (" << sender.mobileNumber << ")" << endl;
        cout << "Receiver: " << receiver.name << " (" << receiver.mobileNumber << ")" << endl;
        cout << "Package Type: " << getType() << endl;
    }
};

class OvernightPackage : public Package {
private:
    double additionalCostPerKg;

public:
    // Parameterized constructor
    OvernightPackage(Person sender, Person receiver, double weight, double standardCostPerKg, double additionalCostPerKg)
        : Package(sender, receiver, weight, standardCostPerKg), additionalCostPerKg(additionalCostPerKg) {}

    double calculateCost() {
        return (weight * (standardCostPerKg + additionalCostPerKg));
    }

    string getType() {
        return "Overnight Package";
    }
};

class TwoDayPackage : public Package {
private:
    double flatFee;

public:
    // Parameterized constructor
    TwoDayPackage(Person sender, Person receiver, double weight, double standardCostPerKg, double flatFee)
        : Package(sender, receiver, weight, standardCostPerKg), flatFee(flatFee) {}

    double calculateCost() {
        return (weight * standardCostPerKg) + flatFee;
    }

    string getType() {
        return "Two-Day Package";
    }
};

int main() {
    // Array of pointers to Package objects
    const int numPackages = 3;
    Package* packages[numPackages];

    // Create sender and receiver objects
    Person sender("Ali", "03211234567", Address("312", "Abubakar Block, Garden Town", "Lahore", "Punjab"));
    Person receiver("Saheen", "03123456789", Address("123", "Gulshan Block ", "Karachi", "Sindh"));

    // Instantiate different types of packages
    packages[0] = new Package(sender, receiver, 5.5, 10.0);
    packages[1] = new OvernightPackage(sender, receiver, 3.0, 12.0, 5.0);
    packages[2] = new TwoDayPackage(sender, receiver, 2.0, 8.0, 20.0);

    // Loop through the array and print details 
    for (int i = 0; i < numPackages; i++) {
        cout << "Package " << i + 1 << " details:" << endl;
        packages[i]->printDetails();
        cout << "Total delivery cost: " << packages[i]->calculateCost() << endl << endl;
    }

    // Free memory allocated for the packages
    for (int i = 0; i < numPackages; i++) {
        delete packages[i];
    }

    return 0;
}
