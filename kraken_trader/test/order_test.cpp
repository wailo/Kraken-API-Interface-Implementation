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

BOOST_AUTO_TEST_CASE(native_order_to_kraken) {

  order order_;
  order_.m_pair = "XXBTZEUR";
  order_.m_side = order::side_t::sell;
  order_.m_ordertype = order::order_type::limit;
  order_.m_price = 100000.0;
  order_.m_price2 = 100000.0;
  order_.m_volume = 1.0;
  order_.m_leverage = "none";
  // order_.oflags;
  order_.m_starttm = 0;
  order_.m_expiretm = 0;
  // order_.userref;
  order_.m_validate = true;

  auto kraken_order = kraken_interface::order_to_kraken_order(order_);

  BOOST_CHECK_EQUAL(kraken_order["pair"], "XXBTZEUR");
  BOOST_CHECK_EQUAL(kraken_order["type"], "sell");
  BOOST_CHECK_EQUAL(kraken_order["ordertype"], "limit");
  BOOST_CHECK_EQUAL(kraken_order["price"], "100000.000000");
  BOOST_CHECK_EQUAL(kraken_order["price2"], "100000.000000");
  BOOST_CHECK_EQUAL(kraken_order["volume"], "1.000000");
  BOOST_CHECK_EQUAL(kraken_order["leverage"], "none");
  BOOST_CHECK_EQUAL(kraken_order["starttm"], "0");
  BOOST_CHECK_EQUAL(kraken_order["expiretm"], "0");
  // BOOST_CHECK_EQUAL(kraken_order["userref"]   = userref;
  BOOST_CHECK_EQUAL(kraken_order.find("validate") != kraken_order.end(), true);
}

BOOST_AUTO_TEST_CASE(native_order_from_kraken) {

  kraken_interface::Input kraken_order;
  kraken_order["pair"] = "XXBTZEUR";
  kraken_order["type"] = "sell";
  kraken_order["ordertype"] = "limit";
  kraken_order["price"] = "100000.000000";
  kraken_order["price2"] = "100000.000000";
  kraken_order["volume"] = "1.000000";
  kraken_order["leverage"] = "none";
  kraken_order["starttm"] = "0";
  kraken_order["expiretm"] = "0";
  // kraken_order["userref"]   = userre;
  kraken_order["validate"];

  auto order_ = kraken_interface::from_kraken_order(kraken_order);

  BOOST_CHECK_EQUAL(order_.m_pair, "XXBTZEUR");
  BOOST_CHECK_EQUAL(unsigned(order_.m_side), unsigned(order::side_t::sell));
  BOOST_CHECK_EQUAL(unsigned(order_.m_ordertype),
                    unsigned(order::order_type::limit));
  BOOST_CHECK_EQUAL(order_.m_price, 100000.0);
  BOOST_CHECK_EQUAL(order_.m_price2, 100000.0);
  BOOST_CHECK_EQUAL(order_.m_volume, 1.0);
  BOOST_CHECK_EQUAL(order_.m_leverage, "none");
  // BOOST_CHECK_EQUAL(order_.m_oflags);
  BOOST_CHECK_EQUAL(order_.m_starttm, 0);
  BOOST_CHECK_EQUAL(order_.m_expiretm, 0);
  // BOOST_CHECK_EQUAL(order_.m_userref);
  BOOST_CHECK_EQUAL(order_.m_validate, true);
}

BOOST_AUTO_TEST_CASE(create_limit_order) {

  order order_ = order::create_limit_order("XXBTZEUR", order::side_t::sell,
                                           150.0, 05, true);
  BOOST_CHECK_EQUAL(order_.m_pair, "XXBTZEUR");
  BOOST_CHECK_EQUAL(unsigned(order_.m_side), unsigned(order::side_t::sell));
  BOOST_CHECK_EQUAL(unsigned(order_.m_ordertype),
                    unsigned(order::order_type::limit));
  BOOST_CHECK_EQUAL(order_.m_price, 5);
  BOOST_CHECK_EQUAL(order_.m_volume, 150.0);
  BOOST_CHECK_EQUAL(order_.m_leverage, "none");
  BOOST_CHECK_EQUAL(order_.m_starttm, 0);
  BOOST_CHECK_EQUAL(order_.m_expiretm, 0);
  BOOST_CHECK_EQUAL(order_.m_validate, true);
}
