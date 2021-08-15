bool search(int* nums, int numsSize, int target)
{
    int mid, left = 0, right = numsSize - 1;
    if (numsSize <= 0) return false;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (nums[mid] == target) return true;
        if (nums[mid] > nums[left])
        {
            if (target >= nums[left] && target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        }
        else if (nums[mid] < nums[left])
        {
            if (target > nums[mid] && target <= nums[right]) left = mid + 1;
            else right = mid - 1;
        }
        else left++;
    }

    return false;
}

//另外一种方法
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int m = nums.size() - 1, left = 0, right;
        if (nums.size() == 1) return target == nums[0];

        for (int i = 1; i < nums.size(); i ++ ){
            if (nums[i] < nums[i - 1]){
                m = i - 1;
                break;
            }
        }

        if (target >= nums[0]){
            right = m;
        }
        else{
            left = m + 1;
            right = nums.size() - 1;
        }
        if (left > right) return false;
        //这里其实是关键步骤，因为很可能说m是最后一位，表明当前数组其实是没有旋转的，表明当前的target比最小的还要小，那就没有找的必要了，直接返回false，所以要加上一个特判！！！

        while (left < right){//这就是二分的模板，以后背下来即可
            int mid = (left + right) >> 1;
            if (nums[mid] >= target) right = mid;
            else left = mid + 1;
        }

        if (nums[left] == target) return true;
        else return false;
    }
};