#include "deque.h"
#include "gtest/gtest.h"
#include <iostream>
using namespace std;

class Deque_Test : public testing::Test {
protected:
	Deque_Test(){

	}
	virtual ~Deque_Test(){

	}
	virtual void SetUp(){
		deq.push_back(0);
		deq.push_back(1);
		deq.push_back(2);
		deq.push_front(20);
	}

	virtual void TearDown(){

	}

	Deque<int> deq = Deque<int>(3); 
};

TEST_F(Deque_Test,EmptyTest){
	EXPECT_EQ(false,deq.empty());
}

TEST_F(Deque_Test,PopTest){
	deq.pop_front();
	EXPECT_EQ(3,deq.size());
	deq.pop_back();
	EXPECT_EQ(2,deq.size());
	}

TEST_F(Deque_Test,GetNominal){
	EXPECT_EQ(20,deq[0]);
}

TEST_F(Deque_Test,NewSize){
	deq.push_front(3);
	EXPECT_EQ(5,deq.size());
}