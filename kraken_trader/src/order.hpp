#ifndef ORDER_H
#define ORDER_H

#include <ctime>
#include <string>

class order {
public:
  friend class kraken_interface;

  //! Default constructor is disabled
  order() = default;

  // order type
  enum class order_type {
    market,
    limit,            // (price = limit price)
    stop_loss,        // (price = stop loss price)
    take_profit,      // (price = take profit price)
    stop_loss_profit, // (price = stop loss price, price2 = take profit price)
    stop_loss_profit_limit, // (price = stop loss price, price2 = take profit
                            // price)
    stop_loss_limit,   // (price = stop loss trigger price, price2 = triggered
                       // limit price)
    take_profit_limit, // (price = take profit trigger price, price2 = triggered
                       // limit price)
    trailing_stop,     // (price = trailing stop offset)
    trailing_stop_limit, // (price = trailing stop offset, price2 = triggered
                         // limit offset)
    stop_loss_and_limit, // (price = stop loss price, price2 = limit price)
    settle_position,
  };

  // order side
  enum class side_t { buy, sell };

  // Helper function to create a limit order
  static order create_limit_order(const std::string &pair,
                                  const order::side_t buy_sell,
                                  const double volume, const double limit_price,
                                  const int userref,
                                  const bool validate = true);

private:
  // asset pair
  std::string m_pair;

  // type of order (buy/sell)
  side_t m_side;

  // order type:
  order_type m_ordertype;

  //  price (optional.  dependent upon ordertype)
  double m_price;

  // secondary price (optional.  dependent upon ordertype)
  double m_price2;

  // order volume in lots
  double m_volume;

  // amount of leverage desired (optional.  default = none);
  std::string m_leverage;

  // comma delimited list of order flags (optional):
  std::string m_oflags;

  // scheduled start time (optional):
  long unsigned int m_starttm;

  // expiration time (optional):
  long unsigned int m_expiretm;

  // user reference id.  32_bit signed number.  (optional)
  std::string m_userref;

  // validate inputs only.  do not submit order (optional)
  bool m_validate{true};
};

#endif /* ORDER_H */
