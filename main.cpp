#include "declarations.h"

void getInput(vector<person>& personVector, string& monthOutput, int& monthInt, int& yearInt, string& phone);
void monthCalculations(int monthInt, int yearInt, int& sundayInt, int& wednesdayInt, int& sunCount, int& wedCount);
void createServices(int sundayInt, int wednesdayInt, int sunCount, int wedCount, int monthInt, int yearInt, vector<service>& serviceVector);
void createFullWeek(vector<service>& serviceVector, int loopCount, int monthInt, int sundayInt, int wednesdayInt, int yearInt, int afterFirstWed);
void createFirstWednesday(vector<service>& serviceVector, int monthInt, int wednesdayInt, int yearInt);
void createLastSunday(vector<service>& serviceVector, int monthInt, int sundayInt, int sundayAddition, int yearInt);
void assignServices(vector<service>& serviceVector, vector<person>& personVector);
void assignPersons(string serviceNumber, service& serviceObj, vector<person>& personVector);
void shuffleNames(vector<person> &personVector);
void output(vector<service>& serviceVector, vector<person>& personVector, string monthOutput, int  yearInt, int sundayInt, int wednesdayInt, int sunCount, int wedCount, string phone);

ifstream inFile("input-file/ParkingLotTeam.csv");

int main() {
	string monthOutput, dayInput = "1", phone;
	int monthInt, yearInt, sundayInt = 1, wednesdayInt = 1, sunCount, wedCount;
	vector<service> serviceVector;
	vector<person> personVector;

	// Method gets input from the user to determine which month and year to create a schedule for
	// and gets input from the input file (ParkingLotTeam.csv) and creates a personVector which stores the members.
	getInput(personVector, monthOutput, monthInt, yearInt, phone);

	// Method is used to determine four things: day of the month for the first
	// Sunday and Wednesday, and number of Sundays and Wednesdays are in the month.
	monthCalculations(monthInt, yearInt, sundayInt, wednesdayInt, sunCount, wedCount);

	// Method populates a vector (serviceVector) with type <service> objects to hold information
	// about each service throughout the month such as: name, date, and who is assigned.
	createServices(sundayInt, wednesdayInt, sunCount, wedCount, monthInt, yearInt, serviceVector);
	
	// Method assigns persons from the personVector to services from the serviceVector
	assignServices(serviceVector, personVector);

	// Method outputs 5 files:
	//	1. serviceOutFile.csv - A basic output of information about each service throughout the month.
	//		Example: "The <service name> service which is on <date>, has <person 1, 2, and 3> assigned to it."
	//	2. personOutFile.csv - A basic output of information to detail which two services
	//		each person is assigned to and how many days apart the services are.
	//		Example: "<person's name> is assigned for <service1 name> on <date> and <service2 name> on <date> (<number> of days apart)"
	//	3. assignedFile.csv - A file which displays how many times a person has been assigned to a service
	//		and total number of people that were assigned for the month.
	//	4. calOutFile.csv - A file which can be imported into an excel template to create a nice looking schedule.
	//	5. vueOutFile.csv - A file which can be imported into the calendar program VueMinder (http://www.vueminder.com/)
	//		which is used to automatically send text/emails to remind members of their shifts.
	output(serviceVector, personVector, monthOutput, yearInt, sundayInt, wednesdayInt, sunCount, wedCount, phone);

	return 0;
}

// Method gets input from the user to determine which month and year to create a schedule for
// and gets input from the input file (ParkingLotTeam.csv) and creates a personVector which stores the members.
void getInput(vector<person>& personVector, string& monthOutput, int& monthInt, int& yearInt, string& phone) {
	string yearInput, monthInput, serviceAvailable, assignOnceFlagStr, personName, skipDays;

	// ----USER INPUT----//
	cout << "Enter the month and year (\"Jan 2016\"): ";
	cin >> monthInput;
	cin >> yearInput;

	// ----INPUT MANIPULATION---- //
	// Month input to lowercase
	transform(monthInput.begin(), monthInput.end(), monthInput.begin(), ::tolower);

	// Month input ("jan", "January", etc.) to an int (1)
	monthInt = monthInputToMonthInt(monthInput, monthOutput);
	// Year input to an int
	yearInt = stoi(yearInput);

	// Create the personVector from input retrieved from the ParkingLotTeam.csv file
	getline(inFile, phone, '\n');
	while (!inFile.eof()) {
		if (inFile.good()) {
			getline(inFile, serviceAvailable, ',');
			getline(inFile, assignOnceFlagStr, ',');
			getline(inFile, personName, ',');
			getline(inFile, skipDays, '\n');
		}

		person person(personName, serviceAvailable, skipDays, stoi(assignOnceFlagStr));
		personVector.push_back(person);
	}
}

// Method is used to determine four things: day of the month for the first
// Sunday and Wednesday, and number of Sundays and Wednesdays are in the month.
void monthCalculations(int monthInt, int yearInt, int& sundayInt, int& wednesdayInt, int& sunCount, int& wedCount) {

	// Method returns the week day that the month starts on (0-6)
	int firstDayOfWeekInt = dayOfWeek(1, monthInt, yearInt);

	// Method returns the first week day of the month (sun-sat)
	string firstWeekDayOfMonth = getFirstDay(firstDayOfWeekInt);

	// Method determines if the year is a leap year
	bool leap = checkLeapYr(yearInt);

	// Method determines what days of the month (0-31) the first Sunday and Wednesday are
	calcFirstDay(firstDayOfWeekInt, sundayInt, wednesdayInt);

	// Method determines the number of Sundays and Wednesdays in the month
	sunWedCalc(monthInt, firstWeekDayOfMonth, sunCount, wedCount, leap);
}

// Method populates a vector (serviceVector) with type <service> objects to hold information
// about each service throughout the month such as: name, date, and who is assigned.
void createServices(int sundayInt, int wednesdayInt, int sunCount, int wedCount, int monthInt, int yearInt, vector<service>& serviceVector) {
	// If there are four Sundays and four Wednesdays
	if (sunCount == wedCount) {
		// If the first Sunday comes before the first Wednesday
		if (sundayInt < wednesdayInt) {
			// Create four full weeks
			createFullWeek(serviceVector, 4, monthInt, sundayInt, wednesdayInt, yearInt, 0);
		}
		// Else if the first Sunday comes after the first Wednesday
		else if (sundayInt > wedCount) {
			// Create the first Wednesday of the month
			createFirstWednesday(serviceVector, monthInt, wednesdayInt, yearInt);

			// Create three full weeks
			createFullWeek(serviceVector, 3, monthInt, sundayInt, wednesdayInt, yearInt, 1);

			// Create the last Sunday of the month
			createLastSunday(serviceVector, monthInt, sundayInt, 21, yearInt);
		}
	}
	// Else if there are five Wednesdays and four Sundays
	else if (sunCount < wedCount) {
		// Create the first Wednesday of the month
		createFirstWednesday(serviceVector, monthInt, wednesdayInt, yearInt);

		// Create four full weeks
		createFullWeek(serviceVector, 4, monthInt, sundayInt, wednesdayInt, yearInt, 1);
	}
	// Else if there are five Sundays and four Wednesdays
	else if (sunCount > wedCount) {
		// Create four full weeks
		createFullWeek(serviceVector, 4, monthInt, sundayInt, wednesdayInt, yearInt, 0);

		// Create the last Sunday of the month
		createLastSunday(serviceVector, monthInt, sundayInt, 28, yearInt);
	}
}

// Method creates a full week
void createFullWeek(vector<service>& serviceVector, int loopCount, int monthInt, int sundayInt, int wednesdayInt, int yearInt, int afterFirstWed) {
	// Create the service objects for all service on sunday <loopCount> times and push to the serviceVector
	for (int i = 0; i < loopCount; i++) {
		service serviceSS("Sunday School", monthInt, sundayInt + (i * 7), yearInt);
		service serviceSM("Sunday Morning", monthInt, sundayInt + (i * 7), yearInt);
		service serviceSN("Sunday Night", monthInt, sundayInt + (i * 7), yearInt);
		serviceVector.push_back(serviceSS);
		serviceVector.push_back(serviceSM);
		serviceVector.push_back(serviceSN);
		service serviceWN("Wednesday Night", monthInt, wednesdayInt + ((i+afterFirstWed) * 7), yearInt);
		serviceVector.push_back(serviceWN);
	}
}

// Method creates the first Wednesday of the month
void createFirstWednesday(vector<service>& serviceVector, int monthInt, int wednesdayInt, int yearInt) {
	// Create the service objects for the first Wednesday and push to the serviceVector
	service serviceWN("Wednesday Night", monthInt, wednesdayInt, yearInt);
	serviceVector.push_back(serviceWN);
}

// Method creates the last Sunday of the month
void createLastSunday(vector<service>& serviceVector, int monthInt, int sundayInt, int sundayAddition, int yearInt) {
	// Create the service objects for the last Sunday and push to the serviceVector
	service serviceSS("Sunday School", monthInt, sundayInt + sundayAddition, yearInt);
	service serviceSM("Sunday Morning", monthInt, sundayInt + sundayAddition, yearInt);
	service serviceSN("Sunday Night", monthInt, sundayInt + sundayAddition, yearInt);
	serviceVector.push_back(serviceSS);
	serviceVector.push_back(serviceSM);
	serviceVector.push_back(serviceSN);
}

// Method assigns persons from the personVector to services from the serviceVector
void assignServices(vector<service>& serviceVector, vector<person>& personVector) {
	// Method assignPersons assigns 3 people to each service
	for (int i = 0; i < serviceVector.size(); i++) {
		if (serviceVector[i].getName() == "Sunday School") {
			assignPersons("1", serviceVector[i], personVector);
		}
		else if (serviceVector[i].getName() == "Sunday Morning") {
			assignPersons("2", serviceVector[i], personVector);
		}
		else if (serviceVector[i].getName() == "Sunday Night") {
			assignPersons("3", serviceVector[i], personVector);
		}
		else if (serviceVector[i].getName() == "Wednesday Night") {
			assignPersons("4", serviceVector[i], personVector);
		}
	}
}

// Method assignPersons assigns 3 people to each service
void assignPersons(string serviceNumber, service& serviceObj, vector<person>& personVector) {
	// Get the day of the month of the service
	string day = to_string(serviceObj.getDay()) +"/";
	
	// ----Assign first shifts---- //
	// Loop 3 times
	for (int j = 0; j < 3; j++) {

		// Randomly shuffle the names before assigning
		shuffleNames(personVector);

		// Itterate through the personVector to find someone for the slot
		for (int i = 0; i < personVector.size(); i++) {

			// If the person can serve on the current service (find the service number 
			// 1,2,3 or 4 in their service string (example: 123 would be all sunday services)		
			if (personVector[i].getServ().find(serviceNumber) != string::npos &&
				// And is not currently assigned to a shift
				personVector[i].getShift1Name() == "empty" && 
				// And they didn't ask to skip that day
				personVector[i].getSkip().find(day) == string::npos) {

				// If the person can only serve once a month
				if (personVector[i].getFlag() == 1) {
					// Set their shift2 so they wont get assigned twice
					personVector[i].setShift2(1, 1, 1, "skip");
				}

				// Depndending on the iteration, assign the person to the first, second, or third slot
				if (j == 0) { serviceObj.setPerson1(personVector[i].getName()); }
				else if (j == 1) { serviceObj.setPerson2(personVector[i].getName()); }
				else if (j == 2) { serviceObj.setPerson3(personVector[i].getName()); }
				// Set the person's shift1 to the date and name of the service
				personVector[i].setShift1(serviceObj.getMonth(), serviceObj.getDay(), serviceObj.getYear(), serviceObj.getName());
				break;
			}
		}
	}

	// ----Assign second shifts---- //
	// Loop 3 times
	for (int j = 0; j < 3; j++) {

		// Randomly shuffle the names before assigning
		shuffleNames(personVector);

		// If the the first slot is empty and on the first iteration
		if ((serviceObj.getPerson1() == "empty" && j == 0) ||
			// Or the second slot is empty and on the second iteration
			(serviceObj.getPerson2() == "empty" && j == 1) ||
			// Or the third slot is empty and on the third iteration
			(serviceObj.getPerson3() == "empty" && j == 2)) {

			// Itterate through the personVector to find someone for the slot
			for (int i = 0; i < personVector.size(); i++) {

				// If the person can serve on the current service (find the service number 
				// 1,2,3 or 4 in their service string (example: 123 would be all sunday services)
				if (personVector[i].getServ().find(serviceNumber) != string::npos &&
					// And the person is assigned to a shift1 but not a shift2
					personVector[i].getShift1Name() != "empty" && personVector[i].getShift2Name() == "empty" &&
					// And it's at least 21 days between shifts
					(serviceObj.getDay() - personVector[i].getShift1Day()) >= 21 &&
					// And they didn't ask to skip that day
					personVector[i].getSkip().find(day) == string::npos) {

					// Depndending on the iteration, assign the person to the first, second, or third slot
					if (j == 0) { serviceObj.setPerson1(personVector[i].getName()); }
					else if (j == 1) { serviceObj.setPerson2(personVector[i].getName()); }
					else if (j == 2) { serviceObj.setPerson3(personVector[i].getName()); }

					// Set the person's shift2 to the date and name of the service
					personVector[i].setShift2(serviceObj.getMonth(), serviceObj.getDay(), serviceObj.getYear(), serviceObj.getName());
					break;
				}
			}
		}
	}
}

// Method randomly shuffles the personVector
void shuffleNames(vector<person> &personVector)
{	
	random_device rd;
	mt19937 g(rd());

	shuffle(personVector.begin(), personVector.end(), g);
}

// Method outputs 5 files:
//	1. serviceOutFile.csv - A basic output of information about each service throughout the month.
//		Example: "The <service name> service which is on <date>, has <person 1, 2, and 3> assigned to it."
//	2. personOutFile.csv - A basic output of information to detail which two services
//		each person is assigned to and how many days apart the services are.
//		Example: "<person's name> is assigned for <service1 name> on <date> and <service2 name> on <date> (<number> of days apart)"
//	3. assignedFile.csv - A file which displays how many times a person has been assigned to a service
//		and total number of people that were assigned for the month.
//	4. calOutFile.csv - A file which can be imported into an excel template to create a nice looking schedule.
//	5. vueOutFile.csv - A file which can be imported into the calendar program VueMinder (http://www.vueminder.com/)
//		which is used to automatically send text/emails to remind members of their shifts.
void output(vector<service>& serviceVector, vector<person>& personVector,
	string monthOutput, int  yearInt, int sundayInt, int wednesdayInt, int sunCount, 
	int wedCount, string phone) {

	// Method creates serviceOut.csv
	serviceOut(serviceVector);

	// Method creates personOut.csv and assignedFile.csv
	personOut(personVector);

	// Method creates calFile.csv
	calOut(serviceVector, monthOutput, yearInt, sundayInt, wednesdayInt, sunCount, wedCount, phone);

	// Method creates vueOutFile
	vueOut(serviceVector, phone);
}