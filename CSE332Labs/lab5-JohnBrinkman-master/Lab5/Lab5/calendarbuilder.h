#pragma once
#include "displayablecomponent.h"
#include<ctime>
#include<map>
#include"Event.h"

class Calendar;

class CalendarBuilder {
public:
	virtual void initCalendar(Calendar *) = 0;
	virtual void buildNewYear(int newYear, bool l, Calendar*) = 0;
	virtual std::shared_ptr<DisplayableComponent> buildEvent(std::string name, std::tm when, std::string calName, Calendar*) = 0;
	virtual void saveToFile(std::string, std::multimap<std::string,std::shared_ptr<Event>>) = 0;
	virtual void restoreFromFile(std::string fileName,Calendar*c) = 0;
	virtual void mergeFromFile(std::string fileName,string cName, Calendar*c) = 0;
private:
	virtual std::shared_ptr<DisplayableComponent> buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) = 0;
	virtual std::shared_ptr<DisplayableComponent> buildWeek(std::tm d, std::shared_ptr<DisplayableComponent> p) = 0;
	virtual std::shared_ptr<DisplayableComponent> buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) = 0;
	virtual std::shared_ptr<DisplayableComponent> buildYear(std::tm d, bool l, std::shared_ptr<DisplayableComponent> p) = 0;
	
};

class FullCalendarBuilder : public CalendarBuilder {
public:
	virtual void initCalendar(Calendar *);
	virtual void buildNewYear(int newYear, bool l, Calendar*c);
	virtual std::shared_ptr<DisplayableComponent> buildEvent(std::string name, std::tm when, std::string calName, Calendar *);
	virtual void saveToFile(std::string, std::multimap<std::string, std::shared_ptr<Event>>);
	virtual void restoreFromFile(std::string fileName,Calendar*);
	virtual void mergeFromFile(std::string fileName, string cName, Calendar*c);
private:
	virtual std::shared_ptr<DisplayableComponent> buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p);
	virtual std::shared_ptr<DisplayableComponent> buildWeek(std::tm d, std::shared_ptr<DisplayableComponent> p);
	virtual std::shared_ptr<DisplayableComponent> buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p);
	virtual std::shared_ptr<DisplayableComponent> buildYear(std::tm d, bool l, std::shared_ptr<DisplayableComponent> p);
};
