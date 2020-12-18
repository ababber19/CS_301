#include <iostream>
#include <algorithm>
#include <string>
using namespace std;



int main() {
    double n;
    cin >> n;

    double nums[] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9};
    while(next_permutation(nums, nums + 10)) {
        double num = nums[0] * 10000 + nums[1] * 1000 + nums[2] * 100 + nums[3] * 10 + nums[4];

        double denom = nums[5] * 10000 + nums[6] * 1000 + nums[7] * 100 + nums[8] * 10 + nums[9];

        if(num / n == denom) {
            string denom_str = to_string((int) denom);
            if(denom_str.size() == 4) {
                denom_str = "0" + denom_str;
            }
            cout << num << " / " << denom_str << " = " << n << endl;
        }
    }
}