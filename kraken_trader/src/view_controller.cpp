#include "view_controller.hpp"


view_controller::view_controller() {

  std::vector<std::string> order_menu_list;
  // auto const& orders = m_trader.open_orders();
  // for( const auto& order : orders ) {
  //   std::string raw_data;
  //   for ( const auto& val : order) {
  //     raw_data += (val.first + ":" + val.second);
  //   }

  //   order_menu_list.push_back(raw_data);
  // }

  order_menu_list.push_back("order 1");
  order_menu_list.push_back("order 2");
  m_text_user_interface.set_orders(order_menu_list);
  // m_text_user_interface.setup_windows(0.5, 1.0, 0.0, 0.0);

  //  order order  = order::create_limit_order("BCHEUR", order::side_t::sell, 1, 5900, 1);
  //  // trader.new_order(order);
  // const auto& open_orders = m_trader.open_orders();
  // m_trader.cancel_all_orders();

}
