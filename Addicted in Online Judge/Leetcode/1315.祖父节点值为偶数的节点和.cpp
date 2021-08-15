/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int total = 0;

    int sumEvenGrandparent(TreeNode* root) {
        search(root, 1);
        return total;
    }
    
    void search(TreeNode* root, int ans){
        if (!root) return;
        if (!ans){
            if (root->right) total += root->right->val;
            if (root->left) total += root->left->val;
        }
        search(root->left, (root->val) % 2);
        search(root->right, (root->val) % 2);
    }
};