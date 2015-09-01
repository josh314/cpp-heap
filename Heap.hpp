#include <cstring>

//TODO:check this shit
//TODO: add logic for setting and using compare_func 
//TODO:add optional ownership?
//TODO: implement update_key()
template<typename T>
class Heap {
public:
  Heap(int max_size=10): 
    size_(0), max_size_(max_size), heap_(NULL), compare_(NULL) {}
  //  Heap(int *a, int num);
  ~Heap();
  bool init();//Must call init() before use;
  bool insert(int *new_elem);
  inline T *peek() {return heap_[1];}
  T *pop();
  bool update_key(); //any args? Is this just heapify_node()?
private:
  typedef bool (*compare_func)(T *, T *);
  T **heap_;
  int max_size_;
  int size_;
  compare_func compare_; 
  bool reallocate();
  inline int left_child(int i) {return i<<1;}
  inline int right_child(int i) {return (i<<1) + 1;}
  inline bool in_bounds(int i) {return i<=size_;}
  inline bool default_compare(T t1, T t2) {return t1 > t2;}//defaults to a max heap. must have operator> defined 
  inline void swap(T **a, T **b) {T *tmp = *a;*a = *b;*b = tmp;} 
  void heapify_node(int i);
  void heapify();
};

template<typename T>
Heap<T>::~Heap() {
  delete[] heap_;
}

template<typename T>
bool Heap<T>::init() {
  if(max_size_ < 10)
    max_size_ = 10;
  heap_ = new T*[max_size_+1];
  if(!heap_)
    return false;
  compare_ = default_compare;
  size_ = 0;
  //will keep heap_[0] empty to simplify parent/child index relations
  return true;
}

template<typename T>
bool Heap<T>::reallocate() {
  int new_max = (max_size_ << 1); 
  T **tmp = new int*[new_max+1];
  if(!tmp)
    return false;//error
  std::memcpy(tmp, heap_, (size_+1)*sizeof(T*));
  delete[] heap_;
  heap_ = tmp;
  max_size_ = new_max;
  return true;
}

template<typename T>
void Heap<T>::heapify_node(int i) {
  if(i > max_size_)
    return;
  int top_priority = i;
  int left = left_child(i);
  if(in_bounds(left) && compare_(*heap_[left],*heap_[i]))
    top_priority = left;
  int right = right_child(i);
  if(in_bounds(right) && compare_(*heap_[right],*heap_[i]))
    top_priority = right;
  if(top_priority != i) {
    swap(heap_+i, heap_+top_priority);
    heapify_node(top_priority);
  }
}

template<typename T>
void Heap<T>::heapify() {
  for(int i=(size_>>1); i>0; --i)
    heapify_node(i);
}

template<typename T>
bool Heap<T>::insert(int *new_elem) {
  if(size_ == max_size_ && !reallocate())
    return false;
  heap_[++size_] = new_elem;
  heapify();
  return true;
}

template<typename T>
T *Heap<T>::pop() {
  if(size_==0)
    return NULL;

  T *result = heap_[1];//remember, heap_[0] is not used;
  std::memcpy(heap_+1,heap_+2, sizeof(T*)*(size_-1));
  --size_;
  heapify();
  return result;
}
