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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return head;

        //计算链表的长度，并对k进行矫正
        int length = 0;
        ListNode* p1 = head;
        while(p1){
            p1 = p1->next;
            length++;
        }
        k = k % length;
        if (k == 0) return head;

        //用双指针法找到新链的头尾
        ListNode* p2 = head;
        ListNode* p3 = new ListNode(0, head);

        while (k > 1){
            p2 = p2 -> next;
            k -- ;
        }

        while (p2 -> next){
            p2 = p2 -> next;//最后面一个点
            p3 = p3 -> next;//要移动的点的前一个点
            //p2先走了k-1步数（起点是0），而p3前面没走（但是起点是-1），所以二者相差k步
        }

        //切割链表
        p2->next = head;
        // ListNode* p = new ListNode(0, p3->next);
        ListNode* p = p3->next;
        p3->next = NULL;

        // return p->next;
        return p;
    }
}; 