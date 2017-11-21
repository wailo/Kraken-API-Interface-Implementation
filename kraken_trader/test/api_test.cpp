#define BOOST_TEST_MAIN
#if !defined( WIN32 )
#define BOOST_TEST_DYN_LINK
#endif

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BaseClassModule"

#define private public
#define protected public


#include <boost/test/unit_test.hpp>

#include "../src/kraken_interface.hpp"
#include "libjson/libjson.h"


BOOST_AUTO_TEST_CASE(get_order_book) {

  kraken_interface api_intfc;
  const auto root = api_intfc.get_order_book("XXBTZEUR", 5);

  BOOST_CHECK_EQUAL(!root, false);
  
  // Check for errors.
  BOOST_CHECK_EQUAL(root.get().at("error").empty(), true);

  // // append errors to output string stream
  // for (auto it = root["error"].begin(); it != root["error"].end(); ++it)
  //    oss << endl << " * " << libjson::to_std_string(it->as_string());

  // Check if there are data
  BOOST_CHECK_EQUAL(!root.get().at("result").empty(), true);

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

  kraken_interface api_intfc;
  auto const& root = api_intfc.get_asset_info(boost::optional<std::string>(),
                                           boost::optional<std::string>(),
                                           boost::optional<std::string>());

  BOOST_CHECK_EQUAL(!root, false);

  // Check for errors.
  BOOST_CHECK_EQUAL(root.get().at("error").empty(), true);

  // Check if there are data
  BOOST_CHECK_EQUAL(!root.get().at("result").empty(), true);

}

BOOST_AUTO_TEST_CASE(get_tradable_pairs) {

  kraken_interface api_intfc;
  auto root = api_intfc.get_tradable_pairs(boost::optional<std::string>(),
                                           boost::optional<std::string>());

  BOOST_CHECK_EQUAL(!root, false);
  // Check for errors.
  BOOST_CHECK_EQUAL(root.get().at("error").empty(), true);

  // Check if there are data
  BOOST_CHECK_EQUAL(!root.get().at("result").empty(), true);
}


BOOST_AUTO_TEST_CASE(get_open_orders) {

  kraken_interface api_intfc;
  const auto json_data = api_intfc.get_open_orders(boost::optional<std::string>(),
                                                   boost::optional<std::string>());
  JSONNode root = libjson::parse(json_data);
  auto results = root.at("result");

  
  // Check for errors.
  BOOST_CHECK_EQUAL(root.at("error").empty(), true);

  // Check if there are data
  BOOST_CHECK_EQUAL(!root.at("result").empty(), true);

}

BOOST_AUTO_TEST_CASE(add_standard_order) {

  order order_ = order::create_limit_order("BCHEUR", order::side_t::sell, 14, 20000);
  kraken_interface api_intfc;
  int tries = 3;
  boost::optional<JSONNode> root;

  auto fn = [&]() ->boost::optional<JSONNode> { return api_intfc.add_standard_order(order_); }; 
  root = api_intfc.send_api_request(3, fn);

  BOOST_CHECK_EQUAL(!root, false);
  //std::cout << root.get().at("error").as_string() << std::endl;
  // std::cout << root.get().at("result").as_string() << std::endl;
  BOOST_CHECK_EQUAL(!root.get().at("result").empty(), true);
}


BOOST_AUTO_TEST_CASE(retry) {

  auto fn = [](){ std::cout << "test" << std::endl;
                  return boost::optional<JSONNode>();};

  kraken_interface api_intfc;

  auto res = api_intfc.send_api_request(3, fn);
  BOOST_CHECK_EQUAL(!res, true);
}


// BOOST_AUTO_TEST_CASE(get_current_balance) {
//   BOOST_CHECK_EQUAL(false , true);
// }

// BOOST_AUTO_TEST_CASE(send_order_to_the_market) {
//   BOOST_CHECK_EQUAL(false , true);
// }
