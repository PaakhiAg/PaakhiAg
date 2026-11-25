#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int max_len = 0;

        for (int i = 0; i < n; ++i) {
            long long prod = 1;
            long long current_gcd = 0;
            long long current_lcm = 1;

            for (int j = i; j < n; ++j) {
                prod *= nums[j];
                current_gcd = gcd(current_gcd, (long long)nums[j]);
                current_lcm = lcm(current_lcm, (long long)nums[j]);

                if (prod == current_lcm * current_gcd) {
                    max_len = max(max_len, j - i + 1);
                }

                // Since nums[k] <= 10, max possible LCM is 2520 and max GCD is 10.
                // Once prod exceeds 25200, it can never match lcm * gcd again.
                if (prod > 25200) {
                    break;
                }
            }
        }

        return max_len;
    }
};