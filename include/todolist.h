#ifndef TODOLIST_H
#define TODOLIST_H

/* #define DEBUG*/

#define VIEW_LEN 20 /* words to be displayed every line*/


#define PROJECT "todolist"                 /* name if program */
#define VERSION "--VERSION--"              /* current release of project */


typedef struct {
  int date;
  char opt;                                   /* option code of remove_num
                                               * option can be:
                                               *   'h'
                                               *   'r'
                                               *   'w'
                                               *   's'
                                               */
  unsigned remove_num;                    /* Number of list to remove*/

  unsigned swap_num1;
  unsigned swap_num2;
} opt_t;

extern opt_t opt;

#endif
