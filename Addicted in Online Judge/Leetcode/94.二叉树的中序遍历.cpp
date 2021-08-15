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
    vector<int> f;

    void postorder(TreeNode* root){
        if (!root) return;
        postorder(root->left);
        f.push_back(root->val);
        postorder(root->right);        
    }

    vector<int> inorderTraversal(TreeNode* root) {
        postorder(root);
        return f;
    }
};