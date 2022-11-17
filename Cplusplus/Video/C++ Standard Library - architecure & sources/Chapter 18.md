# 深入deque

- ```cpp
  template<class T, class Alloc = alloc, size_t BufSiz = 0>
  class deque {
      public:
          typedef T value_type;
          typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
      protected:
          typedef pointer* map_pointer;//T** 它的本质是指针指向指针
      protected:
          iterator start;
          iterator finish;
          map_pointer map;
          size_type map_size;
      public:
          iterator begin() { return start; }
          iterator end() { return finish; }
          size_type size() const {return finish - start; }
  };
  
  template<class T, class Ref, class Ptr, size_t BufSiz >
  struct _deque_iterator {
      typedef random_access_iterator_tag iterator_category;
      typedef T value_type;
      typedef Ptr pointer;
      typedef Ref reference;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef T** map_pointer;
      typedef _deque_iterator self;
  
      T* cur;
      T* first;
      T* last;
      map_pointer node;
  };
  ```