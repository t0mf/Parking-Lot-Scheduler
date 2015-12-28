#ifndef ParkingLotScheduler_month_calc
#define ParkingLotScheduler_month_calc

#include "declarations.h"

// This method takes the user's input month and transforms it into the respective month int (dec -> 12)
// and sets the monthOutput variable to be used during the output
int monthInputToMonthInt(string monthInput, string& monthOutput)
{
	if (monthInput == "jan" || monthInput == "january" || monthInput == "1")
	{
		monthOutput = "Jan";
		return 1;
	}
	else if (monthInput == "feb" || monthInput == "february" || monthInput == "febuary" || monthInput == "2")
	{
		monthOutput = "Feb";
		return 2;
	}
	else if (monthInput == "mar" || monthInput == "march" || monthInput == "mrch" || monthInput == "3")
	{
		monthOutput = "Mar";
		return 3;
	}
	else if (monthInput == "apr" || monthInput == "april" || monthInput == "aprl" || monthInput == "4")
	{
		monthOutput = "Apr";
		return 4;
	}
	else if (monthInput == "may" || monthInput == "5")
	{
		monthOutput = "May";
		return 5;
	}
	else if (monthInput == "jun" || monthInput == "june" || monthInput == "6")
	{
		monthOutput = "Jun";
		return 6;
	}
	else if (monthInput == "jul" || monthInput == "july" || monthInput == "7")
	{
		monthOutput = "Jul";
		return 7;
	}
	else if (monthInput == "aug" || monthInput == "august" || monthInput == "agst" || monthInput == "8")
	{
		monthOutput = "Aug";
		return 8;
	}
	else if (monthInput == "sep" || monthInput == "september" || monthInput == "sept" || monthInput == "spt" || monthInput == "9")
	{
		monthOutput = "Sep";
		return 9;
	}
	else if (monthInput == "oct" || monthInput == "october" || monthInput == "10")
	{
		monthOutput = "Oct";
		return 10;
	}
	else if (monthInput == "nov" || monthInput == "november" || monthInput == "11")
	{
		monthOutput = "Nov";
		return 11;
	}
	else if (monthInput == "dec" || monthInput == "december" || monthInput == "12")
	{
		monthOutput = "Dec";
		return 12;
	}
	else
	{
		return 0;
	}
}

// This method determines the day of the week that the month starts on (Jan 2016 is a Friday, it returns 5)
int dayOfWeek(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

// This method returns  name of the first day of the month (for Jan 2016, it takes 5 and returns "fri")
string getFirstDay(int dayOfWeekInt)
{
	if (dayOfWeekInt == 0)
	{
		return "sun";
	}
	else if (dayOfWeekInt == 1)
	{
		return "mon";
	}
	else if (dayOfWeekInt == 2)
	{
		return "tues";
	}
	else if (dayOfWeekInt == 3)
	{
		return "wed";
	}
	else if (dayOfWeekInt == 4)
	{
		return "thurs";
	}
	else if (dayOfWeekInt == 5)
	{
		return "fri";
	}
	else if (dayOfWeekInt == 6)
	{
		return "sat";
	}
	else
	{
		return "error";
	}
}

// This method returns whether or not the year is a leap year (2016 -> true)
bool checkLeapYr(int yearInt)
{
	return yearInt % 4 == 0 && (yearInt % 100 != 0 || yearInt % 400 == 0);
}

// This method determines what day of the month the first Sunday and Wednesday lie on (Jan 2016 -> sunday = 3 & wednesday = 6)
void calcFirstDay(int firstDayOfWeekInt, int& sundayInt, int& wednesdayInt)
{
	if (firstDayOfWeekInt == 1)
	{
		sundayInt += 6;
	}
	else if (firstDayOfWeekInt == 2)
	{
		sundayInt += 5;
	}
	else if (firstDayOfWeekInt == 3)
	{
		sundayInt += 4;
	}
	else if (firstDayOfWeekInt == 4)
	{
		sundayInt += 3;
	}
	else if (firstDayOfWeekInt == 5)
	{
		sundayInt += 2;
	}
	else if (firstDayOfWeekInt == 6)
	{
		sundayInt += 1;
	}

	if (firstDayOfWeekInt == 0)
	{
		wednesdayInt += 3;
	}
	else if (firstDayOfWeekInt == 1)
	{
		wednesdayInt += 2;
	}
	else if (firstDayOfWeekInt == 2)
	{
		wednesdayInt += 1;
	}
	else if (firstDayOfWeekInt == 4)
	{
		wednesdayInt += 6;
	}
	else if (firstDayOfWeekInt == 5)
	{
		wednesdayInt += 5;
	}
	else if (firstDayOfWeekInt == 6)
	{
		wednesdayInt += 4;
	}
}

// This method determines how many Sundays and Wednesdays are in the month (Jan 2016 -> sundays = 5 & wednesdays = 4)
void sunWedCalc(int monthInt, string firstWeekDayOfMonth, int& sunCount, int& wedCount, bool leap)
{
	if (monthInt == 1 || monthInt == 3 || monthInt == 5 || monthInt == 7 || monthInt == 8 || monthInt == 10 || monthInt == 12)
	{
		if (firstWeekDayOfMonth == "sun" || firstWeekDayOfMonth == "fri" || firstWeekDayOfMonth == "sat")
		{
			sunCount = 5;
			wedCount = 4;
		}
		else if (firstWeekDayOfMonth == "thurs")
		{
			sunCount = 4;
			wedCount = 4;
		}
		else
		{
			sunCount = 4;
			wedCount = 5;
		}
	}
	else if (monthInt == 4 || monthInt == 6 || monthInt == 9 || monthInt == 11)
	{
		if (firstWeekDayOfMonth == "sun" || firstWeekDayOfMonth == "sat")
		{
			sunCount = 5;
			wedCount = 4;
		}
		else if (firstWeekDayOfMonth == "tues" || firstWeekDayOfMonth == "wed")
		{
			sunCount = 4;
			wedCount = 5;
		}
		else
		{
			sunCount = 4;
			wedCount = 4;
		}
	}
	else if (monthInt == 2 && leap == true)
	{
		if (firstWeekDayOfMonth == "sun")
		{
			sunCount = 5;
			wedCount = 4;
		}
		else if (firstWeekDayOfMonth == "wed")
		{
			sunCount = 4;
			wedCount = 5;
		}
		else
		{
			sunCount = 4;
			wedCount = 4;
		}
	}
	else if (monthInt == 2 && leap == false)
	{
		sunCount = 4;
		wedCount = 4;
	}
}

#endif