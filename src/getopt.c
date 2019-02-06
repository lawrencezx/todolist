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
  }
  switch(argv[1][1]) {
    //case 'd':
    //  op = 'd';
    //  break;
    case 'h':
      op = 'h';
      break;
    //case 'l':
    //  op = 'l';
    //  break;
    //case 'm':
    //  op = 'm';
    //  break;
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
    case 'w':
      op = 'w';
      break;
    default:
      fprintf(stderr, "%s: unrecognized option '%s'\n",argv[0],argv[1]);
      break;
  }
  return op;
}
