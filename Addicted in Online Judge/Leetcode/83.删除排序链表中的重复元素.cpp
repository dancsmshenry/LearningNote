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
        ListNode* node1 = head;

        while (node1 != nullptr && node1 -> next != nullptr){
            ListNode* node2 = node1 -> next;
            if (node1 -> val == node2 -> val){
                node1 -> next = node2 -> next;//如果当前的点和下面一个点的值相同，则跳过下一个点，但是node1的位置不变
            }else{
                node1 = node1 -> next;//值不相同，node1的位置才需要变
                continue;
            }
        }//而这种方法就很好的解决了这个问题：后面还要判断以下最后两个元素是否相同

        return head;
    }
};