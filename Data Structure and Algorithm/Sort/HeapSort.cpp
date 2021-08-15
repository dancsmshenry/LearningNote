#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int arr[N];
int n;

void HeapAdjust(int *arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		int record = i, Father = (i - 1) / 2;
		while (1)
		{
			if (arr[i] > arr[Father])
			{
				swap(arr[i], arr[Father]);
				i = Father;
				Father = (i - 1) / 2;
			}
			else
				break;
		}
		i = record;
	}
}

void HeapSort(int *arr, int n)
{
	HeapAdjust(arr, n);
	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		if (i != 1)
			HeapAdjust(arr, i);
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];

	HeapSort(arr, n);

	for (int i = 0; i < n; i++) cout << arr[i] << " ";
	return 0;
}