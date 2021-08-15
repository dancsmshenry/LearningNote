class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        int n = groupSizes.size();
        bool flag[n];
        memset(flag,false,sizeof(flag));
        vector<vector<int>> res;

        for (int i = 0; i < groupSizes.size(); i ++ ){
            if (flag[i] == true) continue;
            int number = groupSizes[i];
            vector<int> mid;
            mid.push_back(i);
            for (int j = i + 1, l = 1; l < number && j < groupSizes.size(); j ++ ){
                if (flag[j] == true) continue;
                if (number == groupSizes[j]){
                    l ++ ;
                    mid.push_back(j);
                    flag[j] = true;
                }
            }
            res.push_back(mid);
        }

        return res;
    }
};