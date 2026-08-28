class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        if (n % 2 == 0 && odd != 0)
            return "";

        int m = n / 2;
        vector<int> cnt(26);

        for (int i = 0; i < 26; i++)
            cnt[i] = freq[i] / 2;

        string left = "";
        int pos = 0;

        while (pos < m) {
            int x = target[pos] - 'a';

            if (cnt[x] == 0)
                break;

            left += target[pos];
            cnt[x]--;
            pos++;
        }

        if (pos == m) {
            string palindrome = left;

            if (n % 2)
                palindrome += mid;

            string rev = left;
            reverse(rev.begin(), rev.end());

            palindrome += rev;

            if (palindrome > target)
                return palindrome;
        }

        for (int i = min(pos, m - 1); i >= 0; i--) {
            if (i < (int)left.size()) {
                cnt[left[i] - 'a']++;
                left.pop_back();
            }

            int current = target[i] - 'a';

            for (int c = current + 1; c < 26; c++) {
                if (cnt[c] == 0)
                    continue;

                string half = left;
                vector<int> temp = cnt;

                half += char('a' + c);
                temp[c]--;

                for (int x = 0; x < 26; x++) {
                    while (temp[x] > 0) {
                        half += char('a' + x);
                        temp[x]--;
                    }
                }

                string ans = half;

                if (n % 2)
                    ans += mid;

                string rev = half;
                reverse(rev.begin(), rev.end());

                ans += rev;

                return ans;
            }
        }

        return "";
    }
};