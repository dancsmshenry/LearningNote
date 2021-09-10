class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        /**
        第一眼看到子集，就觉得可以用位运算来解决
        但是又不知道怎么做

        后续感觉又是用回溯来写，可又卡壳了

        不过，看了一个评论区里面的一个题解，整个人就通畅了

        首先，这道题求子集的过程我已经放到剑指offer 所有子集那里了
        这里重点讨论的是，如何去重：
        如果当前的元素和前面的元素发生重复了怎么办？
        回想之前幂集的做法，当不考虑重复元素的时候，我们是把新的这个元素插入到原来的数列中，获取一个新的数列
        再把这两个数列合并的，是吧
        但，如果出现了相同的，假如加入了a元素后，新的数列是由a1数列和a2数列组成的
        而我后面的元素又是a元素，这是就会造成a1,a2,a2,a2a2数列的重复（即a2和a2是发生了重复的）
        所以为了避免这种重复，当发现了重复元素的时候，我们就选择性的对a2范围的数组进行操作，这样就有效的避免了重复了

        而具体如何操作的呢？
        请下面的代码后的注释
        **/

        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> ans;
        res.push_back(ans);

        //这里的去重实际上是维护了两个left和right指针，这两个指针的范围就是要操作的数列的范围
        for (int i = 0, len = 0, left = 0, right = 0; i < nums.size(); i ++ ){
            if (i != 0 && (nums[i] == nums[i - 1])){//如果前面有元素，并且前后两个都相等
                left = res.size() - len;//那就把左边的范围缩小到a2数组的位置（参考上式）
            }else{
                left = 0;//如果不是，则依旧从0开始计算
            }
            right = res.size();//right是指原数列的尾部嘛
            len = right - left;//维护a1数组的长度，以防后面用得上
            for (int j = left; j < right; j ++ ){
                ans = res[j];
                ans.push_back(nums[i]);
                res.push_back(ans);
            }
        }

        return res;
    }
};