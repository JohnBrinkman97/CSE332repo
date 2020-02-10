========================================================================
    CONSOLE APPLICATION : Lab5 Project Overview
========================================================================
John Brinkman - Lab 5
Adding Event -> Calendar gathers all the information, then passes that to the builder. The calendar also calculates the information for a recurring event and passes that to the builder
			 -> EventBuilder builds event, and if need be, builds another year 
			 -> Event name and pointer are stored in a multimap for efficient searching
Global options -> General Prompt function, then individual functions for each of the options depending on the user input all in calendar
	-> If I had to do over again, I would probably put the prompt stuff in builder or its own object so the calendar could support more date formats or calendar options depending on the calendar type,
	but my thought process was that the calendar has all the info necessary to prompt the user with these options so it should handle it
Local Options -> displayed only when an event is displayed directly, handled by calendar since the location may need to be changed

Save Calendar -> Since the builder builds everything but events from scratch anyway, only events are written to file making for efficient writing and reading in of the file
restore -> components deleted, then ndew calendar is built using same functions as a calendar built from scratch would use
merge -> basically the same as restore, but doesnt delete anything and wraps the events differently
	  -> all events wrapped in a decorator to display outside information that is not essential to the event itself - which calendar it is in
display -> state pattern used for display so that the calendar knows what the current display is and other display methods are called automatically on switch 
zoom in -> since the user would have to say what date they want to zoom in on anyway, the interface would be very similar to jump so I just called the jump prompt
Note: I probably should've used a visitor design pattern, or possibly even a strategy design pattern instead of dynamically casting pointers since that's probably not great practice, I 
just wasn't very familiar with either of those so I didn't think of it until later, after the casting had caused a bunch of issues.
 
	
