#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

void bubble_sort(int arr[], int length)
{
	bool check = false;
	for (int i = length - 1; i > 0; i --)
	{
		for (int j = 0; j < i; j ++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				check = true;
			}
		}
		if (!check) break;
	}
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i ++) cin >> arr[i];

	bubble_sort(arr, length);

	for (int i = 0; i < length; i ++) cout << arr[i] << " ";
	
	return 0;
}