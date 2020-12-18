#include <iostream>
#include <random>
using namespace std;

// Swaps two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


// Creates pivot; swaps elements in arr compared to pivot
int partition(int arr[], int low, int high) {
    // Old code: chooses last element as pivot
    // int pivot = arr[high];
    
    // Randomly selects pivot, moves pivot to last position in arr
    int random = low + rand() % (high - low);
    swap(arr[random], arr[high]);
    int pivot = arr[high];

    // Index of where pivot should be at the end
    // Initialized to 0
    int i = low;
    // For-loop swaps all elements lower than pivot to before the pivot
    for(int j = low; j < high; j++) {
        // If the value is less than the pivot, it moves that value to arr[i] (starts at beginning of arr)
        if(arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    // Swaps pivot to arr[i] (now all elements to the left of the pivot < pivot)
    swap(arr[i], arr[high]);
    
    // Returns index of pivot
    return (i);
}


// Recursive function
// Chooses random partition, and sorts the array from below and above that partition
void quick_sort(int arr[], int low, int high) {
    if(low < high) {
        // Selects a partition
       int p = partition(arr, low, high);
       // Sorts from below the partition
       quick_sort(arr, low, p - 1);
       // Sorts from above the partition
       quick_sort(arr, p + 1, high);
    }
}


// Takes input from console, runs quick_sort, prints sorted arr
int main() {
    // Initialize and input arr_size
    int arr_size;
    cin >> arr_size;

    // Initialize arr
    int arr[arr_size];
    
    // Input arr
     for(int i = 0; i < arr_size; i++) {
         cin >> arr[i];
    }

    // Call quick_sort method
    quick_sort(arr, 0, arr_size - 1);

    // Output sorted array to user
    for(int i = 0; i < arr_size; i++) {
        cout << arr[i] << " ";
    }

return 0;
}