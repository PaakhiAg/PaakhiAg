class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[j] = earliest index in word1 from which
        // word2[j...] can be matched exactly.
        vector<int> suf(m, n);

        int p = n - 1;

        for (int j = m - 1; j >= 0; j--) {
            while (p >= 0 && word1[p] != word2[j]) {
                p--;
            }

            if (p < 0) break;

            suf[j] = p;
            p--;
        }

        vector<int> ans;

        int i = 0;
        bool changed = false;

        for (int j = 0; j < m; j++) {

            // Try to find the smallest exact match.
            while (i < n && word1[i] != word2[j]) {
                
                // We can use our one modification here if
                // the remaining suffix can be matched.
                if (!changed) {
                    if (j == m - 1 || 
                        (suf[j + 1] < n && suf[j + 1] > i)) {
                        
                        ans.push_back(i);
                        changed = true;
                        i++;
                        break;
                    }
                }

                i++;
            }

            if (ans.size() == j + 1)
                continue;

            if (i >= n)
                return {};

            ans.push_back(i);
            i++;
        }

        return ans;
    }
};