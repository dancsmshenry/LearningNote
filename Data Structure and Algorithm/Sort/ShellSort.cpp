#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int n;
int arr[N];

void shell_sort(int arr1[], int n)
{
	int increment = n;
	do
	{
		increment = increment / 3 + 1;
		for (int i = increment; i < n; i ++)
			if (arr1[i] < arr1[i - increment])
			{
				int mid = arr1[i];
				for (int j = i - increment; j >= 0 && mid < arr1[j]; j -= increment)
				{
					arr1[j + increment] = arr1[j];
					arr1[j] = mid;
				}
			}
	}
	while (increment > 1)
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i ++) cin >> arr[i];
	
	shell_sort(arr, n);
	
	for (int i = 0; i < n; i ++) cout << arr[i] << " ";
	return 0;
}