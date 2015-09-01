#include <cstring>

class IntMaxHeap {
public:
  typedef int(*compare_func)(int *, int *);
  IntMaxHeap(int max_size=10): 
    size_(0), max_size_(max_size), heap_(NULL), compare(NULL) {}
  //  IntMaxHeap(int *a, int num);
  ~IntMaxHeap();
  bool init();//Must call init() before use;
  bool insert(int *new_elem);
  inline int *peek() {return heap_[1];}
  int *pop();
private:
  int **heap_;
  int max_size_;
  int size_;
  compare_func compare;
  bool reallocate();
  inline int left_child(int i) {return i<<1;}
  inline int right_child(int i) {return (i<<1) + 1;}
  inline bool in_bounds(int i) {return i<=size_;}
  void heapify_node(int i);
  void heapify();
};

IntMaxHeap::~IntMaxHeap() {
  delete[] heap_;
}

bool IntMaxHeap::init() {
  if(max_size_ < 10)
    max_size_ = 10;
  heap_ = new int*[max_size_+1];
  if(!heap_)
    return false;  
  size_ = 0;
  //will keep heap_[0] empty to simplify parent/child index relations
  return true;
}

bool IntMaxHeap::reallocate() {
  int new_max = (max_size_ << 1); 
  int **tmp = new int*[new_max+1];
  if(!tmp)
    return false;//error
  std::memcpy(tmp, heap_, (size_+1)*sizeof(int*));
  delete[] heap_;
  heap_ = tmp;
  max_size_ = new_max;
  return true;
}

inline void swap(int **a, int **b) {
  int *tmp = *a;
  *a = *b;
  *b = tmp;
} 

void IntMaxHeap::heapify_node(int i) {
  if(i > max_size_)
    return;
  int largest = i;
  int left = left_child(i);
  if(in_bounds(left) && *heap_[left] > *heap_[i])
    largest = left;
  int right = right_child(i);
  if(in_bounds(right) && *heap_[right] > *heap_[i])
    largest = right;
  if(largest != i) {
    swap(heap_+i, heap_+largest);
    heapify_node(largest);
  }
}

void IntMaxHeap::heapify() {
  for(int i=(size_>>1); i>0; --i)
    heapify_node(i);
}

bool IntMaxHeap::insert(int *new_elem) {
  if(size_ == max_size_ && !reallocate())
    return false;
  heap_[++size_] = new_elem;
  heapify();
  return true;
}

int *IntMaxHeap::pop() {
  if(size_==0)
    return NULL;

  int *result = heap_[1];//remember, heap_[0] is not used;
  std::memcpy(heap_+1,heap_+2, sizeof(int*)*(size_-1));
  --size_;
  heapify();
  return result;
}
