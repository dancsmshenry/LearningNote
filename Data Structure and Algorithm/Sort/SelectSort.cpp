#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int n = 0;
int arr[N];

void select_sort(int *arr1, int len)
{
	for (int i = len - 1; i >= 0; i --)
	{
		int maxn = arr1[i], record = i;
		for (int j = 0; j < i; j ++)
			if (maxn < arr1[j])
			{
				record = j;
				maxn = arr1[j];
			} 
		int mid = arr1[record];
		arr1[record] = arr1[i];
		arr1[i] = mid;
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i ++) cin >> arr[i];
	
	select_sort(arr, n);
	
	for (int i = 0; i < n; i ++) cout << arr[i] << " ";

	return 0;
}