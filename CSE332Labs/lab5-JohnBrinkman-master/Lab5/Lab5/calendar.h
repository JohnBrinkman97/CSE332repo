#pragma once
#include "displayablecomponent.h"
#include "calendarcomponents.h"
#include "calendarbuilder.h"
#include<string>
#include<ctime>
#include<iterator>
#include<algorithm>
#include<map>
#include"Event.h"
enum currentView { calendar, year, month, week, day, event };
class Calendar : public CalendarComponent {
	friend FullCalendarBuilder;
public:
	Calendar(std::string buildertype);

	// inherited
	virtual void display();
	multimap<string, shared_ptr<Event>> eventMap; 
	// recurrEvery = # of days to wait before repeating. recurrFor = # of times to repeat. 0,0 for a non-recurring event
	int addEvent(std::string name, std::tm t, int recurrEvery, int recurrFor);  // build an event and add it to the correct day/days based on time
	void zoomIn(unsigned int index); // zoom in on a child of the current_display
	void zoomOut(); // zoom out to the parent of the current_display
	int prompt(); // prompt user each time  calendar is displayed
	int eventPrompt();
	int findEventPrompt();
	int jumpPrompt();
	int savePrompt();
	int restorePrompt();
	int mergePrompt();
	int changeView(currentView view, tm date);
	int editPrompt(shared_ptr<Event>);
private:
	std::shared_ptr<CalendarBuilder> builder;
	std::shared_ptr<DisplayableComponent> current_display;
};