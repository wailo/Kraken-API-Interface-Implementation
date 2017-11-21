#include "trading_agent.hpp"


trading_agent::trading_agent() {
  m_api_intfc.get_open_orders(boost::none, boost::none);
  m_api_intfc.get_trade_balance(boost::none, boost::none);
  //  m_api_intfc.add_standard_order(const order &order_)
}
