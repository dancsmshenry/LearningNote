class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        /**
        看完滑动窗口的解法之后，看到这道题目的第一个思路就是维护一个长度为k+1的窗口
        每进来一个新的数就抛弃掉后面的一个数，
        然后对这个新进来的数和原来窗口里面的数进行匹配，
        如果匹配成功，就直接返回true；否则就继续匹配下去
        如果当前的窗口都没能匹配成功，就检测下一个数
        最后，当窗口的右边界到最后一个数的时候就停下来

        但是这会儿如何用代码去实现呢？
        下面是借用了一位仁兄的代码，思路和我想的完全一致
        可，害..
        **/

        unordered_set<int> existed;

        for (int i = 0; i < nums.size(); i ++ ){
            if (existed.find(nums[i]) == existed.end()){//如果在set中没有找到目标数字
                existed.insert(nums[i]);//就把他加入到该set中
                if (existed.size() > k){//如果当前的长度大于了k，就把最前面的那个数字给删掉
                    existed.erase(nums[i-k]);
                }
            }else{
                return true;
            }
        }

        return false;
    }
};