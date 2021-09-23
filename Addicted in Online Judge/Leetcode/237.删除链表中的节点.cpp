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
        /**
        又看错题了，以为是给一个链表，删除特定值的节点
        没想到是直接给那个需要被删除的节点...

        思路：既然这个点是要被删掉的，那么就可以用这个点把后面的链表给接起来
        首先，把被删除的节点的值变为该节点后一个节点的值
        然后，把被删除的节点的next变为后一个节点的next
        这样就实现了删除节点
        **/

        node -> val = node -> next -> val;
        node -> next = node -> next -> next;
    }
};