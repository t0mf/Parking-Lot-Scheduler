# Parking-Lot-Scheduler
Scheduler for the parking lot team at my church implemented in C++

Created by Thomas Fiveash on 12/27/2015. Copyright &copy; 2015.

### About
The Parking Lot team at my church consists of 40-50 people. Three of which are on duty during any given service; one watching over each of the three parking lots. This program automatically generates a random schedule for the specified month, taking in consideration some constraints.

### The constraints
 - A team member can only be assigned a maximum of two shifts each month.
 - There has to be minimum of 21 days (three weeks) before a team member can be assigned a second shift.
 - Each team member is allowed to request to only be assigned one shift once a month.
 - Each team member is allowed to say which services they can work.
 - Each team member is allowed to say which days they cannot work.

### How the input file works
The input file is named "ParkingLotTeam.csv" and contains various information about each team member. An example input file is provided at /Parking-Lot-Scheduler/Example Input-Output Files/ParkingLotTeam.csv. NOTE: All names in the input file have been randomly generated.

The first line of the file contains:
`Carlos Miller: 123-456-7890`
And contains the team leader's name and phone number and is used in the output to show the users who to contact in case of scheduling issues.

The rest of the lines contain information in the format of:
`Services the team member can do, Flag to tell if they can do one or two shifts, Name, Specific days they can't make`
An Example:
`12,0,Brian Price,3/6/20`

- The number `12` signifies that the member can only serve during the Sunday School and Sunday Morning services.
    - `1` = Sunday School, `2` = Sunday Morning, `3` = Sunday Night, and `4` = Wednesday Night
    - So a value of `234` would be everything but Sunday School and a value of `1` would only be Sunday School.
- The number `0` signifies that the member is willing to do two shifts each month.
    - `0` = Two shifts and `1` = One shift
- The string `Brian Price` signifies the person’s name.
- The numbers `3/6/20/` signifies the the person cannot work.
    - In this case, they cannot work Jan 3rd, 6th, or 20th.

### Quick overview of how the program works
- The program starts by getting an input from the user, month and year to create a schedule for.
    - The input should be in the format of `Jan 2016`, `November 2016`, `apr 2016`, etc. It accepts many different ways to say each month
- Executes "month calculations" to determine the following:
    - The day of the week that the month starts on. (January 2016 starts on a Friday)
    - If the current year is a leap year or not (strictly for February schedules)
    - The days that the first Sunday and Wednesday fall on. (For January 2016 the first Sunday is the 3rd and the first Wednesday is the 6th)
    - The number of Sundays and Wednesdays in the month. (January 2016 has 5 Sundays and 4 Wednesdays)
- Populates a vector full of service objects.
    - There is 1 object for each service throughout the month.
    - Each object contains information such as: name, date, and who is assigned to it.
- Populates a vector full of people objects.
    - There is 1 object for each person.
    - Each object contains information such as: name, services they can do, services assigned to, etc.
- Assigns members to services based on the constraints listed above.
- Outputs the schedule to csv files to be used elsewhere.

### Output files explained

The program has five output files, example files provided at /Parking-Lot-Scheduler/Example Input-Output Files/ :
1. calFile.csv
    - The purpose of the calFile is to import it into an excel template so that there is a nice-looking schedule that can be sent to all the team members
2. vueFile.csv
    - The purpose of the vueFile is to import the schedule into the application VueMinder (http://www.vueminder.com/) which is a great calendar program that allows you to send reminders via email/text. I use this program to remind the team members of their upcoming shifts.
3. assignedFile.csv
    - The purpose of the assignedFile is so that I can quickly see how many times each person was assigned a shift and how many people total got assigned.
4. personOutFile.csv
    - The purpose of the personOutFile is so I can quickly see which services a certain person is assigned to and how many days apart the shifts are.
5. serviceOutFile.csv
    - The purpose of the serviceOutFile is so I can quickly see which people are assigned to each service.





