#include<string>

class Solution {
public:
    vector<string> res;

    vector<string> permutation(string S) {
        /*
        思路：最基本的深搜思路
        把所有的字符都记录到一个数组当中
        然后开始从头搜索，如果当前的字母能够选中，就选中到字符串中，然后继续递归遍历
        直到所有的字符都被选完了（这里用一个flag来表示，即所有的字符都被选完了，就为true，否则为false）
        就把其插入到结果当中
        */

        vector<int> ans(125, 0);

        for (int i = 0; i < S.size(); i ++ ){
            ans[S[i]] ++ ;
        }

        string nullstring = "";
        solve(ans, nullstring);
        return res;
    }

    void solve(vector<int>& ans, string& s){
        bool flag = true;
        for (int i = 0; i < ans.size(); i ++ ){
            //s1是传进来的字符串
            if (ans[i] > 0){
                ans[i] -- ;
                s += (char)i;

                solve(ans, s);
                
                s.pop_back();
                ans[i] ++ ;

                flag = false;
            }
        }
        if (flag){
            res.push_back(s);
        }
    }
};