#include <iostream>
#include <stdexcept>

#include "kraken/kclient.hpp"
#include "view_controller.hpp"

using namespace std;
using namespace Kraken;

//------------------------------------------------------------------------------

int main() {
  curl_global_init(CURL_GLOBAL_ALL);
  view_controller trading_platform;
  curl_global_cleanup();
  return 0;
}
