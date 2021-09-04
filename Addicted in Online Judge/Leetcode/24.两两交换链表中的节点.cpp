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
    ListNode* swapPairs(ListNode* head) {
        /**
        想法一：
        这里有1 2 3 4这四个点
        分别命名为point1 point2 point3 point4
        然后先让point1指向point3
        接着让point2指向point4
        最后让point3指向point2

        导致思绪混乱的原因：没能设定好 方便代码表示 的变量，以至于被变量绕的团团转

        整理思路：
        先设一个空结点，让这个空结点指向目标链表的头结点
        然后，因为我们是要对链表进行处理的，肯定就要用一个循环的结点对链表进行处理
        就设一个结点等于此前设立的空结点
        然后对空结点进行while循环操作

        后续的关键就是，要捋清思路，设好方便的变量
        **/
        ListNode* point = new ListNode(0);
        point -> next = head;
        ListNode* point1 = point;

        while(point1 -> next && point1 -> next -> next){
            ListNode* point2 = point1 -> next;
            ListNode* point3 = point1 -> next -> next;

            point1 -> next = point3;
            point2 -> next = point3 -> next;
            point3 -> next = point2;
            point1 = point2;
        }

        return point -> next;
    }
};