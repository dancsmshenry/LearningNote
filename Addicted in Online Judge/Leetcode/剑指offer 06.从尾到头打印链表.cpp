/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> f1, f2;
        if (!head) return f2;
        int n = 0;

        while (head){
            f1.push_back(head->val);
            head = head->next;
            n ++ ;
        }

        for (int i = n - 1; i >= 0; i --){
            f2.push_back(f1[i]);
        }

        return f2;
    }
};