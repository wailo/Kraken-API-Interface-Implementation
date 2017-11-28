#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <ctime>

class order {
public:

  friend class kraken_interface;
  
  //! Default constructor
  order();


  //! Copy constructor
  // order(const order &other);

  //! Move constructor
  // order(order &&other) noexcept;

  //! Destructor
  // virtual ~order() noexcept;

  //! Copy assignment operator
  // order& operator=(const order &other);

  //! Move assignment operator
  // order& operator=(order &&other) noexcept;

  // private:
  enum class order_type {
    market,
    limit,            // (price = limit price)
    stop_loss,        // (price = stop loss price)
    take_profit,      // (price = take profit price)
    stop_loss_profit, // (price = stop loss price, price2 = take profit price)
    stop_loss_profit_limit, // (price = stop loss price, price2 = take profit price)
    stop_loss_limit,   // (price = stop loss trigger price, price2 = triggered limit price)
    take_profit_limit, // (price = take profit trigger price, price2 = triggered limit price)
    trailing_stop,     // (price = trailing stop offset)
    trailing_stop_limit, // (price = trailing stop offset, price2 = triggered limit offset)
    stop_loss_and_limit, // (price = stop loss price, price2 = limit price)
    settle_position,
  };

  enum class side_t { buy, sell };

  static const order create_limit_order(const std::string& pair,
                                        order::side_t buy_sell,
                                        double volume,
                                        double limit_price,
                                        int userref,
                                        bool validate = true);

  
 private:
  
  // asset pair
  std::string pair;

  // type of order (buy/sell)
  side_t side;

  // order type:
  order_type ordertype;

  //  price (optional.  dependent upon ordertype)
  double price;

  // secondary price (optional.  dependent upon ordertype)
  double price2;

  // order volume in lots
  double volume;

  // amount of leverage desired (optional.  default = none);
  std::string leverage;

  // comma delimited list of order flags (optional):
  std::string oflags;

  // scheduled start time (optional):
  long unsigned int starttm;

  // expiration time (optional):
  long unsigned int expiretm;

  // user reference id.  32_bit signed number.  (optional)
  std::string userref;

  // validate inputs only.  do not submit order (optional)
  bool validate{true};
};

#endif /* ORDER_H */
