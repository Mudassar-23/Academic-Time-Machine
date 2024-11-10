//#include <iostream>
//#include <cstring>
//using namespace std;
//
//int numOfOccurences(const char* sentence, const char* find) {
//
//    int count = 0;
//
//    for (int i = 0; sentence[i] != '0'; i++) {
//
//        char ch = find[i];
//
//        if (sentence[i] == find[0]) {
//            bool cheak = true;
//
//            // Loop through each character in the word
//            for (int j = 0; find[j] != '\0'; j++) {
//                // If the characters don't match
//                if (sentence[i + j] != find[j]) {
//                    cheak = false;
//                    break;
//                }
//            }
//            if (cheak) {
//                count++;
//            }
//        }
//    }
//
//    return count;
//}
//int main() {
//    const int MAX_SIZE = 100;
//    char sentence[MAX_SIZE];
//    char find[MAX_SIZE];
//
//    cout << "Enter the sentence: ";
//    cin.getline(sentence, MAX_SIZE);
//
//    cout << "Enter the word to find: ";
//    cin.getline(find, MAX_SIZE);
//
//    int occurrences = numOfOccurences(sentence, find);
//    cout << "Number of occurrences: " << occurrences << endl;
//    system("pause");
//}