#define BOOST_TEST_MAIN
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif

// Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BaseClassModule"

#include "libjson/libjson.h"
#include <boost/test/unit_test.hpp>

#define private public
#define protected public

#include "../src/kraken_interface.hpp"

const auto key = "key";
const auto secret = "secret";

BOOST_AUTO_TEST_CASE(get_order_book) {

  kraken_interface api_intfc(key, secret);
  const auto root = api_intfc.get_order_book("XXBTZEUR", 5);

  BOOST_REQUIRE_EQUAL(root == std::nullopt, false);

  // Check for errors.
  BOOST_CHECK_EQUAL(root.value().at("error").empty(), true);

  // // append errors to output string stream
  // for (auto it = root["error"].begin(); it != root["error"].end(); ++it)
  //    oss << endl << " * " << libjson::to_std_string(it->as_string());

  // Check if there are data
  BOOST_CHECK_EQUAL(!root.value().at("result").empty(), true);

  // const string& pair = i.at("pair");
  // JSONNode& result = root["result"];
  // JSONNode& result_pair = result.at(pair);

  // vector<Trade> output;
  // for (JSONNode::iterator it = result_pair.begin();
  //      it != result_pair.end(); ++it)
  //   output.push_back(Trade(*it));

  // output.swap(v);
  // return libjson::to_std_string( result.at("last").as_string() );
}

BOOST_AUTO_TEST_CASE(get_asset_info) {

  kraken_interface api_intfc(key, secret);
  ;
  auto const &root = api_intfc.get_asset_info(std::optional<std::string>(),
                                              std::optional<std::string>(),
                                              std::optional<std::string>());

  BOOST_REQUIRE_EQUAL(root == std::nullopt, false);

  // Check for errors.
  BOOST_CHECK_EQUAL(root.value().at("error").empty(), true);

  // Check if there are data
  BOOST_CHECK_EQUAL(!root.value().at("result").empty(), true);
}

BOOST_AUTO_TEST_CASE(get_tradable_pairs) {

  kraken_interface api_intfc(key, secret);
  ;
  auto root = api_intfc.get_tradable_pairs(std::optional<std::string>(),
                                           std::optional<std::string>());

  BOOST_REQUIRE_EQUAL(root == std::nullopt, false);
  // Check for errors.
  BOOST_CHECK_EQUAL(root.value().at("error").empty(), true);

  // Check if there are data
  BOOST_CHECK_EQUAL(!root.value().at("result").empty(), true);
}

BOOST_AUTO_TEST_CASE(get_open_orders) {

  kraken_interface api_intfc(key, secret);
  ;
  auto result = api_intfc.get_open_orders(std::optional<std::string>(),
                                          std::optional<std::string>());

  BOOST_REQUIRE_EQUAL(result == std::nullopt, false);

  for (auto const &row : result.value()) {
    for (auto const &val : row) {
      std::cout << val.first << " -- " << val.second << std::endl;
    }
  }
}

BOOST_AUTO_TEST_CASE(add_standard_order) {

  int volume = 1;
  int userref = 0;
  order order_ = order::create_limit_order("BCHEUR", order::side_t::sell,
                                           volume, 11150, userref);
  kraken_interface api_intfc(key, secret);
  ;
  int tries = 3;
  std::optional<JSONNode> root;

  auto fn = [&]() -> std::optional<JSONNode> {
    return api_intfc.add_standard_order(order_);
  };
  root = api_intfc.send_api_request(3, fn);

  BOOST_REQUIRE_EQUAL(root == std::nullopt, false);
  // std::cout << root.value().at("error").as_string() << std::endl;
  // std::cout << root.value().at("result").as_string() << std::endl;
  BOOST_CHECK_EQUAL(!root.value().at("result").empty(), true);
}

BOOST_AUTO_TEST_CASE(retry) {

  auto fn = []() {
    std::cout << "test" << std::endl;
    return std::optional<JSONNode>();
  };

  kraken_interface api_intfc(key, secret);
  ;

  auto res = api_intfc.send_api_request(3, fn);
  BOOST_CHECK_EQUAL(!res, true);
}

// BOOST_AUTO_TEST_CASE(get_current_balance) {
//   BOOST_CHECK_EQUAL(false , true);
// }

// BOOST_AUTO_TEST_CASE(send_order_to_the_market) {
//   BOOST_CHECK_EQUAL(false , true);
// }
