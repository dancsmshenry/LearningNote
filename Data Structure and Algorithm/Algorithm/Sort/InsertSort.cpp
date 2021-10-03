#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

void insert_sort(int arr[], int n)
{
	for (int i = 1; i < n; i ++)
	{
		int temp = arr[i];
		for (int j = i - 1; j >= 0; j --)
			if (arr[j] > temp){
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}else {
				break;
			}
	}
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i ++) cin >> arr[i];

	insert_sort(arr, length);

	for (int i = 0; i < length; i ++) cout << arr[i] << " ";

	return 0;
}