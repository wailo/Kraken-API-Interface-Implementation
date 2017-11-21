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

 private:
  
  kraken_interface m_api_intfc;
  std::vector<order> open_orders;
  
};


#endif /* TRADING_AGENT_H */
