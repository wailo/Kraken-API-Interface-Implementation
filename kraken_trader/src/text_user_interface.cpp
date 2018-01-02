#include "text_user_interface.hpp"
#include <ncurses.h>
#include <form.h>
#include <array>
#include <string>


using fields_t = std::array<fieldnode*, 4>;


text_user_interface::text_user_interface() {
  /* Ncursor Start */
  initscr();
  noecho();
  cbreak();
}

bool text_user_interface::set_orders(const std::vector<std::string>& orders) {
  m_orders = orders;
  return true;
}

text_user_interface::~text_user_interface() noexcept {

  endwin();
}
