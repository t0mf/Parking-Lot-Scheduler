#ifndef ParkingLotScheduler_person_h
#define ParkingLotScheduler_person_h

#include <iostream>
#include <string>

using namespace std;

class person {
private:
	
	string personName, serviceAvailable, skipDays = "empty", shift1Name = "empty", shift2Name = "empty";
	int shift1Day = 0, shift1Month = 0, shift1Year = 0, shift2Day = 0, shift2Month = 0, shift2Year = 0, assignOnceFlag = 0;

public:

	// Constructor
	person(const string& n, const string& d, const string& s, const int& f) :
		personName(n),
		serviceAvailable(d),
		skipDays(s),
		assignOnceFlag(f)
	{}

	// Gets
	string getName() const { return personName; }
	string getServ() const { return serviceAvailable; }
	string getSkip() const { return skipDays; }
	string getShift1Name() const { return shift1Name; }
	string getShift2Name() const { return shift2Name; }
	string getShift1Date() const { 
		return to_string(shift1Month) + "/" + to_string(shift1Day) + "/" + to_string(shift1Year); 
	}
	string getShift2Date() const {
		return to_string(shift2Month) + "/" + to_string(shift2Day) + "/" + to_string(shift2Year);
	}

	int getShift1Day() const { return shift1Day; }
	int getShift2Day() const { return shift2Day; }
	int getFlag() const { return assignOnceFlag; }
	int getDif() const {
		if (shift2Day - shift1Day > 0) { return shift2Day - shift1Day; }
		else { return 0; }
	}

	// Sets
	void setShift1(const int& m, const int& d, const int& y, string s) {
		shift1Month = m;
		shift1Day = d;
		shift1Year = y; 
		shift1Name = s;
	}
	void setShift2(const int& m, const int& d, const int& y, string s) {
		shift2Month = m;
		shift2Day = d;
		shift2Year = y;
		shift2Name = s;
	}
	
	// Sort method
	static bool sortThis(const person& c1, const person& c2) { return c1.personName < c2.personName; }

	// Overloaded ostream operator user for ouput
	friend ostream& operator<<(ostream& os, const person& obj) {
		os << obj.getName() << " is assigned for " << obj.getShift1Name() << " on " << obj.getShift1Date() << " and " << obj.getShift2Name() << " on " << obj.getShift2Date() << " (" << obj.getDif() << " days apart)\n";
		return os;
	}
};

#endif