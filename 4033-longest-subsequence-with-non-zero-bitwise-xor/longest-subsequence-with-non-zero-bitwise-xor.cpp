class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int xr = 0;
        int nonZero = 0;

        for (int x : nums) {
            xr ^= x;

            if (x != 0)
                nonZero++;
        }

        if (xr != 0)
            return nums.size();

        if (nonZero > 0)
            return nums.size() - 1;

        return 0;
    }
};