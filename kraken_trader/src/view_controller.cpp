#include "view_controller.hpp"


view_controller::view_controller() {

  m_text_user_interface.setup_windows();

  //  order order  = order::create_limit_order("BCHEUR", order::side_t::sell, 1, 5900, 1);
  //  // trader.new_order(order);
  const auto& open_orders = m_trader.open_orders();
  // m_trader.cancel_all_orders();

}
