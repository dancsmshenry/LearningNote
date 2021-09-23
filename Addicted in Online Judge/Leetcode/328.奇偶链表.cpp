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
    ListNode* oddEvenList(ListNode* head) {
        ListNode* node1 = new ListNode();
        node1 -> next = head;
        int length = 0;
        while (node1 -> next){//两个目的：首先是求出总共有多少个要处理的点；找到最后一个点的位置
            length ++;
            node1 = node1 -> next;
        }

        ListNode* node2 = head;
        int count = 1;
        while(length > count && node2 -> next){//总共要处理的就是length个点；确保node2不是最后一个点
            node1 -> next = node2 -> next;//node1是当前链表的最后一个点，确定了node2->next是偶数点，就把它接到最后一个
            node1 = node1 -> next;//既然加了一个点，那么最后一个点就是加的那一个点了

            node2 -> next = node2 -> next -> next;//下一个点被移到后面了，所以要把next指向next的next
            node2 = node2 -> next;//改变了next，那么就也要修改下一次需要处理的点，即把node2往后移

            node1 -> next = nullptr;//既然把当前的点放到了最后，所以最后一个点要指向空（这里不能提前操作，否则node2就不知道往哪指了）

            count += 2;//因为本次处理了两个点，所以要加二
        }

        return head;
    }
};

/**
 * 阴差阳错版：
 * /**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 *
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return head;
        ListNode* node1 = new ListNode();
        node1 -> next = head;
        int length = 0;
        while (node1 -> next){
            length ++;
            node1 = node1 -> next;
        }

        ListNode* node2 = new ListNode();
        node2 = head;
        int count = 1;
        while(length > count){
            if (count % 2 == 1 && node2 -> next -> next){
                ListNode* node = node2 -> next;
                node2 ->next = node2 -> next -> next;
                node1 -> next = node;
                node1 = node1 -> next;
                node1 -> next = nullptr;
            }else{
                node2 = node2 -> next;
            }
            count ++ ;
        }

        return head;
    }
};
 **/ 