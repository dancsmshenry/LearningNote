class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        /**
        要求给的翻转次数要在10*arr.length以内，其实是很容易做到的
        只要不断循环下列算法即可
        首先，找到当前一段数组中的最大值
        从0到最大值的位置翻转一次
        然后再对前半部分进行一次翻转就行了（因为是不断循环下列算法，所以后面就会维护一个递增的有序数列）
        **/
        int length = arr.size();
        vector<int> res;

        for (int i = length; i > 0; i -- ){
            int n = find_max(arr, i);
            reverse(arr.begin(), arr.begin() + n + 1);
            reverse(arr.begin(), arr.end() - (length - i));//这出现了问题，这里应该是翻转前面那一段没有排序好的部分
            res.push_back(n + 1);
            res.push_back(i);
        }

        return res;
    }

    int find_max(vector<int>& arr, int end){
        int maxn = arr[0], number = 0;
        for (int i = 1; i < end; i ++ ){
            if (arr[i] >= maxn){
                number = i;
                maxn = arr[i];
            }
        }
        return number;
    }
};