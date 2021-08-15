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
    int deepth = 0, total = 0;

    int deepestLeavesSum(TreeNode* root) {
        solve(root, 1);
        return total;
    }

    void solve(TreeNode* root, int deep){
        if (!root) return;
        if (deep > deepth){
            deepth = deep;
            total = root->val;
        }
        else if (deep == deepth){
            total += root->val;
        }
        solve(root->left, deep + 1);
        solve(root->right, deep + 1);
    }
};