#include "view_controller.hpp"

view_controller::view_controller(const std::string &key,
                                 const std::string &secret)
    : m_trader(key, secret) {

  m_text_user_interface.set_orders({"order 1", "order 2"});
  // m_text_user_interface.setup_windows(0.5, 1.0, 0.0, 0.0);

  //  order order  = order::create_limit_order("BCHEUR", order::side_t::sell, 1,
  //  5900, 1);
  //  // trader.new_order(order);
  // const auto& open_orders = m_trader.open_orders();
  // m_trader.cancel_all_orders();
}
