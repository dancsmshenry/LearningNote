class Solution {
public:
    string convert(string s, int numRows) {
        string total = "";
        if (numRows == 1) return s;

        for (int i = 0; i < numRows; i++){
            int a = 2 * numRows - 2 - i * 2, j = i, l = 0;
            while(j < s.size()){
                total += s[j];
                if (a == 0) j += (2 * numRows - 2);
                else if (l % 2 == 0 || 2 * numRows - 2 == a) j += a;
                else j+= (2 * numRows - 2 - a);
                l++;
            }
        }

        return total;
    }
};