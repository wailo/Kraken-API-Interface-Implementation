#include "text_user_interface.hpp"
#include <array>
#include <string>

text_user_interface::text_user_interface() {

  /* Ncursor Start */
  initscr();
  noecho();
  cbreak();

}

void text_user_interface::setup_windows() {



  int y, x, y_min, x_min, y_max, x_max;
  getyx(stdscr, y, x);
  getbegyx(stdscr, y_min, x_min);
  getmaxyx(stdscr, y_max, x_max);

  int height = y_max - y_min ;
  int width  = x_max - x_min ;

  WINDOW * menu_win = newwin(10 , x_max-12, y_max-18 , 5);
  box(menu_win, 0,0);
  refresh();
  wrefresh(menu_win);

  keypad(menu_win, true);

  std::array<std::string, 3> choices {"Walk", "Jog", "Run" };
  int  choice;
  int highlight = 0;


  while (true) {
    for (int i=0; i<choices.size(); ++i) {
      if (i == highlight) {
        wattron(menu_win, A_REVERSE);
      }

      mvwprintw(menu_win, i+1, 1, choices[i].c_str());
      wattroff(menu_win, A_REVERSE);
    }


    choice = wgetch(menu_win);
    switch (choice) {
      case KEY_UP:
        highlight--;
        break;
      case KEY_DOWN:
        highlight++;
        break;
      default:
        break;
    }

    if (choice == 10) {
      break;
    }

  }


}


text_user_interface::~text_user_interface() {

  endwin();
}
