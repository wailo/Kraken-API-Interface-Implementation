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
