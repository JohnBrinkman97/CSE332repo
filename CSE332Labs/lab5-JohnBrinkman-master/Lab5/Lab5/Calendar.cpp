#include "stdafx.h"
#include "calendar.h"
#include"commonFunctions.h"
#include<sstream>
#include<iostream>
#include<string>
#include<iterator>
#include<iomanip>
using namespace std;

Calendar::Calendar(string buildertype) : CalendarComponent(tm(),nullptr) { // just initialize with a default tm for now.
	if (buildertype == "full") {
		builder = make_shared<FullCalendarBuilder>();
		builder->initCalendar(this);
		parent = nullptr;
	}
}

void Calendar::display() {
	/*if (current_display.get() != this) {
		current_display->display();
		prompt();
	}
	else {
		zoomIn(0);
	}*/
	cout << "2018 Index: 0" << endl;
	cout << "2019 Index: 1" << endl;
	cout << "2020 Index: 2" << endl;
}

int Calendar::addEvent(string name, std::tm t, int recurrEvery, int recurrFor) {
	// TODO: implement
	//shared_ptr<DisplayableComponent> day = this->getChild(0)->getChild(t.tm_mon)->getChild(t.tm_mday);//somehow need to get week
	//shared_ptr<DisplayableComponent> event = make_shared<Event>(t, name, day);
	
	this->builder->buildEvent(name, t, "Original", this); // build original 
	
	for (int i = 0; i < recurrFor; ++i) { //build recurring
		t.tm_mday += recurrEvery;

		while (t.tm_mday > days[t.tm_mon]) {

			t.tm_mday -= days[t.tm_mon];
			++t.tm_mon;
			if (t.tm_mon > 11) {
				++t.tm_year;
				t.tm_mon = 0;

			}
		}
		tm * tptr = &t;
		mktime(tptr);
		if ((t.tm_year + 1900) >= 2021) {
			cout << "Stopped adding events after 2020" << endl;
			return noErrors; // just dont do anything with event past 2020
		}
		else {
		this->builder->buildEvent(name, t, "Original", this);
	}
	
	}
	//day->addComponent(event);

	//event->display();
	return 0;
}

void Calendar::zoomIn(unsigned int index) {
	shared_ptr<DisplayableComponent> temp = current_display->getChild(index);
	if (temp != nullptr) {
		current_display = temp;
	}
	display();
}

void Calendar::zoomOut() {
	if (current_display->getParent() != nullptr) {
		current_display = current_display->getParent();
	}
	display();
}

int Calendar::prompt() {

	while (inProgress) { // prompt user until noErrors is returned
		cout << "Enter 'Create' to add a new event" << endl;
		cout << "Enter 'Search' to search for an event by name and edit it" << endl;
		cout << "Enter 'Jump' to jump to a specific date" << endl;
		cout << "Enter 'Save' to save the calendar to a file" << endl;
		cout << "Enter 'Restore' to restore a calendar from a file" << endl;
		cout << "Enter 'Merge' to merge another calendar from a file" << endl;
		cout << "Enter 'In' to zoom in a level or 'out' to zoom out" << endl;
		cout << "Enter 'quit' to end program" << endl;
		string input;
		cin >> input;
		istringstream is(input);
		string res;
		is >> res; // wrap input then check if it equals quit
		if (res == "quit") {
			return userQuit;
		}
		if (res == "Create" || res == "create") {
			eventPrompt();
		}
		if (res == "Search" || res == "search") {
			findEventPrompt();
		}
		if (res == "jump" || res == "Jump") {
			jumpPrompt();
		}
		if (res == "Save" || res == "save") {
			savePrompt();
		}
		if (res == "Restore" || res == "restore") {
			restorePrompt();
		}
		if (res == "Merge" || res == "merge") {
			mergePrompt();
		}
		if (res == "in" || res == "In") {
			jumpPrompt();
		}
		if (res == "Out" || res == "out") {
			zoomOut();
		}
		
	}
}

int Calendar::eventPrompt() {
	while (inProgress) {
		globalOption(create);
		string input;
		cin >> input;
		istringstream is(input);
		string res;
		is >> res;
		// turn / into whitespace
		
		for (unsigned int i = 0; i < input.size(); ++i) {
			if (input[i] == '/') {
			input[i] = ' ';
			}
		}
		istringstream iss(input); // wrap input
		int day;
		int month;
		int year;
		while (iss) {
			iss >> month; iss >> day, iss >> year; 
		}
		if (year < 2021 && year > 2017 && month < 13 && month > 0 && day <= CalendarComponent::days[month-1] && day > 0) {
			tm t = tm();
			t.tm_mday = day;
			t.tm_year = year - 1900;
			t.tm_mon = month - 1;
		
			time_t now = time(0); // grab the current time
			tm timeToEnter;
			tm * tptr = &t;
			time_t tt = mktime(tptr);

			gmtime_s(&timeToEnter, &tt);
			while (inProgress) {
				cout << "Enter Event Info" << endl;
				cout << "<name>,<Days before reocuurence>,<Times will reoccur>, (name,0,0,time for one-time event)" << endl;
				string info;
				cin >> info;
				
				// turn , into whitespace
				for (unsigned int i = 0; i < info.size(); ++i) {
					if (info[i] == ',') {
						info[i] = ' ';
					}
				}
				istringstream infoStream(info);
				string name;
				int recurrEvery;
				int recurrFor;
		
				while (infoStream) {
					
					infoStream >> name; infoStream >> recurrEvery; infoStream >> recurrFor;
					if (recurrEvery >= 0 && recurrFor >= 0) {
						cout << "Enter time (Ex. 23:30) " << endl;
						string time;
						cin >> time;
						for (unsigned int j = 0;j < time.size(); ++j) {
							if (time[j] == ':') {
								time[j] = ' ';
							}
						}
						istringstream iss(time);
						int hr;int min;
						while (iss) {
							iss >> hr;iss >> min;
						}
						if (hr >= 0 && hr < 24 && min >= 0 && min < 60) {
							timeToEnter.tm_hour = hr;timeToEnter.tm_min = min;
							addEvent(name, timeToEnter, recurrEvery, recurrFor);
							cout << "Event Added" << endl << endl;
							display();
							return noErrors;
						}
						else {
							cout << "Invalid time" << endl; 
						}
					}
				}
			} 
		}
		else {
			cout << "Date does not exist or year is outside 2018-2020" << endl;
		}
	}
}

int Calendar::findEventPrompt() {
	while (inProgress) { // prompt user until noErrors is returned
		globalOption(searchEvents);
		string input;
		cin >> input;
		istringstream is(input);
		string res;
		is >> res; // wrap input then check if it equals quit
		//based off http://www.cplusplus.com/forum/general/102485/
		pair<multimap<string, shared_ptr<Event>>::iterator, multimap<string, shared_ptr<Event>>::iterator> range;
		range = this->eventMap.equal_range(res);
		shared_ptr<DisplayableComponent> day = nullptr;
		multimap<string, shared_ptr<Event>>::iterator iter = range.first;
		if (this->eventMap.count(res) == 0) {
			cout << "No event named " << res << " was found" << endl;
			return noErrors;
		}

		else if (this->eventMap.count(res) == 1) {


			iter->second->display();
			changeView(event, dateInfo);
			editPrompt(iter->second);
			return noErrors;
		
		}
		else {
			
				cout << "Multiple events with that name found, enter a date to go to event" << endl;
				for (multimap<string, shared_ptr<Event>>::iterator it = range.first; it != range.second; ++it) {
					cout << endl << it->first << "   " << it->second->date.tm_mon + 1 << "/" << it->second->date.tm_mday << "/" << it->second->date.tm_year + CalendarComponent::BASEYEAR << flush;
				}
				while (inProgress) {
				cout << endl;
				string input;
				cin >> input;
				// turn / into whitespace

				for (unsigned int i = 0; i < input.size(); ++i) {
					if (input[i] == '/') {
						input[i] = ' ';
					}
				}
				istringstream iss(input); // wrap input
				int day;
				int month;
				int year;
				while (iss) {
					iss >> month; iss >> day, iss >> year;
				}
				
				tm t = tm();
				t.tm_mon = month-1;
				t.tm_mday = day;
				t.tm_year = year - CalendarComponent::BASEYEAR;
				tm * tptr = &t;
				mktime(tptr);
				shared_ptr<DisplayableComponent> dayPtr = nullptr;
				if (year < 2021 && year > 2017 && month < 13 && month > 0 && day <= CalendarComponent::days[month - 1] && day > 0) {
					
					if (t.tm_wday >= t.tm_mday) {
						dayPtr = this->getChild(t.tm_year - (2018 - 1900))->getChild(t.tm_mon)->getChild(0)->getChild(t.tm_mday - 1);
					}
					else {
					
						dayPtr = this->getChild(t.tm_year - (2018 - 1900))->getChild(t.tm_mon)->getChild((t.tm_mday + (CalendarComponent::DAYSINAWEEK - 2) - t.tm_wday) / CalendarComponent::DAYSINAWEEK)->getChild(t.tm_wday);
						
					}
					
					//dayPtr->display();
					for (size_t i = 0; i < dayPtr->children.size(); ++i) {
						shared_ptr<DisplayableComponent> e = dayPtr->getChild(i);
						for (multimap<string, shared_ptr<Event>>::iterator it = range.first; it != range.second; ++it) {
							if (e == it->second) {
								cout << endl;
								this->current_display = e;
								display();
								changeView(event, dateInfo);
								shared_ptr<currentDecorator> cd = dynamic_pointer_cast<currentDecorator>(e);
								shared_ptr<Event> ep = dynamic_pointer_cast<Event>(cd->component);
								editPrompt(ep);
								return noErrors;
							}
						}
					}
					cout << "Couldn't find event on that day" << endl;
					return noErrors;
					
				}
				else {
					cout << "Can't find date in calendar" << endl;
					return noErrors;
				}
				

			}
		}
	}
}

int Calendar::jumpPrompt() {
	
	while (inProgress) { // prompt user until noErrors is returned
		globalOption(jump);
		string input;
		cin >> input;
		istringstream is(input);
		string res;
		is >> res;
		if (res == "Day" || res == "day") {
			cout << "Enter date: MM/DD/YYYY" << endl;
			while (inProgress) {
				string d;
				cin >> d;
				for (unsigned int i = 0; i < d.size(); ++i) {
					if (d[i] == '/') {
						d[i] = ' ';
					}
				}
				istringstream iss(d);
				int month;int D; int year;
				while (iss) {
					iss >> month; iss >> D; iss >> year;
				}
				if (year > 2020 || year < 2018 || month < 1 || month > 12 || D < 1 || D > 31) {
					cout << "Invalid date" << endl;
					return noErrors;
				}
				tm t = tm();
				t.tm_mon = month - 1;
				t.tm_mday = D;
				t.tm_year = year - CalendarComponent::BASEYEAR;
				tm * tptr = &t;
				mktime(tptr);
				shared_ptr<DisplayableComponent> dayPtr = nullptr;

				if (this->getChild(year - (2018 - 1900)) == nullptr) {
					if (year == 2019) {
						this->builder->buildNewYear(year, false, this);
					}
					else if (year == 2020) {
						this->builder->buildNewYear(year, true, this);
					}
				}
				if (year < 2021 && year > 2017 && month < 13 && month > 0 && D <= CalendarComponent::days[month - 1] && D > 0) {
					dateInfo = t;
					this->changeView(day, dateInfo);
/*
					if (t.tm_wday >= t.tm_mday) {
						dayPtr = this->getChild(t.tm_year - (2018 - 1900))->getChild(t.tm_mon)->getChild(0)->getChild(t.tm_mday - 1);
						this->current_display = dayPtr;
						display();
						return noErrors;

					}
					else {

						dayPtr = this->getChild(t.tm_year - (2018 - 1900))->getChild(t.tm_mon)->getChild((t.tm_mday + (CalendarComponent::DAYSINAWEEK - 2) - t.tm_wday) / CalendarComponent::DAYSINAWEEK)->getChild(t.tm_wday);
						this->current_display = dayPtr;
						display();*/

						return noErrors;
					//}

				}

			}

		}
		if (res == "Month" || res == "month") {
			cout << "Enter MM/YYYY" << endl;
			while (inProgress) {
				string d;
				cin >> d;
				for (unsigned int i = 0; i < d.size(); ++i) {
					if (d[i] == '/') {
						d[i] = ' ';
					}
				}
				istringstream iss(d);
				int m;int y;
				while (iss) {
					iss >> m; iss >> y;
				}
				if (y > 2020 || y < 2018) {
					cout << "Calendar only supports 2018-2020" << endl;
					return noErrors;
				}
				else if (this->getChild(y - 2018) == nullptr) {
					if (y == 2019) {
						this->builder->buildNewYear(y, false, this);
					}
					else {
						this->builder->buildNewYear(y, true, this);
					}
				}
				if (m > 12 || m < 1) {
					cout << "Enter Valid Month" << endl;
				}
				else {

					//shared_ptr<DisplayableComponent> monthPtr = this->getChild(y - 2018)->getChild(m - 1);
					//this->current_display = monthPtr;
					dateInfo.tm_mon = m-1;
					tm *tp = &dateInfo;
					mktime(tp);
					this->changeView(month, dateInfo);
					return noErrors;
				}
			}
		}
		if (res == "Year" || res == "year") {
			cout << "Enter year" << endl;

			while (inProgress) {
				string d;
				cin >> d;

				istringstream iss(d);
				int y;
				iss >> y;
				if (y > 2020 || y < 2018) {
					cout << "Calendar only supports 2018-2020" << endl;
					return noErrors;
				}
				else if (this->getChild(y - 2018) == nullptr) {
					if (y == 2019) {
						this->builder->buildNewYear(y, false, this);
					}
					else {
						this->builder->buildNewYear(y, true, this);
					}
				}
				dateInfo.tm_year = y-1900;
				//shared_ptr<DisplayableComponent> yearPtr = this->getChild(y - 2018);
				//this->current_display = yearPtr;
				this->changeView(year, dateInfo);
				return noErrors;

			}
		}
	}
}

int Calendar::savePrompt() {
	cout << "Enter file name to save calendar state to" << endl;
	string fileName;
	while (inProgress) {
		
		cin >> fileName;
		istringstream iss(fileName);
		iss >> fileName;
		if (fileName.size() > 0) {
			this->builder->saveToFile(fileName, this->eventMap);
			return noErrors;
		}
	}
	
}

int Calendar::restorePrompt() {
	cout << "Enter filename to restore from" << endl;
	cout << "*Note: if not file saved from another calendar, format will be incorrect" << endl;
	string fileName;
	while (inProgress) {

		cin >> fileName;
		istringstream iss(fileName);
		iss >> fileName;
		if (fileName.size() > 0) {
			this->builder->restoreFromFile(fileName,this);
			return noErrors;
		}
	}
}

int Calendar::changeView(currentView view, tm date) {  // switch statement for possible errors
	currentView state = view;
	CalendarComponent::dateInfo = date;
	if (date.tm_year + 1900 > 2018) {
		this->builder->buildNewYear(2019, false, this);
		this->builder->buildNewYear(2020, true, this);
	}
	switch (state) {

	case calendar:
		this->display();
		prompt();
		break;
	case year:
		
		this->getChild(date.tm_year - (2018 - 1900))->display();
		prompt();
		break;
	case month:
		cout << months[date.tm_mon] <<":"<< endl;
		for (int i = 0; i < 7; ++i) {
			cout << left << setw(11) << CalendarComponent::daysoftheweek[i] << flush;
		}
		this->getChild(date.tm_year - (2018 - 1900))->getChild(date.tm_mon)->display();
		break;

	case week:
		for (int i = 0; i < 7; ++i) {
			cout << left << setw(11) << CalendarComponent::daysoftheweek[i] << flush;
		}
		this->getChild(date.tm_year - (2018 - 1900))->getChild(date.tm_mon)->getChild((date.tm_mday + (CalendarComponent::DAYSINAWEEK - 2) - date.tm_wday) / CalendarComponent::DAYSINAWEEK)->display();
		
		break;

	case day:
		
		if (date.tm_wday >= date.tm_mday) {
			this->getChild(date.tm_year - (2018 - 1900))->getChild(date.tm_mon)->getChild(0)->getChild(date.tm_mday - 1)->display();
		
		}
		else {
			this->getChild(date.tm_year - (2018 - 1900))->getChild(date.tm_mon)->getChild((date.tm_mday + (CalendarComponent::DAYSINAWEEK - 2) - date.tm_wday) / CalendarComponent::DAYSINAWEEK)->getChild(date.tm_wday)->display();
		}
			break;
	case event: 
		
		break;
	}
	return state;
}

int Calendar::mergePrompt() {
	cout << "Enter filename to restore from and desired calendar name <fileName> <calendarName>" << endl;
	cout << "*Note: if not file saved from another calendar, format will be incorrect" << endl;
	string fileName; string calendarName;
	while (inProgress) {

		cin >> fileName;
		cin >> calendarName;
		istringstream iss(fileName);
		iss >> fileName;
		if (fileName.size() > 0 && calendarName.size() > 0) {
			this->builder->mergeFromFile(fileName, calendarName, this);
			return noErrors;
		}
		else {
			cout << "Enter file, then a space and calendar name" << endl;
		}
	}
}
int Calendar::editPrompt(shared_ptr<Event> e) {
	cout << endl<< "Enter date, time, or name to edit or cancel to exit" << endl;
	while (inProgress) {
		string in;
		cin >> in;
		istringstream iss(in);
		string input;
		iss >> input;
		if (input == "date" || input == "Date") {
			cout << "Enter new date MM/DD/YYYY" << endl;
			while (inProgress) {
				
				string dateEdit;
				for (unsigned int i = 0; i < dateEdit.size(); ++i) {
					if (dateEdit[i] == '/') {
						dateEdit[i] = ' ';
					}
				}
				istringstream iss(dateEdit); // wrap input
				int day;
				int month;
				int year;
				while (iss) {
					iss >> month; iss >> day, iss >> year;
				}
				if (year < 2021 && year > 2017 && month < 13 && month > 0 && day <= CalendarComponent::days[month - 1] && day > 0) {
					tm t = tm();
					t.tm_mday = day;
					t.tm_year = year - 1900;
					t.tm_mon = month - 1;
				
					time_t now = time(0); // grab the current time
			
					tm * tptr = &t;
					shared_ptr<DisplayableComponent> p = e->getParent();
					for (unsigned int i = 0; i < p->children.size(); ++i) {
						if (p->getChild(i) == e) {
							p->removeComponent(i);
						}
					}
					this->addEvent(e->name, t, 0,0 );
					return noErrors;
				}
				else {
					cout << "Enter Valid Date" << endl;
					return noErrors;
				}
			}

		}
		if (input == "name" || input == "Name") {
			while (inProgress) {
				cout << "Enter Name" << endl;
				string name; 
				cin >> name;
				
				if (name.size() > 0) {
					e->name = name;
					this->eventMap.insert(make_pair(name, e));
					return noErrors;
				}
			}
		}
		if (input == "time" || input == "Time") {
			while (inProgress) {
				cout << "Enter Time '23:23'" << endl;
				string time; int h;int m;
				cin >> time;
				for (unsigned int j = 0; j < time.size(); ++j) {
					if (time[j] == ':') {
						time[j] = ' ';
					}
				}
				istringstream is(time);
				while (is) {
					is >> h >> m;
				}
				if (h >= 0 && h < 24 && m >= 0 && m < 60) {
					e->date.tm_hour = h;
					e->date.tm_min = m;
					return noErrors;
				}
				else { 
				cout << "Invalid Time" << endl; 
				return noErrors; 
				}
			}
		}if (input == "Cancel" || input == "cancel") {
			return noErrors;
		}
	}
}