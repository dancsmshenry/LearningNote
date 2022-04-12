https://zhuanlan.zhihu.com/p/364361964



- cpp的快排实现

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

- 