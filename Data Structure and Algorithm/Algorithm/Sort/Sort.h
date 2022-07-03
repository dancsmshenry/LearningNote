#include <iostream>
#include <vector>
#include <cstring>

void quick_sort(std::vector<int> &arr, int left, int right) {
	if (left >= right) return;
	
	int temp = arr[left], i = left - 1, j = right + 1;
	while (i < j) {
		do i ++ ; while (arr[i] < temp);
		do j -- ; while (arr[j] > temp);
		if (i < j) std::swap(arr[i], arr[j]);
	}
		
	quick_sort(arr, left, j);
	quick_sort(arr, j + 1, right);
}


void bubble_sort(std::vector<int> &arr) {
	int n = arr.size();
	bool flag = false;
	for (int i = n - 1; i > 0; -- i) {
		for (int j = 0; j < i; ++ i) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				flag = true;
			}
		}
		if (!flag) break;
	}
}


void insert_sort(std::vector<int> &arr, int n) {
	for (int i = 1; i < n; ++ i) {
		int temp = arr[i];
		for (int j = i - 1; j >= 0; -- j) {
			if (arr[j] > temp){
				arr[j + 1] = arr[j];
				arr[j] = temp;
			} else {
				break;
			}
		}
	}
}


void select_sort(std::vector<int> &arr, int n) {
	for (int i = n - 1; i > 0; -- i) {
		int record = i;
		for (int j = 0, maxn = arr[i]; j < i; ++ j) {
			if (maxn < arr[j]) {
				record = j;
				maxn = arr[j];
			}
		}
		std::swap(arr[record], arr[i]);
	}
}


void merge_sort(std::vector<int> &arr, int left, int right) {
	if (left >= right) return;

	int mid = left + (right - left) / 2;
	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);
	
	int tmp[right - left + 1];
	int k = 0, i = left, j = mid + 1;
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) tmp[k ++ ] = arr[i ++ ];
		else tmp[k ++ ] = arr[j ++ ];
	}
	while (i <= mid) tmp[k ++ ] = arr[i ++ ];
	while (j <= right) tmp[k ++ ] = arr[j ++ ];
	
	for (i = left, j = 0; i <= right; ++ i, ++ j) arr[i] = tmp[j];
}


void shell_sort(std::vector<int> &arr) {
	int n = arr.size(), increment = n;
	do {
		increment = increment / 3 + 1;
		for (int i = increment; i < n; ++ i)
			if (arr[i] < arr[i - increment]) {
				int mid = arr[i];
				for (int j = i - increment; j >= 0 && mid < arr[j]; j -= increment) {
					arr[j + increment] = arr[j];
					arr[j] = mid;
				}
			}
	} while (increment > 1);
}


void create_heap(std::vector<int> &arr, int x, int n) {
    int l = x * 2 + 1, r = x * 2 + 2;
    int max = x;

    if (l < n && arr[l] > arr[max]) max = l;
    if (r < n && arr[r] > arr[max]) max = r;

    if (max != x){
        std::swap(arr[x], arr[max]);
        create_heap(arr, max, n);
    }
}

void heap_sort(std::vector<int> &arr) {
	// 这里构建的大顶堆，每次把最大值交换到最后面
	int n = arr.size();
	for (int i = n / 2 - 1; i >= 0; -- i) create_heap(arr, i, n);

    for (int i = n - 1; i > 0; -- i) {
        std::swap(arr[0], arr[i]);
        create_heap(arr, 0, i);
    }
}


// maxn为当前数组中最大的数字
void counting_sort(std::vector<int> &arr, int maxn) {
	int n = arr.size();
    int buckets[10086];

    for (int i = 0; i < n; ++ i) {
        buckets[arr[i]] ++;
    }
    for (int i = 0, j = 0; i <= maxn; ++ i) {
        while((buckets[i] --) > 0) {
            arr[j ++ ] = i;
        }
    }
}


//获取当前数组中最大数字的位数
int maxbit(int *data, int n) {
    int maxn = data[0], d = 1;

    for (int i = 1; i < n; ++ i) {
        if (maxn < data[i]) maxn = data[i];
    }

    while (maxn >= 10) {
        maxn /= 10;
        ++ d;
    }

    return d;
}

void radix_sort(int *data, int n) {
    int d = maxbit(data, n);
    int tmp[n];
    int count[10];	//	计数器
    int radix = 1;

    //	进行d次排序，因为d表示该数组中的数字的最多位是多少
    for (int i = 1; i <= d; ++ i) {
        //	清空计数器
        memset(count, 0, sizeof(count)); 

        //统计每个桶中的记录数
        for (int j = 0, k = 0; j < n; ++ j) {
            k = (data[j] / radix) % 10;
            ++ count[k];
        }

        //将tmp中的位置依次分配给每个桶
        for (int j = 1; j < 10; ++ j) {
            count[j] += count[j - 1]; 
        }

        //将所有桶中记录依次收集到tmp中
        for (int j = n - 1, k = 0; j >= 0; -- j) {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            -- count[k];
        }

        //将临时数组的内容复制到data中
        for (int j = 0; j < n; ++ j) {
            data[j] = tmp[j]; 
        }
        radix *= 10;
    }
}