class Solution {
public:
    bool isValid(string s) {
        int n = s.size();

        if (n % 2 == 1){
            return false;
        }

        unordered_map<char, char> pair={
            {')', '('},{']', '['}, {'}', '{'}
        };

        stack<char> stack01;
        for (int i = 0; i < n; i ++ ){
            char ch = s[i];
            if (pair.count(ch)){
                //找到了，即此时的ch是右半边
                //就先看栈顶有没有东西，如果没有就直接为false
                //如果有，则看是否匹配，不匹配的也是false
                //如果有，且匹配，则把栈顶踢出来
                if (stack01.empty()){
                    return false;
                }
                if (stack01.top() == pair[ch]){
                    stack01.pop();
                }else{
                    return false;
                }
            }else{//没找到，即此时的ch是左半边的括号，则把它添加到栈里面
                stack01.push(ch);
            }
        }
        
        //最开始做题的时候没有思路，隐隐约约感觉是用栈来写，但是又不知道具体该怎么写才是对的
        //看了解析之后思路就明白了
        //但是写代码的时候，感觉是不熟悉stl中的stack和unordered_map导致写的时候有点不知所措
        //计划：优先把思路先写出来，然后在想着如何用代码来实现，最后再进行优化
        return stack01.empty();
    }
};