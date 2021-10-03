#include <iostream>

using namespace std;

int main() 
{
    int f[6] = {1, 2, 3, 4, 5, 6};
    int n, left = 0, right = 5;

    cin >> n;
    while (left < right)
    {
        int mid = left + right >> 1;    //加法的比位运算的优先级高
        if (f[mid] < n) left = mid + 1;
        else right = mid;
    }

    if (f[left] == n) cout << left;
    else cout << "XD";

    return 0;
}

/*
#include <iostream>

using namespace std;

int main()
{
    int f[6] = {1, 2, 3, 4, 5, 6};
    int n, left = 0, right = 5;

    cin >> n;
    while (left < right)
    {
        int mid = left + right >> 1;    //加法的比位运算的优先级高
        if (f[mid] < n) left = mid;
        else right = mid - 1;
    }

    if (f[left] == n) cout << left;
    else cout << "XD";

    return 0;
}
*/
//浮点数二分查找法