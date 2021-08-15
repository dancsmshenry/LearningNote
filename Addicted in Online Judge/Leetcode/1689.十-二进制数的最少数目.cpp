class Solution {
public:
    int minPartitions(string n) {
        int flag = 0;

        for(int i = 0; i < n.length(); i ++ )
            if(flag <= (n[i] - '0')) flag = n[i] - '0';
        
        return flag;
    }
};