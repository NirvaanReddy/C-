#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char* argv[]) {
	if (argc < 3) {
		cout << "Enter the valid number of arguments." << endl;
	}
	ofstream ofile;
	ifstream ifile;
	ifile.open(argv[1]);
	if (ifile.fail()) {
		ofile << 0;
		return 0;
	}
	ofile.open(argv[2]);
	int cnt;
	ifile >> cnt;
	if (ifile.fail()) {
		ofile << 0;
		ofile.close();
		return 0;
	}
	if (cnt == 0) {
		ofile << 0;
		ofile.close();
		return 0;
	} 

	int* data = new int [cnt];
	for (int i = 0; i < cnt; i++) {
		ifile >> data[i];
	}

	for (int a = 0; a < cnt; a++) {
		ofile << (data[a] + data[cnt-1]) << endl;
		cnt--;
	}
	
	ifile.close();
	ofile.close();
	delete [] data;
	return 0;
}