#include "Sort.h"

int main() {
    std::vector<int> arr{9,8,7,6,5,4,3,2,1,0};

    heap_sort(arr);
    
    for (auto&& a: arr) {
        std::cout << a << " ";
    }
}