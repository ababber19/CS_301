#include <iostream>
using namespace std;


// Takes input from console, runs counting_sort, prints sorted arr
int main() {
    // Initialize and input arr_size
    int arr_size;
    cin >> arr_size;
    
    // Set n = 1000, since max arr vals < 999
    int n = 1000;
    // Initialize all values in the count arr to 0
    int count[n];
    for(int i = 0; i < n; i++) {
        count[i] = 0;
    }

    // Increments count for each input from user (if input = 7, count[7]++)
    for(int i = 0; i < arr_size; i++) {
        int temp;
        cin >> temp;
        count[temp]++;
    }

    // Prints each val j number of times, where j is frequency of that val in the input
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < count[i]; j++) {
            cout << i << " ";
        }
    }
}