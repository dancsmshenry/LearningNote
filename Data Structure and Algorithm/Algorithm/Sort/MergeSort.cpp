#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N] ,tmp[N];

void merge_sort(int *arr, int left, int right)
{
	if (left >= right) return;

	int mid = (left + right) >> 1;
	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);
	
	int k = 0, i = left, j = mid + 1;
	while (i <= mid && j <= right){
		if (arr[i] <= arr[j]) tmp[k ++ ] = arr[i ++ ];
		else tmp[k ++ ] = arr[j ++ ];
	}
	while (i <= mid) tmp[k ++ ] = arr[i ++ ];
	while (j <= right) tmp[k ++ ] = arr[j ++ ];
	
	for (i = left, j = 0; i <= right; i ++, j ++) arr[i] = tmp[j];
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i ++ ) cin >> arr[i];
	
	merge_sort(arr, 0, length - 1);
	
	for (int i = 0; i < length; i ++ ) cout << arr[i] << " ";
	
	return 0;
}