#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <iostream>
#include <sstream>

using namespace std;

int main (int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Enter a valid number of arguments" << endl;
	}
	ifstream ifile;
	ifile.open(argv[1]);
	vector <string> users; //stores all the unique users
	vector <string> hash;  //stores all the hashtags
	vector <string> data;  //stores all the tweets
	int s = 0;
	string dummy;
	while (!ifile.fail()) {
		data.push_back(dummy);
		getline(ifile, dummy);
		if (dummy == "") {
			continue;
		} 
		else {
			data[s] = dummy;
			s++;
			dummy.clear();
		}
	}
	dummy.clear();
	const int twt_cnt = s;
	int u_ct = 0; //keeps track of unique users
	int h_ct = 0; //keeps track of unique hashtags
	string temp = "";
	string place = "";

	for (int i = 0; i < twt_cnt; i++) {
    	place = data[i];
    	stringstream ss(place);
    	for (unsigned int q = 0; q < place.length(); q++) 
    	{
    	    if (place[q] == '#') 
    	    {
    	    	for (unsigned int v = q+1; v != place.length() && place[v]!= ' '; v++) { //place[v] == ' ';
    	    		temp+=place[v];
   		    	}
    	    
    	        hash.push_back(dummy);
    	        hash[h_ct] = temp;
    	        h_ct++;
    	        temp = "";
    	    }
    	    else if (place[q] == '@') 
    	    {
    	    	for (unsigned int v = q+1; v != place.length() && place[v]!= ' '; v++) {		//!isblank(place[v])
    	    		temp+=place[v];
   		    	}
   		    	
    	        users.push_back(dummy);
    	        users[u_ct] = temp;
    	        u_ct++;
    	        temp = "";
    	    }
		}
	}

	for (unsigned int i = 0; i < users.size() - 1; i++) // delete duplicate values
	{
	    for (unsigned int j = i; j < users.size() -1; j++)
	    {

	        if ( users[i] == users[j+1])
	        {
	        	
	            users[j+1].erase();
	            u_ct--;    
	        }
	    }
	}
	
	for (unsigned int i = 0; i < hash.size() -1; i++ ) // delete duplicate values
	{
	    for (unsigned int j = i; j < hash.size() -1; j++)
	    {
	    	
	        if (hash[i] == hash[j+1]) 
	        {
	        	
	            hash[j+1].erase();   
	            h_ct--; 
	        }
	    }
	}    

	cout << "1. Number of tweets=" << twt_cnt << endl;
	cout << "2. Unique users" << endl;
	for ( int i = 0; i < u_ct;++i)
	{
		cout << users[i] << endl;
	}
    cout << "3. Unique hashtags" << endl;
	for ( int i = 0; i < h_ct;++i)
	{
		cout << hash[i] << endl;
	}
}
