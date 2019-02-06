#ifndef GLOBAL_H
#define GLOBAL_H 1

#include <stdio.h>
#include <time.h>

//#define DEBUG 1


#define SENTENCES_CONFIG "/.todolist/sentences-config"
#define LIST "/.todolist/list.txt"
#define LIST_HISTORY "/.todolist/list_history.txt"

char * HOME;

char * sentences_config_path;
char * list_path;
char * list_history_path;

FILE * sentences_config; /* see ~/.todolist/sentences-config */
FILE * list;             /* see ~/.todolist/list */
FILE * list_history;     /* see ~/.todolist/list-history */

/* 
 * single list structure
 *  order   --stores the output order of this list
 *  words   --stores the content
 */

#define MAXHOMEPATHLEN 250
#define MAXWORDSLEN 250                 /* the max number of characters that one list can contain */
#define MAXSENTENCELEN 250              /* the max number of characters that one sentence can contain */


#define VALID_SENTENCE_SYMBOL '>'       /* the begging character of a valid sentence */
#define SENTENCES_CONFIGLINE 100        /* use for selecting sentence randomly
                                           Attention: 
                                             Usually it is the line number of the last valid sentence.
                                             It should not be great than the line of
                                             the last valid sentence */

typedef struct List {
  int order;
  char *words;
  struct List *next;
} List;

/*
 * lists structure
 *  num   --the total number of lists
 *  lists --lists
 */

typedef struct Lists {
  unsigned int num;
  struct tm time;
  struct List *tail;
  struct List *lists;
} Lists;

#endif
