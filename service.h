#ifndef ParkingLotScheduler_service_h
#define ParkingLotScheduler_service_h

#include <iostream>
#include <string>

using namespace std;

class service {
private:

	string name, person1 = "empty", person2 = "empty", person3 = "empty";
	int day, month, year;

public:

	// Constructor
	service(const string& n, const int& m, const int& d, const int& y) :
		name(n),
		day(d),
		month(m),
		year(y)
	{}
	
	// Gets
	string getName() const { return name; }
	string getDate() const { return to_string(month) + "/" + to_string(day) + "/" + to_string(year); }
	string getPerson1() const { return person1; }
	string getPerson2() const { return person2; }
	string getPerson3() const { return person3; }
	string getAssigned() const { return person1 + ", " + person2 + ", and " + person3; }

	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getYear() const { return year; }

	// Sets
	void setPerson1(const string& p) { person1 = p; }
	void setPerson2(const string& p) { person2 = p; }
	void setPerson3(const string& p) { person3 = p; }
	
	// Overloaded ostream operator user for ouput
	friend ostream& operator<<(ostream& os, const service& obj) {
		os << "The " << obj.getName() << " service which is on " << obj.getDate() << " has " << obj.getAssigned() << " assigned to it.\n";
		return os;
	}
};

#endif