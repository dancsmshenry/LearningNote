#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int n;
int arr[N];

void bubble_sort(int arr1[], int len)
{
	bool check = false;
	for (int i = len - 1; i > 0; i --)
	{
		for (int j = 0; j < i; j ++)
		{
			if (arr1[j] > arr1[j + 1])
			{
				swap(arr1[j], arr1[j + 1]);
				check = true;
			}
		}
		if (!check) break;
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i ++) cin >> arr[i];

	bubble_sort(arr, n);

	for (int i = 0; i < n; i ++) cout << arr[i] << " ";
	
	return 0;
}