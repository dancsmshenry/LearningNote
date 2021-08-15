bool isUgly(int num)
{
    int number;
    if (num < 1) return false;
    else if (num == 1) return true;
    else number = num;

    while (number != 1)
    {
        if (number % 2 == 0) number = number / 2;
        else if (number % 3 == 0) number = number / 3;
        else if (number % 5 == 0) number = number / 5;
        else return false;
    }

    return true;
}

//
class Solution {
public:
    bool isUgly(int n) {
        if (n <= 0) return false;
        while (n != 1){
            bool flag = false;
            if (n % 2 == 0){
                n /= 2;
                flag = true;
            }
            if (n % 3 == 0){
                n /= 3;
                flag = true;
            }
            if (n % 5 == 0){
                n /= 5;
                flag = true;
            }
            if (!flag) return false;
        }

        return true;
    }
};