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
#include "../include/print_list.h"
#include "../include/read_list.h"
#include "../include/time_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define random(x) (rand() % (x))

static void print_lists(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Print Lists Starting ... \n");
  #endif
    
  struct Lists* lists = read_list();
  struct List* preList = lists->lists;
  print_date(lists->time);
  if (preList == NULL) {
   fprintf(stderr, "I don't have anything to do yet!\n");
  } else {
    if (lists->num == 1) {
      fprintf(stderr, "I have only one thing to do today!\n");
    } else {
      fprintf(stderr, "I have %d things to do today!\n", lists->num);
    }
    int order = 1;
    fprintf(stderr, "\n");
    while (preList != NULL) {
      fprintf(stderr, "\033[;31m List %d\033[0m => \033[;31;1m%s\033[0m\n", order++, preList->words);
      preList = preList->next;
    }
  }
}

static void print_targets(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Print Targtes Starting ... \n");
  #endif
    
  struct Lists* lists = read_target();
  struct List* preList = lists->lists;
  print_date(lists->time);
  if (preList == NULL) {
   fprintf(stderr, "I don't have any target to achieve!\n");
  } else {
    if (lists->num == 1) {
      fprintf(stderr, "I have only one target to achieve!\n");
    } else {
      fprintf(stderr, "I have %d targets to achieve!\n", lists->num);
    }
    fprintf(stderr, "\n");
    struct tm *now = &(lists->time);
    fprintf(stderr, "\033[;31;1m COUNTDOWN \033[0m\033[;31;1m   TARGET\033[0m\n");
    while (preList != NULL) {
      int days = preList->days - day_diff((preList->time).tm_year, (preList->time).tm_mon, (preList->time).tm_mday
          , now->tm_year, now->tm_mon, now->tm_mday); 
      if (days == 0) {
        fprintf(stderr, "\033[;31m deadline \033[0m => \033[;31;1m%s\033[0m\n", preList->words);
      } else if (days == 1) {
        fprintf(stderr, "\033[;31m %4.d day \033[0m => \033[;31;1m%s\033[0m\n", days, preList->words);
      } else {
        fprintf(stderr, "\033[;32m %4.d days\033[0m => \033[;32;1m%s\033[0m\n", days, preList->words);
      }
      preList = preList->next;
    }
  }
}

static void print_sentences(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Print Sentences Starting ... \n");
  #endif
  fprintf(stderr, "\n");
  char home[MAXHOMEPATHLEN];
  strcpy(home, HOME);
  sentences_config_path = strcat(home, SENTENCES_CONFIG);
  sentences_config = fopen(sentences_config_path, "r");

  char buff[MAXSENTENCELEN];
  if (sentences_config == NULL) {
    fprintf(stderr, "sentences_config not useful yet!\n See %s \n", sentences_config_path);
  }
  srand(time(NULL));
  int skiplines = random(SENTENCES_CONFIGLINE);
  while(skiplines > 0) {
    if (fscanf((FILE*)sentences_config, "%s", buff) == EOF) {
      fprintf(stderr, "skiplines = %d, Sentences are not enough\n", skiplines);
      break;
    }
    skiplines--;
  }
  while(fscanf((FILE*)sentences_config, "%s", buff) != EOF) 
  {
    if (buff[0] == VALID_SENTENCE_SYMBOL) {
      strcpy(buff, buff+1);
      fprintf(stderr, "\033[1m %s \033[0m\n", buff);
      break;
    }
  }
  fclose(sentences_config);
}

/*
 * Layout:
 *   date
 *   I have ** things to do today!
 *   List num (list order) => list content
 *   A piece of advice
 *
 */
void print_list(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Print List Starting ... \n");
  #endif
  print_lists();
  print_sentences();
}

/*
 * Layout:
 *   date
 *   I have ** targets to achieve!
 *   countdown => target content
 *   A piece of advice
 *
 */
void print_target(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Print Target Starting ... \n");
  #endif
  print_targets();
  print_sentences();
}
