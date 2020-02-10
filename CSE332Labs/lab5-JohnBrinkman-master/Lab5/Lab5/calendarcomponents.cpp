#include "stdafx.h"
#include "calendarcomponents.h"
#include"Event.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<map>
#include<algorithm>
using namespace std;
// from <ctime>
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

const std::vector<string> CalendarComponent::daysoftheweek = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const std::vector<string> CalendarComponent::months = { "January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November","December" };
std::vector<int> CalendarComponent::days = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const int CalendarComponent::DAYSINAWEEK = 7;
const int CalendarComponent::MONTHS = 12;
const int CalendarComponent::BASEYEAR = 1900;

CalendarComponent::CalendarComponent(std::tm d, std::shared_ptr<DisplayableComponent> p) : DisplayableComponent(p), dateInfo(d){}



DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p){ } 



void DisplayableDay::display() {
	

	std::cout << "\t\t" << daysoftheweek[dateInfo.tm_wday] << " ";
	std::cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
	for (size_t i = 0; i < children.size(); ++i) {

		this->getChild(i)->display();
	

	}

}

DisplayableWeek::DisplayableWeek(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) {}

void DisplayableWeek::display() {
	unsigned int counter = 0;

	
	std::cout << setw(0) << endl;
	shared_ptr<DisplayableDay> d = dynamic_pointer_cast<DisplayableDay>(this->getChild(0));
	for (int j = 0; j < d->dateInfo.tm_wday;++j) {
	
		std::cout << left << setw(11) << " " << flush;
	
	}
	for (unsigned int i = 0; i < children.size(); ++i) {
		shared_ptr<DisplayableDay> c = dynamic_pointer_cast<DisplayableDay>(children[i]);
		unsigned int size = getChild(i)->children.size();
		if (size > counter) {
			counter = size;
		}
		std::cout << left << setw(11)<<c->dateInfo.tm_mday <<flush;
	}
	std::cout << setw(0) << endl;
	for (unsigned int j = 0; j < counter; ++j) {
		for (unsigned int i = 0; i < children.size(); ++i) {
			shared_ptr<DisplayableDay> c = dynamic_pointer_cast<DisplayableDay>(children[i]);
			if (c->getChild(j) != nullptr) {
				shared_ptr<currentDecorator> cd = dynamic_pointer_cast<currentDecorator>(c->getChild(j));
				shared_ptr<Event> e = dynamic_pointer_cast<Event>(cd->component);
				std::cout << left << setw(11) << e->name << flush;
			}
			else {
				std::cout << left << setw(11) << " " << flush;
			}
			
		} std::cout << endl;
	}
}

DisplayableMonth::DisplayableMonth(std::tm d, std::shared_ptr<DisplayableComponent> p, string monthname, unsigned int numdays) : CalendarComponent(d, p), name(monthname), numberOfDays(numdays) {}

void DisplayableMonth::display() {// just pass work along to week 
	
	for (size_t i = 0; i < children.size(); ++i) {
		children[i]->display();
	}
	
}

DisplayableYear::DisplayableYear(std::tm d, std::shared_ptr<DisplayableComponent> p, bool l) : CalendarComponent(d, p), leap(l) {}

void DisplayableYear::display() {
	int counter = 0;
	tm t = dateInfo;
	tm* tptr = &t;
	std::cout << endl << "Year " << dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;
	for (unsigned int i = 0; i < children.size(); ++i) {
		counter = 0;
		t.tm_mon = i;
		t.tm_mday = 1; 
		mktime(tptr); //sets wday 
		std::cout <<endl<< endl << CalendarComponent::months[i] << endl<<endl;
		std::cout << "S  M  T  W  T  F  S" << endl << endl;

		for (int j = 0; j < t.tm_wday;++j) {
			std::cout << "   " << flush;
			++counter;
		}
		for (int j = 0; j < days[i]; ++j) {
			if (j < 9) {
				std::cout << j + 1 << "  " << flush;
			}
			else { std::cout << j + 1 << " " << flush; }
			++counter;
			if (counter == 7 && j+1 < days[i]) {
				std::cout << endl;
				counter = 0;
			}
		}
	}
}


