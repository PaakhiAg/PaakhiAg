class Solution {
public:
    struct Node {
        int pre, suf, best, len;
        char leftChar, rightChar;
    };

    vector<Node> tree;
    string s;

    Node mergeNode(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;

        res.len = a.len + b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        res.pre = a.pre;
        res.suf = b.suf;

        res.best = max(a.best, b.best);

        if (a.rightChar == b.leftChar) {

            // substring crossing the middle
            res.best = max(res.best, a.suf + b.pre);

            // entire left part is same character
            if (a.pre == a.len)
                res.pre = a.len + b.pre;

            // entire right part is same character
            if (b.suf == b.len)
                res.suf = b.len + a.suf;
        }

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = {1, 1, 1, 1, s[l], s[l]};
            return;
        }

        int mid = (l + r) / 2;

        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);

        tree[node] = mergeNode(tree[2 * node],
                               tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, char ch) {

        if (l == r) {
            s[idx] = ch;
            tree[node] = {1, 1, 1, 1, ch, ch};
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(2 * node, l, mid, idx, ch);
        else
            update(2 * node + 1, mid + 1, r, idx, ch);

        tree[node] = mergeNode(tree[2 * node],
                               tree[2 * node + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {

        this->s = s;

        int n = s.size();

        tree.resize(4 * n);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {

            update(
                1,
                0,
                n - 1,
                queryIndices[i],
                queryCharacters[i]
            );

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};