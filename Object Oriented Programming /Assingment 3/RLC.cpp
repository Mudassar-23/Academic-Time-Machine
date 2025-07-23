#include <iostream>
#include<string>
#include <cmath>
#include <string>
using namespace std;

class Complex
{
private:
	float real;
	float imag;
public:
	Complex():real(0.0),imag(0.0){}

	Complex(float r, float i) :real(r), imag(i) {}

	Complex operator+(const Complex&c) {
		return Complex(real + c.real, imag + c.imag);
	}
	Complex operator-(const Complex& c) {
		return Complex(real - c.real, imag - c.imag);
	}
	Complex operator*(const Complex& c) {
		float real_p = real * c.real - imag * c.imag;
		float imag_p = real * c.imag - imag * c.real;
		return Complex(real_p, imag_p);
	}
	Complex operator/(const Complex& other) {
		float denominator = other.real * other.real + other.imag * other.imag;
		float real_part = (real * other.real + imag * other.imag) / denominator;
		float imag_part = (imag * other.real - real * other.imag) / denominator;
		return Complex(real_part, imag_part);
	}
	
	float magnitude() const {
		return sqrt(real * real + imag * imag);
	}
	float phase_angle() const {
		return atan2(imag, real);
	}
	float get_real() const {
		return real;
	}
	float get_imag() const {
		return imag;
	}
};

class RLC_Circuit {
private:
	float R, L, C;
	float frequency;
	string circuit_type;
	string rollno;
public:
	RLC_Circuit():R(0.0),L(0.0),C(0.0){}

	RLC_Circuit(string r): rollno(r) {}

	void input() {
		cout << "Enter Resistance: ";
		cin >> R;
		cout << "Enter Inductance: ";
		cin >> L;
		cout << "Enter Capacitance: ";
		cin >> C;
		cout << "Enter Frequency: ";
		cin >> frequency;
		cout << "Enter Circuit Type (series or parallel): ";
		cin >> circuit_type;
	}

	Complex calculate_impedance() {
		float omega = 2 * 3.14 * frequency;
		float impedance_real, impedance_imag;

		if (circuit_type == "series") {
			impedance_real = R;
			impedance_imag = omega * L - 1 / (omega * C);
		}
		else if (circuit_type == "parallel") {
			float inv_RLC = 1 / (omega * L - 1 / (omega * C));
			impedance_real = 1 / (1 / R + inv_RLC);
			impedance_imag = inv_RLC;
		}

		return Complex(impedance_real, impedance_imag);
	}


	float calculate_resonant_frequency() {
		return 1 / (2 * 3.14 * sqrt(L * C));
	}

	Complex calculate_total_current(Complex voltage) {
		Complex impedance = calculate_impedance();
		return voltage / impedance;
	}

	void calculate_power(Complex current, Complex voltage, float& real_power) {

		real_power = voltage.get_real() * current.get_real() + voltage.get_imag() * current.get_imag();
	
	}

};
int main() {
	int num_circuits = 0;
	string roll;
	cout << "Enter your roll number: ";
	cin >> roll;
	cout << "Enter the number of RLC circuits: ";
	cin >> num_circuits;

	RLC_Circuit *circuits= new RLC_Circuit[num_circuits];

	for (int i = 0; i < num_circuits; i++)
	{
		cout << "\nCircuit " << i + 1 << ":" << endl;
		circuits[i].input();
	}
	for (int i = 0; i < num_circuits; i++) {
		cout << "\nResults for circuit " << i + 1 << ":" << endl;

		Complex impedance = circuits[i].calculate_impedance();
		cout << "Equivalent Impedance" << impedance.get_real() << " +j " << impedance.get_imag() << endl;

		float resonant_freq = circuits[i].calculate_resonant_frequency();
		cout << "Resonant Frequency: " << resonant_freq << " Hz" << endl;

		Complex voltage(100, 0); 
		Complex total_current = circuits[i].calculate_total_current(voltage);
		cout << "Total Current: " << total_current.get_real() << " + j" << total_current.get_imag() << endl;

		float real_power, reactive_power;
		circuits[i].calculate_power(total_current, voltage, real_power);
		cout << "Real Power: " << real_power << " Watts" << endl;
	}
	delete[]circuits;
	return 0;
}