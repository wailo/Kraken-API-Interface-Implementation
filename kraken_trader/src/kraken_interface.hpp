#ifndef KRAKEN_INTERFACE_H
#define KRAKEN_INTERFACE_H

#include "kraken/kclient.hpp"
#include "order.hpp"

#include <boost/optional.hpp>
#include <unordered_map>

class kraken_interface {
public:
  using Input = Kraken::KInput;

  //! Default constructor
  kraken_interface();

  //! Copy constructor
  kraken_interface(const kraken_interface &other) = delete;

  //! Move constructor
  kraken_interface(kraken_interface &&other) = delete;

  //! Destructor
  ~kraken_interface() = default;

  //! Copy assignment operator
  kraken_interface &operator=(const kraken_interface &other) = default;

  //! Move assignment operator
  kraken_interface &operator=(kraken_interface &&other) = default;

  //! Convert to kraken map
  static Input order_to_kraken_order(const order &order_);

  //! From kraken map
  static order from_kraken_order(Input &data);

  static const std::unordered_map<order::order_type, const std::string>
      order_types_to_string;
  static const std::unordered_map<std::string, const order::order_type>
      order_types_to_enum;

  static std::string order_side_to_string(order::side_t side);

  static order::side_t order_side_from_string(const std::string &side);

  // Kraken API Calls

  std::string get_server_time() const;

  boost::optional<JSONNode>
  get_asset_info(const boost::optional<std::string> &info,
                 const boost::optional<std::string> &aclass,
                 const boost::optional<std::string> &asset) const;

  boost::optional<JSONNode>
  get_tradable_pairs(const boost::optional<std::string> &info,
                     const boost::optional<std::string> &pair) const;

  std::string get_ticker_info(const std::string &pair) const;

  std::string get_ohlc_data(const Input &in) const;

  boost::optional<JSONNode> get_order_book(const std::string &pair,
                                           const boost::optional<int> &count) const;

  std::string get_recent_trades(const std::string &pair,
                                const std::string &since) const;

  std::string get_recent_spread_data(const std::string &pair) const;

  std::string get_account_balance(const Input &in) const;

  std::string get_trade_balance(const std::string &aclass,
                                const std::string &asset) const;

  typedef std::vector<std::unordered_map<std::string, std::string>>
      order_data_t;
  boost::optional<order_data_t>
  get_open_orders(const boost::optional<std::string> &trades,
                  const boost::optional<std::string> &userref) const;

  std::string get_closed_orders(const std::string &trades,
                                const std::string &userref,
                                const std::string &start,
                                const std::string &end, const std::string &ofs,
                                const std::string &closetime) const;

  std::string query_orders_info(const std::string &trades,
                                const std::string &userref,
                                const std::string &txid) const;

  std::string get_trades_history(const Input &in) const;

  std::string query_trades_info(const Input &in) const;

  std::string get_open_positions(const Input &in) const;

  std::string get_ledgers_info(const Input &in) const;

  std::string query_ledgers(const Input &in) const;

  std::string get_trade_volume(const Input &in) const;

  boost::optional<JSONNode> add_standard_order(const order &order_);

  boost::optional<JSONNode> cancel_open_order(const std::string &txid);

  std::string deposit_methods(const Input &in);

  std::string deposit_addresses(const Input &in);

  std::string deposit_status(const Input &in);

  std::string get_withdrawal_info(const Input &in) const;

  std::string withdraw_funds(const Input &in);

  std::string withdraw_status(const Input &in);

  std::string withdraw_cancel(const Input &in);

  template <class function_type>
  auto send_api_request(int tries, function_type fn) -> decltype(fn()) {
    decltype(fn()) res;
    while (tries--) {
      res = fn();
      if (res) {
        break;
      }
    }

    return res;
  }

private:
  Kraken::KClient m_kapi;
};

#endif /* KRAKEN_INTERFACE_H */
