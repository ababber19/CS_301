#include <iostream>
using namespace std;


// Finds total power of all digits in a num
int pow_of_num(int a) {
    // Arr with power of each digit (arr[0] = power needed to display digit 0)  
    int dig_pow[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

    // Ensures a != 0 because while-loop ends when a==0
    if(a == 0) {
        return dig_pow[0];
    }

    // Var to keep track of total power of num a
    int tot_pow = 0;

    // Iterates through each digit of a, adds power of that digit to tot_pow
    while(a != 0) {
        int temp = a % 10;
        tot_pow += dig_pow[temp];
        a /= 10;
    }
    
    // Returns tot_pow
    return tot_pow;
}


// Finds all possible equations given a certain allocated power
void all_possible_eq(int pow) {
    // Var = total number of equations that work
    int total_eq = 0;
    
    // Goes through all possible sums from 0-1998
    for(int a = 0; a < 1000; a++) {
        int a_pow = pow_of_num(a);
        // Checks if power of a < pow to skip unnecessary steps
        if(a_pow < pow) {
            for(int b = a; b < 1000; b++) {
                // Gets power of b and c
                int c = a + b;
                int b_pow = pow_of_num(b);
                int c_pow = pow_of_num(c);

                // If total power of num == allocated power for digits, it is a possible equation
                if(a_pow + b_pow + c_pow == pow) {
                    total_eq++;
                    // If a != b, there are two combinations for this equation
                    // a + b = c; b + a = c
                    if(a != b) {
                        total_eq++;
                    }
                }
            }
        }    
    }
    // Prints total number of possible equations to console
    cout << total_eq;
}
    


int main() {
    // Gets total power from console
    int pow;
    cin >> pow;
    // Subtract 4 because +, = takes 2 units of power each
    pow -= 4;
    
    // Calls method to find all possible eq of pow
    all_possible_eq(pow);
}