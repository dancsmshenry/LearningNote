class Solution {
public:
    int lengthOfLastWord(string s) {
        int length = s.size();
        while (length > 0){
            if (s[length - 1] == ' '){
                length -- ;
            }else{
                break;
            }
        }

        for (int i = length - 1; i >= 0; i -- ){
            if (s[i] == ' '){
                return length - i - 1;
            }
        }

        return length;
        /*
        下次一定要读了题目在写
        出现bug的时候最好是先看一下是那个测试用例出现了问题
        我人傻了，这道题做了我半个小时，老是debug了
        */
    }
};