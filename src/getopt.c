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
#include "../include/todolist.h"
#include "../include/getopt.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
  ERR_UO,         /*unrecognized option*/
  ERR_RN,         /*invalid remove number*/
  ERR_SN,         /*invalid swap number*/
  ERR_TFA         /*no remove number*/
} errcode;

static void err(errcode errCode) 
{
  switch(errCode) {
    case ERR_UO:
      fprintf(stderr, "unrecognized option\n");
      break;
    case ERR_RN:
      fprintf(stderr, "invalid remove number, num should be a positive integer\n");
      break;
    case ERR_TFA:
      fprintf(stderr, "too few arguments\n");
      break;
    default:
      break;
  }
}

int 
getopt(argc, argv)
  int argc;
  char *const *argv;
{
  int op = 0;
  if (argc <= 1)
  {
    err(ERR_UO);
    return op;
  } else if (argv[1][0] != '-' || argv[1][2] != 0){
    fprintf(stderr, "%s: unrecognized option '%s'\n",argv[0],argv[1]);
    return 0;
  }
  switch(argv[1][1]) {
    case 'h':
      op = 'h';
      break;
    case 's':
      if (argc < 4) {
        err(ERR_TFA);
        break;
      } else if (atoi(argv[2]) <=0 || atoi(argv[3]) <= 0){
        err(ERR_SN);
        break;
      } else {
        opt.swap_num1 = (unsigned)atoi(argv[2]);
        opt.swap_num2 = (unsigned)atoi(argv[3]);
      }
      op = 's';
      break;
    case 'r':
      if (argc < 3) {
        err(ERR_TFA);
        break;
      } else if (atoi(argv[2]) <= 0) {
        err(ERR_RN);
        break;
      } else {
        opt.remove_num = (unsigned)atoi(argv[2]);
      }
      op = 'r';
      break;
    case 't':
      op = 't';
      opt.target_opt = '\0';
      if (argc >=3) {
        if (argv[2][1] != 0){
          fprintf(stderr, "%s: unrecognized option '%s %s'\n",argv[0],argv[1],argv[2]);
          return 0;
        }
        if (argv[2][0] == 'w') {
          opt.target_opt = 'w';
        } else if (argv[2][0] == 'r') {
          opt.target_opt = 'r';
          if (argc < 4) {
            return 0;
          } else if (atoi(argv[3]) <= 0) {
            return 0;
          } else {
            opt.remove_num = (unsigned)atoi(argv[3]);
          }
        } else if (argv[2][0] == 's') {
          opt.target_opt = 's';
          if (argc < 5) {
            return 0;
          } else if (atoi(argv[3]) <=0 || atoi(argv[4]) <= 0){
            return 0;
          } else {
            opt.swap_num1 = (unsigned)atoi(argv[3]);
            opt.swap_num2 = (unsigned)atoi(argv[4]);
          }
        } else {
          fprintf(stderr, "%s: unrecognized option '%s %s'\n",argv[0],argv[1],argv[2]);
          return 0;
        }
      }
      break;
    case 'w':
      op = 'w';
      break;
    default:
      fprintf(stderr, "%s: unrecognized option '%s'\n",argv[0],argv[1]);
      break;
  }
  opt.opt = op;
  return op;
}
