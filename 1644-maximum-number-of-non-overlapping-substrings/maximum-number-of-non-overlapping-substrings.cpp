class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {

        vector<int> first(26, -1);
        vector<int> last(26, -1);

        // Find first and last occurrence of every character
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';

            if (first[c] == -1) {
                first[c] = i;
            }

            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        // Try every character as the starting character
        for (int c = 0; c < 26; c++) {

            if (first[c] == -1)
                continue;

            int l = first[c];
            int r = last[c];

            bool valid = true;

            for (int i = l; i <= r; i++) {

                int x = s[i] - 'a';

                // This character appeared before l,
                // so this substring cannot contain all its occurrences
                if (first[x] < l) {
                    valid = false;
                    break;
                }

                // Need to extend the substring
                r = max(r, last[x]);
            }

            if (valid) {
                intervals.push_back({l, r});
            }
        }

        // Sort by ending position
        sort(intervals.begin(), intervals.end(),
             [](pair<int,int> a, pair<int,int> b) {
                 return a.second < b.second;
             });

        vector<string> ans;

        int end = -1;

        for (auto interval : intervals) {

            int l = interval.first;
            int r = interval.second;

            if (l > end) {
                ans.push_back(s.substr(l, r - l + 1));
                end = r;
            }
        }

        return ans;
    }
};