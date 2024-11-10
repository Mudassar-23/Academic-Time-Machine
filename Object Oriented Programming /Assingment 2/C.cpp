#include<iostream>
#include<string>
using namespace std;

class Vehicle {
public:
  string make;
  string name;
};

class Car : public Vehicle {
public:
   int seats;
};

class Truck : public Vehicle {
public:
   int wheels;
   int capacity;
};

class ShowRoom {
public:
   Car cars[100];
   Truck trucks[100]; 
   int car_count = 0;
   int truck_count = 0;

   void AddCarInList(string make, string name, int seats) {
       cars[car_count].make = make;
       cars[car_count].name = name;
       cars[car_count].seats = seats;
       car_count++;
   }

   void AddTruckInList(string make, string name, int wheels, int capacity) {
       trucks[truck_count].make = make;
       trucks[truck_count].name = name;
       trucks[truck_count].wheels = wheels;
       trucks[truck_count].capacity = capacity;
       truck_count++;
   }

   void DisplayVehicles() {
       int vehicle_number = 1;
       for (int i = 0; i < truck_count; i++) {
           cout << "Vehicle " << vehicle_number++ << ":\n" << endl;
          cout << "Truck Info:\n";
          cout << trucks[i].make << " - " << trucks[i].name << "\n";
          cout << "No of Wheels : " << trucks[i].wheels << "\n";
          cout << "Loading Capacity: " << trucks[i].capacity << " Tons\n" << endl;
       }
       for (int i = 0; i < car_count; i++) {
           cout << "\nVehicle " << vehicle_number++ << ":\n" ;
           cout << "Car Info:\n";
           cout << cars[i].make << " - " << cars[i].name << "\n";
           cout << "No of seats: " << cars[i].seats << "\n";
       }
   }
};

int main() {

   ShowRoom sr;

   sr.AddTruckInList("Hino", "Jumbo Ranger", 14, 100);
   sr.AddCarInList("Honda", "City", 4);
   sr.AddCarInList("Suzuki", "Mehran", 4);
   sr.AddTruckInList("Nissan", "Atlas", 8, 50);

   sr.DisplayVehicles();

   return 0;
}