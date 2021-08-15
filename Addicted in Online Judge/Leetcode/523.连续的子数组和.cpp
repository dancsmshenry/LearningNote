bool checkSubarraySum(int* nums, int numsSize, int k)
{
    int i, j, k1;
    int f[100000];
    k1 = abs(k);
    
    if (numsSize < 2) return false;

    f[0] = nums[0];
    for (i = 1; i < numsSize; i++)
    {
        f[i] = f[i - 1] + nums[i];
        if (i > 1 && f[i] == f[i - 2] && k == 0) return true;  
    }

    if ((k1 == 0 && f[0] == f[numsSize - 1]) || (k1 == 1)) return true;
    else if (k1 == 0) return false;
    
    for (i = 1; i < numsSize; i++)
    {
        if (i == 1 && f[1] % k == 0) return true;
        else if (i == 1 && f[1] % k != 0) continue;
        else
        {
            for (j = 0; j < i - 1; j++)
            if ((f[i] - f[j]) % k == 0) return true;
        }
    }

    if (f[numsSize - 1] % k == 0) return true;
    else return false;
}


/**超时了，不知道如何优化....
 * class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        if(n < 1){
            return false;
        }

        for(int i = 1; i <= n; ++ i){
            sum[i] = sum[i - 1] + nums[i - 1];
            for(int j = i - 2; j >= 0; -- j){
                int t = sum[i] - sum[j];
                if(!k && t == 0){
                    return true;
                }else if(!k && t % k == 0){
                    return true;
                }
            }
        }
        
        return false;
    }
};
 **/ 

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m = {{0,-1}};//这里初始化0对应的坐标是-1
        //好处有两个：第一个是如果后面有数相加后（数量大于2）为0，这样用当前坐标返回找的时候
        //相减会始终大于2
        int rem = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            rem = (rem + nums[i])%k;
            if(m.count(rem))//这里是比较巧妙的地方：因为如果出现了两个相同的余数
            //就表示这两个位置中间的数字相加之和会是k的数倍（否则怎么会出现两个相同的余数呢？）
            //今晚看一看map的api是这么使用的...
            {
                int pos = m[rem];
                if(i - pos >= 2){
                    return true;
                }
            }
            else{
                m[rem] = i;
            }
        }
        return false;
    }
};