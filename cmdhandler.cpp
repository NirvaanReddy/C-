#include "cmdhandler.h"
#include <iostream>
#include "setops.h"
#include <cstring>
#include "util.h"
#include <fstream>
#include <cctype>

using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler(){

}

AndHandler::AndHandler(Handler* next) 
  : Handler(next) 
{

}

bool AndHandler::canHandle(const std::string& cmd) const 
{
	return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const{
	std::vector <string> art;
	string temp;
	while (instr >> temp){
		art.push_back(temp);
	}
	std::vector <Tweet*> ae = eng -> search(art,0);
	displayHits(ae);

	return HANDLER_OK;
}

OrHandler::OrHandler(){

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
 	return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::vector <string> art;
	string temp;
	while (instr >> temp){
		art.push_back(temp);
	}
	std::vector <Tweet*> ae = eng -> search(art,1);
	displayHits(ae);

	return HANDLER_OK;
}

TweetHandler::TweetHandler(){

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const 
{
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng * eng, std::istream& instr) const 
{
	//TWEET Mark Treat CS104 right #summerfun
	stringstream ss;
	string temp;
	getline(instr,temp);
	ss << temp;
	temp.clear();
	ss >> temp;
	string text;
	getline(ss,text);
	if (instr.fail()) {
		return HANDLER_ERROR;
	}
	DateTime curr;
	eng -> addTweet(temp, curr, text);
	return HANDLER_OK;
}

FollowHandler::FollowHandler(){

}

FollowHandler::FollowHandler(Handler* next)
  :  Handler(next)
{

}

bool FollowHandler::canHandle(const std::string& cmd) const {
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng * eng, std::istream& istr)const 
{
	string user;
	string follower;
	istr >> follower;
	istr >> user;
	std::map<std::string, User*> people = eng -> usersSet();
	if (people.find(user) == people.end()){
		cerr << "The Person To Be Followed does not exist" << endl;
		return HANDLER_ERROR;
	}
	if (people.find(follower) == people.end()){
		cerr << "The follower does not exist" << endl;
		return HANDLER_ERROR;
	}
	User* pt = people.find(follower) -> second;
	people.find(user) -> second -> addFollower(pt);
	return HANDLER_OK;
}

SaveHandler::SaveHandler(){
}

SaveHandler::SaveHandler(Handler* next)
  :  Handler(next)
{

}

bool SaveHandler::canHandle(const std::string& cmd) const {
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng * eng, std::istream& istr)const 
{
	std::list<Tweet*> tweets_;
	string filename;
	istr >> filename;
	ofstream outputFile(filename.c_str());
	std::map<std::string,User*> people = eng -> usersSet();
	outputFile << people.size() - 1;
	for (std::map<std::string,User*>::iterator it = people.begin(); it != people.end(); ++it){
		User* basic = it -> second;
		outputFile << basic-> name() << " ";
		std::set<User*> ll = basic -> following();
		for (std::set<User*>::iterator jt = ll.begin(); jt != ll.end(); ++jt){
			outputFile << (*jt) -> name() << " ";
		} 
		outputFile << endl;
		std::list<Tweet*> temp_list = it -> second -> tweets();
		for (list<Tweet*>::iterator r = temp_list.begin(); r != temp_list.end();++r){
			tweets_.push_back((*r));
		}
	}
	for (list<Tweet*>::iterator u = tweets_.begin(); u != tweets_.end();++u){
		outputFile << *(*u) << endl;
	}
	return HANDLER_OK;
}


