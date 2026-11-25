#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        
        const uint64_t MOD1 = 1000000007ULL;
        const uint64_t MOD2 = 1000000009ULL;
        const uint64_t BASE1 = 1315423911ULL % MOD1;
        const uint64_t BASE2 = 2654435761ULL % MOD2;

        vector<uint64_t> pow1(n + 1, 1), pow2(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            pow1[i] = (pow1[i - 1] * BASE1) % MOD1;
            pow2[i] = (pow2[i - 1] * BASE2) % MOD2;
        }

        auto hasUniqueOfLength = [&](int L) -> bool {
            uint64_t h1 = 0, h2 = 0;
            for (int i = 0; i < L; ++i) {
                h1 = (h1 * BASE1 + nums[i]) % MOD1;
                h2 = (h2 * BASE2 + nums[i]) % MOD2;
            }

            unordered_map<uint64_t, int> freq;
            freq.reserve(n - L + 1);
            
            uint64_t combined = (h1 << 32) | h2;
            freq[combined]++;

            for (int i = L; i < n; ++i) {
                uint64_t rem1 = (nums[i - L] * pow1[L - 1]) % MOD1;
                uint64_t rem2 = (nums[i - L] * pow2[L - 1]) % MOD2;
                
                h1 = (h1 + MOD1 - rem1) % MOD1;
                h2 = (h2 + MOD2 - rem2) % MOD2;

                h1 = (h1 * BASE1 + nums[i]) % MOD1;
                h2 = (h2 * BASE2 + nums[i]) % MOD2;

                combined = (h1 << 32) | h2;
                freq[combined]++;
            }

            for (const auto& [hashVal, count] : freq) {
                if (count == 1) return true;
            }
            return false;
        };

        int low = 1, high = n, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hasUniqueOfLength(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};