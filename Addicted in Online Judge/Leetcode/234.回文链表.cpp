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
    bool isPalindrome(ListNode* head) {
        /**
        先获取链表的长度
        然后把链表的前半段进行翻转
        然后用快慢指针，快指针先走到中间，慢指针从头开始走
        一一比较各个元素
        **/
        //先获取链表长度
        int length = 0;
        ListNode* point1 = new ListNode();
        point1 -> next = head;
        while(point1->next){
            length ++ ;
            point1 = point1 -> next;
        }

        //把链表前半段翻转
        ListNode* node1 = nullptr;
        ListNode* node2 = head;
        int half = length >> 1;
        while (half){
            ListNode* node3 = node2 -> next;
            node2 -> next = node1;
            node1 = node2;
            node2 = node3;
            half -- ;
        }
        
        //记录下半段开始的点
        if (length % 2 == 1){
            node2 = node2 -> next;
        }

        //接着，对两个指针指针进行比较
        while (node1 && node2){
            if (node1->val == node2 -> val){
                node1 = node1 -> next;
                node2 = node2 -> next;
            }else{
                return false;
            }
        }

        return true;
    }
};