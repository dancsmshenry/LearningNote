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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        /**
        一开始对题目的理解有误，导致后面被困了好久都没看出来哪里有问题
        实际上，这道题就是两个链表在某一处有相交，然后问你怎么把他找出来
        但是看了解析后豁然开朗了

        即如果两个链表都没有相交的话：
        长度一样，那么走到最后都是null，就直接返回null
        长度不一样，那对于走A链表的来说，走完了A，就走B链表
        对于走B链表的来说，走完了B，就走A链表
        那么就可以保证它们走的路程一样了，
        那既然路程一样，最后指向的也一定是一样的了

        而如果两个链表有相交的话：
        相交点之前路程一样，那就可以同时走到相交点，就相同了
        不一样，那思路不变（两者相遇一定是要走相同步数的路的）
        A走完了就走B，B走完了就走A，最后就会相遇了

        这道题要抓住的就是如果有相遇，那么走的路程一定是相同的
        而怎么塑造相同，就是关键了
        **/

        if (!headA || !headB){
            return nullptr;
        }

        ListNode* node1 = headA;
        ListNode* node2 = headB;
        while (node1 != node2){
            if (node1 == nullptr){
                node1 = headB;
            }else{
                node1 = node1 -> next;
            }

            if (node2 == nullptr){
                node2 = headA;
            }else{
                node2 = node2 -> next;
            }
        }

        return node1;
    }
};