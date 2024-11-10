//#include <iostream>
//#include <cstdlib> 
//#include <ctime>   
//using namespace std;
//
//void fillArray(int* arr, int size) {
//    for (int i = 0; i < size; i++) {
//        arr[i] = rand() % 100 + 1;
//    }
//}
//void findEvenOdd(int* arr, int size, int** evenPtr, int** oddPtr) {
//    int evenCount = 0;
//    int oddCount = 0;
//
//    for (int i = 0; i < size; i++) {
//        if (arr[i] % 2 == 0) {
//            evenPtr[evenCount++] = &arr[i];
//        }
//        else {
//            oddPtr[oddCount++] = &arr[i];
//        }
//    }
//     Null-terminate the arrays of pointers
//    evenPtr[evenCount] = nullptr;
//    oddPtr[oddCount] = nullptr;
//}
//
//void display(int** x, int size) {
//    for (int i = 0; x[i] != nullptr; i++) {
//        cout << *x[i] << " ";
//    }
//    cout << endl;
//}
//int main() {
//     Seed the random number generator
//    srand(time(nullptr));
//
//    int size;
//    cout << "Enter the size of the array: ";
//    cin >> size;
//
//    int* arr = new int[size];
//    int** evenPtr = new int* [size];
//    int** oddPtr = new int* [size];
//
//     Fill the array with random numbers
//    fillArray(arr, size);
//
//    findEvenOdd(arr, size, evenPtr, oddPtr);
//
//    cout << "Even numbers in the array:\n";
//    display(evenPtr, size);
//
//    cout << "\nOdd numbers in the array:\n";
//    display(oddPtr, size);
//
//    delete[] arr;
//    delete[] evenPtr;
//    delete[] oddPtr;
//
//    return 0;
//}
//
//
