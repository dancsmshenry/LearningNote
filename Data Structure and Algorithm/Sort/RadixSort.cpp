#include<iostream>

using namespace std;

int maxbit(int data[], int n)//获取当前数组中最大数字的位数
{
    int maxData = data[0], d = 1, p = 10;

    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i]) maxData = data[i];
    }

    while (maxData >= p)
    {
        maxData /= 10;
        ++ d;
    }

    return d;
}

void radixsort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;

    for(i = 1; i <= d; i++) //进行d次排序，因为d表示该数组中的数字的最多位是多少
    {
        for(j = 0; j < 10; j++) count[j] = 0; //清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++) count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--) 
        {
            //将所有桶中记录依次收集到tmp中
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++)  data[j] = tmp[j]; //将临时数组的内容复制到data中
        radix = radix * 10;
    }
    
    delete []tmp;
    delete []count;
}

int main()
{
    int n;
    int arr[10000];
	cin >> n;
	for (int i = 0; i < n; i ++) cin >> arr[i];

	radixsort(arr, n);

	for (int i = 0; i < n; i ++) cout << arr[i] << " ";
	
	return 0;
}