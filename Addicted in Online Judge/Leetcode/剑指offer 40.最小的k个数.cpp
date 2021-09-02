class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        /**
            最开始想到的思路：
            想到了快排的方式：
            快排的原理就是对于一个数组，先找到一个数字，对于小于它的就放到左边，大于它的就放到右边
            如果左边的数量等于k，就把左边的数字放到数组输出即可
            如果小于k的话，就先把数字放进去，然后再把右边的最小的k-l个数字放进去
            如果大于k的话，就在左边找最小的k个数字

            而标准答案给的一个比较好的思路就是，我先不把数字放进去，继续排序
            因为我知道一定会存在一种情况是左边恰好有k个数字，所以
            如果左边的数字数目大于k的话，那么我就对左边排列
            如果左边的数字小于k的话，那我就对右边排列
            这里的一个关键就是i，i表面上看，一开始是记录了最左边的数字的下标，但是排序过后它却是记录了左边实际有多少个数字

            这里给我的一个教训是，要学会优化自己的想法，让自己的想法更加容易的被代码表达出来
        **/
        int n = arr.size();
        if (k >= n) return arr;
        return quickSort(arr, k, 0, n - 1);
    }
private:
    vector<int> quickSort(vector<int>& arr, int k, int l, int r) {
        //快排的全程
        int i = l, j = r;
        while (i < j) {
            while (i < j && arr[j] >= arr[l]) j--;
            while (i < j && arr[i] <= arr[l]) i++;
            swap(arr[i], arr[j]);
        }
        swap(arr[i], arr[l]);

        //这里的精华就在于i，因为有了i就可以判断是否要继续排序，这也是我思路上的一个阻塞
        if (i > k) return quickSort(arr, k, l, i - 1);//如果左边的数字大于k，就对左边继续排序
        if (i < k) return quickSort(arr, k, i + 1, r);//如果左边的数字小于k，就对右边继续排序
        vector<int> res;
        res.assign(arr.begin(), arr.begin() + k);
        return res;
    }
};