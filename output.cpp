#ifndef ParkingLotScheduler_output
#define ParkingLotScheduler_output

#include "declarations.h"

ofstream vueFile("output-files/vueFile.csv");
ofstream calFile("output-files/calFile.csv");
ofstream assignedFile("output-files/assignedFile.csv");
ofstream serviceOutFile("output-files/serviceOutFile.csv");
ofstream personOutFile("output-files/personOutFile.csv");

int assignedCount = 0;

// Method outputs all service and who the assigned persons are
void serviceOut(vector<service>& serviceVector) {
	for (int i = 0; i < serviceVector.size(); i++) {
		// Output to serviceOutFile using the overloaded oeprator
		serviceOutFile << serviceVector[i];
	}
}

// Method outputs all persons and which services they are assigned to
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

// Method outputs a csv which can be imported into an excel
// template to create a calendar which is sent to all the members.
void calOut(vector<service>& sv, string month, int year, int sundayInt, int wednesdayInt, int sunCount, int wedCount, string phone) {

	// Temporary strings used for output
	string ss1, ss2, ss3, sm1, sm2, sm3, sn1, sn2, sn3, wn1, wn2, wn3;

	calFile << month << " " << year << ",,,Parking Lot Duty\n"
		<< "Sunday School,Sunday Morning Service,Sunday Evening Service,Wednesday Evening Service\n"
		<< "9:00 - 10:15,10:15 - 11:45,5:30 - 8:15,6:30 - 8:15\n";
			
	if (sunCount == wedCount) { // If there are 4 Sundays and 4 Wednesdays
		if (sundayInt < wednesdayInt) { // If the first Sunday comes before the first Wednesday
			// Output to calFile 4 full weeks
			for (int i = 0; i < sv.size(); i += 4) {
				calFile << sv[i].getDay() << "-" << month << "," << sv[i+1].getDay() << "-" << month << "," << sv[i+2].getDay() << "-" << month << "," << sv[i+3].getDay() << "-" << month << "\n,,,\n";

				ss1 = sv[i].getPerson1();
				ss2 = sv[i].getPerson2();
				ss3 = sv[i].getPerson3();

				sm1 = sv[i+1].getPerson1();
				sm2 = sv[i+1].getPerson2();
				sm3 = sv[i+1].getPerson3();

				sn1 = sv[i+2].getPerson1();
				sn2 = sv[i+2].getPerson2();
				sn3 = sv[i+2].getPerson3();

				wn1 = sv[i+3].getPerson1();
				wn2 = sv[i+3].getPerson2();
				wn3 = sv[i+3].getPerson3();

				calFile << ss1 << ',' << sm1 << ',' << sn1 << ',' << wn1 << '\n';
				calFile << ss2 << ',' << sm2 << ',' << sn2 << ',' << wn2 << '\n';
				calFile << ss3 << ',' << sm3 << ',' << sn3 << ',' << wn3 << "\n,,,\n";
			}
		}
		else if (sundayInt > wedCount) { // Else if the first Sunday comes after the first Wednesday
			// Output to calFile the first Wednesday
			calFile << ",,," << sv[0].getDay() << "-" << month << endl << ",,," << endl
				<< ",,," << sv[0].getPerson1() << endl
				<< ",,," << sv[0].getPerson2() << endl
				<< ",,," << sv[0].getPerson3() << endl << ",,," << endl;
			// Output to calFile 3 full weeks
			for (int i = 1; i < sv.size()-3; i += 4) {
				calFile << sv[i].getDay() << "-" << month << "," << sv[i + 1].getDay() << "-" << month << "," << sv[i + 2].getDay() << "-" << month << "," << sv[i + 3].getDay() << "-" << month << "\n,,,\n";

				ss1 = sv[i].getPerson1();
				ss2 = sv[i].getPerson2();
				ss3 = sv[i].getPerson3();

				sm1 = sv[1+1].getPerson1();
				sm2 = sv[i+1].getPerson2();
				sm3 = sv[i+1].getPerson3();

				sn1 = sv[i+2].getPerson1();
				sn2 = sv[i+2].getPerson2();
				sn3 = sv[i+2].getPerson3();

				wn1 = sv[i+3].getPerson1();
				wn2 = sv[i+3].getPerson2();
				wn3 = sv[i+3].getPerson3();

				calFile << ss1 << ',' << sm1 << ',' << sn1 << ',' << wn1 << '\n';
				calFile << ss2 << ',' << sm2 << ',' << sn2 << ',' << wn2 << '\n';
				calFile << ss3 << ',' << sm3 << ',' << sn3 << ',' << wn3 << "\n,,,\n";
			}
			// Output to calFile the last Sunday
			calFile << sv[sv.size()-3].getDay() << "-" << month << "," << sv[sv.size()-2].getDay() << "-" << month << "," << sv[sv.size() - 1].getDay() << "-" << month << endl;

			ss1 = sv[sv.size()-3].getPerson1();
			ss2 = sv[sv.size()-3].getPerson2();
			ss3 = sv[sv.size()-3].getPerson3();

			sm1 = sv[sv.size()-2].getPerson1();
			sm2 = sv[sv.size()-2].getPerson2();
			sm3 = sv[sv.size()-2].getPerson3();

			sn1 = sv[sv.size()-1].getPerson1();
			sn2 = sv[sv.size()-1].getPerson2();
			sn3 = sv[sv.size()-1].getPerson3();

			calFile << ss1 << ',' << sm1 << ',' << sn1 << '\n';
			calFile << ss2 << ',' << sm2 << ',' << sn2 << '\n';
			calFile << ss3 << ',' << sm3 << ',' << sn3 << "\n,,,\n";
		}
	}
	else if (sunCount < wedCount) { // Else if there are 5 Wednesdays and 4 Sundays
		// Output to calFile the first Wednesday
		calFile << ",,," << sv[0].getDay() << "-" << month << endl << ",,," << endl
			<< ",,," << sv[0].getPerson1() << endl
			<< ",,," << sv[0].getPerson2() << endl
			<< ",,," << sv[0].getPerson3() << endl << ",,," << endl;
		// Output to calFile 4 full weeks
		for (int i = 1; i < sv.size(); i += 4) {
			calFile << sv[i].getDay() << "-" << month << "," << sv[i + 1].getDay() << "-" << month << "," << sv[i + 2].getDay() << "-" << month << "," << sv[i + 3].getDay() << "-" << month << "\n,,,\n";

			ss1 = sv[i].getPerson1();
			ss2 = sv[i].getPerson2();
			ss3 = sv[i].getPerson3();

			sm1 = sv[i + 1].getPerson1();
			sm2 = sv[i + 1].getPerson2();
			sm3 = sv[i + 1].getPerson3();

			sn1 = sv[i + 2].getPerson1();
			sn2 = sv[i + 2].getPerson2();
			sn3 = sv[i + 2].getPerson3();

			wn1 = sv[i + 3].getPerson1();
			wn2 = sv[i + 3].getPerson2();
			wn3 = sv[i + 3].getPerson3();

			calFile << ss1 << ',' << sm1 << ',' << sn1 << ',' << wn1 << '\n';
			calFile << ss2 << ',' << sm2 << ',' << sn2 << ',' << wn2 << '\n';
			calFile << ss3 << ',' << sm3 << ',' << sn3 << ',' << wn3 << "\n,,,\n";
		}

	}
	else if (sunCount > wedCount) { // Else if there are 5 Sundays and 4 Wednesdays
		// Output to calFile 4 full weeks
		for (int i = 0; i < sv.size()-3; i += 4) {
			calFile << sv[i].getDay() << "-" << month << "," << sv[i + 1].getDay() << "-" << month << "," << sv[i + 2].getDay() << "-" << month << "," << sv[i + 3].getDay() << "-" << month << "\n,,,\n";

			ss1 = sv[i].getPerson1();
			ss2 = sv[i].getPerson2();
			ss3 = sv[i].getPerson3();

			sm1 = sv[i + 1].getPerson1();
			sm2 = sv[i + 1].getPerson2();
			sm3 = sv[i + 1].getPerson3();

			sn1 = sv[i + 2].getPerson1();
			sn2 = sv[i + 2].getPerson2();
			sn3 = sv[i + 2].getPerson3();

			wn1 = sv[i + 3].getPerson1();
			wn2 = sv[i + 3].getPerson2();
			wn3 = sv[i + 3].getPerson3();

			calFile << ss1 << ',' << sm1 << ',' << sn1 << ',' << wn1 << '\n';
			calFile << ss2 << ',' << sm2 << ',' << sn2 << ',' << wn2 << '\n';
			calFile << ss3 << ',' << sm3 << ',' << sn3 << ',' << wn3 << "\n,,,\n";
		}
		// Output to calFile the last Sunday
		calFile << sv[sv.size() - 3].getDay() << "-" << month << "," << sv[sv.size() - 2].getDay() << "-" << month << "," << sv[sv.size() - 1].getDay() << "-" << month << "\n,,,\n";

		ss1 = sv[sv.size() - 3].getPerson1();
		ss2 = sv[sv.size() - 3].getPerson2();
		ss3 = sv[sv.size() - 3].getPerson3();

		sm1 = sv[sv.size() - 2].getPerson1();
		sm2 = sv[sv.size() - 2].getPerson2();
		sm3 = sv[sv.size() - 2].getPerson3();

		sn1 = sv[sv.size() - 1].getPerson1();
		sn2 = sv[sv.size() - 1].getPerson2();
		sn3 = sv[sv.size() - 1].getPerson3();

		calFile << ss1 << ',' << sm1 << ',' << sn1 << '\n';
		calFile << ss2 << ',' << sm2 << ',' << sn2 << '\n';
		calFile << ss3 << ',' << sm3 << ',' << sn3 << "\n,,,\n";
	}

	// Output to calFile a message to go below the calendar
	calFile << "\"Please check in with me a minimum of thirty (30) minutes prior to time of duty. When you check in with me, I will show you your location of service. When\"\n"
		<< "\"you need to make changes, please call me at least 24 hours in advance of the change you will be making.Thank you in advance for your help and dedication\"\n"
		<< "\"in keeping our church and member's property safe.\"\n"
		<< ",\"GOD BLESS YOU!\"\n"
		<< ",\"" << phone << "\"";	
}

// Method outputs a csv which can be imported into the calendar application VueMinder (http://www.vueminder.com/)
// VueMinder is used to send text/emails to members to remind them of their assigned services
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