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
#ifndef TODOLIST_H_RAU9Y12W
#define TODOLIST_H_RAU9Y12W

#define VIEW_LEN 20                           /* words to be displayed every line */


#define PROJECT "todolist"                    /* name if program */
#define VERSION "--VERSION--"                 /* current release of project */


typedef struct {
  int date;
  char opt;                                   /* option code
                                               * option can be:
                                               *   'h'
                                               *   'r'
                                               *   'w'
                                               *   's'
                                               *   't'
                                               */
  char target_opt;                            /* option code of target
                                               * option can be:
                                               *   'r'
                                               *   'w'
                                               *   's'
                                               */
  unsigned remove_num;                        /* Number of list to remove */

  unsigned swap_num1;                         
  unsigned swap_num2;

  int days;
} opt_t;

extern opt_t opt;

#endif /* end of include guard: TODOLIST_H_RAU9Y12W */
