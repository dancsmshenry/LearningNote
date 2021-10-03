#include <iostream>

using namespace std;

int fastindex(int base, int index)
{
    int result = 1;
    while (index > 1)
    {
        if (index % 2 == 0)
        {
            index /= 2;
            base *= base;
        }
        else
        {
            index -- ;
            index /= 2;
            base *= base;
            result *= base;
        }
    }

    return result;
}

int main()
{
    int base, index;

    cin >> base >> index;

    cout << fastindex(base, index);

    return 0;
}