#include "rem_dup_lib.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

int main (int argc, char* argv[]) {
	ifstream ifile;
	ifile.open(argv[1]);
	ofstream ofile;
	ofile.open(argv[2]);
	string re = "";
	getline(ifile,re);
	stringstream ss (re);
	vector <int> holder;
	int r;
	while (ss >>r) {
		holder.push_back(r);
	}
	Item* head1 = new Item(holder[holder.size()-1],nullptr);
	for (int i = holder.size()-2; i >= 0; i--){
		Item* temp = new Item(holder[i],head1);
		head1 = temp;
	}
	string h = "";
	getline(ifile,h);
	stringstream s1 (h);
	vector <int> line2;
	while (s1 >> r) {
		line2.push_back(r);
	}
	Item* head2 = new Item(line2[line2.size()-1],nullptr);
	for (int i = line2.size()-2; i >= 0; i--){
		Item* rec = new Item(line2[i],head2);
		head2 = rec;
	}

	removeConsecutive(head1);
	Item* head3 = concatenate(head1,head2);
	while (head3 != nullptr) {
		ofile << head3 -> val << " ";
		head3 = head3-> next;	
	}	
	ofile << endl;

	while (head1 != nullptr) {
		Item* temp = head1 -> next;
		delete head1;
		head1 = temp;
	}	
	while (head2 != nullptr) {
		Item* temp = head2 -> next;
		delete head2;
		head2 = temp;
	}
	delete [] head1;
	delete [] head2;
	ifile.close();
	ofile.close();
}