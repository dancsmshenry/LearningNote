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
    void deleteNode(ListNode* node) {
        //看了题解才知道是要删除这个节点的下一个节点，555，语文不过关的问题吗？？？？
        node->val = node->next->val;
        
        ListNode* node_delete = node->next;
        
        node->next = node->next->next;

        delete node_delete;
    }
};