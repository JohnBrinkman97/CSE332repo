#pragma once
#include<ctime>
#include<string>
#include<iostream>
#include"displayablecomponent.h"
using namespace std; 

class Event: public DisplayableComponent {
public:
	Event(tm date, string name,shared_ptr<DisplayableComponent> p);
	string name; 
	tm date;
	int recurrEvery;
	int recurrFor;
	virtual void display();
	
};
bool operator<(Event i, Event j);

class DisplayDecorator : public DisplayableComponent {
public:
	shared_ptr<DisplayableComponent> component;
	DisplayDecorator(shared_ptr<DisplayableComponent>);
};

class currentDecorator : public DisplayDecorator {
public:
	string label;
	currentDecorator(shared_ptr<DisplayableComponent>, string);
	virtual void display();
};