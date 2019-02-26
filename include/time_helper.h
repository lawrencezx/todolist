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
#ifndef TIME_HELPER_H_JW7B0MLZ
#define TIME_HELPER_H_JW7B0MLZ

#include<stdio.h>
#include<time.h>

int same_day(struct tm *time1, struct tm *time2);

void print_date(struct tm time);

int day_diff(int year_start, int month_start, int day_start
			, int year_end, int month_end, int day_end);


#endif /* end of include guard: TIME_HELPER_H_JW7B0MLZ */
