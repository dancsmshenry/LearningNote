class Solution {
public:
    vector<int> A;

    void function(int num, long number, long max, int k, int j){
        int i1 = num + k;
        if (i1 < 10){
            int number1 = number + i1 * j * 10;
            if (number1 >= max) A.push_back(number1);
            else function(i1, number1, max, k, j * 10);
        }

        int i2 = num - k;
        if (i2 >= 0 && k){//这里加一个k也太妙了吧
            int number2 = number + i2 * j * 10;
            if (i2 == 0 && number * 10 >= max) return;
            if (number2 >= max) A.push_back(number2);
            else function(i2, number2, max, k, j * 10);
        }
    }

    vector<int> numsSameConsecDiff(int n, int k) {      
        int max = 1, n1 = n - 1;
        while(n1 -- ){
            max *= 10;
        }

        for (int i = 0; i <10; i ++ ){
            if (k == 0 && i == 0) continue;
            if (i + k <= 9 || i - k >= 0){
                function(i, i, max, k, 1);
            }
        }

        return A;
    }
};