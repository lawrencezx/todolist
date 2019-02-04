#include "../include/global.h"
#include "../include/read_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 *  RETURN
 *        1   the same day,month,year
 *        0   not the sam day,month,year
 */
static int same_day(struct tm *time1, struct tm *time2) {
  return (time1->tm_year == time2->tm_year) &&
         (time1->tm_mon == time2->tm_mon) &&
         (time1->tm_mday == time2->tm_mday);
}

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
  if (fscanf(list, "%d", &last.tm_mday) != EOF) {
    fscanf(list, "%d", &last.tm_mon);
    fscanf(list, "%d", &last.tm_year);
    if(!same_day(&last, now)) 
    {
    }
    else {
      char buf[MAXWORDSLEN];
      struct List *tail = NULL;
      while(fscanf(list, "%s", buf) != EOF) {
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
