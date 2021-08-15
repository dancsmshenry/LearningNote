class Solution {
public:
    int arrangeCoins(int n) {
        long mid, left = 0, right = 65536;

        while (left <= right)
        {
            mid = right + (left - right) / 2;
            if ((mid * (mid + 1) / 2) == n) return mid;
            if ((mid * (mid + 1) / 2) < n) left = mid + 1;
            else right = mid - 1;
        }

        if (mid * (mid + 1) / 2 > n) return mid - 1;
        else return mid;
    }
};