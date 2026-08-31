class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;
        int first = -1;
        int last = -1;
        int minDistance = INT_MAX;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {

                if (first == -1) {
                    first = index;
                } else {
                    minDistance = min(minDistance, index - last);
                }

                last = index;
            }

            prev = curr;
            curr = next;
            index++;
        }

        if (first == last)
            return {-1, -1};

        return {minDistance, last - first};
    }
};