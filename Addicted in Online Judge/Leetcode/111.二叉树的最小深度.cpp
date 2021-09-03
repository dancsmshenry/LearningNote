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
    int minDepth(TreeNode* root) {
        return solve(root, 1);
    }

    int solve(TreeNode* node, int deepth){
        if (!node){//当前的结点时空结点
            return deepth - 1;
        }

        if (!node -> left && !node -> right){//当前的结点时叶子结点
            return deepth;
        }

        if (node -> left && node -> right){//当前的结点不是叶子结点，但是其左边和右边都可以走
            return min(solve(node -> left, deepth + 1), solve(node -> right, deepth + 1));
        }

        if (!node -> left && node -> right){//只能走右边
            return solve(node -> right, deepth + 1);
        }

        if (node -> left && !node -> right){//只能走左边
            return solve(node -> left, deepth + 1);
        }

        return deepth;
    }
};