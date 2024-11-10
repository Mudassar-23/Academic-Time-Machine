#include <iostream>
using namespace std;
void allocateMemory(int*& ans, int size) {
	ans = new int[size];
}
void RotateArray(int* ans, int size, int k) {
	int* temp = new int[k];
	for (int i = 0; i < k; i++) {
		temp[i] = ans[size - k + i];
	}
	for (int i = size - 1; i >= k; i--) {
		ans[i] = ans[i - k];
	}
	for (int i = 0; i < k; i++) {
		ans[i] = temp[i];
	}
	delete[] temp;
}
void deallocateMemory(int*& ans) {
	delete[] ans;
	ans = nullptr;
}
int main() {
	int* ans = nullptr;
	int size, k;
	cout << "Enter the size of the array: ";
	cin >> size;
	cout << "Enter the value of k: ";
	cin >> k;
	allocateMemory(ans, size);
	cout << "Enter the elements of the array:" << endl;
	for (int i = 0; i < size; i++)
		cin >> ans[i];
	RotateArray(ans, size, k);
	cout << "Rotatate array is :" << endl;
	for (int i = 0; i < size; i++)
		cout << ans[i] << " ";
	deallocateMemory(ans);
}
