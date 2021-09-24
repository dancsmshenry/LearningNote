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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        int n = search_deep(root);
        vector<vector<int>> res(n);

        //从第一个点开始操作
        solve(res, root, 1);

        //最后记得把其倒置过来
        reverse(res.begin(), res.end());
        return res;
    }
    //先求出二叉树的深度并记录下来
    int search_deep(TreeNode* root){
        if (!root){
            return 0;
        }

        return max(search_deep(root -> right), search_deep(root -> left)) + 1;
    }

    //暴力，每一次都把当前的元素放入对应的vector中
    void solve(vector<vector<int>>& res, TreeNode* root, int floor){
        if (!root){
            return ;
        }
        res[floor - 1].push_back(root -> val);
        solve(res, root -> left, floor + 1);
        solve(res, root -> right, floor + 1);
    }
};