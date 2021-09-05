class Solution {
public:
    int longestPalindrome(string s) {
        /**
        首先的想法：
        先统计所有的字母出现的次数
        然后对所有的次数，如果是偶数，就把他加至total
        如果是奇数，那么就把它减一后加至total（这里设置一个bool值，如果触发了，就设为false）
        最后，如果bool值为false，则return total + 1;
        否则return total;
        **/

        int count[128];
        memset(count, 0, sizeof(count));
        int total = 0;
        bool flag = true;
        for (int i = 0; i < s.size(); i ++ ){
            count[s[i]] ++ ;
        }

        for (int i = 0; i < 128; i ++ ){
            if (count[i] % 2 != 0){
                flag = false;
                total -- ;
            }
            total += count[i];
        }

        return flag ? total : total + 1;
    }
};