#include <stack>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "Invalid number of arguments" << endl;
	}

	ifstream ifile;
	ofstream ofile;
	ifile.open(argv[1]);
	ofile.open(argv[2]);
	string read_in = "";
	getline(ifile,read_in);
	stringstream ss (read_in);
	int placeholder;
	stack <int> laundry;
	while (ss >> placeholder) {
		if (placeholder < 1) {
			laundry.push(placeholder);
		}
		else {
			for (int i = 0; i < placeholder; i++){
				if (laundry.empty()) {
					break;
				}
				int a = laundry.top();
				laundry.pop();
				if (a == 0) {
					ofile << "black ";
				}
				else ofile << "white ";
			}
			ofile << endl;
		}
	}
}