#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

template <typename T>
struct Comparator {
	bool operator()(const T& left, const T& right){
		return left < right;
	}
};

template <typename T, typename Comparator >
void heapify(std::vector<T>& data, size_t loc, size_t effsize, Comparator& c);

// template <typename T, typename Comparator >
// void hsort(std::vector<T>& data, Comparator c = Comparator());

template <typename T, typename Comparator >							//if(c(data[i], data[smallestChild])){       smallestChild = i;     } 	
void hsort(std::vector<T>& data, Comparator c = Comparator()){
	if (data.size() == 0){
		return;
	}
	for (int last = data.size()/2; last >=0;last--){
		heapify(data,last,data.size(),c);
	}
	
	for (int i = data.size()-1; i >=0; i--){
		std::swap(data[0],data[i]);
		heapify(data,0,i,c);						
		//calls heapify i times	(id est, however big the vector is)									
	}
	int last = data.size()-1;
	for (int start = 0; start <=last;start++){
		std::swap(data[last],data[start]);
		last--;
	}
}  
//{3,7,120,20,60,4}
//c(data[0], data[1]); //data[1] = 3, data[0] = 4, 
//child - 1 / 2 = parent
//parent*2 + 1 = child	


template <typename T, typename Comparator >
void heapify(std::vector<T>& data, size_t loc, size_t effsize, Comparator& c){
		if (2*loc+1 >= effsize) {
			return;
		}
		size_t smallestChild = 2*loc+1;
		if ((2*loc+2) < effsize){
			size_t rightChild = 2*loc+2;
			if (c(data[rightChild],data[smallestChild])){
				smallestChild = rightChild;
			}
		}
		if (c(data[smallestChild],data[loc])){
			std::swap(data[loc],data[smallestChild]);
			heapify(data,smallestChild,effsize,c);
		}
}