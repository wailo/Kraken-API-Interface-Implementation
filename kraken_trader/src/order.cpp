#include "order.hpp"

order order::create_limit_order(const std::string &pair,
                                order::side_t buy_sell, double volume,
                                double limit_price, int userref,
                                bool validate) {
  order order_;
  order_.m_pair = pair;
  order_.m_side = buy_sell;
  order_.m_ordertype = order::order_type::limit;
  order_.m_price = limit_price;
  // order_.m_price2 = 100000.0;
  order_.m_volume = volume;
  order_.m_leverage = "none";
  // order_.m_oflags;
  order_.m_starttm = 0;
  order_.m_expiretm = 0;
  order_.m_userref = std::to_string(userref);
  order_.m_validate = validate;
  return order_;
}
