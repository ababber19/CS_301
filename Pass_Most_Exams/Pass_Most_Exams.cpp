#include <iostream>

using namespace std;

// Swaps two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Creates pivot; swaps elements in arr compared to pivot
int partition(int a[], int b[], int low, int high) {
    // Randomly selects pivot, moves pivot to last position in arr
    int random = low + rand() % (high - low);
    swap(a[random], a[high]);
    swap(b[random], b[high]);
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
            i++;
        }
    }
    // Swaps pivot to arr[i] (now all elements to the left of the pivot < pivot)
    swap(a[i], a[high]);
    swap(b[i], b[high]);
    
    // Returns index of pivot
    return (i);
}

// Recursive function
// Chooses random partition, and sorts the array from below and above that partition
void quick_sort(int a[], int b[], int low, int high) {
    if(low < high) {
        // Selects a partition
       int p = partition(a, b, low, high);
       // Sorts from below the partition
       quick_sort(a, b, low, p - 1);
       // Sorts from above the partition
       quick_sort(a, b, p + 1, high);
    }
}


int main() {
    // n = number of exams, free_days = days without exams, counter = counter of tests_taken_prep
    // total_ex = # of exams taken, max_index = index of largest prep day
    int n, free_days, counter = 0, total_ex = 0, max_index = 0, max_index2 = 1, ind_count = 0;
    cin >> n;

    // Initialize arrays (a = exams; b = prep days for exams, c = # of rest days)
    // (tests_taken_prep = prep days of exams taken)
    int a[n], b[n], c[n], tests_taken_prep[n];

    // Takes inputs for array a (days of exams)
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        tests_taken_prep[i] = -1;
    }

    // Takes inputs for array b (prep time for each exam)
    for(int j = 0; j < n; j++) {
        cin >> b[j];
    }
    
    // Sorts arrays a, b in ascending order by a
    quick_sort(a, b, 0, n - 1);
    
    // Sets # of free days to # of free days between day 1 and day of first exam
    free_days = a[0] - 1;

    
    // Goes through every exam
    for(int i = 0; i < n; i++) {
        // If we are past exam #1, updates free_days to previous free days + free days between exam #i and exam #i-1
        if(i > 0) {
            free_days += a[i] - a[i-1] - 1;
        }
        // Sets array[i] to # of free days currently
        c[i] = free_days;

        // If total rest days > the days needed to prepare for the exam, take the exam
        // In other words, if the exam can be taken, take it
        if(c[i] >= b[i]) {
            // Adds prep time of exam taken to vector
            tests_taken_prep[counter] = b[i];

            counter++;
            // Subtracts from free_days # of prep days
            free_days -= b[i];
            total_ex++;
        }
        

        // If you can't take the current exam given the number of free days you have
        else {
            max_index = 0;
            for(int j = 0; j < counter; j++) {
                if(tests_taken_prep[j] > tests_taken_prep[max_index]) {
                    max_index = j;
                }
            }

            // If largest prep time > # current rest days, swap exams taken
            if(tests_taken_prep[max_index] > b[i]) {
                // Adds prep days of original exam, subtract prep days of new exam
                free_days += tests_taken_prep[max_index] - b[i];
                
                // Remove old exam, add new exam taken
                tests_taken_prep[max_index] = b[i];
            }

            // Otherwise, skip exam day, and add 1 to free_days
            else {
                free_days++;
            }   
        }
    }
    
    // Print to console # of exams taken
    cout << total_ex;
}