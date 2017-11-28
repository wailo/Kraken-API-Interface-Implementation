#include "trading_agent.hpp"


trading_agent::trading_agent()
{

  // get open orders;
  {
    auto fn_open_orders = [&](){ return m_api_intfc.get_open_orders(boost::none, boost::none);};
    auto open_orders_res =  m_api_intfc.send_api_request(3, fn_open_orders);
    if (open_orders_res) {
      open_orders = open_orders_res.get();
    }
    else
      {
        throw std::runtime_error("Can't get open orders.");
      }
  }
}


int trading_agent::cancel_order(const std::string& order_id) {
  auto fn_cancel_orders = [&](){ return m_api_intfc.cancel_open_order(order_id); };
  auto cancel_orders_res =  m_api_intfc.send_api_request(3, fn_cancel_orders);

  if (cancel_orders_res) {
    return cancel_orders_res.get()["count"] != "0";
  }
  return -1;


}

int trading_agent::cancel_all_orders() {
  int count = 0;
  for ( auto& order : open_orders ) {
    const auto& id = order["id"];
    count+= cancel_order(id);
  }

  return count;
}


//! send new order
void trading_agent::new_order( const order& p_order) {
    auto fn_new_order = [&](){ return m_api_intfc.add_standard_order(p_order);};
    auto new_orders_res =  m_api_intfc.send_api_request(4, fn_new_order);
}


// // Get open orders;
// {
//   auto fn_trade_balance  = [&](){ return m_api_intfc.get_trade_balance("", "");};
//   auto trade_balance_res =  m_api_intfc.send_api_request(3, fn_trade_balance);
//   if (trade_balance_res) {
//     open_orders = trade_balance_res.get();
//   }
//   else
//   {
//     throw std::runtime_error("Can't get open orders.");
//   }
// }

//  m_api_intfc.get_trade_balance(boost::none, boost::none);
//  m_api_intfc.add_standard_order(const order &order_)
// }
