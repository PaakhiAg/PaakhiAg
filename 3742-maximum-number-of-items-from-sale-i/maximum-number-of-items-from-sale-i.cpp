class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> bonus(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0)
                    bonus[i]++;
            }
        }

        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; i++) {
            int p = items[i][1];
            vector<int> ndp = dp;

            for (int r = 0; r < p && r <= budget; r++) {
                int best = INT_MIN;

                for (int c = r; c <= budget; c += p) {
                    int t = (c - r) / p;

                    if (t > 0)
                        best = max(best, dp[c - p] - (t - 1));

                    if (best != INT_MIN)
                        ndp[c] = max(ndp[c], bonus[i] + t + best);
                }
            }

            dp = ndp;
        }

        return *max_element(dp.begin(), dp.end());
    }
};