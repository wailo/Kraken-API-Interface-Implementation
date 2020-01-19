#include <iostream>
#include <stdexcept>

#include "kraken/kclient.hpp"
#include "view_controller.hpp"

using namespace std;
using namespace Kraken;

//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  if (argc < 3) {
    cerr << "Must be called with key and a secret tokens for API authentication"
         << endl;
  }

  const auto &key = argv[1];
  const auto &secret = argv[2];

  curl_global_init(CURL_GLOBAL_ALL);
  view_controller trading_platform(key, secret);

  return 0;
}
