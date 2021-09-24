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
    bool isBalanced(TreeNode* root) {
        return solve(root, 1);
    }

    //判断一个节点符不符合条件
    bool solve(TreeNode* root, int floor){
        //如果当前节点是空子树，就符合条件
        if (!root){
            return true;
        }

        //否则，先判断当前的节点是否符合条件
        int left = floor, right = floor;//floor为当前节点的高度
        if (root -> left){
            left = search_high(root -> left, floor + 1);//为左子树的高度
        }

        if (root -> right){
            right = search_high(root -> right, floor + 1);//为右子树的高度
        }

        if (abs(left - right) >= 2){
            return false;
        }

        return solve(root -> left, floor + 1) && solve(root -> right, floor + 1);
    }

    //搜索当前节点的高度
    int search_high(TreeNode* root, int floor){
        int result = floor;
        if (root -> left){
            result = max(search_high(root->left, floor + 1), result);
        }
        if (root -> right){
            result = max(search_high(root->right, floor + 1), result);
        }
        return result;
    }
};

////////////////////////////////////////////////////////////////
//优化后的版本1

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
    bool isBalanced(TreeNode* root) {
        //如果当前节点是空子树，就符合条件
        if (!root){
            return true;
        }

        //否则，先判断当前的节点是否符合条件
        int left = search_high(root -> left), right = search_high(root -> right);//left表示左子树的高度，right表示右子树的高度

        if (abs(left - right) >= 2){
            return false;
        }

        //再判断下面两个节点是否符合条件
        return isBalanced(root -> left) && isBalanced(root -> right);
    }

    int search_high(TreeNode* root){
        if (!root){
            return 0;
        }else{
            return max(search_high(root -> left), search_high(root -> right)) + 1;
        }
    }
};

////////////////////////////////////////////////////////////////
//优化后的版本二

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
    int height(TreeNode* root) {
        if (root == NULL) {//如果当前的节点是空的，那么他相对他的父节点的高度就是0
            return 0;
        }
        int leftHeight = height(root->left);//计量左子树的高度
        int rightHeight = height(root->right);//计量右子树的高度
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
            //这里有个前提，如果当前的节点对应的不是平衡二叉树，那么就把他的高度设为-1
            //如果左子树或右子树不是平衡二叉树，或者左子树和右子树的高度差大于1，那么该节点就不符合平衡二叉树的定义，就设为-1
            return -1;
        } else {
            //如果当前的节点的树是平衡二叉树，就返回他的高度（当前节点到最远的叶子的层数）
            return max(leftHeight, rightHeight) + 1;
        }
    }

    bool isBalanced(TreeNode* root) {
        /**
            这种思路厉害的地方在于：在自顶向下中，每一次都只是求出该子树的深度，然后只对当前的节点进行比较
            而自下向顶的思路中，是每次求深度的同时，就对途径的树的结点进行了操作统计，降低了时间复杂度
        **/
        return height(root) >= 0;
    }
};