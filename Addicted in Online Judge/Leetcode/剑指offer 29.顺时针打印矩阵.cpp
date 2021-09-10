class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        /**
        这道题目和螺旋矩阵II是有很大的不同的，但是也有相同的地方

        首先，螺旋矩阵II其实是保证了提供给你的是一个正方形，那么就会少很多的边界情况（比如没有行，只有一行或只有一列的边界情况）
        其次，在螺旋矩阵II中，我的做法其实是分为两步，第一步走外面的框框，所以对于每一次走的行列来说，最后都留下一个没走，当作下一次的首一个
        第二步则是判断当前是否有最后一个还没有走（即n等于奇数的时候），如果有，就把他走完

        而这道题的情况是与众不同的，因为这个是一个矩阵（最后留在中间的可能是一行，而且会遇到只有一行或一列的情况），不能像之前那样思考了

        所以需要改变思路来做这道题：
        必须一次某一行某一列走尽，而这个时候的关键就是如何适配循环的边界
        如果走完了一行或是一列，就需要及时更新边界
        **/
        vector<int> res;
        if (!matrix.size() || !matrix[0].size()){
            return res;
        }
        int n = matrix.size(), m = matrix[0].size();
        int row_min = 0, line_min = 0, row_max = m - 1, line_max = n - 1;//因为每次都是从这里开始走的（指从min起步），而且都是要走到底的（指要遍历到max），所以要这样初始化
        int count = n * m;

        while (count >= 1){//这里就是while循环的一个不好的地方，如果在程序执行到一半时不符合式子里的条件，那程序是会继续运行下去，而不是停下来
            for (int i = row_min; i <= row_max && count >= 1; i ++ , count -- ){
                res.push_back(matrix[line_min][i]);
            }//向右走，走完后把行最小上调
            line_min ++ ;

            for (int i = line_min; i <= line_max && count >= 1; i ++, count -- ){
                res.push_back(matrix[i][row_max]);
            }//向下走，走完后把列最大下调
            row_max -- ;

            for (int i = row_max; i >= row_min && count >= 1; i --, count -- ){
                res.push_back(matrix[line_max][i]);
            }//向左走，走完后把行最大下调
            line_max -- ;

            for (int i = line_max; i >= line_min && count >= 1; i --, count -- ){
                res.push_back(matrix[i][row_min]);
            }//向上走，走完后把列最小上调
            row_min ++ ;
        }

        return res;
    }
};