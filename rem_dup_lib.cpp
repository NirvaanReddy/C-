#include "rem_dup_lib.h"
#include <iostream>
using namespace std;

// Deletes consecutive equal values from the list
void removeConsecutive(Item* head){
	if (head == nullptr) return;
	else if (head -> next == nullptr){	//base case
		return;
	}
	else {
		if (head -> next -> val == head -> val) {
			Item* temp = head -> next -> next;
			delete head->next;
			head -> next = temp; //if they the following number is the same
			removeConsecutive(head);
		}
		else {
			removeConsecutive(head->next); // if the following number is not 
		}
	}
}

// Makes a copy of the items in the head1 and head2 lists
// concatenating the new head2 items to the end of the
// new head1 list items.
Item* concatenate(Item* head1, Item* head2){
	if (head1 == nullptr && head2 != nullptr) return head2;
	else if (head1 != nullptr && head2 == nullptr) return head1;
	else if (head1 == nullptr && head2 == nullptr) return nullptr; 
	else {
		Item* sum = new Item (head1 -> val,nullptr);
		helper(head1->next,head2,sum);
		return sum; 
	}
	// if (head1 -> next == nullptr) {
	// 	head1 -> next = head2;
	// 	return head1;
	// }
	// else {
	// 	return concatenate(head1->next, head2);

	// 	//make a deep copy
	// }

	/*
	else {
		Item* sum;
		helper(head1,head2,sum);
	}
	
	*/
}


Item* helper(Item* head1, Item* head2, Item* sum){
	if (head1 == nullptr && head2 == nullptr){
		return sum;
	}
	else if (head1 == nullptr) {
		//add head 2 to the end of sum
		Item* a = new Item(head2->val,nullptr);
		sum->next = a;
		return helper(head1, head2->next, sum->next);
	}
	else {
		Item* a = new Item(head1->val,nullptr);
		sum->next = a;
		return helper(head1->next, head2, sum->next);
	}
}

	/*
	else {
		sum->next = head1;
		return helper(head1->next,head2,sum->next);
	}
	*/
