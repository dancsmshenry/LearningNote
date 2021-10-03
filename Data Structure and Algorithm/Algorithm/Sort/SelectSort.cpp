#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

void select_sort(int *arr, int length)
{
	for (int i = length - 1; i > 0; i --)
	{
		int record = i;
		for (int j = 0, maxn = arr[i]; j < i; j ++){
			if (maxn < arr[j]){
				record = j;
				maxn = arr[j];
			}
		}
		swap(arr[record], arr[i]);
	}
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i ++) cin >> arr[i];
	
	select_sort(arr, length);
	
	for (int i = 0; i < length; i ++) cout << arr[i] << " ";

	return 0;
}