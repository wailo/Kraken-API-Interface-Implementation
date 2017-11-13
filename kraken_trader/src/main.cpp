#include <iostream>
#include <stdexcept>

#include "../../krakenapi/kraken/kclient.hpp"
#include "order.hpp"

using namespace std;
using namespace Kraken;

//------------------------------------------------------------------------------

int main() 
{ 
  curl_global_init(CURL_GLOBAL_ALL);
  try {
    
    KClient kapi("ap17PlvHnPKnshgUp6BLN0ugzoacA3W12W2lphhp2zHoAFhMuKfcDihz",
              "npeixUc5WShaqIsqV9Kk2dgnQs3zBFMjCg45hK8MS93W4o/E2tcjOviFwn+zvLT6ty+plFEusbPlNQrqKmh82w==");
    
    // KInput spread;
    // // get recent trades 
    // spread.insert(make_pair("pair", "XXBTZEUR"));
    // cout << kapi.public_method("Spread", spread) << endl;

    // std::cout << "------------ end of data -----------" << std::endl;
    
    // KInput closed_orders;
    // // get recent trades
    // closed_orders.insert(make_pair("pair", "XXBTZEUR"));
    // //closed_orders.insert(make_pair("trades", "true"));
    // cout << kapi.private_method("ClosedOrders", closed_orders) << endl;

    // std::cout << "------------ end of data -----------" << std::endl;
     order dummy_order;
    auto dummy_order_data = dummy_order.to_kraken_order();

    for ( auto item : dummy_order_data ) { 
      std::cout << item.first << " -- " << item.second << std::endl;
    }

    cout << kapi.private_method("AddOrder", dummy_order_data) << endl;
  }
  catch(exception& e) {
    cerr << "Error: " << e.what() << endl;
  }
  catch(...) {
    cerr << "Unknow exception." << endl;
  }

  curl_global_cleanup();
  return 0;
}
