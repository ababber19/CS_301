#include <iostream>
using namespace std;



// Kadane alg to calculate max sum of contiguous array
int max_sum_in_arr(int arr[], int n) {
    int max_sum = -9999, current_max = 0;
    
    for(int i = 0; i < n; i++) {
        current_max += arr[i];

        if(current_max > max_sum) max_sum = current_max;

        if(current_max < 0) current_max = 0;
    }

    return max_sum;
}



int main() {
    // Size of array, max_sum of rectangles set to min val
    int n, max_sum = -9999;;
    cin >> n;

    // Sets matrix from inputs
    int matrix[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    
    // Arr of running sum
    int running_sum[n];


    // Goes through all left cols
    for(int left = 0; left < n; left++) {
        // Set running_sum to 0 for new left
        for(int k = 0; k < n; k++) {
            running_sum[k] = 0;
        }

        // Goes through all right cols
        for(int right = left; right < n; right++) {
            // Adds vals to running_sum arr
            for(int k = 0; k < n; k++) {
                running_sum[k] += matrix[right][k];
            }
            
            // Calculates temp_sum (max sum of running_sum arr)
            int temp_sum = max_sum_in_arr(running_sum, n);

            // If max_sum of running_sum arr > current max_sum, sets max_sum to temp_sum
            if(temp_sum > max_sum) max_sum = temp_sum;
        }
    }

    // Prints out max_sum
    cout << max_sum;
    

    // End of main method
    return 0;
}