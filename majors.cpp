#include "setops.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

/*I worked with CP Julie to fix an error that would only appear on my end. The error was when I ran my code with majors1.cmd, I would always get 
another BUAD printed after EE BUAD which would duplicate the previous BUAD set. This would only happen on my laptop, and when CP Julie ran the same code
on her laptop she would get everything perfectly. If there any questions, please let me know.
*/

int main(int argc, char* argv[]) {
	if (argc < 4) {
		std::cerr << "Invalid number of arguments entered" << endl;
		return 0;
	}
	string dummy = "";
	ifstream ifile;
	ifstream rfile;
	set<string> majors;
	ifile.open(argv[1]);
	if (ifile.fail()) std::cerr << "Invalid input file" << endl;
	rfile.open(argv[2]);
	if (rfile.fail()) std::cerr << "Invalid input file" << endl;
	ofstream ofile;
	ofile.open(argv[3]);
	if (ofile.fail()) std::cerr << "Invalid output file" << endl;
	std::map<string,set<string>> map;
	std::vector<std::string> dat;
	std::set<string> temp;
	unsigned int p_cnt = 0; 
	unsigned int m_cnt = 0;
	while (!ifile.fail()) {
		dat.push_back(dummy);
		getline(ifile,dummy);
		dat[p_cnt] = dummy; 
		p_cnt++;
		dummy = "";
	}
	unsigned int c;
	string people;
	string maj;
	for (unsigned int i = 0; i < dat.size() -1; i++) {
		people = "";
		maj = "";
		temp.clear();
		dummy = dat[i];
		for (c = 0; dummy[c]!= ','; c++) {
			if (isalpha(dummy[c]) || isalpha(dummy[c+1]) || dummy[c] == '.') {
				people+=dummy[c]; 
			}
		}
		c++;
		temp.insert(people);
		string ae = dummy.substr(c);
		stringstream stemp(ae);
		ae.clear();
		while (stemp >> maj) {
			for (unsigned int j = 0; j < maj.length(); j++) {
				maj[j] = toupper(maj[j]);	
			}			
			if (maj.empty()) {
			}
			else  {
				if (map.find(maj) != map.end()) {
					//map.find(maj) -> second.insert(people);
					map[maj].insert(people);
				}
				else {
					//map.insert(make_pair(maj,temp));
					map[maj] = temp;
					maj = "";
				}	
			}
		}

		
	}
	std::map<std::string, std::set<string>>::iterator it;
	std::set<std::string>::iterator te;
	vector <string> ma;
	string tt;
	int cntr = 0;
	while (!rfile.fail()) {
		//majors.clear();
		ma.clear();
		getline(rfile,tt);
		stringstream st(tt);
		tt.clear();
		while (st >> tt) {
			for (unsigned int ge = 0; ge < tt.length(); ge++) {
				tt[ge] = toupper(tt[ge]);
			}
			ma.push_back(tt);
		//	majors.insert(tt);
	
		}
		set <string> result;
		for (unsigned int i = 0; i < ma.size(); i++) {
			ofile << ma[i];
			if (i == ma.size() -1) {
				ofile << endl;
			}
			else {
				ofile << " ";
			}
			it = map.find(ma[i]);
			if (it != map.end()) {
				m_cnt = it -> second.size();
				if (m_cnt != 0) {
					set <string> temp_ = map.find(ma[i]) -> second;  
					if (i == 0) result = temp_;
					else result = temp_ & result;
				}
			}
		}
		  for (te = result.begin(); te!= result.end(); ++te) { 
		  	ofile << (*te) << endl;
		  } 					
			ofile << endl;
			cntr++;
			st.clear();
	}
	ifile.close();
	rfile.close();
	ofile.close();
	return 0;
}


