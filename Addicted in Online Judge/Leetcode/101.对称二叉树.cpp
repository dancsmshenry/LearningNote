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
    bool isSymmetric(TreeNode* root) {
        return solve(root->left, root->right);
    }

    bool solve(TreeNode* node1, TreeNode* node2){
        if (!node1 && !node2){//如果两个结点都是null，就直接返回true
            return true;
        }
        if ((!node1 && node2) || (!node2 && node1)){//如果有一个结点是空，另一个不是，那直接返回false
            return false;
        }
        return (node1 -> val == node2 -> val) && solve(node1 -> left, node2 -> right) && solve(node1 -> right, node2 -> left);
        //返回true的条件：两个值都相等，且左子树对称右子树，右子树对称左子树
    }
};