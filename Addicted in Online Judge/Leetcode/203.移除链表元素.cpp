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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* node = new ListNode(0);
        node -> next = head;//在head结点前面加一个空结点
        ListNode* node1 = node;
        /**
        解释以下为什么要先让一个空结点node指向head，再让node1变为node的原因：
        因为如果我们直接用node去操作的话，是可以操作的
        但，如果遇到了第一个元素就是要移除的那个元素的话
        就会发生：我们只是在操作的过程中把这个结点给跳过了，但是实际的链表中却没有跳过（删除）这个结点

        即我原来是直接返回head结点，在其他的测试样例中都过了，但是唯独那个第一个就是目标元素的那个没有过
        后来我发现就是因为我是直接返回head结点的,如果我的第一个结点就是目标结点
        那么我的node1就会直接跳过head结点，然后对后面处理
        而我最后又是返回head结点的，所以第一个目标元素始终是删不掉的..

        附上源代码：
        ListNode* node1 = new ListNode(0);
        node1 -> next = head;

        while (node1 -> next){
            ListNode* node2 = node1 -> next;
            if (node2 -> val == val){
                node1 -> next = node2 -> next;
            }else{
                node1 = node1 -> next;
                continue;
            }
        }

        return head;
        **/

        while (node1 -> next){
            ListNode* node2 = node1 -> next;
            if (node2 -> val == val){
                node1 -> next = node2 -> next;//如果相等，就把该节点给跳过，但是node1的位置不变
            }else{
                node1 = node1 -> next;//不相等，则跳过该节点
                continue;
            }
        }

        return node -> next;
    }
};