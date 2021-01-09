#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <iostream>

using namespace std;


int isValid(map<int,int> &variables, map<int,vector<int>> &clauses){ //1 = solution, 0 = no solution, -1 = undetermined
	vector <int> v;
	for (map<int,vector<int>>::iterator it = clauses.begin(); it != clauses.end(); ++it){
		bool b = true;
		bool r = true;
		vector <int> tempp = it -> second; // 1 2 -4 0   ----- 3 0 ----- -1 -2 0
		for (unsigned int i = 0; i < tempp.size(); i++){
			if (tempp[i] == 0 && r && b){
				return 0; 
			}
			else if (tempp[i] == 0 && !r && b){
				return -1;
			}
			int state = variables.find(tempp[i]) -> second; //this will be the state of the variable (i.e, 1,0,-1).
			if (state == -1){ //if the number is unassigned go to the next one
				r = false;
				continue;
			}
			else if (state == 0 && tempp[i] < 0){
				v.push_back(1); 
				b = false; //will stop the for loop (state is false and number is negative)
			}
			else if (state == 1 && tempp[i] > 0){
				v.push_back(1);
				b = false; //will stop the for loop if a solution is found (state is true and number is positive)
			}
		}
	}
	return 1;
}

bool solve_helper(map<int,int> &variables,map<int,vector<int>> &clauses, const int num_cl, const int num_vars, vector <int> &cl_results, int &currN){
	if (currN > num_vars){
		return false;
	}
	else {
		int state = variables.find(currN) -> second; //1, -1; //handle the case when a variable is assigned vs unassigned
		if (state == -1){													//consider the idea of 
			variables.find(currN) -> second = 0; //false
			int s = isValid(variables,clauses);
			if (s == 1){
				return true;
			}
			else if (s == 0 && currN == 1){
				return false;
			}
			else if (s == 0){
				if (currN == 1){
					solve_helper(variables,clauses,num_cl,num_vars,cl_results,currN);
				}
				else {
					solve_helper(variables,clauses,num_cl,num_vars,cl_results,--currN);
				}
			}
			else {
				solve_helper(variables,clauses,num_cl,num_vars,cl_results,++currN);
			}
			if (isValid(variables,clauses) != 1){
				variables.find(currN) -> second = -1; //false
			}
			if (isValid(variables,clauses) == 1){
				return true;
			}
		}
		else if (state == 0){
			variables.find(currN) -> second = 1; //false
			int s = isValid(variables,clauses);
			if (s == 1){
				return true;
			}
			else if (s == 0 && currN == 1){
				return false;
			}
			else if (s == 0){
				if (currN == 1){
					solve_helper(variables,clauses,num_cl,num_vars,cl_results,currN);
				}
				else {
					solve_helper(variables,clauses,num_cl,num_vars,cl_results,--currN);
				}
			}

			else {
				solve_helper(variables,clauses,num_cl,num_vars,cl_results,++currN);
			}
			if (isValid(variables,clauses) != 1){
				variables.find(currN) -> second = -1; //false
			}
			if (isValid(variables,clauses) == 1){
				return true;
			}
		}
		else if (state == 1){
			variables.find(currN) -> second = -1; //false
			int s = isValid(variables,clauses);
			if (s == 1){
				return true;
			}
			else if (s == 0 && currN == 1){
				return false;
			}
			else if (s == 0){
				if (currN == 1){
					solve_helper(variables,clauses,num_cl,num_vars,cl_results,currN);
				}
				else {
					solve_helper(variables,clauses,num_cl,num_vars,cl_results,--currN);
				}
			}
			else {
				solve_helper(variables,clauses,num_cl,num_vars,cl_results,++currN);
			}
			if (isValid(variables,clauses) != 1){
				variables.find(currN) -> second = -1; //false
			}
			if (isValid(variables,clauses) == 1){
				return true;
			}
		}
		solve_helper(variables,clauses, num_cl,num_vars,cl_results, currN);
	}
}

void solve(map<int,int> &variables,map<int,vector<int>> &clauses, const int num_cl, const int num_vars, ofstream& ofile){
	vector <int> cl_results;
	int currN = 1;
	solve_helper(variables,clauses,num_cl,num_vars, cl_results,currN);
	bool result = true;
	for (unsigned int i = 0; i < cl_results.size();i++){
		if (cl_results[i] == false){
			result = false;
			break;
		}
	}  
	if (result){
		int cnt = 1;
		for (map<int,int>::iterator ct = variables.begin();ct!=variables.end();++ct){
			if (ct -> second == -1){
			
			} 
			else {
				ofile << cnt << " = " << ct -> second << endl;
			}
			cnt++;
		}
	}
	else {
		ofile << "No solution" << endl;
	}
}


int main (int argc, char* argv[]){
	if (argc < 3){
		cerr << "Give an input & output file." << endl;
		return 0;
	}
	ifstream ifile;
	ifile.open(argv[1]);
	ofstream ofile;
	ofile.open(argv[2]);
	string temp = "";
	getline(ifile,temp);
	while (temp[0] == 'c'){
		getline(ifile,temp);
	}
	stringstream ss(temp);
	temp.clear();
	ss >> temp;
	temp.clear();
	ss >> temp;
	int num_vars = 0;
	int num_cl = 0;
	ss >> num_vars;
	ss >> num_cl;
	map <int,int> variables; //-1 = unassigned, 0 = false, 1 = true
	for (int i = 1; i <= num_vars; i++){
		variables.insert(make_pair(i,-1));
	}
	map <int,vector<int>> clauses;
	for (int i = 1; i <= num_cl; i++){
		temp.clear();
		getline(ifile,temp); 
		stringstream tr (temp);
		int copy;
		vector <int> temp_vec;
		while (tr >> copy){
			if (copy == 0){
				temp_vec.push_back(0);
				clauses.insert(make_pair(i,temp_vec));
			}
			temp_vec.push_back(copy);
		}
	}
	solve(variables, clauses, num_cl, num_vars, ofile);
	//deleting memory here 
}