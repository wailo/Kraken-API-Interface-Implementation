#ifndef TRADING_AGENT_H
#define TRADING_AGENT_H

#include "order.hpp"
#include "kraken_interface.hpp"


class trading_agent
{
 public:
  //! Default constructor
  trading_agent();

  //! Copy constructor
  trading_agent(const trading_agent &other) = default;

  //! Move constructor
  trading_agent(trading_agent &&other) = default;

  //! Destructor
  ~trading_agent() = default;

  //! Copy assignment operator
  trading_agent& operator=(const trading_agent &other) = default;

  //! Move assignment operator
  trading_agent& operator=(trading_agent &&other) = default;

  //! send new order
  void new_order( const order& p_order);

  int cancel_order(const std::string& order_id);

  int cancel_all_orders();


 private:

  using orders_storage_t = kraken_interface::order_data_t;

  kraken_interface m_api_intfc;

  orders_storage_t open_orders;


};


#endif /* TRADING_AGENT_H */
