#ifndef ParkingLotScheduler_declarations_h
#define ParkingLotScheduler_declarations_h

#include <string>
#include <vector>
#include "service.h"
#include "person.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

// monthCalculations.cpp
int monthInputToMonthInt(string monthInput, string& monthOutput);
int dayOfWeek(int d, int m, int y);
string getFirstDay(int dayOfWeekInt);
bool checkLeapYr(int yearInt);
void calcFirstDay(int firstDayOfWeekInt, int& sundayInt, int& wednesdayInt);
void sunWedCalc(int monthInt, string firstWeekDayOfMonth, int& sunCount, int& wedCount, bool leap);

// main.cpp
void createServices(int sundayInt, int wednesdayInt, int sunCount, int wedCount, int monthInt, int yearInt, vector<service>& serviceVector);
void assignServices(vector<service>& serviceVector, vector<person>& personVector);
void assignPersons(string serviceNumber, service& serviceObj, vector<person>& personVector);
void shuffleNames(vector<person> &personVector);

// output.cpp
void serviceOut(vector<service>& serviceVector);
void personOut(vector<person>& personVector);
void calOut(vector<service>& sv, string month, int year, int sundayInt, int wednesdayInt, int sunCount, int wedCount, string phone);
void vueOut(vector<service>& serviceVector, string phone);

#endif