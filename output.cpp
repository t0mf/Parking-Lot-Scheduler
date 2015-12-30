#ifndef ParkingLotScheduler_output
#define ParkingLotScheduler_output

#include "declarations.h"

ofstream vueFile("output-files/vueFile.csv");
ofstream calFile("output-files/calFile.csv");
ofstream assignedFile("output-files/assignedFile.csv");
ofstream serviceOutFile("output-files/serviceOutFile.csv");
ofstream personOutFile("output-files/personOutFile.csv");

int assignedCount = 0;

// Method outputs serviceOutFile.csv - A basic output of information about each service throughout the month.
//	Example: "The <service name> service which is on <date>, has <person 1, 2, and 3> assigned to it."
void serviceOut(vector<service>& serviceVector) {
	for (int i = 0; i < serviceVector.size(); i++) {
		// Output to serviceOutFile using the overloaded oeprator
		serviceOutFile << serviceVector[i];
	}
}

// Method outputs personOutFile.csv - A basic output of information to detail which two services
//	each person is assigned to and how many days apart the services are.
//	Example: "<person's name> is assigned for <service1 name> on <date> and <service2 name> on <date> (<number> of days apart)"
// Method outputs assignedFile.csv - A file which displays how many times a person has been assigned to a service
//	and total number of people that were assigned for the month.
void personOut(vector<person>& personVector) {
	
	// Sorts the personVector to be alphabetical
	sort(personVector.begin(), personVector.end(), person::sortThis);

	// For each person in the personVector
	for (int i = 0; i < personVector.size(); i++) {
		// Output to personOutFile using the overloaded oeprator
		personOutFile << personVector[i];

		// Output to assignedFile their name and how many shifts they are assigned to
		if (personVector[i].getShift1Name() == "empty" && personVector[i].getShift2Name() == "empty") {
			assignedFile << personVector[i].getName() << ": 0\n";
		}
		else if (personVector[i].getShift1Name() != "empty" && personVector[i].getShift2Name() == "empty") {
			assignedFile << personVector[i].getName() << ": 1\n";
			assignedCount++;
		}
		else if (personVector[i].getShift1Name() != "empty" && personVector[i].getShift2Name() != "empty") {
			assignedFile << personVector[i].getName() << ": 2\n";
			assignedCount++;
		}
	}

	// Output to assignedFile the total number of people assigned in the month
	assignedFile << "Total assigned: " << assignedCount;
}

// Method outputs calOutFile.csv - A file which can be imported into an excel template to create a nice looking schedule.
void calOut(vector<service>& serviceVector, string month, int year, int sundayInt, int wednesdayInt, int sunCount, int wedCount, string phone) {

	// Output to calFile column headers
	calFile << month << " " << year << ",,,Parking Lot Duty\n"
		<< "Sunday School,Sunday Morning Service,Sunday Evening Service,Wednesday Evening Service\n"
		<< "9:00 - 10:15,10:15 - 11:45,5:30 - 8:15,6:30 - 8:15\n";
			
	// If there are four Sundays and four Wednesdays
	if (sunCount == wedCount) {
		// If the first Sunday comes before the first Wednesday
		if (sundayInt < wednesdayInt) {
			// Output to calFile four full weeks
			outputFullWeek(serviceVector, 0, serviceVector.size(), month);
		}
		// Else if the first Sunday comes after the first Wednesday
		else if (sundayInt > wedCount) {
			// Output to calFile the first Wednesday of the month
			outputFirstWednesday(serviceVector, month);

			// Output to calFile three full weeks
			outputFullWeek(serviceVector, 1, serviceVector.size() - 3, month);

			// Output to calFile the last Sunday of the month
			outputLastSunday(serviceVector, month);
		}
	}
	// Else if there are five Wednesdays and four Sundays
	else if (sunCount < wedCount) { 
		// Output to calFile the first Wednesday of the month
		outputFirstWednesday(serviceVector, month);

		// Output to calFile last four full weeks
		outputFullWeek(serviceVector, 1, serviceVector.size(), month);

	}
	// Else if there are five Sundays and four Wednesdays
	else if (sunCount > wedCount) { 
		// Output to calFile the first four weeks
		outputFullWeek(serviceVector, 0, serviceVector.size() - 3, month);

		// Output to calFile the last Sunday of the month
		outputLastSunday(serviceVector, month);
	}

	// Output to calFile a message to go below the calendar
	calFile << "\"Please check in with me a minimum of thirty (30) minutes prior to time of duty. When you check in with me, I will show you your location of service. When\"\n"
		<< "\"you need to make changes, please call me at least 24 hours in advance of the change you will be making.Thank you in advance for your help and dedication\"\n"
		<< "\"in keeping our church and member's property safe.\"\n"
		<< ",\"GOD BLESS YOU!\"\n"
		<< ",\"" << phone << "\"";	
}

// Method outputs a full week to calFile
void outputFullWeek(vector<service>& serviceVector, int start, int loopCount, string month) {
	for (int i = start; i < loopCount; i += 4) {
		calFile << serviceVector[i].getDay() << "-" << month << ","
				<< serviceVector[i + 1].getDay() << "-" << month << ","
				<< serviceVector[i + 2].getDay() << "-" << month << ","
				<< serviceVector[i + 3].getDay() << "-" << month << "\n,,,\n"
				<< serviceVector[i].getPerson1() << ','
				<< serviceVector[i + 1].getPerson1() << ','
				<< serviceVector[i + 2].getPerson1() << ','
				<< serviceVector[i + 3].getPerson1() << '\n'
				<< serviceVector[i].getPerson2() << ','
				<< serviceVector[i + 1].getPerson2() << ','
				<< serviceVector[i + 2].getPerson2() << ','
				<< serviceVector[i + 3].getPerson2() << '\n'
				<< serviceVector[i].getPerson3() << ','
				<< serviceVector[i + 1].getPerson3() << ','
				<< serviceVector[i + 2].getPerson3() << ','
				<< serviceVector[i + 3].getPerson3() << "\n,,,\n";
	}
}

// Method outputs the first Wednesday of the month to calFile
void outputFirstWednesday(vector<service>& serviceVector, string month) {
	calFile << ",,," << serviceVector[0].getDay() << "-" << month << endl << ",,," << endl
			<< ",,," << serviceVector[0].getPerson1() << endl
			<< ",,," << serviceVector[0].getPerson2() << endl
			<< ",,," << serviceVector[0].getPerson3() << endl << ",,," << endl;
}

// Method outputs the last Sunday of the month to calFile
void outputLastSunday(vector<service>& serviceVector, string month) {

	calFile << serviceVector[serviceVector.size() - 3].getDay() << "-" << month << "," 
			<< serviceVector[serviceVector.size() - 2].getDay() << "-" << month << "," 
			<< serviceVector[serviceVector.size() - 1].getDay() << "-" << month << endl
			<< serviceVector[serviceVector.size() - 3].getPerson1() << ',' 
			<< serviceVector[serviceVector.size() - 2].getPerson1() << ',' 
			<< serviceVector[serviceVector.size() - 1].getPerson1() << '\n'
			<< serviceVector[serviceVector.size() - 3].getPerson2() << ',' 
			<< serviceVector[serviceVector.size() - 2].getPerson2() << ',' 
			<< serviceVector[serviceVector.size() - 1].getPerson2() << '\n'
			<< serviceVector[serviceVector.size() - 3].getPerson3() << ',' 
			<< serviceVector[serviceVector.size() - 2].getPerson3() << ',' 
			<< serviceVector[serviceVector.size() - 1].getPerson3() << "\n,,,\n";
}

// Method outputs vueOutFile.csv - A file which can be imported into the calendar program VueMinder (http://www.vueminder.com/)
//	which is used to automatically send text/emails to remind members of their shifts.
void vueOut(vector<service>& serviceVector, string phone) {
	vueFile << "Title, Start date, Start time, Description\n";

	// For each service in the serviceVector output to vueFile 
	// "Service name: Names of assigned, 8:00:00AM, Message"
	for (int i = 0; i < serviceVector.size(); i++) {
		vueFile << serviceVector[i].getName() << ": " << serviceVector[i].getPerson1() << " " << serviceVector[i].getPerson2() << " " << serviceVector[i].getPerson3() << ","
			<< serviceVector[i].getDate() << ",8:00:00AM,";

		if (serviceVector[i].getName() == "Sunday School") {
			vueFile << "Reminder: You have Parking Lot Duty tomorrow morning at 9am. Contact" << phone << " if you can't make it.\n";
		}
		else if (serviceVector[i].getName() == "Sunday Morning") {
			vueFile << "Reminder: You have Parking Lot Duty tomorrow morning at 10:15am. Contact" << phone << " if you can't make it.\n";
		}
		else if (serviceVector[i].getName() == "Sunday Night") {
			vueFile << "Reminder: You have Parking Lot Duty tomorrow night at 5:30pm. Contact" << phone << " if you can't make it.\n";
		}
		else if (serviceVector[i].getName() == "Wednesday Night") {
			vueFile << "You have Parking Lot Duty tomorrow night at 6:30pm. Contact" << phone << " if you can't make it.\n";
		}
	}
}

#endif