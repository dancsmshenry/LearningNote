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
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return maxn(root, 0);
    }

    int maxn(TreeNode* root, int deep){
        if (!root) return deep;

        int x1 = maxn(root->left, deep + 1);
        int x2 = maxn(root->right, deep + 1);

        return max(x1, x2);
    }
};