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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* pre = head;
        int n = 1;
        
        for (; pre -> next; n ++){
            pre = pre -> next;
        }

        pre = head;
        for (int i = 1; i <= n - k; i ++ ){
            pre = pre -> next;
        }

        return pre;
    }
};//方法一

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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* pre1 = head;
        ListNode* pre2 = head;
        
        for (int i = 0; i < k - 1; ++ i){//注意，这里的快指针和满指针之间差的是k-1的距离，不是k
            pre1 = pre1 -> next;
        }

        while(pre1 -> next){
            pre1 = pre1 -> next;
            pre2 = pre2 -> next;
        }

        return pre2;
    }
};//方法二