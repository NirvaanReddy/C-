#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> storage;
  int effsize;
  int child_size;
  bool minHeap;
  PComparator c;
  void TrickleUp(int loc);
  void heapify(int loc);
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  child_size = m;
  effsize = 0;
  }
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){
  
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int loc){
  if (child_size*loc+1 >= effsize) {
    return;
  }
  int smallestChild = loc*child_size+1;
  for(int i = 1; i < child_size; i++){
    if (smallestChild+i < effsize){
      int rightChild = smallestChild+i;
      if (c(storage[rightChild],storage[smallestChild])){
        smallestChild = rightChild;
      }
  }
  }
  if (c(storage[smallestChild], storage[loc])){
    std::swap(storage[loc],storage[smallestChild]);
    heapify(smallestChild);
  }
}

//helper function for push
template <typename T, typename PComparator>
void Heap<T,PComparator>::TrickleUp(int loc){
  int parent = (loc-1) / child_size;
  while (parent >= 0 && c(storage[loc],storage[parent])){
    std::swap(storage[loc],storage[parent]);
    loc = parent;
    parent = (loc -1) / child_size;
  } 
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  if (effsize == 0){
    return true;
  }
  else {return false;}
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  storage.push_back(item);
  TrickleUp(effsize);
  effsize++;
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return storage[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  std::swap(storage[0],storage[effsize-1]);
  effsize--;
  heapify(0);
}


#endif

