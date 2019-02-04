#include "../include/global.h"
#include "../include/write_list.h"
#include "../include/read_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void write_list_to_file(struct Lists *lists) {
  #ifdef DEBUG
    fprintf(stderr, "Write List Starting ... \n");
  #endif
  
  char home[MAXHOMEPATHLEN];
  strcpy(home, HOME);
  list_path = strcat(home, LIST);
  list = fopen(list_path, "r+");

  struct List* preList = lists->lists;
  if(preList != NULL) {
    struct tm time = lists->time;
    fprintf(list, "%d\n", time.tm_mday);
    fprintf(list, "%d\n", time.tm_mon);
    fprintf(list, "%d\n", time.tm_year);

    while (preList != NULL) {
      fprintf(list, "%s\n", preList->words);
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

  write_list_to_file(newLists);
  //fprintf(stderr, "home: %s\n", getenv("HOME"));
  //print_sentences();
}
