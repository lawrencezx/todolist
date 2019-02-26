/*                              __   _,--="=--,_   __
                               /  \."    .-.    "./  \
                              /  ,/  _   : :   _  \/` \
                              \  `| /o\  :_:  /o\ |\__/
                               `-'| :="~` _ `~"=: |
                                  \`     (_)     `/
                           .-"-.   \      |      /   .-"-.
.-------------------------{     }--|  /,.-'-.,\  |--{     }-------------------------.
 )                        (_)_)_)  \_/`~-===-~`\_/  (_(_(_)                        (
(  todolist - Command line application to manage your daily or long-term schedule.  )
 ) You can write both lists and targets.                                           (
(  A list is a thing that you have to do in the very day.                           )
 ) A target is a thing that you have to finish in limited days that you input.     (
'-----------------------------------------------------------------------------------*/
#include "../include/time_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 

/*
 *  RETURN
 *        1   the same day,month,year
 *        0   not the sam day,month,year
 */
int same_day(struct tm *time1, struct tm *time2) 
{
  return (time1->tm_year == time2->tm_year) &&
         (time1->tm_mon == time2->tm_mon) &&
         (time1->tm_mday == time2->tm_mday);
}


void print_date(struct tm time) 
{
  fprintf(stderr, "date:%2.d,%2.d,%5.d\n", time.tm_mday, 1 + time.tm_mon, 1900 + time.tm_year);
}


/*
 * Count the days between two date.
 *
 */
int day_diff(int year_start, int month_start, int day_start
			, int year_end, int month_end, int day_end)
{
  month_start += 1;
  year_start += 1900;
  month_end += 1;
  year_end += 1900;
	int y2, m2, d2;
	int y1, m1, d1;
	
	m1 = (month_start + 9) % 12;
	y1 = year_start - m1/10;
	d1 = 365*y1 + y1/4 - y1/100 + y1/400 + (m1*306 + 5)/10 + (day_start - 1);
 
	m2 = (month_end + 9) % 12;
	y2 = year_end - m2/10;
	d2 = 365*y2 + y2/4 - y2/100 + y2/400 + (m2*306 + 5)/10 + (day_end - 1);
	
	return (d2 - d1);
}
