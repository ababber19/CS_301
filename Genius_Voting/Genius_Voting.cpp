#include <iostream>
#include <math.h>
using namespace std;

int main() {
    // Takes console input n, where n = number of geniuses in competition
    int n;
    cin >> n;
    
    // Looking for highest value j where 2^j < n (number of geniuses)
    // Start at i = 12 because 2^(13) > 5000 (max possible input)
    for(int i = 12; i > 0; i--) {
        if(pow(2, i) < n) {
            // Prints value to console
            cout << pow(2, i);
            break;
        }
    }
}
