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
    ListNode* reverseList(ListNode* head) {
        ListNode* t = nullptr;

        while (head){
            ListNode* t1 = head->next;
            head->next = t;
            t = head;
            head = t1;
        }
        return t;
    }
};