#include <numeric>

class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        /*
        这道题和传统的硬币问题类似，都可以这样想
        如果n元是最优解，那最后一样东西买的是什么呢？肯定是礼包或者单件物品，
        那么遍历递归下去，就可以找到最优解了
        但，问题是现在有n件物品，那我的状态方程的数组就不知道应该怎么设了..

        所以这道题我觉得就只能用动态规划的思想来思考：
        即我每一个方向都试一下，如果可以拿，就继续往下拿，不过是在最后judge一下res的大小罢了
        那这么说，就是最基本的dfs
        但是我最开始写了一个dfs，两个函数来回递归，虽然最后能够得到结果，但是最终总是超时了（即两个函数，一个单拿物品，一个买礼包）
        深究递归，不断的调用函数本身其实是非常耗时的一件事情，所以即使是dfs或是bfs都必须要注意减少函数的递归次数
        后面修改了一下，在一个函数里面一个拿物品，另一个拿礼包，但最终还是超时了

        后来看了解析，发现如果用动态规划或模拟一下，就会发现，其实对于拿物品这个环节，是不需要可以去模拟的
        因为为我们知道，如果拿完了礼包，最后只能去单拿物品；或着说，每次拿礼包之前，我们都可以假设当前的所有余额都去单拿物品
        那其实，我们只要把res的初值设为是当前的所有余额都去单拿物品，单独去模拟那礼包的情况，然后相互judge即可

        思考：还是要好好学习stl中vector的用法
        */
        int res = inner_product(price.begin(), price.end(), needs.begin(), 0);//内积

        for (int i = 0, n = needs.size(); i < special.size(); i ++ ){
            bool flag = true;
            for (int j = 0; j < n; j ++ ){
                if (needs[j] < special[i][j]){
                    flag = false;
                }//判断当前是否可以拿这个礼包
            }
            if (flag){
                for (int l = 0; l < n; l ++ ){
                    needs[l] -= special[i][l];
                }
                res = min(shoppingOffers(price, special, needs) + special[i][n], res);
                for (int l = 0; l < n; l ++ ){
                    needs[l] += special[i][l];
                }
            }
        }

        return res;
    }
};