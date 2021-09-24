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
    bool isValidBST(TreeNode* root) {
        /**
        思路：暴力深搜，对于每一个点，都判断是不是其左边所有的数都小于当前的结点值，其右边的所有数都大于当前的结点值
        **/
        if (!root){
            return true;
        }
        
        if (!solve(root -> left, root -> val, true) || !solve(root -> right, root -> val, false)){
            return false;
        }

        return isValidBST(root -> left) && isValidBST(root -> right);
    }

    bool solve(TreeNode* root, int number, bool flag){//同一个搜索函数，flag==1表示往左边搜，==0表示往右边搜
        if (!root){
            return true;
        }
        if (flag){
            if (root -> val >= number){
                return false;
            }
        }else{
            if (root -> val <= number){
                return false;
            }
        }

        return solve(root -> left, number, flag) && solve(root -> right, number, flag);
    }
};