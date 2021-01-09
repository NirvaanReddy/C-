#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "deque.h"

/** 
 * Your Stack<T> class must be templated and
 * privately inherit from Deque<T>. All
 * operations must run in O(1).
 *
 * Both pop() and top() must throw std::underflow_error
 * if the stack is empty.
 */

template <typename T>
class Stack : private Deque<T>
{
public:
  Stack();
  ~Stack();
  size_t size() const;
  bool empty() const;
  void push(const T& item);
  void pop();
  T const & top() const;
private:
	void resize();
	size_t d_cnt;
	size_t d_sz;
	T* dq;
	T* dq_temp;
	size_t front;
	size_t back;
  // size_t size() const;
  // bool empty() const;
  // T& operator[](size_t i);
  // T const & operator[](size_t i) const;
  // void push_back(const T& item);
  // void push_front(const T& item);
  // void pop_back();
  // void pop_front();
};


template <typename T>
Stack<T>::Stack(){
	dq = new T [10];
	d_sz = 10;
	d_cnt = 0;
}

template <typename T>
Stack<T>::~Stack(){
	delete [] dq;
	delete [] dq_temp;
}

template <typename T>
size_t Stack<T>::size() const{
	return d_sz;
}

template <typename T>
bool Stack<T>::empty() const{
	if (d_cnt == 0) return true;
	else return false;
}

template <typename T>
void Stack<T>::push(const T& item){
	Deque<T>::push_front(item);
}

template <typename T>
void Stack<T>::pop(){
	if (empty()) {
		throw std::underflow_error("Invalid operation.");
	}
	else {
		Deque<T>::pop_front();
	}
}

template <typename T>
T const& Stack<T>::top() const {
	return dq[0];
}

template <typename T>
  void Stack<T>::resize() {
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
