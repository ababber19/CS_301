#include <iostream>
using namespace std;



void merge(int arr[], int low, int mid, int high) {
    int size_left = mid - low + 1;
    int size_right = high - mid;
    

    // Creates two temp arrays; one before mid, one after mid
    int left_arr[size_left], right_arr[size_right];

    // Adds left arr elements
    for(int i = 0; i < size_left; i++) {
        left_arr[i] = arr[low + i];
    }

    // Adds right arr elements
    for(int i = 0; i < size_right; i++) {
        right_arr[i] = arr[mid + 1 + i];
    }


    // Index of first arr
    int i = 0;
    // Index of second arr
    int j = 0;
    // Index of sorted arr
    int k = low;

    // While loop to sort elements
    while(i < size_left && j < size_right) {
        // Adds left_arr element if < right_arr (starts from index 0 for both arr)
        if(left_arr[i] < right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        }
        // Otherwise, adds right_arr element
        else {
            arr[k] = right_arr[j];
            j++;
        }
        // Increments sorted arr counter
        k++;
    }

    // Adds any elements left from left_arr to end of arr
    while(i < size_left) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    // Adds any elements left from right_arr to end of arr
    while(j < size_right) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

// Recursive function
// Chooses mid point of arr, sorts arr before mid and after mid
void merge_sort(int arr[], int low, int high) {
    if(low < high) {
        // Gets mid index of arr; used to divide arr
        int mid = low + (high - low) / 2;
        
        // Sorts left arr
        merge_sort(arr, low, mid);
        // // Sorts right arr
        merge_sort(arr, mid + 1, high);
        
        // // Merges two arrays together
        merge(arr, low, mid, high);
    }
}


// Takes input from console, runs merge_sort, prints sorted arr
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

    // Call merge_sort method
    merge_sort(arr, 0, arr_size - 1);


    // Output sorted array to user
    for(int i = 0; i < arr_size; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}