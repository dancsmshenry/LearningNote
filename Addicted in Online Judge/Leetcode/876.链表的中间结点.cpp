/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int count = 0, k = 0;
        ListNode* node = head;

        while (node){//先统计链表的长度
            count ++ ;
            node = node -> next;
        }

        node = head;

        while (k < count / 2){//然后开始遍历链表，无论是奇数还是偶数，都遍历到下标为count/2的位置
            k ++ ;
            node = node -> next;
        }

        return node;
    }
};