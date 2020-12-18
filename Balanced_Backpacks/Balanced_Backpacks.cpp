#include <iostream>
#include <vector>
using namespace std;

// Gets the weights possible given a certain backpack
// Takes vector of weights in backpack, max weight allowed, and arr to put final values in
void get_weights(vector<int> backpack, int max_weight, bool final_arr[]) {
    // n = rows, m = cols
    int n = backpack.size() + 1;
    int m = max_weight + 1;

    // Arr contains possible weights for all weights
    bool weights[n][m];

    // Initialize row 1 = false
    for(int i = 0; i < m; i++) {
        weights[0][i] = false;
    }

    // Initialize col 1 = true
    // (0, 0) = true
    for(int i = 0; i < n; i++) {
        weights[i][0] = true;
    }

    // Dynamic table to calculate all possible weights
    // Rows = i
    for(int i = 1; i < n; i++) {
        // Cols = j
        for(int j = 1; j < m; j++) {
            // If weight is already possible from previous weights, weight is still possible
            if(weights[i - 1][j]) {
                weights[i][j] = true;
            }

            else {
                // Calculates remaining weight after using current weight
                int rem_weight = j - backpack[i - 1];
                
                // If current weight <= desired weight && weight rem_weight is possible
                // Weight is possible
                if((rem_weight >= 0) && (weights[i - 1][rem_weight])) {
                    weights[i][j] = true;
                }
                // Else weight is not possible
                else {
                    weights[i][j] = false;
                }
            }
        }
    }
    // Sets values in arr to last arr of weights
    // Represents which weights can be achieved in that specific backpack
    for(int i = 0; i < m; i++) {
        final_arr[i] = weights[n-1][i];
    }
}



int main() {
    // n = # of backpacks, temp_val = input from console, counter = current backpack # in while loop,
    // min_backpack_weight = total weight of lightest backpack, 
    // current_backpack_weight = weight of current backpack
    int n, temp_val, counter = 0, min_backpack_weight = 10000, current_backpack_weight = 0;
    
    // Takes n
    cin >> n;
    
    if(n == 0) min_backpack_weight = 0;

    // Keeps track of backpacks, and weights in each backpack
    vector<vector<int> > backpacks;

    // Current backpack; cleared for every new backpack
    vector<int> current_backpack;
    
    // Adds all weights for all backpacks
    while(counter < n) {
        // Takes input
        cin >> temp_val;

        // If there are no more weights for backpack (input = -1), add backpack to vec var backpacks
        if(temp_val == -1) {
            backpacks.push_back(current_backpack);

            // Checks if current backpack's max weight is less than current max weight
            if(current_backpack_weight < min_backpack_weight) {
                min_backpack_weight = current_backpack_weight;
            }
            // Clears current_backpack_weight
            current_backpack_weight = 0;

            // Empty current backpack, and move onto next backpack
            current_backpack.clear();
            counter++;
        }
        // Add weight to current_backpack backpack
        else {
            current_backpack.push_back(temp_val);
            current_backpack_weight += temp_val;
        }
    }



    // # of cols in board1
    int m = min_backpack_weight + 1;

    
    
    
    
    
    
    
    // Board #1 = keeps track of all weights each backpack can reach from 0-->weight of lightest backpack
    bool board[n][m];

    for(int i = 0; i < n; i++) {
        bool temp[m];
        get_weights(backpacks[i], min_backpack_weight, temp);

        for(int j = 0; j < m; j++) {
            board[i][j] = temp[j];

            if(i > 0 && j > 0 && !(board[i-1][j])) {
                board[i][j] = false;
            }
        }
    }


    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         cout << board[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << endl << endl << endl;
    int max = 0;

    for(int i = min_backpack_weight; i >= 0; i--) {
        if(board[n-1][i]) {
            max = i;
            break;
        }
    }
    cout << max;
}