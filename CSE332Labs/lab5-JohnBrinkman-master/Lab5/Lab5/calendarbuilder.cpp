#include "stdafx.h"
#include "calendarbuilder.h"
#include "calendar.h"
#include"commonFunctions.h"
#include "calendarcomponents.h"
#include"Event.h"
#include<fstream>
using namespace std;
void FullCalendarBuilder::initCalendar(Calendar * c) {
	time_t now = time(0); // grab the current time
	tm now_tm; 
	gmtime_s(&now_tm, &now); // create a struct tm(now_tm) from the current time
	
	c->dateInfo = now_tm; // set the current time info for the Calendar
	tm year = now_tm; // setup tm to represent the January 1st of the current year
	year.tm_sec = 0;
	year.tm_min = 0;
	year.tm_hour = 0;
	year.tm_mday = 1;
	year.tm_mon = 0;
	year.tm_wday = (now_tm.tm_wday + CalendarComponent::DAYSINAWEEK - (now_tm.tm_yday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK; // calculate and set the day of the week of January 1st, 2018. Very sloppy, I know
	year.tm_yday = 0;
	year.tm_isdst = 0;
	c->addComponent(buildYear(year,false, shared_ptr<DisplayableComponent>(c)));
	c->current_display = c->getChild(0);
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildEvent(string name, tm when, string calName, Calendar * c) {
	//MAKE BUILD YEAR ITS OWN FUNC 
	if (when.tm_year-(2018-1900) == 1 && c->getChild(1) == nullptr) {
		buildNewYear(2019, false, c);
	}
	if (when.tm_year - (2018 - 1900) == 2 && c->getChild(2) == nullptr) {
		if (c->getChild(1) == nullptr) {
			buildNewYear(2019, false, c);
		}
		buildNewYear(2020, true, c);
	}
	
	shared_ptr<DisplayableComponent> month = c->getChild(when.tm_year-(2018-1900))->getChild(when.tm_mon);
	shared_ptr<DisplayableComponent> day = nullptr;
	shared_ptr<Event> event = nullptr;
	
	if (when.tm_wday >= when.tm_mday) {
		
		 day = month->getChild(0)->getChild(when.tm_mday-1);
		  event = make_shared<Event>(when, name, day);
		  
		 day->addComponent(event);
	}
	else {
		day = month->getChild((when.tm_mday + (CalendarComponent::DAYSINAWEEK - 2) - when.tm_wday) / CalendarComponent::DAYSINAWEEK)-> getChild(when.tm_wday);
		
		event = make_shared<Event>(when, name, day);
		shared_ptr<DisplayableComponent> q = make_shared<currentDecorator>(event,calName);
		day->addComponent(q);
	
		
	}
	c->eventMap.insert(make_pair(name, event));
	return event;
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> day = make_shared<DisplayableDay>(d, p);
	
	return day;

}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildWeek(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	int index = d.tm_mon;
	shared_ptr<DisplayableComponent> w = make_shared<DisplayableWeek>(d, p);
	for (d.tm_wday; d.tm_wday < CalendarComponent::DAYSINAWEEK && d.tm_mday <= CalendarComponent::days[index]; ++d.tm_wday) {
		w->addComponent(buildDay(d, w));
		d.tm_mday += 1;
	}
	return w;
}
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	int index = d.tm_mon;
	shared_ptr<DisplayableComponent> m = make_shared<DisplayableMonth>(d, p, CalendarComponent::months[index], CalendarComponent::days[index]);
	// add first week - may be shorter than 7 days
	m->addComponent(buildWeek(d, m)); 
	d.tm_mday += (CalendarComponent::DAYSINAWEEK - d.tm_wday); 
	d.tm_wday = 0; // reset wday to 0, and handle the rest of the remaining weeks

	for (; d.tm_mday <= CalendarComponent::days[index]; d.tm_mday += CalendarComponent::DAYSINAWEEK) {
		m->addComponent(buildWeek(d,m));
	}
	return m;
}
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildYear(std::tm d,bool l, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> y = make_shared<DisplayableYear>(d,p,l);
	if (l == true) {
		CalendarComponent::days[1] = 29;
	}
	else {
		CalendarComponent::days[1] = 28;
	}
	for (int i = 0; i < CalendarComponent::MONTHS; ++i) {
		d.tm_mon = i;
		y->addComponent(buildMonth(d, y));
		d.tm_wday = (d.tm_wday + CalendarComponent::days[i]) % CalendarComponent::DAYSINAWEEK;
	}
	return y;
}

void FullCalendarBuilder::buildNewYear(int newYear, bool l, Calendar* c) {
	time_t now = time(0); // grab the current time
	tm now_tm;
	gmtime_s(&now_tm, &now);
	tm year = now_tm; // setup tm to represent the January 1st of the current year
	year.tm_sec = 0;
	year.tm_min = 0;
	year.tm_hour = 0;
	year.tm_mday = 1;
	year.tm_mon = 0;
	year.tm_year = newYear - CalendarComponent::BASEYEAR;
	tm * yrptr = &year;
	mktime(yrptr);
	//year.tm_wday = (now_tm.tm_wday + CalendarComponent::DAYSINAWEEK - (now_tm.tm_yday % CalendarComponent::DAYSINAWEEK)) % CalendarComponent::DAYSINAWEEK; // calculate and set the day of the week of January 1st, 2018. Very sloppy, I know

	year.tm_yday = 0;
	year.tm_isdst = 0;
	c->addComponent(buildYear(year, l, shared_ptr <DisplayableComponent>(c)));
}

void FullCalendarBuilder::saveToFile(string fileName, multimap<string, shared_ptr<Event>> eventMap ) {
	
	ofstream outputFile(fileName);
	multimap<string, shared_ptr<Event>>::iterator pos;
	if (outputFile.is_open()) {
		for (pos = eventMap.begin(); pos != eventMap.end(); ++pos) {
			outputFile << pos->second->date.tm_mon << " " << pos->second->date.tm_mday << " " << pos->second->date.tm_year << " " << pos->second->date.tm_hour << " " << pos->second->date.tm_min << " " << pos->second->name << endl;
		}
		outputFile.close();
	}
	else {
		cout << "couldn't create/open file" << endl;
	}
}

void FullCalendarBuilder::restoreFromFile(string fileName,Calendar* c) {
	int month;int day;int year; int min; int hour; string name;
	for (unsigned int i = 0; i < c->children.size();++i) {
		c->removeComponent(i);
	}
	c->eventMap.clear();
	c->children.clear();
	this->initCalendar(c);
	this->buildNewYear(2019, false, c);
	this->buildNewYear(2020, true, c);
	ifstream inputFile;
	inputFile.open(fileName);
	if (!inputFile) {
		cout << "couldn't open file" << endl;
		return;
	}
	while (inputFile >> month >> day >> year >> hour >> min >> name) {
		
		tm t = tm();
		t.tm_mday = day;
		t.tm_year = year;
		t.tm_mon = month;
		t.tm_hour = hour;
		t.tm_min = min;
		tm * tptr = &t;
		mktime(tptr);
		this->buildEvent(name, t,"Original", c);
	}
	c->current_display = c->getChild(0);
	
}

void FullCalendarBuilder::mergeFromFile(std::string fileName, string cName, Calendar*c) {
	int month;int day;int year; int min; int hour; string name;
	
	//this->initCalendar(c);
	this->buildNewYear(2019, false, c);
	this->buildNewYear(2020, true, c);
	ifstream inputFile;
	inputFile.open(fileName);
	if (!inputFile) {
		cout << "couldn't open file" << endl;
		return;
	}
	while (inputFile >> month >> day >> year >> hour >> min >> name) {

		tm t = tm();
		t.tm_mday = day;
		t.tm_year = year;
		t.tm_mon = month;
		t.tm_hour = hour;
		t.tm_min = min;
		tm * tptr = &t;
		mktime(tptr);
		this->buildEvent(name, t, cName, c);
	}
	c->current_display = c->getChild(0);
}