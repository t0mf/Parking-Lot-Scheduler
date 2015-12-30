# Parking-Lot-Scheduler
Scheduler for the parking lot team at my church implemented in C++

First revision created by Thomas Fiveash 12/2014.

Second revision (current version) created by Thomas Fiveash on 12/27/15.

### About
The Parking Lot team at my church consists of 40-50 people, three of which are on duty during any given service (watching over each of the three parking lots). This program automatically generates a random schedule for the specified month, taking in consideration some constraints.

### The constraints
 - A team member can only be assigned a maximum of two shifts per month.
 - A minimum of 21 days (three weeks) must elapse before a team member can be assigned a second shift.
 - Each team member is allowed to request to only be assigned one shift once a month.
 - Each team member is allowed to say which services they can work.
 - Each team member is allowed to say which days they cannot work.

### How the input file works
The input file is named "ParkingLotTeam.csv" and contains various information about each team member. An example input file is provided at /Parking-Lot-Scheduler/input-file/ParkingLotTeam.csv. **NOTE:** All names in the input file have been randomly generated.

The first line of the file contains:
`Carlos Miller: 123-456-7890`
This line contains the team leader's name and phone number and is used in the output to show the team members who to contact in case of scheduling issues.

The rest of the lines contain information in the format of:
`Services the team member can do, Flag to tell if they can do one or two shifts, Name, Specific days they can't work`

An Example:
`12,0,Brian Price,3/6/20`

- The number `12` signifies that the member can only serve during the Sunday School and Sunday Morning services.
    - `1` = Sunday School, `2` = Sunday Morning, `3` = Sunday Night, and `4` = Wednesday Night
    - A value of `234` would be everything but Sunday School, and a value of `1` would be only Sunday School.
- The number `0` signifies that the member is willing to do two shifts each month.
    - `0` = Two shifts and `1` = One shift
- The string `Brian Price` signifies the person’s name.
- The numbers `3/6/20/` signifies the the person cannot work.
    - In this case, they cannot work Jan 3rd, 6th, or 20th.

### Quick overview of how the program works
1. The program calls the getInput method.
    - The method gets input from the user to determine which month and year to create a schedule for and gets input from the input file (ParkingLotTeam.csv) and creates a vector (personVector) which stores the members' information.
    - The input from the user should be in the format of `Jan 2016`, `November 2016`, `apr 2016`, etc. It accepts a variety of ways to say each month
2. The program executes the monthCalculations method, which gets the following:
    - The day of the week that the month starts on (January 2016 starts on a Friday).
    - If the current year is a leap year or not (strictly for February schedules).
    - The days that the first Sunday and Wednesday fall on (For January 2016, the first Sunday is the 3rd, and the first Wednesday is the 6th).
    - The number of Sundays and Wednesdays in the month (January 2016 has five Sundays and four Wednesdays).
3. The program calls the createServices method. 
    - The method populates a vector (serviceVector) with type <service> objects to hold information about each service throughout the month such as: name, date, and who is assigned.
4. The program calls the assignServices method. 
    - The method assigns members from the personVector to services from the serviceVector.
5. The program calls the output method.
    - The method outputs five various files, explained below. 

### Output files explained

The program has five output files, example files provided at /Parking-Lot-Scheduler/output-files/ :

1. serviceOutFile.csv
    - A basic output of information about each service throughout the month.
    - Example: `The <service name> service which is on <date>, has <person 1, 2, and 3> assigned to it.`

2. personOutFile.csv
    - A basic output of information to detail which two services each person is assigned to and how many days apart the services are.
    - Example: `<person's name> is assigned for service1 name> on <service1 date> and <service2 name> on <service2 date> (<number> of days between shifts)`

3. assignedFile.csv
    - A file which displays how many times a member has been assigned to a shift and the total number of members who were assigned for the month.

4. calOutFile.csv
    - A file which can be imported into an excel template to create a nice looking schedule.
    
2. vueOutFile.csv
    - A file which can be imported into the calendar program VueMinder (http://www.vueminder.com/) which is used to automatically send text/emails to remind members of their shifts.
