#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

void bucket_sort(int* arr, int length){
}

int main()
{
	cin >> length;
	for (int i = 0; i < length; i ++) cin >> arr[i];

	bucket_sort(arr, length);

	for (int i = 0; i < length; i ++) cout << arr[i] << " ";
	
	return 0;
}