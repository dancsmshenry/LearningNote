bool cmp(vector<int>& a, vector<int>& b)
{
    return (a[0] > b[0]) || (a[0] == b[0] && a[1] < b[1]);
}

class Solution {
public:
    // static bool cmp(vector<int>& a, vector<int>& b)
    // {
    //     return (a[0] > b[0]) || (a[0] == b[0] && a[1] < b[1]);
    // }
    //为什么这里的cmp函数在类里面的时候就一定要用static使其在编译的时候运行呢？
    //一个解释：静态函数和全局函数都没有this指针，而sort需要传参的cmp函数，如果在类内不是static函数，就会被默认需要传入this指针
    //所以这里需要把cmp设为全局函数或者静态函数

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int>> res;
        sort(people.begin(), people.end(), cmp);//sort函数是可以对其中的第一项进行排序的（这里必须要看源码）

        for(int i = 0; i < people.size(); i ++ ){
            res.insert(res.begin() + people[i][1], people[i]);
            //前面要插入的位置
        } 

        return res;
    }
};