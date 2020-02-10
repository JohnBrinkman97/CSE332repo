// Calendar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "calendar.h"
#include"commonFunctions.h"
#include<iostream>
#include<ctime>
#include<map>
using namespace std;

int main()
{
	Calendar c("full");
	tm t = tm();
	t.tm_mday = 21;
	t.tm_year = 2020-1900;
	t.tm_mon = 8;

	time_t now = time(0); // grab the current time
	tm timeToEnter;
	tm * tptr = &t;
	time_t tt = mktime(tptr);
	
	gmtime_s(&timeToEnter, &tt);
	
	c.changeView(calendar, t);
	//c.display();
    return 0;
}

