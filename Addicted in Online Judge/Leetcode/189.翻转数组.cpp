class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        /**
        第一个想法：
        找一个数组把后面k位数字存放起来，然后把前n-k个数放到后面
        再把后面k个数放到前面
        用代码的语言来表示就是，利用%运算把数字重新放入一个新的数组中
        vector<int> news;
        int j = 0;
        k %= nums.size();
        for (int i = k; i < nums.size(); i ++ ){
            news[j ++ ] = nums[i];
        }
        for (int i = 0; i < k; i ++ ){
            news[j ++ ] = nums[i];
        }
        nums.assign(news.begin(), news.end());

        第二个想法：
        对于前面的n-k个数，逐个逐个的往后面移动
        比如1234567，k=3
        那我就对前面的n-k个数，即前4个数进行后移

        可惜这种方法被卡时间了
        
        int n = nums.size();
        k = k % n;
        if (k == 0){
            return ;
        }

        for (int i = n - k - 1, t = 0; i >= 0; i -- ){
            int tmp = nums[i];
            
        }
        **/
        
        //这种方法看了看题解就理解了，就是通过不断的翻转达到的
        k %= nums.size();
        solve(nums, 0, nums.size() - 1);//先翻转全部的数字
        solve(nums, 0, k - 1);//再单独翻转前k个数字
        solve(nums, k, nums.size() - 1);//最后再翻转n-k个数字
    }

    void solve(vector<int>& nums, int left, int right){
        while(left <= right){
            swap(nums[left ++ ], nums[right -- ]);
        }
    }
};