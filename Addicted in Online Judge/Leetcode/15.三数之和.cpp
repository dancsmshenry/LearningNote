class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        /**
        最开始的想法：
        感觉这道题和两数之和一样
        先对数组进行排序，然后从小往后开始遍历
        如果遇到重复的就跳过
        如果遇到正数了，就直接退出
        然后对当前这个数之后的数字用两数之和的方法进行处理

        可问题是，还是无法处理重复的情况

        最后，看了解析，是说用排序和双指针来解决（还是说遇到去除重复的就用双指针）
        **/

        vector<vector<int>> res;
        int n = nums.size();
        if (n < 3) return res;

        sort(nums.begin(), nums.end());

        for (int i = 0 ;i < n; i ++ ){
            if (i > 0 && nums[i] == nums[i - 1]){
                continue;
            }
            
            if (nums[i] > 0){
                break;
            }

            int left = i + 1, right = n - 1;
            while (left < right){
                //这里要注意一下等号，不要等号哈
                int target = nums[i] + nums[left] + nums[right];
                if (target == 0){
                    res.push_back({nums[i], nums[left], nums[right]});
                    //去重
                    while (left < right && nums[left] == nums[left + 1]) left ++ ;
                    while (right > left && nums[right] == nums[right - 1]) right -- ;
                    left ++ ;
                    right -- ;
                }else if (target > 0){
                    right -- ;
                }else{
                    left ++ ;
                }
            }
        }

        return res;

    }
};