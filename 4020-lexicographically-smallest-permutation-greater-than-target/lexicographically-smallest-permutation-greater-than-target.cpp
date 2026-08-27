class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> freq(26, 0);

        for(char ch : s)
            freq[ch - 'a']++;

        string ans = "";

        int i = 0;

        while(i < n) {
            int x = target[i] - 'a';

            if(freq[x] > 0) {
                ans += target[i];
                freq[x]--;
                i++;
            }
            else {
                break;
            }
        }

        if(i == n) {
            i--;
            freq[ans.back() - 'a']++;
            ans.pop_back();
        }

        while(i >= 0) {

            int current = target[i] - 'a';

            for(int ch = current + 1; ch < 26; ch++) {

                if(freq[ch] > 0) {

                    ans += char('a' + ch);
                    freq[ch]--;

                    for(int c = 0; c < 26; c++) {
                        while(freq[c] > 0) {
                            ans += char('a' + c);
                            freq[c]--;
                        }
                    }

                    return ans;
                }
            }

            if(i == 0)
                break;

            i--;

            freq[ans.back() - 'a']++;
            ans.pop_back();
        }

        return "";
    }
};