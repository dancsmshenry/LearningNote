- 对于stl中的算法，对于算法的实现者来说，并不知道你是什么容器
- 算法与容器是通过迭代器关联的
- std::lower_bound二分查找的话，是通过std::distance确定中间点的，显然时间复杂度很高，所以容器有特化版本时，一定要使用特化版本
- std::distance对于RandomAccessIterator迭代器实现的，即对于连续的容器，是可以通过O(1)实现的，而对于普通的ForwardIterator显然是要O（n）来实现（比如set的底层是红黑树，所以如果使用std::lower_bound的话，就等价于从头再找了...）
- 所以，如果能够使用特化版的算法，就使用特化版的，避免低效



- lower_bound在stl中的实现

- ```cpp
  template <class ForwardIterator, class T>
    ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val)
  {
    ForwardIterator it;
    iterator_traits<ForwardIterator>::difference_type count, step;
    count = distance(first,last);
    while (count>0)
    {
      it = first; step=count/2; advance (it,step);
      if (*it < val) {                 // or: if (comp(*it,val)), for version (2)
        first  = ++it;
        count -= step+1;
      }
      else count = step;
    }
    return first;
  }
  
  //简化版
  count = last - start;
  while (count > 0) {
      step = count/2;
      int* it = first + step;
      if (*it < target) {
          count = count - (step + 1);
          first = it + 1;
      } else {
          count=step;
      }
  }
  return first;
  ```



- upper_bound

- ```cpp
  template <class ForwardIterator, class T>
    ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val)
  {
    ForwardIterator it;
    iterator_traits<ForwardIterator>::difference_type count, step;
    count = std::distance(first,last);
    while (count>0)
    {
      it = first; step=count/2; std::advance (it,step);
      if (!(val<*it))                 // or: if (!comp(val,*it)), for version (2)
        { first=++it; count-=step+1;  }
      else count=step;
    }
    return first;
  }
  
  //简化版
  lo = 0, hi = n;
          // upper_bound
          while (lo < hi) {
              int mid = (lo + hi) / 2;
              if (A[mid] <= target) {
                  lo = mid + 1;
              } else {
                  hi = mid;
              }
          }
          return lo;
  ```





sort的实现

- ```cpp
  #include <algorithm>
  #include <iterator>
  #include <forward_list>
   
  template <class ForwardIt>
  void quicksort(ForwardIt first, ForwardIt last)
  {
      if(first == last) return;
      auto pivot = *std::next(first, std::distance(first,last)/2);
      ForwardIt middle1 = std::partition(first, last, 
                           [pivot](const auto& em){ return em < pivot; });
      ForwardIt middle2 = std::partition(middle1, last, 
                           [pivot](const auto& em){ return !(pivot < em); });
      quicksort(first, middle1);
      quicksort(middle2, last);
  }
  ```

- https://zhuanlan.zhihu.com/p/364361964





tie函数

```cpp
tie(t1, t2) = t2, t1; // 不能够交换t1和t2的值（这里最后都会变成t1）
// 因为左边其实本质上是左值引用，他会先给t1f
```

- 但是适合批量的赋值

- ```cpp
  dp1 = dp2;
  dp2 = dp3;
  
  // 等价于
  tie(dp1, dp2) = {dp2, dp3};
  ```

- 