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
#include "../include/edit_list.h"
#include "../include/read_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* edit lists */
static void write_list_to_file(struct Lists *lists, unsigned int removeList) {
  #ifdef DEBUG
    fprintf(stderr, "Write List Starting ... \n");
  #endif
  
  char home[MAXHOMEPATHLEN];
  strcpy(home, HOME);
  list_path = strcat(home, LIST);
  list = fopen(list_path, "w");

  struct List* preList = lists->lists;
  if(preList != NULL) {
    struct tm time = lists->time;
    fprintf(list, "%d\n", time.tm_mday);
    fprintf(list, "%d\n", time.tm_mon);
    fprintf(list, "%d\n", time.tm_year);

    unsigned int cnt = 1;
    while (preList != NULL) {
      if (cnt != removeList) {
        fprintf(list, "%s\n", preList->words);
      }
      cnt++;
      preList = preList->next;
    }
  }
  fclose(list);
}

/*
 * Write file ~/.todolist/list.txt
 * Write list below the last list in the file
 * file structure:
 *    day
 *    month
 *    year
 *    list1
 *    ...
 *    list...
 *
 */
void write_list(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Write List Starting ... \n");
  #endif

  fprintf(stderr, "'q' to exit\n");
  struct Lists *newLists = read_list();
  struct List *tail = newLists->tail;
  while(1) {
    fprintf(stderr, "<<");
    char c;
    char str[MAXWORDSLEN];
    int i = 0;
    while((c = getchar()) != '\n') {
      str[i++] = c;
    }
    str[i++] = '\0';

    if(strcmp(str, "q") == 0) break;

    char *newWords = (char *)malloc(i*sizeof(char));
    memcpy(newWords, str, i*sizeof(char));

    struct List *newList = (struct List *)malloc(sizeof(struct List));
    newList->order = newLists->num;
    newList->words = newWords;
    newList->next = NULL;

    if (tail != NULL) {
      tail->next = newList;
    } else {
      newLists->lists = newList;
    }
    tail = newList;

    newLists->num++;
  }
  newLists->tail = tail;

  write_list_to_file(newLists, 0);
}



void remove_list(unsigned num)
{
  #ifdef DEBUG
    fprintf(stderr, "Remove List Starting ... \n");
  #endif
  struct Lists *newLists = read_list();
  if (newLists->num < num) 
  {
    fprintf(stderr, "List %d does not exist!\n", num);
    return;
  } else 
  {
    write_list_to_file(newLists, num);
    fprintf(stderr, "List %d has been deleted!\n", num);
  }
}



static void swapList(struct List *list1, struct List *list2)
{
  unsigned tmpNum;
  tmpNum = list1->order;
  list1->order = list2->order;
  list2->order = tmpNum;

  char* tmpWords;
  tmpWords = list1->words;
  list1->words = list2->words;
  list2->words = tmpWords;
}

void swap_list(unsigned num1, unsigned num2)
{
  #ifdef DEBUG
    fprintf(stderr, "Swap List Starting ... \n");
  #endif
  struct Lists *newLists = read_list();
  struct List *preList = newLists->lists;
  struct List *list1 = NULL;
  struct List *list2 = NULL;
  if (newLists->num < num1 || newLists->num < num2 || num1 == num2)
  {
    fprintf(stderr, "List does not exist or same lists\n");
    return;
  } else
  {
    unsigned cnt = 1;
    while (preList != NULL) {
      if (cnt == num1) {
        list1 = preList;
      } else if (cnt == num2) {
        list2 = preList;
      }
      cnt++;
      preList = preList->next;
    }
    swapList(list1, list2);
    write_list_to_file(newLists, 0);
  }
}


/* edit targets */
static void write_target_to_file(struct Lists *lists, unsigned int removeList) {
  #ifdef DEBUG
    fprintf(stderr, "Write Target Starting ... \n");
  #endif
  
  char home[MAXHOMEPATHLEN];
  strcpy(home, HOME);
  target_path = strcat(home, TARGET);
  target = fopen(target_path, "w");

  struct List* preList = lists->lists;

  struct tm time = lists->time;
  unsigned int cnt = 1;
  while (preList != NULL) {
    if (cnt != removeList) {
      fprintf(target, "%d\n", time.tm_mday);
      fprintf(target, "%d\n", time.tm_mon);
      fprintf(target, "%d\n", time.tm_year);

      fprintf(target, "%s\n", preList->words);
      
      fprintf(target, "%d\n", preList->days);
    }
    cnt++;
    preList = preList->next;
  }
  fclose(target);
}


/*
 * Write file ~/.todolist/target.txt
 * Write target below the last target oin the file
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
 */
void write_target(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Write Target Starting ... \n");
  #endif

  fprintf(stderr, "Please input your\033[;31m target\033[0m and the\033[;31m days\033[0m to achieve your target\n 'q' to exit\n");
  struct Lists *newLists = read_target();
  struct List *tail = newLists->tail;
  if (tail != NULL) {
    fprintf(stderr, "tail : %s \n", tail->words);
  }
  while(1) {
    fprintf(stderr, "TARGET<<");
    char c;
    char str[MAXWORDSLEN];
    int i = 0;
    while((c = getchar()) != '\n') {
      str[i++] = c;
    }
    str[i++] = '\0';

    if(strcmp(str, "q") == 0) break;

    char *newWords = (char *)malloc(i*sizeof(char));
    memcpy(newWords, str, i*sizeof(char));

    struct List *newList = (struct List *)malloc(sizeof(struct List));
    newList->order = newLists->num;
    newList->words = newWords;
    fprintf(stderr, "DAYS  <<");
    i = 0;
    while((c = getchar()) != '\n') {
      str[i++] = c;
    }
    newList->days = atoi(str);
    newList->next = NULL;
     
    if (tail != NULL) {
      tail->next = newList;
    } else {
      newLists->lists = newList;
    }

    tail = newList;

    newLists->num++;
  }
  newLists->tail = tail;

  write_target_to_file(newLists, 0);
}


void remove_target(unsigned num)
{
  #ifdef DEBUG
    fprintf(stderr, "Remove Target Starting ... \n");
  #endif
  struct Lists *newLists = read_target();
  if (newLists->num < num) 
  {
    fprintf(stderr, "Target %d does not exist!\n", num);
    return;
  } else 
  {
    write_target_to_file(newLists, num);
    fprintf(stderr, "Target %d has been deleted!\n", num);
  }
}


static void swapTarget(struct List *list1, struct List *list2)
{
  unsigned tmpNum;
  tmpNum = list1->order;
  list1->order = list2->order;
  list2->order = tmpNum;

  tmpNum = list1->days;
  list1->days = list2->days;
  list2->days = tmpNum;

  struct tm tmpTime;
  tmpTime = list1->time;
  list1->time = list2->time;
  list2->time = tmpTime;

  char* tmpWords;
  tmpWords = list1->words;
  list1->words = list2->words;
  list2->words = tmpWords;
}

void swap_target(unsigned num1, unsigned num2)
{
  #ifdef DEBUG
    fprintf(stderr, "Swap Target Starting ... \n");
  #endif
  struct Lists *newLists = read_target();
  struct List *preList = newLists->lists;
  struct List *list1 = NULL;
  struct List *list2 = NULL;
  if (newLists->num < num1 || newLists->num < num2 || num1 == num2)
  {
    fprintf(stderr, "Target does not exist or same targets\n");
    return;
  } else
  {
    unsigned cnt = 1;
    while (preList != NULL) {
      if (cnt == num1) {
        list1 = preList;
      } else if (cnt == num2) {
        list2 = preList;
      }
      cnt++;
      preList = preList->next;
    }
    swapTarget(list1, list2);
    write_target_to_file(newLists, 0);
  }
}

