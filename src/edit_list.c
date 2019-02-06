#include "../include/global.h"
#include "../include/edit_list.h"
#include "../include/read_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void write_list_to_file(struct Lists *lists, unsigned int skipList) {
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
      if (cnt != skipList) {
        fprintf(list, "%s\n", preList->words);
      }
      cnt++;
      preList = preList->next;
    }
  }
  fclose(list);
}

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
    int i = 0;
    char str[MAXWORDSLEN];
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
  //fprintf(stderr, "home: %s\n", getenv("HOME"));
  //print_sentences();
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
  struct List *list1;
  struct List *list2;
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
    write_list_to_file(newLists, -1);
  }
}
