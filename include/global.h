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
#ifndef GLOBAL_H_ALNZVGYB
#define GLOBAL_H_ALNZVGYB

#include <stdio.h>
#include <time.h>

/*#define DEBUG 1*/


#define SENTENCES_CONFIG "/.todolist/sentences-config"
#define LIST "/.todolist/list.txt"
#define TARGET "/.todolist/target.txt"
#define LIST_HISTORY "/.todolist/list_history.txt"

char * HOME;

char * sentences_config_path;
char * list_path;
char * target_path;
char * list_history_path;

FILE * sentences_config; /* see ~/.todolist/sentences-config */
FILE * list;             /* see ~/.todolist/list */
FILE * target;           /* see ~/.todolist/target */
FILE * list_history;     /* see ~/.todolist/list-history */

/* 
 * single list structure
 *  order   --stores the output order of this list
 *  words   --stores the content
 */

#define MAXHOMEPATHLEN 250
#define MAXWORDSLEN 250                 /* the max number of characters that one list/target can contain */
#define MAXSENTENCELEN 250              /* the max number of characters that one sentence can contain */


#define VALID_SENTENCE_SYMBOL '>'       /* the begging character of a valid sentence */
#define SENTENCES_CONFIGLINE 157        /* use for selecting sentence randomly
                                           Attention: 
                                             Usually it is the line number of the last valid sentence.
                                             It should not be great than the line of
                                             the last valid sentence */

typedef struct List {
  int order;              /* both list and target */
  char *words;            /* both list and target */
  struct tm time;         /* target */
  unsigned days;          /* targte */
  struct List *next;      /* both list and target */
} List;


/*
 * lists structure
 *  num   --the total number of items
 *  item --target or list
 */

typedef struct Lists {
  unsigned int num;
  struct tm time;
  List *tail;
  List *lists;
} Lists;

#endif /* end of include guard: GLOBAL_H_ALNZVGYB */
