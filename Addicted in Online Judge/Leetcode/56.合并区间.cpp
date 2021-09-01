class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        /**
            想到的一个方法，对所有区间的最小值进行排序
            然后先以第一个区间作为标准
            对后续的区间进行操作：
            将第一个区间的最小值设为imin，最大值设为imax
            如果当前的区间最小值小于imax，那就把imax设为当前区间的最大值
            如果当前区间的最小值大于等于imax，则把当前的imin和imax组成一个数组，插入到res中

            debug:
            如果当前的区间最小值小于等于imax且当前的最大值大于imax，那就把imax设为当前区间的最大值
            如果当前的区间最小值小于等于imax而当前的最大值也小于imax，则跳过
            如果当前区间的最小值大于imax，则把当前的imin和imax组成一个数组，插入到res中
        **/

        if (intervals.size() == 0) {
            return {};
        }

        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res;

        int i = 0;
        while (i < intervals.size()) {
            int imin = intervals[i][0], imax = intervals[i][1];
            int j = i + 1;
            while(j < intervals.size()){
                if (intervals[j][0] <= imax && intervals[j][1] > imax){
                    imax = intervals[j][1];//思考数据的多样性（[[1,4],[2,3]]）
                }else if (intervals[j][0] > imax){
                    res.push_back({imin, imax});
                    break;
                }
                j ++ ;
            }
            if (j >= intervals.size()){
                res.push_back({imin, imax});
            }
            i = j;
        }

        return res;
    }
};