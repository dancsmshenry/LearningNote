class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        /*
        这道题看到是logn，就知道一定要用上二分查找来写
        但是想了半天发现没法子，所以直接看题解了：
        对于任何一个数，我们可以发现如果他的右边大于等于他本身，那么就意味着他的右边出现两种情况
        1、首先是一直增长，那最右边的一定是山峰了
        2、如果是跌宕起伏的话，那就这么在右边一定有山峰
        ps:题目说保证不会出现左右两边相等的情况
        如果是左边大于右边的话，同理，在左边一定有山峰

        至此，有一个判断条件，还有其详细的情况，就可以写一个二分查找了
        */

        int left = 0, right = nums.size() - 1;

        while (left < right){
            int mid = (left + right) >> 1;
            if (nums[mid] <= nums[mid + 1]){
                left = mid + 1;
            }else{
                right = mid;
            }
        }

        return left;
    }
};