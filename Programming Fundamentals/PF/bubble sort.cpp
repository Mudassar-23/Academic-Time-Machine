#include<iostream>
#include<fstream>
using namespace std;

void displayArray(int arr[]) {

	for(int i = 0; i < 10; i++) {
	    cout << arr[i] << " ";
	}
}
// Ascending 
void sortAscending(int arr[]) {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
// Dscending 
void sortDescending(int arr[]) {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			if (arr[j] < arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

int main() {
	
	int arr[10];

	ifstream inputFile("d:\\lmn.txt");
	//ofstream outputFile("d:\\pqr.txt");

	if (inputFile.is_open()) {
		for (int i = 0; i < 10; i++) {
			inputFile>> arr[i];
		}
		inputFile.close();
	}
	else {
		cout << "Unable to open the file.\n";
		return 1;
	}
	
	cout << "Original Array: " << endl;
	displayArray(arr);

	cout << "Array  sorting in ascending order: " << endl;
	
	 sortAscending(arr);
	 for (int i = 0; i < 10; i++) {

		 cout << arr[i] << endl;

	 }

	cout << "Array  sorting in descending order: " << endl;
	sortDescending(arr);
	for (int i = 0; i < 10; i++) {

		cout << arr[i]<<endl;
	
	}
	return 0;
}