class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        int i1 = 0;
        string target;

        while (1)
        {
            target = paths[i1][1];
            for (int i = 0; i < paths.size(); i ++ )
            {
                if (paths[i][0] == target)
                {
                    i1 = i;
                    break;
                }
                else if (i == paths.size() - 1) return target;
            }
        }

        return target;
    }
};