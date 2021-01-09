  #include "tweet.h"
  #include "user.h"
  using namespace std;

  Tweet::Tweet() {
  }

  Tweet::Tweet(User* user, const DateTime& time, const std::string& text) 
    : owner(user), time_(time), tw(text)
  {
            
  }

  Tweet::~Tweet(){
    
  }

  /**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
  User* Tweet::user() const {
    return owner;
  }

  DateTime const & Tweet::time() const {
    return time_;
  }

  void Tweet::addData(User* user, const DateTime& time, const std::string& text){
    owner = user;
    time_ = time;
    tw =  text;        
  }

  /**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
  std::string const & Tweet::text() const {
    return tw;
  }

  /**
   * Returns the hashtagged words without the '#' sign
   *
   */
  std::set<std::string> Tweet::hashTags() const {
    return hashs;
  }

  /**
   * Return true if this Tweet's timestamp is less-than other's
   *
   * @return result of less-than comparison of tweet's timestamp
   */
  bool Tweet::operator<(const Tweet& other) const {
    if (this -> time_ < other.time_) return true;
    else return false;
  }

  /**
   * Outputs the tweet to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS username tweet_text
   *
   * @return the ostream passed in as an argument
   */
  std::ostream& operator<<(std::ostream& os, const Tweet& t){
    os << t.time_ << t.owner -> name() << t.tw;
    return os;
  }
  void Tweet::add_hash(std::string text) {
    hashs.insert(text);
  }

  /* Create any other public or private helper functions you deem 
     necessary */
