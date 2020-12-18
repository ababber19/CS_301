#include <iostream>
#include <vector>
using namespace std;

// Swaps two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Creates pivot; swaps elements in arr compared to pivot
int partition(int a[], int b[], int c[], int low, int high) {
    // Randomly selects pivot, moves pivot to last position in arr
    int random = low + rand() % (high - low);
    swap(a[random], a[high]);
    swap(b[random], b[high]);
    swap(c[random], c[high]);
    int pivot = a[high];

    // Index of where pivot should be at the end
    // Initialized to 0
    int i = low;
    // For-loop swaps all elements lower than pivot to before the pivot
    for(int j = low; j < high; j++) {
        // If the value is less than the pivot, it moves that value to arr[i] (starts at beginning of arr)
        if(a[j] < pivot) {
            swap(a[i], a[j]);
            swap(b[i], b[j]);
            swap(c[i], c[j]);
            i++;
        }
    }
    // Swaps pivot to arr[i] (now all elements to the left of the pivot < pivot)
    swap(a[i], a[high]);
    swap(b[i], b[high]);
    swap(c[i], c[high]);
    
    // Returns index of pivot
    return (i);
}

// Recursive function
// Chooses random partition, and sorts the array from below and above that partition
void quick_sort(int a[], int b[], int c[], int low, int high) {
    if(low < high) {
        // Selects a partition
       int p = partition(a, b, c, low, high);
       // Sorts from below the partition
       quick_sort(a, b, c, low, p - 1);
       // Sorts from above the partition
       quick_sort(a, b, c, p + 1, high);
    }
}


// Calculates product using strings
// (Long multiplication by digits)
string big_number_multiplication(string num1, string num2) {
    // len1 = # of digits of num1, len2 = # of digits of num2
    int len1 = num1.size(), len2 = num2.size();
    // If either value is 0, return 0 (x * 0 = 0)
    if (len1 == 0 || len2 == 0)
    return "0";
  
    // Product of two number stored in vector of length (len1+len2)
    // Will store product in reverse order
    vector<int> result(len1 + len2, 0);

    // Indexes of num1, num2
    int i_n1 = 0, i_n2 = 0;
      
    // Nested for loop calculates product
    // First for loop, go from right to left in num1
    for(int i = len1-1; i >= 0; i--) {
        // Carry = value carried from multiplying two digits
        // n1 = current digit of first number
        int carry = 0, n1 = num1[i] - '0';
  
        // Resets index of num2
        i_n2 = 0;
        
        // Go from right to left in num2
        for (int j = len2-1; j >= 0; j--) { 
            // Take current digit of second number 
            int n2 = num2[j] - '0'; 
  
            // Multiplies two digits, adds carry that exists, adds previous result at that digit
            int sum = n1*n2 + result[i_n1 + i_n2] + carry; 
  
            // Calculates what the "carry" will be for next operation
            // e.g. (27 * 14 --> 7*4 = 28, carry = 2)
            carry = sum / 10; 
  
            // Stores result 
            result[i_n1 + i_n2] = sum % 10; 

            // Iterates num2
            i_n2++;
        } 

        // If last multiplication results in a carry, adds the carry to the position
        // e.g. (47 * 96 --> 6 * 4 = 24 --> remaining carry of 2 after finishing 
        // multiplication of first digit in num2)
        if (carry > 0) result[i_n1 + i_n2] += carry; 
 
        // Shifts index of num1
        i_n1++; 
    } 
  
    // Ignore '0's from the right
    // Remember that result is backwards (4620 --> 0264 --> 264)
    int i = result.size() - 1; 
    while(i >= 0 && result[i] == 0) i--;
    
    if(i == -1) return "0";
    // Result string formatted (unreverses result)
    string s = "";
    while (i >= 0) s += std::to_string(result[i--]); 
    // Returns result string
    return s; 
}


// Calculates division using strings
// (Long division)
string big_number_division(string numerator, int denom) { 
    // Result
    string ans; 
    
    // Index of numerator
    int i = 0; 
    // Sets temp to first digit in numerator
    int temp = numerator[i] - '0'; 
    
    // If temp < denom
    while (temp < denom) {
        // Adds next digit of numerator to temp
        temp = (temp * 10) + (numerator[++i] - '0'); 
    }


    // Repeatedly divides denom with temp. After every division, update temp to include one more digit.
    while (numerator.size() > i) { 
        // Store result in answer i.e. temp / denom 
        ans += (temp / denom) + '0'; 
  
        // Takes next digit of numerator 
        temp = (temp % denom) * 10 + numerator[++i] - '0'; 
    } 
  
    // If denom is greater than numerator, answer = 0 (num/denom = 0)
    if (ans.length() == 0) return "0";
  
    // else return ans
    return ans; 
} 


// Main method
int main() {
    // # of pairs
    int n;
    cin >> n;

    if(n == 0) {
        cout << 0;
        return 0;
    }
    
    // a = first digit in pair, b = second digit in pair, products = a*b
    int a[n+1], b[n+1], products[n+1];
    
    // Gets all pairs from console
    for(int i = 0; i < n + 1; i++) {
        cin >> a[i] >> b[i];
        // Calculates product
        products[i] = a[i] * b[i];
    }


    // Sorts pairs & products by products ascending (fixed first pair)
    quick_sort(products, a, b, 1, n);
    

    // Calculates numerator
    string total_num = to_string(a[0]);
    // Multiplies all vals a needed to produce numerator of last digit
    for(int i = 1; i < n; i++) {
        total_num = big_number_multiplication(total_num, to_string(a[i]));
    }

    // Prints result
    cout << big_number_division(total_num, b[n]);    
}