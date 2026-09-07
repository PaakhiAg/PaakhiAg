class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;

        vector<long long> last(26, 0);
        long long total = 0;

        for (char ch : s) {
            int x = ch - 'a';

            long long add = (total + 1) % MOD;
            long long newTotal = (total + add - last[x] + MOD) % MOD;

            last[x] = add;
            total = newTotal;
        }

        return total;
    }
};