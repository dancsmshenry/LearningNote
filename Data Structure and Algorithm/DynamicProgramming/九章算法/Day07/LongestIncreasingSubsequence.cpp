#include <iostream>
#include <vector>

using namespace std;

/**
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

解释：
这里b数组实际上可以看为是一个栈，
代码中的二分查找是找比当前的数还小的最大的那一个数，
找到了以后，便把它后面的这个数替换为当前的数，
然后看此时的数组长度和所要求的数组长度哪个大，取大的那一个作为top

为什么会发现有这种优化方法：
因为你看，假设前面有两个数分别为5和6结尾的，以它们结尾的序列长度都是4，但是我们一般就会认为
最好选以5结尾的（或是说更小的那一个），为什么，因为选择更小的那一个，就会给后面的数字更多的就会
比如说后面有一个6，加入选择的是以6结尾的，那我们就选不上了；但是如果选择
**/

int main(){
    vector<int> a = {5, 4, 1, 2, 3};
    int n = a.size();

    if (n == 0){
        cout << 0;
    }

    int b[n + 1];
    int top = 0;
    b[0] = INT_MIN;

    for (int i = 0; i < n; i ++ ){
        int start = 0, end = top;
        int j = 0;

        //find
        while (start <= end){
            int mid = start + end >> 1;
            if (b[mid] < a[i]){
                j = mid;
                start = mid + 1;
            }else{
                end = mid - 1;
            }
        }

        b[j + 1] = a[i];
        if (j + 1 > top){
            top = j + 1;
        }
    }

    cout << top;
}