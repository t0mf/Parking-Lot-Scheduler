#ifndef ParkingLotScheduler_declarations_h
#define ParkingLotScheduler_declarations_h

#include <string>
#include <vector>
#include "service.h"
#include "person.h"
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <ctime>

using namespace std;

// monthCalculations.cpp
int monthInputToMonthInt(string monthInput, string& monthOutput);
int dayOfWeek(int d, int m, int y);
string getFirstDay(int dayOfWeekInt);
bool checkLeapYr(int yearInt);
void calcFirstDay(int firstDayOfWeekInt, int& sundayInt, int& wednesdayInt);
void sunWedCalc(int monthInt, string firstWeekDayOfMonth, int& sunCount, int& wedCount, bool leap);

// output.cpp
void serviceOut(vector<service>& serviceVector);
void personOut(vector<person>& personVector);
void calOut(vector<service>& sv, string month, int year, int sundayInt, int wednesdayInt, int sunCount, int wedCount, string phone);
void outputFullWeek(vector<service>& serviceVector, int start, int loopCount, string month);
void outputFirstWednesday(vector<service>& serviceVector, string month);
void outputLastSunday(vector<service>& serviceVector, string month);
void vueOut(vector<service>& serviceVector, string phone);

#endif