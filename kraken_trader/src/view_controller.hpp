#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

#include "text_user_interface.hpp"
#include "trading_agent.hpp"

class view_controller {
public:
  //! Default constructor
  view_controller(const std::string &key, const std::string &secret);

private:
  trading_agent m_trader;
  text_user_interface m_text_user_interface;
};

#endif /* VIEW_CONTROLLER_H */
