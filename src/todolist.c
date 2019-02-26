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
#include "../include/print_list.h"
#include "../include/edit_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

opt_t opt;

static void init(void) 
/*
 * Initial environment.
 *
 */
{
  HOME = getenv("HOME");
}

static void usage (FILE *st)
/*
 * Print usage information on stream st.
 *
 */
{
  fprintf (st, "Usage:  %s [options]\n", PROJECT);
  fprintf (st, "        -h              print usage information\n");
  fprintf (st, "        -s num1 num2    swap list num1, num2\n");
  fprintf (st, "        -r num          remove list item by order number\n");
  fprintf (st, "        -w              write todolist\n");
  fprintf (st, "        -t              print all targets\n");
  fprintf (st, "        -t s num1 num2  swap target num1, num2\n");
  fprintf (st, "        -t r num1       remove target item by order number\n");
  fprintf (st, "        -t w            write target\n");
}

static void usage_short (FILE *st)
/*
 * Print abbreviated usage information on stream st.
 *
 */
{
  fprintf(st, "Usage: %s [options]\n", PROJECT);
  fprintf(st, "Try '%s -h' for more information\n", PROJECT);
}

static void usage_long (FILE *st)
/*
 * Print usage information on stream st, including a header text.
 *
 */
{
  fprintf(st, "%s - lists your to-do list and helps you manage your energy\n", PROJECT);
  fprintf(st, "       (c) Lawrence Zou <email: iwatchnima@gmail.com>\n");
  fprintf(st, "       web page: not created yet!\n");
  usage (st);
}

static void process_commandline(int argc, char *argv[])
/*
 * Process command line options.
 *
 *  argc, argv   command line as passed to main())
 *
 */
{
  int oc;

  memset (&opt, 0, sizeof(opt_t));

  if (argc <= 1) {
    print_list();
    return ;
  }

  if (argc >= 2 && argv[1] != NULL
      && (strcmp(argv[1], "--help") == 0|| strcmp(argv[1], "-?") == 0))
  {
    usage_long(stdout);
    return ;
  }

  /*
   * Parse Command Line
   */
  do {
    oc = getopt(argc, argv);
    switch (oc) {
      case 'd':
        break;
      case 'h':
        usage_long(stdout);
        break;
      case 'l':
        break;
      case 'm':
        break;
      case 's':
        swap_list(opt.swap_num1, opt.swap_num2);
        break;
      case 't':
        if (opt.target_opt == '\0') {
          print_target();
        } else {
          if (opt.target_opt == 'w') {
            write_target();
          } else if (opt.target_opt == 's') {
            swap_target(opt.swap_num1, opt.swap_num2);
          } else if (opt.target_opt == 'r') {
            remove_target(opt.remove_num);
          } else {
          }
        }
        break;
      case 'r':
        remove_list(opt.remove_num);
        break;
      case 'w':
        write_list();
        break;
      default:
        usage_short(stdout);
        break;
    }
  } while(0);
  return ;
}

int main(int argc, char *argv[]) 
{
  init();

  #ifdef DEBUG
    fprintf(stderr, "TODOLIST STARTING ...\n");
  #endif

  /*
   * Prrocess command line options
   */
  #ifdef DEBUG
    fprintf(stderr, "Parsing Command Line ...\n");
  #endif
  
  process_commandline(argc, argv);
  return EXIT_SUCCESS;
}
