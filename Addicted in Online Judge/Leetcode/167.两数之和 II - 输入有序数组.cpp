class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        /*经典的双指针+二分，好像以前做过*/
        int left = 0, right = numbers.size() - 1;

        while (left < right){
            if (target > (numbers[left] + numbers[right])){
                left ++ ;
            }else if (target < (numbers[left] + numbers[right])){
                right -- ;
            }else{
                return {left + 1, right + 1};
            }
        }

        return {left + 1, left + 2};
    }
};