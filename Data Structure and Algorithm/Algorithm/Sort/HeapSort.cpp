#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

void HeapAdjust(int a[], int x, int n)
{
    int l = x * 2 + 1, r = x * 2 + 2;
    int max = x;

    if (l < n && a[l] > a[max]) max = l;
    if (r < n && a[r] > a[max]) max = r;

    if (max != x){
        swap(a[x], a[max]);
        HeapAdjust(a, max, n);
    }
}

void heap_sort(int a[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i -- ) HeapAdjust(a, i, n);

    for (int i = n - 1; i > 0; i -- ){
        swap(a[0], a[i]);
        HeapAdjust(a, 0, i);
    }
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i ++ ) cin >> arr[i];

	heap_sort(arr, length);

	for (int i = 0; i < length; i ++ ) cout << arr[i] << " ";
	return 0;
}