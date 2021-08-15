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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* node_01 = new ListNode(0);
        ListNode* node_02 = node_01;

        while(l1 && l2){//这里的循环条件是l1或l2谁的结尾不是null的
            if (l1->val > l2 -> val){
                node_02 -> next = l2;
                node_02 = node_02 -> next;
                l2 = l2 -> next;
            }else{
                node_02 -> next = l1;
                node_02 = node_02 -> next;
                l1 = l1 -> next;
            }
        }//比较l1和l2的值谁比较小，小的就放到新的链表中
        
        if(!l1){
            node_02 -> next = l2;
        }//如果l1走完了，但是l2还没走完，就把l2后面的部分接上去
        if(!l2){
            node_02 -> next = l1;
        }//如果l2走完了，但是l1还没走完，就把l1后面的部分接上去

        /**
        看到的一种双指针的做法
        先是创造一个结点（dummy），然后让一个指针指向这个结点（cur）
        **/
        return node_01 -> next;
    }
};