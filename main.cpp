#include "declarations.h"

ifstream inFile("ParkingLotTeam.csv");

int main() {
	string monthInput, yearInput, monthOutput, firstWeekDayOfMonth, dayInput, serviceAvailable, skipDays, personName, assignOnceFlagStr, phone;
	int monthInt, yearInt, sundayInt = 1, wednesdayInt = 1, sunCount, wedCount, firstDayOfWeekInt;
	bool leap;
	vector<service> serviceVector;
	vector<person> personVector;

	// ----USER INPUT----//
	cout << "Enter the month and year (\"Jan 2016\"): ";
	cin >> monthInput;
	cin >> yearInput;

	dayInput = "1";

	// ----INPUT MANIPULATION---- //
	// Month input to lowercase
	transform(monthInput.begin(), monthInput.end(), monthInput.begin(), ::tolower);

	// Month input ("jan", "January", etc.) to an int (1)
	monthInt = monthInputToMonthInt(monthInput, monthOutput);
	// Year input to an int
	yearInt = stoi(yearInput);

	// ----Month Calculations---- //
	// Method returns the week day that the month starts on (0-6)
	firstDayOfWeekInt = dayOfWeek(1, monthInt, yearInt);

	// Method returns the first week day of the month (sun-sat)
	firstWeekDayOfMonth = getFirstDay(firstDayOfWeekInt);

	// Method determines if the year is a leap year
	leap = checkLeapYr(yearInt);

	// Method determines what days of the month (0-31) the first Sunday and Wednesday are
	calcFirstDay(firstDayOfWeekInt, sundayInt, wednesdayInt);

	// Method determines the number of Sundays and Wednesdays in the month
	sunWedCalc(monthInt, firstWeekDayOfMonth, sunCount, wedCount, leap);

	// ----Create Services---- //
	// Method populates a vector (serviceVector) with type <service> objects to hold information
	// about each event such as: name, date, and who is assigned.
	createServices(sundayInt, wednesdayInt, sunCount, wedCount, monthInt, yearInt, serviceVector);

	// ----Assign People to Services---- //
	// Get's input from the input file and populates a vector (personVector) with type <person> objects which
	// hold information about each person such as: name, services available to serve, and days to skip
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

	// Method assigns persons from the personVector to services from the serviceVector
	assignServices(serviceVector, personVector);

	// ----Output---- //
	// Method outputs all service and who the assigned persons are
	serviceOut(serviceVector);
	// Method outputs all persons and which services they are assigned to
	personOut(personVector);
	// Method outputs a csv which can be imported into an excel
	// template to create a calendar which is sent to all the members.
	calOut(serviceVector, monthOutput, yearInt, sundayInt, wednesdayInt, sunCount, wedCount, phone);
	// Method outputs a csv which can be imported into the calendar application VueMinder (http://www.vueminder.com/)
	// VueMinder is used to send text/emails to members to remind them of their assigned services
	vueOut(serviceVector, phone);

	return 0;
}

// Method populates a vector (sv) with type <service> objects to hold information
// about each event such as: name, date, and who is assigned.
void createServices(int sundayInt, int wednesdayInt, int sunCount, int wedCount, int monthInt, int yearInt, vector<service>& serviceVector) {
	if (sunCount == wedCount) { // If there are 4 Sundays and 4 Wednesdays
		if (sundayInt < wednesdayInt) { // If the first Sunday comes before the first Wednesday
			// Create 4 full weeks (Sunday then Wednesday)
			for (int i = 0; i < 4; i++) {
				service serviceSS("Sunday School", monthInt, sundayInt+(i*7), yearInt);
				service serviceSM("Sunday Morning", monthInt, sundayInt+(i*7), yearInt);
				service serviceSN("Sunday Night", monthInt, sundayInt+(i*7), yearInt);
				serviceVector.push_back(serviceSS);
				serviceVector.push_back(serviceSM);
				serviceVector.push_back(serviceSN);
				service serviceWN("Wednesday Night", monthInt, wednesdayInt+(i*7), yearInt);
				serviceVector.push_back(serviceWN);
			}
		}
		else if (sundayInt > wedCount) { // Else if the first Sunday comes after the first Wednesday
			// Create 1 Wednesday
			service serviceWN("Wednesday Night", monthInt, wednesdayInt, yearInt);
			serviceVector.push_back(serviceWN);
			// Create 3 full weeks (Sunday then Wednesday)
			for (int i = 0; i < 3; i++) {
				service serviceSS("Sunday School", monthInt, sundayInt + (i * 7), yearInt);
				service serviceSM("Sunday Morning", monthInt, sundayInt + (i * 7), yearInt);
				service serviceSN("Sunday Night", monthInt, sundayInt + (i * 7), yearInt);
				serviceVector.push_back(serviceSS);
				serviceVector.push_back(serviceSM);
				serviceVector.push_back(serviceSN);
				service serviceWN("Wednesday Night", monthInt, wednesdayInt + (i * 7), yearInt);
				serviceVector.push_back(serviceWN);
			}
			// Create 1 Sunday
			service serviceSS("Sunday School", monthInt, sundayInt + 21, yearInt);
			service serviceSM("Sunday Morning", monthInt, sundayInt + 21, yearInt);
			service serviceSN("Sunday Night", monthInt, sundayInt + 21, yearInt);
			serviceVector.push_back(serviceSS);
			serviceVector.push_back(serviceSM);
			serviceVector.push_back(serviceSN);
		}
	}
	else if (sunCount < wedCount) { // Else if there are 5 Wednesdays and 4 Sundays
		// Create 1 Wednesday
		service serviceWN("Wednesday Night", monthInt, wednesdayInt, yearInt);
		// Create 4 full weeks (Sunday then Wednesday)
		serviceVector.push_back(serviceWN);
		for (int i = 0; i < 4; i++) {
			service serviceSS("Sunday School", monthInt, sundayInt + (i * 7), yearInt);
			service serviceSM("Sunday Morning", monthInt, sundayInt + (i * 7), yearInt);
			service serviceSN("Sunday Night", monthInt, sundayInt + (i * 7), yearInt);
			serviceVector.push_back(serviceSS);
			serviceVector.push_back(serviceSM);
			serviceVector.push_back(serviceSN);
			service serviceWN("Wednesday Night", monthInt, wednesdayInt + (i * 7), yearInt);
			serviceVector.push_back(serviceWN);
		}

	}
	else if (sunCount > wedCount) { // Else if there are 5 Sundays and 4 Wednesdays
		// Create 4 full weeks (Sunday then Wednesday)
		for (int i = 0; i < 4; i++) {
			service serviceSS("Sunday School", monthInt, sundayInt + (i * 7), yearInt);
			service serviceSM("Sunday Morning", monthInt, sundayInt + (i * 7), yearInt);
			service serviceSN("Sunday Night", monthInt, sundayInt + (i * 7), yearInt);
			serviceVector.push_back(serviceSS);
			serviceVector.push_back(serviceSM);
			serviceVector.push_back(serviceSN);
			service serviceWN("Wednesday Night", monthInt, wednesdayInt + (i * 7), yearInt);
			serviceVector.push_back(serviceWN);
		}
		// Create 1 Sunday
		service serviceSS("Sunday School", monthInt, sundayInt + 28, yearInt);
		service serviceSM("Sunday Morning", monthInt, sundayInt + 28, yearInt);
		service serviceSN("Sunday Night", monthInt, sundayInt + 28, yearInt);
		serviceVector.push_back(serviceSS);
		serviceVector.push_back(serviceSM);
		serviceVector.push_back(serviceSN);
	}
}

// Method assignServices assigns persons from the personVector to services from the serviceVector
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
			if (personVector[i].getServ().find(serviceNumber) != string::npos 
				// And is not currently assigned to a shift
				&& personVector[i].getShift1Name() == "empty" 
				// And they didn't ask to skip that day
				&& personVector[i].getSkip().find(day) == string::npos) {

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
		if ((serviceObj.getPerson1() == "empty" && j == 0) 
			// Or the second slot is empty and on the second iteration
			|| (serviceObj.getPerson2() == "empty" && j == 1) 
			// Or the third slot is empty and on the third iteration
			|| (serviceObj.getPerson3() == "empty" && j == 2)) {

			// Itterate through the personVector to find someone for the slot
			for (int i = 0; i < personVector.size(); i++) {

				// If the person can serve on the current service (find the service number 
				// 1,2,3 or 4 in their service string (example: 123 would be all sunday services)
				if (personVector[i].getServ().find(serviceNumber) != string::npos 
					// And the person is assigned to a shift1 but not a shift2
					&& personVector[i].getShift1Name() != "empty" && personVector[i].getShift2Name() == "empty" 
					// And it's at least 21 days between shifts
					&& (serviceObj.getDay() - personVector[i].getShift1Day()) >= 21 
					// And they didn't ask to skip that day
					&& personVector[i].getSkip().find(day) == string::npos) {

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
	srand(unsigned(time(NULL)));
	random_shuffle(personVector.begin(), personVector.end());
}