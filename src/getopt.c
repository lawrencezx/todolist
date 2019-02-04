#include "../include/global.h"
#include "../include/getopt.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int 
getopt(argc, argv)
  int argc;
  char *const *argv;
{
  int op = 0;
  switch(argv[1][1]) {
    case 'd':
      op = 'd';
      break;
    case 'h':
      op = 'h';
      break;
    case 'l':
      op = 'l';
      break;
    case 'm':
      op = 'm';
      break;
    case 'r':
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
