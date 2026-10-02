class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        backtrack(result, current, 0, 0, n);
        return result;
    }

private:
    void backtrack(vector<string>& result, string& current, int open, int close, int maxPairs) {
        if (current.size() == maxPairs * 2) {
            result.push_back(current);
            return;
        }
        
        if (open < maxPairs) {
            current.push_back('(');
            backtrack(result, current, open + 1, close, maxPairs);
            current.pop_back();
        }
        
        if (close < open) {
            current.push_back(')');
            backtrack(result, current, open, close + 1, maxPairs);
            current.pop_back();
        }
    }
};
