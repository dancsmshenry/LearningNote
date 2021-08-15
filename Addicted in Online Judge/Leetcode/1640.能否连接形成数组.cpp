class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        for (int j = 0;;)
        {
            for (int i = 0; i < pieces.size(); i ++ )
            {
                if (arr[j] == pieces[i][0])
                {
                    for (int l = 0; l < pieces[i].size(); l ++ )
                    {
                        if (arr[j] == pieces[i][l]) j ++ ;
                        else return false;
                    }
                    break;
                }
                else if (i == pieces.size() - 1) return false;
            }
            if (j == arr.size()) return true;
        }

        return true;
    }
};