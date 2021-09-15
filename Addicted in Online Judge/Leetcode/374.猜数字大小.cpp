/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int left = 0, right = n;

        while (left < right){
            // int mid = (left + right) >> 1;
            int mid = left + (right - left) / 2;//二分查找防溢出
            if (guess(mid) == 1){
                left = mid + 1;
            }else if (guess(mid) == -1){
                right = mid;
            }else if (guess(mid) == 0){
                return mid;
            }
        }

        return left;
    }
};