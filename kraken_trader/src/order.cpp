#include "order.hpp"


/*
  pair = asset pair
  type = type of order (buy/sell)
  ordertype = order type:
  market
  limit (price = limit price)
  stop-loss (price = stop loss price)
  take-profit (price = take profit price)
  stop-loss-profit (price = stop loss price, price2 = take profit price)
  stop-loss-profit-limit (price = stop loss price, price2 = take profit price)
  stop-loss-limit (price = stop loss trigger price, price2 = triggered limit price)
  take-profit-limit (price = take profit trigger price, price2 = triggered limit price)
  trailing-stop (price = trailing stop offset)
  trailing-stop-limit (price = trailing stop offset, price2 = triggered limit offset)
  stop-loss-and-limit (price = stop loss price, price2 = limit price)
  settle-position
  price = price (optional.  dependent upon ordertype)
  price2 = secondary price (optional.  dependent upon ordertype)
  volume = order volume in lots
  leverage = amount of leverage desired (optional.  default = none)
  oflags = comma delimited list of order flags (optional):
  viqc = volume in quote currency (not available for leveraged orders)
  fcib = prefer fee in base currency
  fciq = prefer fee in quote currency
  nompp = no market price protection
  post = post only order (available when ordertype = limit)
  starttm = scheduled start time (optional):
  0 = now (default)
  +<n> = schedule start time <n> seconds from now
  <n> = unix timestamp of start time
  expiretm = expiration time (optional):
  0 = no expiration (default)
  +<n> = expire <n> seconds from now
  <n> = unix timestamp of expiration time
  userref = user reference id.  32-bit signed number.  (optional)
  validate = validate inputs only.  do not submit order (optional)

  optional closing order to add to system when order gets filled:
  close[ordertype] = order type
  close[price] = price
  close[price2] = secondary price


*/
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

const order order::create_limit_order(const std::string& pair,
                                      side_t buy_sell,
                                      double volume,
                                      double limit_price,
                                      bool validate) {
  order order_;
  order_.pair = pair;
  order_.side = buy_sell;
  order_.ordertype = order_type::limit;
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

const std::unordered_map<order::order_type, const std::string > order::order_types_to_string = {
  {order_type::market, "market"},
  {order_type::limit, "limit"},
  {order_type::stop_loss, "stop_loss"},
  {order_type::take_profit, "take_profit"},
  {order_type::stop_loss_profit, "stop_loss_profit"},
  {order_type::stop_loss_profit_limit, "stop_loss_profit_limit"},
  {order_type::stop_loss_limit, "stop_loss_limit"},
  {order_type::take_profit_limit, "take_profit_limit"},
  {order_type::trailing_stop, "trailing_stop"},
  {order_type::trailing_stop_limit, "trailing_stop_limit"},
  {order_type::stop_loss_and_limit, "stop_loss_and_limit"},
  {order_type::settle_position, "settle_position"}    
};

const std::unordered_map< std::string, const order::order_type> order::order_types_to_enum = {
  {"market", order_type::market},
  {"limit", order_type::limit},
  {"stop_loss", order_type::stop_loss},
  {"take_profit", order_type::take_profit},
  {"stop_loss_profit", order_type::stop_loss_profit},
  {"stop_loss_profit_limit", order_type::stop_loss_profit_limit},
  {"stop_loss_limit", order_type::stop_loss_limit},
  {"take_profit_limit", order_type::take_profit_limit},
  {"trailing_stop", order_type::trailing_stop},
  {"trailing_stop_limit", order_type::trailing_stop_limit},
  {"stop_loss_and_limit", order_type::stop_loss_and_limit},
  {"settle_position", order_type::settle_position}
};

order::Input order::to_kraken_order() const
{
  Input data;
  data["pair"]      = pair;
  data["type"]      = side_to_string(side);
  data["ordertype"] = order_types_to_string.at(ordertype);
  data["price"]    = std::to_string(price);
  data["price2"]    = std::to_string(price2);
  data["volume"]    = std::to_string(volume);
  data["leverage"]  = leverage;
  if (!oflags.empty()) {
    data["oflags"] = oflags;
  }
  data["starttm"]   = std::to_string(starttm);
  data["expiretm"]  = std::to_string(expiretm);
  data["userref"]   = userref;

  if (validate) {
    data["validate"];
  }

  return data;
}

// from kraken map
order order::from_kraken_order(order::Input& data)
{
  order order_;
  order_.pair      = data["pair"];
  order_.side      = side_from_string(data["type"]);
  order_.ordertype = order_types_to_enum.at(data["ordertype"]);
  order_.price     = std::stod(data["price"]);
  order_.price2    = std::stod(data["price2"]);
  order_.volume    = std::stod(data["volume"]);
  order_.leverage  = data["leverage"];
  order_.oflags    = data["oflags"];
  order_.starttm   = std::stoi(data["starttm"]);
  order_.expiretm  = std::stoi(data["expiretm"]);
  order_.userref   = data["userref"];
  order_.validate  = (data.find("validate") != data.end());
  return order_; 
}


