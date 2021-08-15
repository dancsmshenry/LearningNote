int findMin(int* nums, int numsSize)
{
    int i, min = nums[0];

    for (i = 1; i < numsSize; i++)
    {
        if (nums[i - 1] < nums[i]) continue;
        else
        {
            min = min < nums[i] ? min : nums[i];
            break;
        }
    }

    return min;
}
//正规做法
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;

        while (left < right){
            int mid = (left + right) >> 1;
            if (nums[mid] < nums[right]){
                right = mid;
            }
            else{
                left = mid + 1;
            }
        }

        return nums[left];
    }
};