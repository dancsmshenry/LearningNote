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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        /**
            首先的想法：
            先走到left点，记录下left点前面一个点的next和left点的next
            然后在走到right点之前每走一步都把链表的next指向它的前一个点
            然后找到了right以后，记录right点的地址和right之后一个点的地址
            最后让left的next指向right之后一个点的地址，让left前一个点的next指向right的地址
        **/
        
        //先创建一个结点，指向该链表
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;

        //此时的right记录要翻转的链表的范围
        right -= left;

        //再找到left前面的那一个结点，即hh为left前面的那一个结点
        ListNode* hh = dummyHead;
        while (left-- > 1) hh = hh->next;

        //即prv是left结点，cur是left的下一个结点
        ListNode* prv = hh->next;
        ListNode* cur = prv->next;

        //这一步的作用：把要反转的部分全部都翻转一遍；然后prv为right结点，cur为right的下一个结点
        while (right-- > 0) {
            ListNode* nxt = cur->next;
            cur->next = prv;
            prv = cur;
            cur = nxt;
        }

        //最后一步：先把left的next指向right的下一个结点（hh->next->next为left的next，cur为right的下一个结点），接着就把left前一个结点的next接上right结点
        hh->next->next = cur;
        hh->next = prv;
        return dummyHead->next;
    }
};