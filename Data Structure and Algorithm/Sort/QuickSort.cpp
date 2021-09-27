#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

void quick_sort(int *arr, int left, int right)
{
	if (left >= right) return;
	
	int temp = arr[left], i = left - 1, j = right + 1;
	while (i < j)
	{
		do i ++ ; while (arr[i] < temp);
		do j -- ; while (arr[j] > temp);
		if (i < j) swap(arr[i], arr[j]);
	}
		
	quick_sort(arr, left, j);
	quick_sort(arr, j + 1, right);
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i ++ ) cin >> arr[i];
	
	quick_sort(arr, 0, length - 1);
	
	for (int i = 0; i < length; i ++ ) cout << arr[i] << " ";
	
	return 0;
}
