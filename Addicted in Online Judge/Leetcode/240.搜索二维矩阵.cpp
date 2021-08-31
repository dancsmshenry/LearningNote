class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        /**
        一开始的想法：
        先对当前的第一行处理（从右边往左边缩小范围，因为当前的数字代表着这一列最小的数字，如果target比最小的数字还要小，那这一列就可以不用找了）
        再对当前的第一列处理（进行同样的处理）
        
        然后搜索的范围不是被缩小了嘛，接着用同样的方法操作
        最后应该能够找出答案

        但是这里的问题就是如果缩小到没办法缩小的地步，那是不是只能挨个挨个去查找了呢？
        那时间效率还是很低啊啊...

        后面看了一遍解析发现，只要从右上方开始寻找，（target）大了就往下面走，小了就往右边走
        不过还是老问题，要注意判空，还有边界的处理
        **/

        int matrix_size = matrix.size();
        //预先判空
        if (!matrix_size){
            return false;
        }
        
        int line = 0, row = matrix[0].size() - 1;//居然是这里没有-1，真是糊涂了

        while(line < matrix_size && row >= 0){//注意，这里的row是可以等于0的
            int number = matrix[line][row];
            if (number == target){
                return true;
            }
            if (number > target){
                row -- ;
            }else{
                line ++ ;
            }
        }

        return false;
    }
};