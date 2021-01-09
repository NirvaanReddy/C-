#include "twiteng.h"
#include "user.h"
#include "tweet.h"
#include "util.h"
#include <fstream>
#include <cctype>
#include "setops.h"
#include <cstring>

using namespace std;

TwitEng::TwitEng() {

}

TwitEng::~TwitEng() {
	for (map<string,User*>::iterator it = twi_users.begin();it != twi_users.end(); ++it){
		delete it -> second;
	}
	for (set<Tweet*>::iterator it = tew.begin();it != tew.end(); ++it){
		delete (*it);
	}
}

std::map<std::string, User*> TwitEng::usersSet() const {
	return twi_users;
}

std::map<std::string,std::set<Tweet*>> TwitEng::tags_set() const
{
	return tags;
}

   /**
   * Parses the Twitter database and populates internal structures
   * @param filename of the database file
   * @return true if there is an error, false if successful
   */
bool TwitEng:: parse(char* filename){
	string temp = "";
	string send = "";
	ifstream ifile;
	ifile.open(filename);
	if (ifile.fail()) return true;
	int cnt;
	ifile >> cnt;
	//parsing the User and who follows them 
	for (int x = 0; x < cnt+1; x++) {
		string r;
		getline(ifile,r);
		stringstream ss (r);
		//temp.clear();
		ss >> r;
		User* basic;
		if (twi_users.find(r) == twi_users.end()) {
			basic = new User(r);
			twi_users.insert(make_pair(r,basic));
		}
		else {
			basic = twi_users.find(r) -> second;
		}
		string local;
		//parsing the rest of the people 
		while (ss >> local) { 
			User* person_temp;
			if (twi_users.find(local) != twi_users.end()) {
				person_temp = twi_users.find(local) -> second;
			}
			else {
				person_temp = new User(local);
				twi_users.insert(make_pair(local,person_temp));
			}
			basic -> addFollowing(person_temp);
			local.clear();
		}
		twi_users.insert(make_pair(basic -> name(),basic));
	}
	//parsing the actual tweet
	while (getline(ifile,temp)) {
		if (!isblank(temp[0])) {
			DateTime dt;
			//cout << temp << endl;
			stringstream ss(temp);
			ss >> dt;
			string username;
			ss >> username; 
			temp.clear();
			getline(ss,temp);
			addTweet(username,dt,temp); //only gets here if there is no @'s in the tweet
			temp.clear();
			send.clear();
			
		}
	}
	return false;
} 


 /**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */
void TwitEng::addTweet(const std::string& username, const DateTime& time, const std::string& text){
	if (twi_users.find(username) == twi_users.end()){
		User* basic = new User (username);
		twi_users.insert(make_pair(username,basic));
	}
	User* person_temp = twi_users.find(username) -> second;
	string tea = "";
	Tweet* c = new Tweet();
	c -> addData(person_temp, time, text);
	tew.insert(c);
	for (unsigned int i = 0; i < text.length(); i++){ //ADDS HASHTAGS
		if (text[i] == '#') {
			for (int j = i+1; isalpha(text[j]); j++){
				tea+= text[j];
			}
			convLower(tea);
			c -> add_hash(tea);				//check to see if the hashtag has been used in previous tweets
			if (tags.find(tea) == tags.end()){
				set<Tweet*> cd;
				cd.insert(c);
				tags.insert(make_pair(tea,cd));
			}
			else {
				std::map<std::string, std::set<Tweet*>>::iterator it = tags.find(tea);
				it -> second.insert(c);
			}
			tea.clear();
		}
	}
	bool start = false, elsewhere = false;
	for (unsigned int s = 1; s < text.size();s++){
		if (text[s] == '@'){
			if (s == 1){
				start = true;
				break;
			}
			else {
				elsewhere = true;
				break;
			}
		}
	}
	if (elsewhere){ //if there is an @ in the middle of the tweet
		string ment_user = "";
		for (unsigned int i = 0; i < text.length();++i){
			if (text[i] == '@'){
				for (int j = i+1; j!= ' ';++j){
					ment_user+=text[j];
				}
			}
		}
		User* at;
		if (twi_users.find(ment_user) == twi_users.end()){
			at = new User(ment_user);
		}
		else {
			at = twi_users.find(ment_user) -> second; //at is the user being mentioned 
		}
		at -> addMention(c);
		person_temp -> addTweet(c);
	}
	else if (start){ //if there is an @ at the beginning of the street
		string ment_user = "";
		for (unsigned int i = 2; text[i]!= ' ';i++){
			ment_user+=text[i];
		}
		User* at;
		if (twi_users.find(ment_user) == twi_users.end()){
			at = new User(ment_user);
		}
		else {
			at = twi_users.find(ment_user) -> second; //at is the user being mentioned 
		}
		at -> addMention(c);
		if (at->checkFollowing(person_temp)){ //checks to see if the mentioned person (@Mark) is following the person who tweeted the tweet
			at->addTweet(c);//if the mentioned person does follow the person then add to the timeline
		}
		person_temp->addTweet(c);
		//checks who is following the Tweeter and makes sure they delete it from their TimeLine
		std::set<User*> arj = person_temp -> followers();
		for (set<User*>::iterator ir = arj.begin(); ir != arj.end();++ir){
			(*ir) -> addErase(c);
		}
	}
	else { //if there is no @ in the tweet
		person_temp -> addTweet(c); //adds tweet to User
	}
}

  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
std::vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy){
	vector <Tweet*> holder;
	set <Tweet*> temp;
	if (tags.find(terms[0])!= tags.end()) {
		temp = tags.find(terms[0]) -> second;
	}
	if (strategy == 0) { //intersection
		for (unsigned int i = 0; i < terms.size(); i++) {
			std::map<std::string, std::set<Tweet*>>::iterator it = tags.find(terms[i]);
			temp = temp & (it->second);
		}
	}
	else { //union
		for (unsigned int i = 0; i < terms.size(); i++) {
			std::map<string,set<Tweet*>>::iterator it = tags.find(terms[i]);
			temp = temp | (it->second);
		}
	}
	for (set<Tweet*>::iterator it = temp.begin(); it!=temp.end();++it){
		holder.push_back((*it));
	}
	return holder;
}

  /**
   * Dump feeds of each user to their own file
   */
void TwitEng::dumpFeeds()
{ 	
	//outputting the .feeds
	for (map<string,User*>::iterator it = twi_users.begin(); it != twi_users.end(); ++it){
		string a = it -> second -> name() + ".feed";
		ofstream outputFile (a.c_str());
		outputFile << it -> second -> name() << endl;
		std::vector<Tweet*> myfeedvec = it -> second -> getFeed();
		for (unsigned int a = 0; a < myfeedvec.size();++a){
			User* vec_temp = myfeedvec[a] -> user();
			std::list<Tweet*> erase_list = vec_temp -> getErase();
			for (list<Tweet*>::iterator ij = erase_list.begin();ij!=erase_list.end();++ij) {
				for (unsigned int s = 0; s < myfeedvec.size();s++){
				//check if the user's follow each other
					// string tweetinfo = (*ij) -> text();
					// string ared = "";
					// for (unsigned int i = 2; tweetinfo[i]!= ' ';i++){
					// 	ared+=tweetinfo[i];
					// }
					// User* ment_user = twi_users.find(ared) -> second;
					// User* rr = (*ij) -> user();
					// if (rr->checkFollowing(ment_user) && rr->checkFollower(ment_user)){
					// 	cout << "ciao" << endl;
					// 	break;
					// }
				//if they do not follow each other, remove it 
					if (myfeedvec[s] == (*ij)){
						Tweet* temp___ = myfeedvec[s];
						myfeedvec[s] = myfeedvec[myfeedvec.size()-1];
						myfeedvec[myfeedvec.size()-1] = temp___;
						myfeedvec.pop_back();
					}
				}
			}
		}
		for (unsigned int r = 0; r < myfeedvec.size();++r){
			outputFile << myfeedvec[r] -> time() << myfeedvec[r] -> user() -> name() << myfeedvec[r] -> text() << endl;
		}
	}
	//outputting the .mentions
	for (map<string,User*>::iterator it = twi_users.begin(); it != twi_users.end(); ++it){
		string a = it -> second -> name() + ".mentions";
		string namee = it -> second -> name();
		ofstream outputFile (a.c_str());
		outputFile << it -> second -> name() << endl;
		std::vector<Tweet*> myfeedvec = it -> second -> getMFeed();
		for (unsigned int r = 0; r < myfeedvec.size();++r){
			if (myfeedvec[r]->user()->name()!= namee){
				outputFile << myfeedvec[r] -> time() << myfeedvec[r] -> user() -> name() << myfeedvec[r] -> text() << endl;
			}
		}
	}

}