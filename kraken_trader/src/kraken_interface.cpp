#include "kraken_interface.hpp"

#include <iostream>
#include <string>

kraken_interface::kraken_interface(const std::string &key,
                                   const std::string &secret)
    : m_kapi(key, secret) {}

std::string kraken_interface::order_side_to_string(order::side_t side) {
  if (side == order::side_t::buy) {
    return "buy";
  } else if (side == order::side_t::sell) {
    return "sell";
  }

  throw std::logic_error("Unknown side_t side");
}

order::side_t
kraken_interface::order_side_from_string(const std::string &side) {
  if (side == "buy") {
    return order::side_t::buy;
  } else if (side == "sell") {
    return order::side_t::sell;
  }
  throw std::logic_error("Unknown side name");
}

const std::unordered_map<order::order_type, const std::string>
    kraken_interface::order_types_to_string = {
        {order::order_type::market, "market"},
        {order::order_type::limit, "limit"},
        {order::order_type::stop_loss, "stop_loss"},
        {order::order_type::take_profit, "take_profit"},
        {order::order_type::stop_loss_profit, "stop_loss_profit"},
        {order::order_type::stop_loss_profit_limit, "stop_loss_profit_limit"},
        {order::order_type::stop_loss_limit, "stop_loss_limit"},
        {order::order_type::take_profit_limit, "take_profit_limit"},
        {order::order_type::trailing_stop, "trailing_stop"},
        {order::order_type::trailing_stop_limit, "trailing_stop_limit"},
        {order::order_type::stop_loss_and_limit, "stop_loss_and_limit"},
        {order::order_type::settle_position, "settle_position"}};

const std::unordered_map<std::string, const order::order_type>
    kraken_interface::order_types_to_enum = {
        {"market", order::order_type::market},
        {"limit", order::order_type::limit},
        {"stop_loss", order::order_type::stop_loss},
        {"take_profit", order::order_type::take_profit},
        {"stop_loss_profit", order::order_type::stop_loss_profit},
        {"stop_loss_profit_limit", order::order_type::stop_loss_profit_limit},
        {"stop_loss_limit", order::order_type::stop_loss_limit},
        {"take_profit_limit", order::order_type::take_profit_limit},
        {"trailing_stop", order::order_type::trailing_stop},
        {"trailing_stop_limit", order::order_type::trailing_stop_limit},
        {"stop_loss_and_limit", order::order_type::stop_loss_and_limit},
        {"settle_position", order::order_type::settle_position}};

kraken_interface::Input
kraken_interface::order_to_kraken_order(const order &order_) {
  Input data = {{"pair", order_.m_pair},
                {"type", order_side_to_string(order_.m_side)},
                {"ordertype", order_types_to_string.at(order_.m_ordertype)},
                {"price", std::to_string(order_.m_price)},
                {"price2", std::to_string(order_.m_price2)},
                {"volume", std::to_string(order_.m_volume)},
                {"leverage", order_.m_leverage},
                {"starttm", std::to_string(order_.m_starttm)},
                {"expiretm", std::to_string(order_.m_expiretm)},
                {"userref", order_.m_userref}};

  if (!order_.m_oflags.empty()) {
    data["oflags"] = order_.m_oflags;
  }

  if (order_.m_validate) {
    data["validate"] = "true";
  }
  return data;
}

// from kraken map
order kraken_interface::from_kraken_order(kraken_interface::Input &data) {
  order order_;
  order_.m_pair = data["pair"];
  order_.m_side = order_side_from_string(data["type"]);
  order_.m_ordertype = order_types_to_enum.at(data["ordertype"]);
  order_.m_price = std::stod(data["price"]);
  order_.m_price2 = std::stod(data["price2"]);
  order_.m_volume = std::stod(data["volume"]);
  order_.m_leverage = data["leverage"];
  order_.m_oflags = data["oflags"];
  order_.m_starttm = std::stoi(data["starttm"]);
  order_.m_expiretm = std::stoi(data["expiretm"]);
  order_.m_userref = data["userref"];
  order_.m_validate = (data.find("validate") != data.end());
  return order_;
}

std::string kraken_interface::get_server_time() const {
  Input in;
  return m_kapi.public_method("Time", in);
}

std::optional<JSONNode> kraken_interface::get_asset_info(
    const std::optional<std::string> &info,
    const std::optional<std::string> &aclass,
    const std::optional<std::string> &asset) const {
  Input in;
  if (info) {
    in["info"] = info.value();
  }

  if (aclass) {
    in["alcass"] = aclass.value();
  }

  if (asset) {
    in["asset"] = asset.value();
  }

  auto const json_data = m_kapi.public_method("Assets", in);
  std::optional<JSONNode> root;

  try {
    root = libjson::parse(json_data);
  } catch (...) {
    std::cerr << "Failed to parse json data: " << json_data << '\n';
    return std::nullopt;
  }

  // TODO: Implement generic while loop here
  return root;
}

std::optional<JSONNode> kraken_interface::get_tradable_pairs(
    const std::optional<std::string> &info,
    const std::optional<std::string> &pair) const {
  Input in;
  if (info) {
    in["info"] = info.value();
  }

  if (pair) {
    in["pair"] = pair.value();
  }

  std::string json_data = m_kapi.public_method("AssetPairs", in);
  std::optional<JSONNode> root;

  try {
    root = libjson::parse(json_data);

    // Check if there are data
    const auto &error = root.value().at("error");
  } catch (...) {
    std::cerr << "Failed to parse json data: " << json_data << '\n';
    return std::nullopt;
  }

  return root;
}

std::string kraken_interface::get_ticker_info(const std::string &pair) const {
  const Input in{{"pair", pair}};
  return m_kapi.public_method("Ticker", in);
}

std::string kraken_interface::get_ohlc_data(const Input &in) const {
  return m_kapi.public_method("OHLC", in);
}

std::optional<JSONNode>
kraken_interface::get_order_book(const std::string &pair,
                                 const std::optional<int> &count) const {
  Input in{{"pair", pair}};

  if (count) {
    in.insert(make_pair("count", std::to_string(count.value())));
  }

  auto const json_data = m_kapi.public_method("Depth", in);
  std::optional<JSONNode> root;

  try {
    root = libjson::parse(json_data);
  } catch (...) {
    std::cerr << "Failed to parse json data: " << json_data << '\n';
    return std::nullopt;
  }

  return root;
}

std::string
kraken_interface::get_recent_trades(const std::string &pair,
                                    const std::string &since) const {
  const Input in{{"pair", pair}, {"since", since}};
  return m_kapi.public_method("Trades", in);
}

std::string
kraken_interface::get_recent_spread_data(const std::string &pair) const {
  const Input in{{"pair", pair}};
  return m_kapi.public_method("Spread", in);
}

std::string kraken_interface::get_account_balance(const Input &in) const {
  return m_kapi.private_method("Balance", in);
}

std::string
kraken_interface::get_trade_balance(const std::string &aclass,
                                    const std::string &asset) const {
  const Input in = {{"aclass", aclass}, {"asset", asset}};
  return m_kapi.private_method("TradeBalance", in);
}

std::optional<kraken_interface::order_data_t> kraken_interface::get_open_orders(
    const std::optional<std::string> &trades,
    const std::optional<std::string> &userref) const {
  Input in;
  if (trades) {
    in.insert(make_pair("trades", trades.value()));
  }

  if (userref) {
    in.insert(make_pair("userref", userref.value()));
  }

  auto const json_data = m_kapi.private_method("OpenOrders", in);
  JSONNode root;

  try {
    root = libjson::parse(json_data);
  } catch (...) {
    std::cerr << "Failed to parse json data: " << json_data << '\n';
    return std::nullopt;
  }

  auto const &result = root.at("result");
  // Check for errors.
  if (!root.at("error").empty() || result.empty()) {
    return std::nullopt;
  }

  auto const &open_orders_data = result.at("open");
  order_data_t open_orders = {};

  for (JSONNode::const_iterator order = open_orders_data.begin();
       order != open_orders_data.end(); order++) {
    open_orders.emplace_back(order_data_t::value_type(
        {{"id", order->name()},
         {"refid", order->at("refid").as_string()},
         {"userref", order->at("userref").as_string()},
         {"status", order->at("status").as_string()},
         {"opentm", order->at("opentm").as_string()},
         {"starttm", order->at("starttm").as_string()},
         {"expiretm", order->at("expiretm").as_string()},
         {"pair", order->at("descr").at("pair").as_string()},
         {"type", order->at("descr").at("type").as_string()},
         {"ordertype", order->at("descr").at("ordertype").as_string()},
         {"price", order->at("descr").at("price").as_string()},
         {"price2", order->at("descr").at("price2").as_string()},
         {"leverage", order->at("descr").at("leverage").as_string()},
         {"order", order->at("descr").at("order").as_string()}}));
  }

  return open_orders;
}

std::string kraken_interface::get_closed_orders(
    const std::string &trades, const std::string &userref,
    const std::string &start, const std::string &end, const std::string &ofs,
    const std::string &closetime) const {
  Input in;
  in.insert(make_pair("trades", trades));
  in.insert(make_pair("userref", userref));
  in.insert(make_pair("start", start));
  in.insert(make_pair("end", end));
  in.insert(make_pair("ofs", ofs));
  in.insert(make_pair("closetime", closetime));
  return m_kapi.private_method("ClosedOrders", in);
}

std::string kraken_interface::query_orders_info(const std::string &trades,
                                                const std::string &userref,
                                                const std::string &txid) const {
  const Input in{{"trades", trades}, {"userref", userref}, {"txid", txid}};
  return m_kapi.private_method("QueryOrders", in);
}

std::string kraken_interface::get_trades_history(const Input &in) const {
  return m_kapi.private_method("TradesHistory", in);
}

std::string kraken_interface::query_trades_info(const Input &in) const {
  return m_kapi.private_method("QueryTrades", in);
}

std::string kraken_interface::get_open_positions(const Input &in) const {
  return m_kapi.private_method("OpenPositions", in);
}

std::string kraken_interface::get_ledgers_info(const Input &in) const {
  return m_kapi.private_method("Ledgers", in);
}

std::string kraken_interface::query_ledgers(const Input &in) const {
  return m_kapi.private_method("QueryLedgers", in);
}

std::string kraken_interface::get_trade_volume(const Input &in) const {
  return m_kapi.private_method("TradeVolume", in);
}

std::optional<JSONNode>
kraken_interface::add_standard_order(const order &order_) {

  auto const &in = order_to_kraken_order(order_);
  std::optional<JSONNode> root;
  std::string json_data = m_kapi.private_method("AddOrder", in);

  try {
    root = libjson::parse(json_data);

    // Check if there are data
    const auto &errors = root.value().at("error");
    if (!errors.empty()) {
      std::cerr << "Error in json data: " << json_data << '\n';
      return std::nullopt;
    }
    // if (error == "[\"EService:Unavailable\"]") {
    //}

  } catch (...) {
    std::cerr << "Failed to parse json data: " << json_data << '\n';
    return std::nullopt;
  }

  return root;
}

std::optional<JSONNode>
kraken_interface::cancel_open_order(const std::string &txid) {
  const Input in{{"txid", txid}};
  const auto json_data = m_kapi.private_method("CancelOrder", in);
  std::optional<JSONNode> root;
  try {
    root = libjson::parse(json_data);

    // Check if there are data
    const auto &errors = root.value().at("error");
    if (!errors.empty()) {
      std::cerr << "Error in json data: " << json_data << '\n';
      return std::nullopt;
    }

  } catch (...) {
    std::cerr << "Failed to parse json data: " << json_data << '\n';
    return std::nullopt;
  }

  return root;
}

std::string kraken_interface::deposit_methods(const Input &in) {
  return m_kapi.private_method("DepositMethods", in);
}

std::string kraken_interface::deposit_addresses(const Input &in) {
  return m_kapi.private_method("DepositAddresses", in);
}

std::string kraken_interface::deposit_status(const Input &in) {
  return m_kapi.private_method("DepositStatus", in);
}

std::string kraken_interface::get_withdrawal_info(const Input &in) const {
  return m_kapi.private_method("WithdrawInfo", in);
}

std::string kraken_interface::withdraw_funds(const Input &in) {
  return m_kapi.private_method("Withdraw", in);
}

std::string kraken_interface::withdraw_status(const Input &in) {
  return m_kapi.private_method("WithdrawStatus", in);
}

std::string kraken_interface::withdraw_cancel(const Input &in) {
  return m_kapi.private_method("WithdrawCancel", in);
}
