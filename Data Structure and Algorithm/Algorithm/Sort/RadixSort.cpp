#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int length;
int arr[N];

//获取当前数组中最大数字的位数
int maxbit(int *data, int n){
    int maxn = data[0], d = 1;

    for (int i = 1; i < n; i ++ ){
        if (maxn < data[i]) maxn = data[i];
    }

    while (maxn >= 10){
        maxn /= 10;
        ++ d;
    }

    return d;
}

void radix_sort(int *data, int n){
    int d = maxbit(data, n);
    int tmp[n];
    int count[10];//计数器
    int radix = 1;

    //进行d次排序，因为d表示该数组中的数字的最多位是多少
    for (int i = 1; i <= d; i ++) {
        //清空计数器
        memset(count, 0, sizeof(count)); 

        //统计每个桶中的记录数
        for (int j = 0, k = 0; j < n; j ++){
            k = (data[j] / radix) % 10;
            count[k] ++;
        }

        //将tmp中的位置依次分配给每个桶
        for (int j = 1; j < 10; j ++){
            count[j] += count[j - 1]; 
        }

        //将所有桶中记录依次收集到tmp中
        for (int j = n - 1, k = 0; j >= 0; j --) {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k] --;
        }

        //将临时数组的内容复制到data中
        for (int j = 0; j < n; j ++){
            data[j] = tmp[j]; 
        }
        radix *= 10;
    }
}

int main(){
	cin >> length;
	for (int i = 0; i < length; i ++) cin >> arr[i];

	radix_sort(arr, length);

	for (int i = 0; i < length; i ++) cout << arr[i] << " ";
	
	return 0;
}