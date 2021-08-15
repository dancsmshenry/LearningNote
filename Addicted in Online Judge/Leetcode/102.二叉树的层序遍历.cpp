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
    vector<vector<int>> res;

    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return res;
        solve(0, root);
        return res;
    }

    void solve(int floor, TreeNode* root){
        if (!root) return ;
        if (floor >= res.size()){
            vector<int> ans;
            ans.push_back(root->val);
            res.push_back(ans);
        }else{
            res[floor].push_back(root->val);
        }
        solve(floor + 1, root->left);
        solve(floor + 1, root->right);
    }
};