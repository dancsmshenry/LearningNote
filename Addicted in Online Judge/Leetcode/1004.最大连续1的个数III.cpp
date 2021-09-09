class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        /**
        这道题可以用双指针来分析
        维护一个left和right指针，结果res，还有一个配额k1

        对下列算法进行循环：条件是right < n(每一次对res++的时候，都要维护一个maxn最大值，最后返回的是这个最大值)
        right负责向右边移动，如果右边为1，则res ++ ，并且继续向右移
        如果为0，则先看配额k1是否大于0，如果是，则k1 --,res ++
        但是如果配额为0了，则left --,res --（）
        **/
        int left = 0, right = 0;
        int k1 = K, res = 0;
        int n = A.size(), maxn = INT_MIN;

        while (right < n){
            if (A[right] == 1){//如果直接是1，那就res++
                res ++ ;
                maxn = max(maxn, res);
                right ++ ;
            }else{
                if (k1 > 0){//是0的话，就要先看配额是否足够，足够的话就用配额；否则就就修改左边界
                    k1 -- ;
                    res ++ ;
                    maxn = max(maxn, res);
                    right ++ ;
                }else{
                    if (A[left] == 0){
                        k1 ++ ;
                    }
                    res -- ;
                    left ++ ;
                }
            }
        }

        return maxn;
    }
};