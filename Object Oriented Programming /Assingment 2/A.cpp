#include<iostream>
#include<iomanip>
using namespace std;

class Angle {
private:
	int degree;
	float minutes;
	char direction;
public:
	Angle(int deg, float min, char dir);
	void getAngle();
	void displayAngle(); 
};
Angle::Angle(int deg, float min, char dir) {
	degree = deg;
	minutes = min;
	direction = dir;
}
void Angle :: getAngle() {
	
		cout << "Enter degress: ";
		cin >> degree;
		cout << "Enter minutes: ";
		cin >> minutes;
		cout << "Enter direction ( N, S, E, or W): ";
		cin >> direction;
}
void Angle::displayAngle(){
	cout << degree << " " << fixed << setprecision(1) << minutes << " ` " << direction << endl;
}
int main() {
	Angle firstAngle(149, 34.8, 'W');
	cout << "First Angle : ";
	firstAngle.displayAngle();
	char choice;
	do {
		Angle secondAngle(0, 0.0, 'N');
		secondAngle.getAngle();

		cout << "Entered Angle: ";
		secondAngle.displayAngle();

		cout << "You want to enter another angle (y/n): ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
}
