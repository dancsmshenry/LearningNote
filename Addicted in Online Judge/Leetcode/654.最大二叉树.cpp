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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return solve(0, nums.size(), nums);
    }

    TreeNode* solve(int begin, int end, vector<int>& nums){
        if (begin >= end) return nullptr;

        int ans = 0;

        for (int i = begin, maxn = 0; i < end; i ++ ){
            if (nums[i] >= maxn){
                maxn = nums[i];
                ans = i;
            }
        }

        TreeNode* root = new TreeNode(nums[ans]);
        root->left = solve(begin, ans ,nums);//这里报错是我没想到的
        root->right = solve(ans + 1, end ,nums);

        return root;
    }
};