#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

void shell_sort(int *arr, int n)
{
	int increment = n;
	do{
		increment = increment / 3 + 1;
		for (int i = increment; i < n; i ++)
			if (arr[i] < arr[i - increment]){
				int mid = arr[i];
				for (int j = i - increment; j >= 0 && mid < arr[j]; j -= increment){
					arr[j + increment] = arr[j];
					arr[j] = mid;
				}
			}
	}
	while (increment > 1);
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i ++) cin >> arr[i];
	
	shell_sort(arr, length);
	
	for (int i = 0; i < length; i ++) cout << arr[i] << " ";
	return 0;
}