class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> re;

        for (int i = 0; i < queries.size(); i ++ ){
            int res = 0;
            for (int j = 0; j < points.size(); j ++ ){
                int r_2 = queries[i][2] * queries[i][2];
                int len_2_x = (points[j][0] - queries[i][0]) *(points[j][0] - queries[i][0]);
                int len_2_y = (points[j][1] - queries[i][1]) *(points[j][1] - queries[i][1]);
                if (r_2 >= (len_2_x + len_2_y)) res ++;
            }
            re.push_back(res);
        }

        return re;
    }
};