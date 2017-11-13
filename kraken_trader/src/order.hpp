#ifndef ORDER_H
#define ORDER_H

#include "../../krakenapi/kraken/kclient.hpp"

#include <ctime>
#include <unordered_map>

class order {
public:
  using Input = Kraken::KInput;
  //! Default constructor
  order();

  // convert to kraken map
  Input to_kraken_order() const;

  // from kraken map
  static order from_kraken_order(Input &data);

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
  
  static const std::unordered_map<order_type, const std::string > order_types_to_string;
  static const std::unordered_map< std::string, const order_type> order_types_to_enum;
  static const order create_limit_order(const std::string& pair,
                                        side_t buy_sell,
                                        double volume,
                                        double limit_price,
                                        bool validate = true);
                                        
  static std::string side_to_string(side_t side) {
    if ( side == side_t::buy ) {
      return "buy";
    }
    else if ( side == side_t::sell ) {
      return "sell";
    }
    
    throw std::logic_error("Unknown side_t side");
  }


  static side_t side_from_string(const std::string& side) {
    if ( side == "buy" ) {
      return side_t::buy;
    }
    else if ( side == "sell" ) {
      return side_t::sell;
    }
    
    throw std::logic_error("Unknown side name");
  }
  
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
