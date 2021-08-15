#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int n;
int arr[N];

void insert_sort(int arr1[], int n)
{
	for (int i = 1; i < n; i ++)
	{
		int mid = arr1[i];
		for (int j = i - 1; j >= 0; j --)
			if (arr1[j] > mid)
			{
				arr1[j + 1] = arr1[j];
				arr1[j] = mid;
			}
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i ++) cin >> arr[i];

	insert_sort(arr, n);

	for (int i = 0; i < n; i ++) cout << arr[i] << " ";

	return 0;
}