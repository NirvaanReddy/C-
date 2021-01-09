#include "datetime.h"
#include "tweet.h"
#include "user.h"
#include <vector>
#include <ctime>
#include <cctype>
using namespace std;

	DateTime::DateTime() {
		time_t rawtime;
  		struct tm * timeinfo;
		time (&rawtime);
    	timeinfo = localtime(&rawtime);
    	hour = timeinfo -> tm_hour;
    	min = timeinfo -> tm_min;
		sec = timeinfo -> tm_sec;
		year = timeinfo -> tm_year + 1900;
		month = timeinfo -> tm_mon + 1;
		day = timeinfo -> tm_mday;
	}

	DateTime::DateTime(string tim)
	{
		vector <int> array;
		string temp = "";
		for (unsigned int i = 0; i < tim.length(); i++){
			if (isdigit(tim[i])){
				temp += tim[i];
			}
			else {
				stringstream ss (temp);
				int r; 
				ss >> r;
				array.push_back(r);
				temp.clear();
			}
		}
		year = array[0];
		month = array[1];
		day = array[2];
		hour = array[3];
		min = array[4];
		sec = array[5];
	}
  /**
   * Alternative constructor 
   */
	DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day){
		hour = hh;
		min = mm;
		sec = ss;
		this -> year = year;
		this -> month = month;
		this -> day = day;
	}

  /**
   * Return true if the timestamp is less-than other's
   *
   * @return result of less-than comparison of timestamp
   */
	bool DateTime::operator<(const DateTime& other) const{
		if (this -> year > other.year) return false;
		else if (this -> year < other.year) return true;
		if (this -> month > other.month) return false;
		else if (this -> month < other.month) return true;
		if (this -> day > other.day) return false;
		else if (this -> day < other.day) return true;
		if (this -> hour > other.hour) return false;
		else if (this -> hour < other.hour) return true;
		if (this -> min > other.min) return false;
		else if (this -> min < other.min) return true;
		if (this -> sec > other.sec) return false;
		else if (this -> sec < other.sec) return true;
		return true;
	}

  /**
   * Outputs the timestamp to the given ostream in format:
   *   YYYY-MM-DD HH:MM:SS
   *
   * @return the ostream passed in as an argument
   */
	std::ostream& operator<<(std::ostream& os, const DateTime& other) {
		os << other.year << "-";
		if (other.month < 10){
			os << "0" << other.month << "-";
		}
		else {
			os << other.month << "-";
		}
		if (other.day < 10){
			os << "0" << other.day << " "; 
		}
		else {
			os << other.day << " "; 
		}
		if (other.hour < 10) {
			os << "0" << other.hour << ":"; 
		}
		else {
			os << other.hour << ":"; 
		}
		if (other.min < 10){
			os << "0" << other.min << ":";
		}
		else {
			os << other.min << ":";
		}
		if (other.sec < 10){
			os << "0" << other.sec << " ";
		}
		else {
			os << other.sec << " ";
		}
		return os;
	}

  /**
   * Inputs the timestamp from the given istream expecting the format:
   *   YYYY-MM-DD HH:MM:SS
   *  Returns if an error in the format with the DateTime set to the
   *   current system time/date
   *   
   *
   * @return the istream passed in as an argument
   */


	DateTime DateTime::currentTime() const 
	{
		DateTime helo;
		return helo;
	}
	//getline deliminator
	std::istream& operator>>(std::istream& is, DateTime& dt) {
		char a;
		char b;
		is >> dt.year;
		is >> a >> dt.month;
		is >> b >> dt.day; 
		is >> dt.hour; 
		is >> b >> dt.min >> a >> dt.sec;
		return is;
	}
