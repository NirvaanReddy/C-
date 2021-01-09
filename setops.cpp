#include "setops.h"
using namespace std;


// Computes the intersection of s1 and s2
std::set<Tweet*> operator&(const std::set<Tweet*>& s1, const std::set<Tweet*>& s2) 
{
	std::set<Tweet*> block;
	std::set<Tweet*>::iterator ss = s1.begin();
	std::set<Tweet*>::iterator sr = s2.begin();
	while (ss != s1.end()) {
		if ((*ss) == (*sr)) {
			block.insert((*ss));
		}
		++sr;
		if (sr == s2.end()) {
			sr = s2.begin();
			++ss;
		}
	}
	return block;
}

// Computes the union of s1 and s2
std::set<Tweet*> operator|(const std::set<Tweet*>& s1, const std::set<Tweet*>& s2)
{
	std::set<Tweet*> block;
	std::set<Tweet*>::iterator ss = s1.begin();
	std::set<Tweet*>::iterator sr = s2.begin();
	while (ss != s1.end()) {
		block.insert((*ss));
		block.insert((*sr));
		++sr;
		if (sr == s2.end()) {
			sr = s2.begin();
			++ss;
		}
	}
	return block;
}

// Computes the difference of s1 - s2
std::set<Tweet*> operator-(const std::set<Tweet*>& s1, const std::set<Tweet*>& s2)
{
	std::set<Tweet*> block;
	std::set<Tweet*>::iterator ss = s1.begin();
	std::set<Tweet*>::iterator sr = s2.begin();
	while (ss != s1.end()) {
		if ((*ss) == (*sr)) {
			sr = s2.begin();
			++ss;
		}
		++sr;
		if (sr == s2.end()) {
			sr = s2.begin();
			block.insert((*ss));
			++ss;
		}
	}
	return block;
}