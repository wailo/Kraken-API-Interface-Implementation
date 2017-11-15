#include "order.hpp"


order::order()
{
  pair = "XXBTZEUR";
  side = side_t::buy;
  ordertype = order_type::limit;
  price  = 6130.0;
  //price2 = 100000.0;
  volume = 2.7;
  leverage = "none";
  // oflags;
  starttm =  0;
  expiretm = 0;
  // userref;cpc
  validate = true;
}

