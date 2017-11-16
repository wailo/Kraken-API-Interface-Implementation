#include "order.hpp"


order::order()
{
  // pair = "XXBTZEUR";
  // side = side_t::buy;
  // ordertype = order_type::limit;
  // price  = 6130.0;
  // //price2 = 100000.0;
  // volume = 2.7;
  // leverage = "none";
  // // oflags;
  // starttm =  0;
  // expiretm = 0;
  // // userref;cpc
  // validate = true;
}



const order order::create_limit_order(const std::string& pair,
                                                 order::side_t buy_sell,
                                                 double volume,
                                                 double limit_price,
                                                 bool validate) {
  order order_;
  order_.pair = pair;
  order_.side = buy_sell;
  order_.ordertype = order::order_type::limit;
  order_.price  = limit_price;
  //order_.price2 = 100000.0;
  order_.volume = volume;
  order_.leverage = "none";
  // order_.oflags;
  order_.starttm =  0;
  order_.expiretm = 0;
  // order_.userref;cpc
  order_.validate = validate;
  return order_;
}

