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
#include "../include/global.h"
#include "../include/read_list.h"
#include "../include/time_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/*
 * Read file ~/.todolist/list.txt
 * file structure:
 *    day
 *    month
 *    year
 *    list1
 *    ...
 *    list...
 *
 * RETURN:
 *    A Lists structure carrying date and lists
 */
struct Lists* read_list(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Read List Starting ... \n");
  #endif
  char home[MAXHOMEPATHLEN];
  strcpy(home, HOME);
  list_path = strcat(home, LIST);
  list = fopen(list_path, "r");

  time_t timeNow;
  time(&timeNow);
  struct tm *now = gmtime(&timeNow);
  
  struct Lists *newLists = (struct Lists *)malloc(sizeof(struct Lists));
  newLists->num = 0;
  memcpy(&(newLists->time), now, sizeof(struct tm));
  newLists->tail = NULL;
  newLists->lists = NULL;

  struct tm last;
  if (fscanf(list, "%d", &last.tm_mday) != EOF &&
    fscanf(list, "%d", &last.tm_mon) != EOF &&
    fscanf(list, "%d", &last.tm_year) != EOF) {
    if(!same_day(&last, now)) 
    {
    }
    else {
      char buf[MAXWORDSLEN];
      struct List *tail = NULL;
      while(fscanf(list, "\n%[^\n]", buf) != EOF) {
        char *newWords = (char *)malloc(MAXWORDSLEN*sizeof(char));
        memcpy(newWords, buf, MAXWORDSLEN*sizeof(char));

        struct List *newList = (struct List *)malloc(sizeof(struct List));
        newList->order = newLists->num;
        newList->words = newWords;
        newList->next = NULL;

        if (tail!=NULL) {
          tail->next = newList;
        } else {
          newLists->lists = newList;
        }
        tail = newList;

        newLists->num++;
      };
      newLists->tail = tail;
    }
  }
  fclose(list);
  return newLists;
}


/*
 * Read file ~/.todolist/target.txt
 * file structure:
 *    day1
 *    month1
 *    year1
 *    target1
 *    days1
 *    ...
 *    day...
 *    month...
 *    year...
 *    target...
 *    days...
 *
 * RETURN:
 *    A Lists structure carrying date and targets
 */
struct Lists* read_target(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Read Target Starting ... \n");
  #endif
  char home[MAXHOMEPATHLEN];
  strcpy(home, HOME);
  target_path = strcat(home, TARGET);
  target = fopen(target_path, "r");

  time_t timeNow;
  time(&timeNow);
  struct tm *now = gmtime(&timeNow);
  
  struct Lists *newLists = (struct Lists *)malloc(sizeof(struct Lists));
  newLists->num = 0;
  memcpy(&(newLists->time), now, sizeof(struct tm));
  newLists->tail = NULL;
  newLists->lists = NULL;

  struct List *newList = (struct List *)malloc(sizeof(struct List));
  struct List *tail = NULL;
  
  while (fscanf(target, "%d", &((newList->time).tm_mday)) != EOF &&
    fscanf(target, "%d", &((newList->time).tm_mon)) != EOF &&
    fscanf(target, "%d", &((newList->time).tm_year)) != EOF) {

    char buf[MAXWORDSLEN];
    if (fscanf(target, "\n%[^\n]", buf) == EOF) break;
    char *newWords = (char *)malloc(MAXWORDSLEN*sizeof(char));
    memcpy(newWords, buf, MAXWORDSLEN*sizeof(char));

    newList->order = newLists->num;
    newList->words = newWords;
    newList->next = NULL;
    if (tail!=NULL) {
      tail->next = newList;
    } else {
      newLists->lists = newList;
    }
    if (fscanf(target, "%d", &(newList->days)) == EOF) break;

    if(newList->days - day_diff((newList->time).tm_year, (newList->time).tm_mon, (newList->time).tm_mday
          , now->tm_year, now->tm_mon, now->tm_mday) < 0) 
    {
      continue;
    } else {
      tail = newList;
      newLists->num++;
      newList = (struct List *)malloc(sizeof(struct List));
    };
  }
  newLists->tail = tail;
  free(newList);
  fclose(target);
  return newLists;
}
