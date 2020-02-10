#pragma once
// This file contains declarations for various components used in a Calendar. All components inherit from DisplayableComponent

#include "displayablecomponent.h"
#include<ctime>
#include<string>

//struct tm {
//	int tm_sec;   // seconds of minutes from 0 to 61
//	int tm_min;   // minutes of hour from 0 to 59
//	int tm_hour;  // hours of day from 0 to 24
//	int tm_mday;  // day of month from 1 to 31
//	int tm_mon;   // month of year from 0 to 11
//	int tm_year;  // year since 1900
//	int tm_wday;  // days since sunday
//	int tm_yday;  // days since January 1st
//	int tm_isdst; // hours of daylight savings time
//}

class FullCalendarBuilder;
class Calendar;
class CalendarComponent : public DisplayableComponent {
	friend FullCalendarBuilder;
	friend Calendar;

public:
	CalendarComponent(std::tm, std::shared_ptr<DisplayableComponent>);
	virtual void display() = 0;
	std::tm viewDate;
	std::tm dateInfo;
protected:
	

	// some static constants to use in place of hardcoded calendar values
	static const std::vector<std::string> daysoftheweek;
	static const std::vector<std::string> months;
	static std::vector<int> days;
	static const int DAYSINAWEEK;
	static const int MONTHS;
	static const int BASEYEAR;
};


class DisplayableDay : public CalendarComponent {
public:
	DisplayableDay(std::tm, std::shared_ptr<DisplayableComponent>);
	virtual void display();
};

class DisplayableWeek : public CalendarComponent {
public:
	DisplayableWeek(std::tm, std::shared_ptr<DisplayableComponent>);
	virtual void display();
};

class DisplayableMonth : public CalendarComponent {
public:
	DisplayableMonth(std::tm, std::shared_ptr<DisplayableComponent>, std::string monthname, unsigned int numdays);
	virtual void display();
private:
	std::string name;
	unsigned int numberOfDays;
};

class DisplayableYear : public CalendarComponent {
public:
	DisplayableYear(std::tm, std::shared_ptr<DisplayableComponent>, bool);
	virtual void display();
private:
	bool leap;
};