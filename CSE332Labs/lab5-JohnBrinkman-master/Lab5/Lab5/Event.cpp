#include"stdafx.h"
#include"Event.h"
#include<iomanip>

Event::Event(tm date, string name, shared_ptr<DisplayableComponent> p) : DisplayableComponent(p), date(date), name(name) {};

	
	void Event::display() {
	cout << std::setw(2) << std::setfill('0')<<date.tm_hour << ":" << std::setw(2) << std::setfill('0')<< date.tm_min <<"   " << name<< flush;
}

	bool operator<(Event i, Event j)
	{
		return (i.date.tm_hour + i.date.tm_min) < (j.date.tm_hour + j.date.tm_min);
	}


	DisplayDecorator::DisplayDecorator(shared_ptr<DisplayableComponent> comp): DisplayableComponent(comp->getParent()), component(comp) {
	}
	currentDecorator::currentDecorator(shared_ptr<DisplayableComponent> comp,string label) : DisplayDecorator(comp),label(label) {}


	void currentDecorator::display() {

		component->display();
		if (label.size() > 0) {
			cout << "::" << label << endl;
		}
		 
	}