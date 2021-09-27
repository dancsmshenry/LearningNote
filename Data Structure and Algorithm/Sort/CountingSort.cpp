#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];
int maxn = INT_MIN;

void counting_sort(int *arr, int length, int maxn){
    int buckets[N];
    for (int i = 0; i < length; i ++ ){
        buckets[arr[i]] ++;
    }
    for (int i = 0, j = 0; i <= maxn; i ++ ){
        while((buckets[i]--) > 0){
            arr[j ++ ] = i;
        }
    }
}

int main()
{
    cin >> length;
    for (int i = 0; i < length; i ++ ){
        cin >> arr[i];
        maxn = max(arr[i], maxn);
    }

    counting_sort(arr, length, maxn);    

    for (int i = 0; i < length; i ++ ) cout << arr[i] << " ";

    return 0;
}