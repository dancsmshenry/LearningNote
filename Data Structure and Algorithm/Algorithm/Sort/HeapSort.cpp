#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

void HeapAdjust(int *arr, int n)
{
	for (int i = 1; i < n; i++){
		int record = i, father = (i - 1) / 2;
		while (1){
			if (arr[i] > arr[father]){
				swap(arr[i], arr[father]);
				i = father;
				father = (i - 1) / 2;
			}
			else{
				break;
			}
		}
		i = record;
	}
}

void heap_sort(int *arr, int length)
{
	HeapAdjust(arr, length);
	for (int i = length - 1; i > 0; i --){
		swap(arr[0], arr[i]);
		if (i != 1){
			HeapAdjust(arr, i);
		}
	}
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i++) cin >> arr[i];

	heap_sort(arr, length);

	for (int i = 0; i < length; i++) cout << arr[i] << " ";
	return 0;
}