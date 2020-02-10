#pragma once
#include<memory>
#include<vector>

// forward declaration, needed for friend declaration
class FullCalendarBuilder;
class Calendar;

// abstract base class representing a composite object
class DisplayableComponent {
	friend FullCalendarBuilder;
	friend Calendar;
	
public:
	virtual void display() = 0;
	virtual std::shared_ptr<DisplayableComponent> getParent();
	virtual std::shared_ptr<DisplayableComponent> getChild(unsigned int);
	std::vector<std::shared_ptr<DisplayableComponent> > children;
protected:
	DisplayableComponent(std::shared_ptr<DisplayableComponent>);
	virtual ~DisplayableComponent();	
	std::shared_ptr<DisplayableComponent> parent; // should probably be a weak_ptr to avoid cycles

	// construction and traversal functions
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>);
	virtual std::shared_ptr<DisplayableComponent> removeComponent(unsigned int);
};
