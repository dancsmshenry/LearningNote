class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        int ans = words.size();
        string f[1000];
        vector<string> a = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

        for (int i = 0; i < words.size(); i ++ )
        {
            string s="";
            for (int j = 0; j < words[i].size(); j ++ ) s += a[words[i][j] - 'a'];
            f[i] = s;
        }

        for (int i = 0; i < words.size(); i ++ )
            for (int j = 0; j < i; j ++ )
                if (f[i] == f[j]) ans -- ;
        
        return ans;
    }
};