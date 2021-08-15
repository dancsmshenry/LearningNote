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
    /**
    遇到的两个边缘情况
    第一个是如果当前只有一个节点的并且删除的就是这个节点
    第二个就是如果当前要删除的是头节点
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* p1 = head;
        ListNode* p2 = head;

        while (n > 1){
            p1 = p1->next;
            n -- ;
        }

        while(p1->next->next){
            p1 = p1->next;
            p2 = p2->next;
        }

        p2->next = p2->next->next;

        return head;
    }
    解决办法：在链表的前面再接一个指针，最后返回这个指针的next即可

    因为会出现说链表中需要被删除的点是其中唯一一个点，所以就让后面的慢指针指向头节点的前一个节点
    可以使得即使当前只有一个点且只删除一个点的时候，删除操作不会执行错误
    **/
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* newp1 = new ListNode(0, head);
        ListNode* p1 = head;
        ListNode* p2 = newp1;

        while (n > 1){
            p1 = p1->next;
            n -- ;
        }

        while(p1->next){
            p1 = p1->next;
            p2 = p2->next;
        }

        p2->next = p2->next->next;
        ListNode* res = newp1->next;

        return res;
    }
};