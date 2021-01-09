#include "user.h"
#include <algorithm>
#include "tweet.h"
#include "hsort.h"
using namespace std;

	User::User(std::string name){
		name_ = name;
	}
   /**
   * Destructor
   */
	User::~User() {
	}

	void User::setName(string r) {
		name_ = r;
	}
	
	/**
     * Gets the name of the user 
     * 
     * @return name of the user 
     */

	std::string User::name() const {
		return name_;
	}
  /**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
	std::set<User*> User::followers() const {
		return users;
	}

  /**
   * Gets all the users whom this user follows  
   * 
   * @return Set of Users whom this user follows
   */
	std::set<User*> User::following() const{
		return f1;
	}

  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
	std::list<Tweet*> User::tweets() const {
		return timeline;
	}

	std::list<Tweet*> User::getErase() const{
		return erase;
	}

	std::list<Tweet*> User::m_tweets() const {
		return mentions;
	}
  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
	void User::addFollower(User* u) {
		users.insert(u);
		u -> f1.insert(this);
	}

  /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
	void User::addFollowing(User* u) {
		f1.insert(u);
		u -> users.insert(this);
	}


	bool User::checkFollower(User* s){
		if (users.find(s) == users.end()){
			return false;
		}
		else return true;
	}
	bool User::checkFollowing(User* s){
		if (f1.find(s) == f1.end()){
			return false;
		}
		else return true;
	}

	std::list<Tweet*> User::getMentions(Tweet* t){
		return mentions;
	}

	void User::addErase(Tweet* t){
		erase.push_back(t);
	}


  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
	void User::addTweet(Tweet* t){
		timeline.push_back(t);
	}
	 void User::addMention(Tweet* t){
	 	mentions.push_back(t);
	 }
  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
	std::vector<Tweet*> User::getFeed(){
		std::vector<Tweet*> myfeedvec; 
		for (list<Tweet*>::iterator r = timeline.begin(); r != timeline.end(); ++r){
			myfeedvec.push_back((*r));
		} 
		for (std::set<User*>::iterator i = f1.begin(); i!=f1.end();++i){
			std::list<Tweet*> tr = (*i) -> tweets();
			for (list<Tweet*>::iterator r = tr.begin(); r != tr.end(); ++r) {
				myfeedvec.push_back((*r));
			}
		}
		//cout << endl;
		hsort(myfeedvec,TweetComp());
		return myfeedvec;
	}

	std::vector<Tweet*> User::getMFeed(){
		std::vector<Tweet*> myfeedvec; 
		for (list<Tweet*>::iterator r = mentions.begin(); r != mentions.end(); ++r){
			myfeedvec.push_back((*r));
		} 
		for (std::set<User*>::iterator i = f1.begin(); i!=f1.end();++i){
			std::list<Tweet*> tr = (*i) -> m_tweets();
			for (list<Tweet*>::iterator r = tr.begin(); r != tr.end(); ++r) {
				myfeedvec.push_back((*r));
			}
		}
		//cout << endl;
		//sort(myfeedvec.begin(), myfeedvec.end(), TweetComp());
		hsort(myfeedvec,TweetComp());
		return myfeedvec;
	}


