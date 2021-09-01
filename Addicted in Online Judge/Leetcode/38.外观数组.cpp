#include <string.h>

class Solution {
public:
    string countAndSay(int n) {
        /**
         * 用循环来求解
         * 每一次都计算出当前的i对于的string，然后作为下一次i+1的求解标准
         * 求解string的步骤：
         * 如果和前面的相同，就count+1，调到下一次循环
         * 如果不同，就把count和t1加到res中
         * 
         * 记住，最后还要再把count和t1加到res中
         * 
         * 然后这一次的res就是下一次的循环对象
         **/ 
        string t = "1", res = "";//string类型 s[i] 返回值是 char类型的引用，而不是 string类型
        int count = 1;
        char t1;//用全体变量的确是比每次循环开辟新变量速度上来的快一点
        if (n == 1) return t;

        for (int i = 2; i <= n; i ++ ){
            res = "";
            t1 = t[0];
            count = 0;
            for (int j = 0; j < t.size(); j ++ ){
                if (t1 == t[j]){
                    count ++ ;
                    continue;
                }else{
                    res += to_string(count);
                    res += t1;
                    t1 = t[j];
                    count = 1;
                }
            }
            res += to_string(count);
            res += t1;
            t = res;
        }

        return res;
    }
};