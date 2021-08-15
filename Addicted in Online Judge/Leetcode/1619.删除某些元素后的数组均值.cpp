class Solution {
public:
    double trimMean(vector<int>& arr) {
        int sum = 0;

        sort(arr.begin(),arr.end());
        for(int i = arr.size() / 20; i < arr.size() - arr.size() / 20; i ++ ) sum += arr[i];

        return sum/(arr.size() - (arr.size() / 20) * 2.0);
    }
};