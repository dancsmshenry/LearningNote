class Solution {
public:
    int findMagicIndex(vector<int>& nums) {
        /**
        这道题感觉就是经典的双指针类型
        维护两个指针left（指向0）和right（指向n-1）
        对于left，如果left==nums[left]，那就直接返回left，因为这肯定是最小的魔术索引
        对于right，如果相等，那就更新res，然后right左移，接着继续查找（因为可能当前的不是最小的那一个魔术索引）
        都不相等，则两个指针同时向中间移动
        **/
        int left = 0, right = nums.size() - 1;
        int res = INT_MAX;

        while (left <= right){
            if (nums[left] == left){
                return left;
            }else if (nums[right] == right){
                res = min(right, res);
                right -- ;
            }else{
                left ++ ;
                right -- ;
            }
        }

        return res == INT_MAX ? -1 : res;
    }
};