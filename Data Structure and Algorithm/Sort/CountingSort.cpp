#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n, maxn = INT_MIN;
    int a[10000], buckets[10000];

    cin >> n;
    for (int i = 0; i < n; i ++ )
    {
        cin >> a[i];
        maxn = max(a[i], maxn);
    }

    for (int i = 0; i < n; i ++ ) buckets[a[i]] ++;
    for (int i = 0, j = 0; i <= maxn; i ++ )
        while((buckets[i]--) > 0)
            a[j ++ ] = i;

    for (int i = 0; i < n; i ++ ) cout << a[i] << " ";

    return 0;
}