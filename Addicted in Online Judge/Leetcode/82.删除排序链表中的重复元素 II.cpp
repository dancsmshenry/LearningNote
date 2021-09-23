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
    ListNode* deleteDuplicates(ListNode* head) {
        /**
        这道题的思路：
        在head前面再加上一个点，然后从这个点开始
        对于下一个点和下下一个点的值做出判断，如果相等，就先将这个值设为target
        然后进入while循环，循环到一个点的值不等于target，把当前点和循环到的这个点连接起来

        注意：while循环的时候，一定要判空
        **/
        ListNode* node1 = new ListNode();
        ListNode* node3 = new ListNode();
        node1 -> next = head;
        node3 = node1;

        while (node1 -> next && node1 -> next -> next){
            if (node1 -> next -> val == node1 -> next -> next -> val){
                int target = node1 -> next -> val;
                ListNode* node2 = node1 -> next;
                while (node2 && node2 -> val == target){
                    node2 = node2 -> next;
                }
                node1 -> next = node2;
            }else{
                node1 = node1 -> next;
            }
        }

        return node3 -> next;
    }
};