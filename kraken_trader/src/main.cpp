#include <iostream>
#include <stdexcept>

#include "../../krakenapi/kraken/kclient.hpp"
#include "trading_agent.hpp"

using namespace std;
using namespace Kraken;

//------------------------------------------------------------------------------

int main() 
{ 
  curl_global_init(CURL_GLOBAL_ALL);
  trading_agent trader;
  // order order  = order::create_limit_order("BCHEUR", order::side_t::sell, 1, 5900, 1, false);
  // trader.new_order(order);
  // trader.cancel_all_orders();
  curl_global_cleanup();
  return 0;
}
