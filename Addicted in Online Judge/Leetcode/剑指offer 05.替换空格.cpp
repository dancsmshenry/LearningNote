class Solution {
public:
    string replaceSpace(string s) {
        string f;

        for (int i = 0; i < s.size(); i ++ )
            if (s[i] == ' ')
            {
                f.push_back('%');
                f.push_back('2');
                f.push_back('0');
            }
            else f.push_back(s[i]);
        
        return f;
    }
};