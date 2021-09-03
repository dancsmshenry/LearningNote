/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q){//如果两个结点都是null，就直接返回true
            return true;
        }
        if ((!p && q) || (!q && p)){//如果有一个结点是空，另一个不是，那直接返回false
            return false;
        }
        return (p -> val == q -> val) && isSameTree(p -> right, q -> right) && isSameTree(p -> left, q -> left);
        //返回true的条件：两个值都相等，且左子树=左子树，右子树=右子树
    }
};