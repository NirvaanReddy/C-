#ifndef DEQUE_H
#define DEQUE_H
#include <stdexcept>
#include <cstdlib>

/**
 * Implements a templated, array-based, 
 * double-ended queue.
 *
 * The Deque should allow for amortized O(1) 
 * insertion and removal from either end. 
 * It should dynamically resize, when it becomes
 * full, but never needs to shrink.  
 *
 * It should use a circular buffer approach
 * by tracking the "front" and "back" location.
 *
 */


template <typename T>
class Deque
{
 public:
  /* START - DO NOT CHANGE ANY OF THESE LINES */
  /**
   *  Default constructor 
   *   Create an array of size 1 by default
   */
  Deque();

  /**
   *  Default constructor 
   *   Create an array of the given capacity.
   */
  Deque(size_t capacity);

  /**
   *  Destructor
   */
  ~Deque();

  /**
   *  Returns the number of elements in the Deque. 
   *   - Must run in O(1)
   */
  size_t size() const;

  /**
   *  returns true if the deque is empty
   *   - Must run in O(1)
   */
  bool empty() const;

  /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
  T& operator[](size_t i);

  /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
  T const & operator[](size_t i) const;

  /**
   *  Inserts a new item at the back of the
   *  Deque
   *   - Must run in amortized O(1)
   */
  void push_back(const T& item);

  /**
   *  Inserts a new item at the front of the
   *  Deque
   *   - Must run in amortized O(1)
   */
  void push_front(const T& item);

  /**
   *  Removes the back item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
  void pop_back();

  /**
   *  Removes the front item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
  void pop_front();
  /* END - DO NOT CHANGE ANY OF THESE LINES */
 private:
  /* Add data members and private helper 
   * functions below 
   */
  size_t d_cnt;
  size_t d_sz;
  size_t front;
  size_t back;
  void resize();
  T* dq;
  T* dq_temp;
};

/* Implement each Deque<T> member function below 
 * taking care to meet the runtime requirements
 */
//array to store the data, keep track of indices of front/back
  template <typename T> 
  Deque<T>::Deque() {
    dq = new T [1];
    d_sz = 1;
    d_cnt = 0;
    front = 0;
    back = 0;
  }
  
  template <typename T> 
  Deque<T>::Deque(size_t capacity) {
    d_sz = capacity;
    dq = new T [capacity];
    d_cnt = 0;
    front = 0;
    back = 0;
  }  

  template <typename T> 
  Deque<T>::~Deque() {
    delete [] dq;
    delete [] dq_temp;
  }
  template <typename T> 
  size_t Deque<T>::size() const {
    return d_cnt;
  }

  template <typename T> 
  bool Deque<T>::empty() const {
    if (d_cnt == 0) {
      return true;
    }
    else {
      return false;
    }
  }

  template <typename T> 
  T& Deque<T>::operator[](size_t i) {
    if (i >=d_sz || i < 0) {
      throw std::out_of_range("Index is out of range"); 
    }
    else 
      if (front == 0){
        return dq[i]; //return dq[i-1];
      }
      else {
        return dq[((front+i)%d_sz)];
      }
  }

  template <typename T> 
  T const & Deque<T>::operator[](const size_t i) const {
    if (i >=d_sz || i < 0) {
      throw std::out_of_range("Index is out of range"); 
    }
    else {
      if (front == 0){
        return dq[i]; //return dq[i-1];
      }
      else {
        return dq[((front+i)%d_sz)];
      }
    }
  }

  template <typename T> 
  void Deque<T>::push_back(const T& item) {
    if (d_cnt == d_sz){
      resize();
    }
    dq[d_cnt] = item;
    if (((back+1)%d_sz) == 0) back = d_sz;
    else  back = (back+1)%d_sz;
    d_cnt++;
  }

  template <typename T> 
  void Deque<T>::push_front(const T& item) {
    if (d_sz == d_cnt){
      resize();
    }
    if (front == 0){
      front = d_sz-1;
    }
    else {
      front--;
    }
    d_cnt++;
    dq[front] = item;  
  }

  template <typename T> 
  void Deque<T>::pop_back() {
    back--;
    d_cnt--;
  }

  template <typename T> 
  void Deque<T>::pop_front() {
    if (front == (d_sz-1)) {
      front = 0;
      d_cnt--;
    }
    else {
      front++;
      d_cnt--;
    }
  }

  template <typename T>
  void Deque<T>::resize() {
    if (d_cnt == d_sz){
      d_sz *= 2;
      dq_temp = new T[d_sz];
      for (unsigned int i = 0; i < d_sz; i++) {
        dq_temp[i] = 0;
      }
      for (unsigned int i = front; i < back; i = (i+1)%d_sz) {
        dq_temp[i] = dq[i];
      }
      dq = dq_temp;
    }
  }

#endif
