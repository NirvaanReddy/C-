#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void readWords(char* filename, vector<vector<string> >& words);

// client interface
void generateSentences(vector<vector<string> >& words, ofstream& ofile);

// recursive helper function
void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences);

void readWords(char* filename,vector<vector<string> >& words)
{
	vector <string> push;
	for (int i = 0; i < 4; i++){
		words.push_back(push);
	}
	ifstream ifile;
	ifile.open(filename);
	string temp = "";
	for (int i = 0; i < 4;i++) {
		getline(ifile,temp);
		stringstream ss(temp);
		temp.clear();
  		while (ss >> temp){
		 	words[i].push_back(temp);
		 	temp.clear();
		}
	}
}

void generateSentences(vector<vector<string> >& words, ofstream& ofile)
{
  int numSentences = 0;
  genHelper(words,ofile, 0, "",numSentences);
  ofile << numSentences << " sentences.";
}

void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences)
{
	 if (currentOption == 4){
	 	ofile << "The";
	 	ofile << sentence;
 		ofile << "." << endl;
		numSentences++;
	 	return;
	 } 

	else if (currentOption == 0){
		currentOption++;
		for (unsigned int i = 0; i < words[0].size();++i){	
			genHelper(words,ofile,currentOption,sentence + " " + words[0][i], numSentences);
		}
		genHelper(words,ofile, currentOption,sentence,numSentences);
	}
	else if (currentOption == 1){
		currentOption++;
		for (unsigned int i = 0; i < words[1].size();++i){	
			genHelper(words,ofile,currentOption,sentence + " " + words[1][i], numSentences);
		}
	}
	else if (currentOption == 2){
		currentOption++;
		for (unsigned int i = 0; i < words[2].size();++i){	
			genHelper(words,ofile,currentOption,sentence + " " + words[2][i], numSentences);
		}
	}
	else if (currentOption == 3){
		currentOption++;
		for (unsigned int i = 0; i < words[3].size();++i){	
			genHelper(words,ofile,currentOption,sentence + " " + words[3][i], numSentences);
		}
		genHelper(words,ofile,currentOption,sentence, numSentences);
	}
}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Usage ./sentences input_file output_file" << endl;
  }
  vector<vector<string> > words;
  // Parse the file
  readWords(argv[1], words);

  // Check the status of parsing
  
  if(words.size() < 4){
    cerr << "Input file requires 4 lines of words" << endl;
    return 1;
  }

  // Open the output file
  ofstream ofile(argv[2]);
 
  // generate all the sentence options writing them to ofile
  generateSentences(words, ofile);

  ofile.close();

  return 0;
}
