#include "../include/global.h"
#include "../include/print_list.h"
#include "../include/read_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define random(x) (rand() % (x))

static void print_date(struct tm time) 
{
  fprintf(stderr, "date:%2.d,%2.d,%5.d\n", time.tm_mday, 1 + time.tm_mon, 1900 + time.tm_year);
}

static void print_lists(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Print Lists Starting ... \n");
  #endif
    
  struct Lists* lists = read_list();
  #ifdef DEBUG
    fprintf(stderr, "pass read_list\n");
  #endif
  struct List* preList = lists->lists;
  print_date(lists->time);
  if (preList == NULL) {
   fprintf(stderr, "I don't have anything to do yet!\n");
  } else {
    if (lists->num == 1) {
      fprintf(stderr, "I have only one thing to do today!\n");
    } else {
      fprintf(stderr, "We have %d things to do today!\n", lists->num);
    }
    int order = 1;
    fprintf(stderr, "\n");
    while (preList != NULL) {
      fprintf(stderr, "\033[;31m List %d\033[0m => \033[;31;1m%s\033[0m\n", order++, preList->words);
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
    fscanf((FILE*)sentences_config, "%s", buff);
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

void print_list(void) 
{
  #ifdef DEBUG
    fprintf(stderr, "Print List Starting ... \n");
  #endif
  print_lists();
  print_sentences();
}
