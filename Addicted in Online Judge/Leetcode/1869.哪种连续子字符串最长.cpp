class Solution {
public:
    bool checkZeroOnes(string s) {
        int point = 0;
        int n = s.size();
        int len_0 = 0, len_1 = 0;

        while (point < n){
            if (s[point] == '1'){
                int sum = 0;
                while (s[point] == '1'){
                    point ++ ;
                    sum ++ ;
                }
                len_1 = len_1 > sum ? len_1 : sum;
            }else{
                int sum = 0;
                while (s[point] == '0'){
                    point ++ ;
                    sum ++ ;
                }
                len_0 = len_0 > sum ? len_0 : sum;
            }
        }

        return len_1 > len_0 ? true : false;
    }
};