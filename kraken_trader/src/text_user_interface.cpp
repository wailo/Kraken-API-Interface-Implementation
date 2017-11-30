#include "text_user_interface.hpp"
#include <array>
#include <string>

text_user_interface::text_user_interface() {

  /* Ncursor Start */
  initscr();
  noecho();
  cbreak();

}

bool text_user_interface::set_orders(const std::vector<std::string> orders) {
  m_orders = orders;
  return true;
}


void text_user_interface::setup_windows(float y_min, float x_min, float y_max, float x_max) {

  int y_min_screen, x_min_screen,  y_max_screen, x_max_screen;
  getbegyx(stdscr, y_min_screen, x_min_screen);
  getmaxyx(stdscr, y_max_screen, x_max_screen);  

  y_min_screen = y_min * y_max_screen;
  y_max_screen = y_max * y_max_screen;

  x_min_screen = x_min * x_min_screen;
  x_max_screen = x_max * x_max_screen;

  WINDOW * menu_win = newwin(10,
                             y_max_screen,
                             y_max_screen,
                             x_max_screen);
  box(menu_win, 0,0);
  refresh();
  wrefresh(menu_win);

  keypad(menu_win, true);

  int  choice;
  int highlight = 0;


  while (true) {
    for (int i=0; i<m_orders.size(); ++i) {
      if (i == highlight) {
        wattron(menu_win, A_REVERSE);
      }

      mvwprintw(menu_win, i+1, 1, m_orders[i].c_str());
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


text_user_interface::~text_user_interface() noexcept {

  endwin();
}
