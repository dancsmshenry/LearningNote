class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        /*
        这道题目以前也做过，但是使用笨方法做的，即双重循环，非常耗时

        现在看到这道题，想到的就是用双指针来记录当前状态
        即维护两个指针left和right，还有一个字符数组

        right往右移动，遇到一个字母就把其对应的字符上加一，如果等于1，则用left-right更新maxn
        否则，就移动left指针，知道该字母剪到1为止
        */
        int left = 0, right = 0;
        int maxn = 0;
        int ans[1000] = {0};

        while (right < s.size()){
            if (ans[s[right]] == 0){
                ans[s[right]] ++ ;
                right ++ ;
                maxn = max(maxn, right - left);
            }else{
                ans[s[right]] ++ ;
                while (ans[s[right]] > 1 && left <= right){
                    ans[s[left]] --;
                    left ++;
                }
                right ++ ;
            }
        }

        return maxn;
    }
};