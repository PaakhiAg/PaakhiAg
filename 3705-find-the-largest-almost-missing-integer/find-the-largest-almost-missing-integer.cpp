class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        int count[51] = {0};

        for (int i = 0; i <= n - k; i++) {
            set<int> s;

            for (int j = i; j < i + k; j++) {
                s.insert(nums[j]);
            }

            for (int x : s) {
                count[x]++;
            }
        }

        for (int x = 50; x >= 0; x--) {
            if (count[x] == 1) {
                return x;
            }
        }

        return -1;
    }
};