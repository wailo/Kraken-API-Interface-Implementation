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

BOOST_AUTO_TEST_CASE(native_order_to_kraken) {

  order order_;
  order_.pair = "XXBTZEUR";
  order_.side = order::side_t::sell;
  order_.ordertype = order::order_type::limit;
  order_.price  = 100000.0;
  order_.price2 = 100000.0;
  order_.volume = 1.0;
  order_.leverage = "none";
  // order_.oflags;
  order_.starttm =  0;
  order_.expiretm = 0;
  // order_.userref;
  order_.validate = true;

  auto kraken_order =  kraken_interface::order_to_kraken_order(order_);

  BOOST_CHECK_EQUAL(kraken_order["pair"], "XXBTZEUR");
  BOOST_CHECK_EQUAL(kraken_order["type"], "sell");
  BOOST_CHECK_EQUAL(kraken_order["ordertype"], "limit");
  BOOST_CHECK_EQUAL(kraken_order["price"], "100000.000000");
  BOOST_CHECK_EQUAL(kraken_order["price2"], "100000.000000");
  BOOST_CHECK_EQUAL(kraken_order["volume"], "1.000000");
  BOOST_CHECK_EQUAL(kraken_order["leverage"], "none");
  BOOST_CHECK_EQUAL(kraken_order["starttm"], "0");
  BOOST_CHECK_EQUAL(kraken_order["expiretm"], "0");
  //BOOST_CHECK_EQUAL(kraken_order["userref"]   = userref;
  BOOST_CHECK_EQUAL(kraken_order.find("validate") != kraken_order.end(), true);
}

BOOST_AUTO_TEST_CASE(native_order_from_kraken) {

  kraken_interface::Input kraken_order;
  kraken_order["pair"] =  "XXBTZEUR";
  kraken_order["type"] =  "sell";
  kraken_order["ordertype"] =  "limit";
  kraken_order["price"] =  "100000.000000";
  kraken_order["price2"] =  "100000.000000";
  kraken_order["volume"] =  "1.000000";
  kraken_order["leverage"] =  "none";
  kraken_order["starttm"] =  "0";
  kraken_order["expiretm"] =  "0";
  //kraken_order["userref"]   = userre;
  kraken_order["validate"];

  auto order_ = kraken_interface::from_kraken_order(kraken_order);

  BOOST_CHECK_EQUAL(order_.pair , "XXBTZEUR");
  BOOST_CHECK_EQUAL(unsigned(order_.side) , unsigned(order::side_t::sell));
  BOOST_CHECK_EQUAL(unsigned(order_.ordertype) , unsigned(order::order_type::limit));
  BOOST_CHECK_EQUAL(order_.price  , 100000.0);
  BOOST_CHECK_EQUAL(order_.price2 , 100000.0);
  BOOST_CHECK_EQUAL(order_.volume , 1.0);
  BOOST_CHECK_EQUAL(order_.leverage , "none");
  // BOOST_CHECK_EQUAL(order_.oflags);
  BOOST_CHECK_EQUAL(order_.starttm ,  0);
  BOOST_CHECK_EQUAL(order_.expiretm , 0);
  // BOOST_CHECK_EQUAL(order_.userref);
  BOOST_CHECK_EQUAL(order_.validate , true);
}

BOOST_AUTO_TEST_CASE(create_limit_order) {

  order order_ = order::create_limit_order("XXBTZEUR", order::side_t::sell, 150.0, 05, true);
  BOOST_CHECK_EQUAL(order_.pair , "XXBTZEUR");
  BOOST_CHECK_EQUAL(unsigned(order_.side) , unsigned(order::side_t::sell));
  BOOST_CHECK_EQUAL(unsigned(order_.ordertype) , unsigned(order::order_type::limit));
  BOOST_CHECK_EQUAL(order_.price  , 5);
  BOOST_CHECK_EQUAL(order_.volume , 150.0);
  BOOST_CHECK_EQUAL(order_.leverage , "none");
  BOOST_CHECK_EQUAL(order_.starttm ,  0);
  BOOST_CHECK_EQUAL(order_.expiretm , 0);
  BOOST_CHECK_EQUAL(order_.validate , true);
}

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
