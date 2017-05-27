#include <ncurses.h>
#include "include/text_mode.h"
//#include <iostream>
//#include <string>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

//std::string choices[] =
char * choices[] =
                  {
                    (char*)"Choice 1",
		    (char*)"Choice 2",
		    (char*)"Choice 3",
		    (char*)"Choice 4",
		    (char*)"Exit",
                  };

int n_choices = sizeof(choices) / sizeof( char * );
void print_menu(WINDOW *menu_win, int highlight);

void text_mode_init()
{
  int row,col;

  initscr();			/* Start curses mode 		  */
  getmaxyx(stdscr,row,col);
  printw("Hello World !!! %d, %d",row,col);	/* Print Hello World		  */
  refresh();			/* Print it on to the real screen */
  getch();			/* Wait for user input */
  endwin();			/* End curses mode		  */
}

void text_mode_menu()
{
  WINDOW *menu_win;
  int highlight = 1 ;
  int choice = 0 ;
  int c ;

  initscr();
  clear();
  noecho();
  cbreak();
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  keypad(menu_win, TRUE);
  mvprintw(0,0, "Use arrow keys to go up and down, Press enter to select a choice");
  refresh();
  print_menu(menu_win, highlight);
  while(1)
  {
    c = wgetch(menu_win);
    switch(c)
    {
      case KEY_UP:
      {
        if(highlight ==1)
	{
          highlight = n_choices;
	}
	else
	{
          --highlight;
	}
	break;
      }
      case KEY_DOWN:
      {
        if(highlight == n_choices)
	{
          highlight = 1;
	}
	else
	{
          ++highlight;
	}
	break;
      }
      case 10:
      {
        choice = highlight;
	break;
      }
      default:
      {
        mvprintw(24,0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c , c);
	refresh();
	break;
      }
    }
    print_menu(menu_win, highlight);
    if(choice != 0)
    {
      break;
    }
  }
  mvprintw(23,0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
  clrtoeol();
  refresh();
  endwin();

}

void print_menu(WINDOW *menu_win, int highlight)
{
  int x, y, i;

  x=2;
  y=2;
  box(menu_win, 0, 0);
  for(i = 0 ; i < n_choices; ++i)
  {
    if(highlight == i + 1)
    {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    }
    else
    {
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    }
    ++y;
  }
  wrefresh(menu_win);
}




