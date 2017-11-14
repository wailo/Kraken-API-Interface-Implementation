#include "kraken_interface.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////// ** id="public-market-data" Public market data
//! Get server time
//! //!
//! - Result: Server's time
//! unixtime =  as unix timestamp
//! rfc1123 = as RFC 1123 time format
//!
//! - Note: This is to aid in approximating the skew time between the server and client.
//!
std::string get_server_time() {
  kapi.public_method("Time");
}

//! *** //! Get asset info
//! //!
//! - Input:
//! info = info to retrieve (optional):
//!     info = all info (default)
//! aclass = asset class (optional):
//!     currency (default)
//! asset = comma delimited list of assets to get info on (optional.  default = all for given asset class)
//!
//! - Result: array of asset names and their info
//! asset_name = asset name
//!     altname = alternate name
//!     aclass = asset class
//!     decimals = scaling decimal places for record keeping
//!     display_decimals = scaling decimal places for output display
//!
//!
std::string get_asset_info(const KAPI::Input& in) {
  kapi.public_method("Assets");
}

//! *** //! Get tradable asset pairs
//! //!
//! - Input:
//! info = info to retrieve (optional):
//!     info = all info (default)
//!     leverage = leverage info
//!     fees = fees schedule
//!     margin = margin info
//! pair = comma delimited list of asset pairs to get info on (optional.  default = all)
//!
//! - Result: array of pair names and their info
//! pair_name = pair name
//!     altname = alternate pair name
//!     aclass_base = asset class of base component
//!     base = asset id of base component
//!     aclass_quote = asset class of quote component
//!     quote = asset id of quote component
//!     lot = volume lot size
//!     pair_decimals = scaling decimal places for pair
//!     lot_decimals = scaling decimal places for volume
//!     lot_multiplier = amount to multiply lot volume by to get currency volume
//!     leverage_buy = array of leverage amounts available when buying
//!     leverage_sell = array of leverage amounts available when selling
//!     fees = fee schedule array in [volume, percent fee] tuples
//!     fees_maker = maker fee schedule array in [volume, percent fee] tuples (if on maker/taker)
//!     fee_volume_currency = volume discount currency
//!     margin_call = margin call level
//!     margin_stop = stop-out/liquidation margin level
//!
//! - Note: If an asset pair is on a maker/taker fee schedule, the taker side
//! is given in "fees" and maker side in "fees_maker". For pairs not on
//! maker/taker, they will only be given in "fees".
//!
std::string get_tradable_pairs(const KAPI::Input& in) {
  kapi.public_method("AssetPairs");
}

//! *** //! Get ticker information
//! //!
//! - Input:
//! pair = comma delimited list of asset pairs to get info on
//!
//! - Result: array of pair names and their ticker info
//! pair_name = pair name
//!     a = ask array(price, whole lot volume, lot volume),
//!     b = bid array(price, whole lot volume, lot volume),
//!     c = last trade closed array(price, lot volume),
//!     v = volume array(today, last 24 hours),
//!     p = volume weighted average price array(today, last 24 hours),
//!     t = number of trades array(today, last 24 hours),
//!     l = low array(today, last 24 hours),
//!     h = high array(today, last 24 hours),
//!     o = today's opening price
//!
//! - Note: Today's prices start at 00:00:00 UTC
//!
std::string get_ticker_info(const std::string& pair) {
  KAPI::Input in;
  in.insert(make_pair("pair", pair));
  kapi.public_method("Ticker", in);
}

//! *** //! Get OHLC data
//! //!
//! - Input:
//! pair = asset pair to get OHLC data for
//! interval = time frame interval in minutes (optional):
//!     1 (default), 5, 15, 30, 60, 240, 1440, 10080, 21600
//! since = return committed OHLC data since given id (optional.  exclusive)
//!
//! - Result: array of pair name and OHLC data
//! pair_name = pair name
//!     array of array entries(time, open, high, low, close, vwap, volume, count)
//! last = id to be used as since when polling for new, committed OHLC data
//!
//! - Note: the last entry in the OHLC array is for the current, not-yet-committed frame and will always be present, regardless of the value of &quot;since&quot;.
//!
std::string get_ohlc_data(const KAPI::Input& in) {
  kapi.public_method("OHLC");
}

//! *** //! Get order book
//! //!
//! - Input:
//! pair = asset pair to get market depth for
//! count = maximum number of asks/bids (optional)
//!
//! - Result: array of pair name and market depth
//! pair_name = pair name
//!     asks = ask side array of array entries(price, volume, timestamp)
//!     bids = bid side array of array entries(price, volume, timestamp)
//!
std::string get_order_book(const KAPI::Input& in) {
  KAPI::Input in;
  in.insert(make_pair("pair", pair));
  in.insert(make_pair("count", count));
  kapi.public_method("Depth", in);
}

//! *** //! Get recent trades
//! //!
//! - Input:
//! pair = asset pair to get trade data for
//! since = return trade data since given id (optional.  exclusive)
//!
//! - Result: array of pair name and recent trade data
//! pair_name = pair name
//!     array of array entries(price, volume, time, buy/sell, market/limit, miscellaneous)
//! last = id to be used as since when polling for new trade data
//!
std::string get_recent_trades(const KAPI::Input& in)  {
  KAPI::Input in;
  in.insert(make_pair("pair", pair));
  in.insert(make_pair("since", since));
  kapi.public_method("Trades", in);
}

//! *** //! Get recent spread data
//! //!
//! - Input:
//! pair = asset pair to get spread data for
//! since = return spread data since given id (optional.  inclusive)
//!
//! - Result: array of pair name and recent spread data
//! pair_name = pair name
//!     array of array entries(time, bid, ask)
//! last = id to be used as since when polling for new spread data
//!
//! - Note: &quot;since&quot; is inclusive so any returned data with the same time as the previous set should overwrite all of the previous set's entries at that time
//!
std::string get_recent_spread_data(const KAPI::Input& in) {
  KAPI::Input in;
  in.insert(make_pair("pair", pair));
  kapi.public_method("Spread", in);
}

//! //////////////////////////////////////////////////////////////////////////////////////////////////// ** id="private-user-data" Private user data
//! *** //! Get account balance
//! //!
//! - Result: array of asset names and balance amount
//!
std::string get_account_balance(const KAPI::Input& in) {
  kapi.private_method("Balance", in);
}

//! *** //! Get trade balance
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = base asset used to determine balance (default = ZUSD)
//!
//! - Result: array of trade balance info
//! eb = equivalent balance (combined balance of all currencies)
//! tb = trade balance (combined balance of all equity currencies)
//! m = margin amount of open positions
//! n = unrealized net profit/loss of open positions
//! c = cost basis of open positions
//! v = current floating valuation of open positions
//! e = equity = trade balance + unrealized net profit/loss
//! mf = free margin = equity - initial margin (maximum margin available to open new positions)
//! ml = margin level = (equity / initial margin) * 100
//!
//! - Note: Rates used for the floating valuation is the midpoint of the best bid and ask prices
//!
std::string get_trade_balance(const KAPI::Input& in) {
  KAPI::Input in;
  in.insert(make_pair("aclass", aclass));
  in.insert(make_pair("asset", asset));
  kapi.private_method("TradeBalance", in);
}

//! *** //! Get open orders
//! //!
//! - Input:
//! trades = whether or not to include trades in output (optional.  default = false)
//! userref = restrict results to given user reference id (optional)
//!
//! - Result: array of order info in open array with txid as the key
//! refid = Referral order transaction id that created this order
//! userref = user reference id
//! status = status of order:
//!     pending = order pending book entry
//!     open = open order
//!     closed = closed order
//!     canceled = order canceled
//!     expired = order expired
//! opentm = unix timestamp of when order was placed
//! starttm = unix timestamp of order start time (or 0 if not set)
//! expiretm = unix timestamp of order end time (or 0 if not set)
//! descr = order description info
//!     pair = asset pair
//!     type = type of order (buy/sell)
//!     ordertype = order type (See )
//!     price = primary price
//!     price2 = secondary price
//!     leverage = amount of leverage
//!     order = order description
//!     close = conditional close order description (if conditional close set)
//! vol = volume of order (base currency unless viqc set in oflags)
//! vol_exec = volume executed (base currency unless viqc set in oflags)
//! cost = total cost (quote currency unless unless viqc set in oflags)
//! fee = total fee (quote currency)
//! price = average price (quote currency unless viqc set in oflags)
//! stopprice = stop price (quote currency, for trailing stops)
//! limitprice = triggered limit price (quote currency, when limit based order type triggered)
//! misc = comma delimited list of miscellaneous info
//!     stopped = triggered by stop price
//!     touched = triggered by touch price
//!     liquidated = liquidation
//!     partial = partial fill
//! oflags = comma delimited list of order flags
//!     viqc = volume in quote currency
//!     fcib = prefer fee in base currency (default if selling)
//!     fciq = prefer fee in quote currency (default if buying)
//!     nompp = no market price protection
//! trades = array of trade ids related to order (if trades info requested and data available)
//!
//! - Note: Unless otherwise stated, costs, fees, prices, and volumes are in the asset pair's scale, not the currency's scale. For example, if the asset pair uses a lot size that has a scale of 8, the volume will use a scale of 8, even if the currency it represents only has a scale of 2. Similarly, if the asset pair's pricing scale is 5, the scale will remain as 5, even if the underlying currency has a scale of 8.
//!
std::string get_open_orders(const KAPI::Input& in) {
  KAPI::Input in;
  in.insert(make_pair("trades", trades));
  in.insert(make_pair("userref", userref));
  kapi.private_method("OpenOrders", in);
}

//! *** //! Get closed orders
//! //!
//! - Input:
//! trades = whether or not to include trades in output (optional.  default = false)
//! userref = restrict results to given user reference id (optional)
//! start = starting unix timestamp or order tx id of results (optional.  exclusive)
//! end = ending unix timestamp or order tx id of results (optional.  inclusive)
//! ofs = result offset
//! closetime = which time to use (optional)
//!     open
//!     close
//!     both (default)
//!
//! - Result: array of order info
//! closed = array of order info.  See .  Additional fields:
//!     closetm = unix timestamp of when order was closed
//!     reason = additional info on status (if any)
//! count = amount of available order info matching criteria
//!
//! - Note: Times given by order tx ids are more accurate than unix timestamps. If an order tx id is given for the time, the order's open time is used
//!
std::string get_closed_orders(const KAPI::Input& in) {

  KAPI::Input in;
  in.insert(make_pair("trades", trades));
  in.insert(make_pair("userref", userref));
  in.insert(make_pair("start", start));
  in.insert(make_pair("end", end));
  in.insert(make_pair("ofs", ofs));
  in.insert(make_pair("closetime", closetime));
  kapi.private_method("ClosedOrders",in);
}

//! *** //! Query orders info
//! //!
//! - Input:
//! trades = whether or not to include trades in output (optional.  default = false)
//! userref = restrict results to given user reference id (optional)
//! txid = comma delimited list of transaction ids to query info about (20 maximum)
//!
//! - Result: associative array of orders info
//! order_txid = order info.  See
//!
//!
std::string query_orders_info(const KAPI::Input& in) {
  KAPI::Input in;
  in.insert(make_pair("trades", trades));
  in.insert(make_pair("userref", userref));
  in.insert(make_pair("txid", txid));
  kapi.private_method("QueryOrders", in);
}

//! *** //! Get trades history
//! //!
//! - Input:
//! type = type of trade (optional)
//!     all = all types (default)
//!     any position = any position (open or closed)
//!     closed position = positions that have been closed
//!     closing position = any trade closing all or part of a position
//!     no position = non-positional trades
//! trades = whether or not to include trades related to position in output (optional.  default = false)
//! start = starting unix timestamp or trade tx id of results (optional.  exclusive)
//! end = ending unix timestamp or trade tx id of results (optional.  inclusive)
//! ofs = result offset
//!
//! - Result: array of trade info
//! trades = array of trade info with txid as the key
//!     ordertxid = order responsible for execution of trade
//!     pair = asset pair
//!     time = unix timestamp of trade
//!     type = type of order (buy/sell)
//!     ordertype = order type
//!     price = average price order was executed at (quote currency)
//!     cost = total cost of order (quote currency)
//!     fee = total fee (quote currency)
//!     vol = volume (base currency)
//!     margin = initial margin (quote currency)
//!     misc = comma delimited list of miscellaneous info
//!         closing = trade closes all or part of a position
//! count = amount of available trades info matching criteria
//!
//! - If the trade opened a position, the follow fields are also present in the trade info:
//!     posstatus = position status (open/closed)
//!     cprice = average price of closed portion of position (quote currency)
//!     ccost = total cost of closed portion of position (quote currency)
//!     cfee = total fee of closed portion of position (quote currency)
//!     cvol = total fee of closed portion of position (quote currency)
//!     cmargin = total margin freed in closed portion of position (quote currency)
//!     net = net profit/loss of closed portion of position (quote currency, quote currency scale)
//!     trades = list of closing trades for position (if available)
//!
//! - Note:
//!
//!
//!
//!
std::string get_trades_history(const KAPI::Input& in) {
  kapi.private_method("TradesHistory", in);
}

//! *** //! Query trades info
//! //!
//! - Input:
//! txid = comma delimited list of transaction ids to query info about (20 maximum)
//! trades = whether or not to include trades related to position in output (optional.  default = false)
//!
//! - Result: associative array of trades info
//! trade_txid = trade info.  See
//!
//!
std::string query_trades_info(const KAPI::Input& in) {
  kapi.private_method("QueryTrades", in);
}

//! *** //! Get open positions
//! //!
//! - Input:
//! txid = comma delimited list of transaction ids to restrict output to
//! docalcs = whether or not to include profit/loss calculations (optional.  default = false)
//!
//! - Result: associative array of open position info
//! position_txid = open position info
//!     ordertxid = order responsible for execution of trade
//!     pair = asset pair
//!     time = unix timestamp of trade
//!     type = type of order used to open position (buy/sell)
//!     ordertype = order type used to open position
//!     cost = opening cost of position (quote currency unless viqc set in oflags)
//!     fee = opening fee of position (quote currency)
//!     vol = position volume (base currency unless viqc set in oflags)
//!     vol_closed = position volume closed (base currency unless viqc set in oflags)
//!     margin = initial margin (quote currency)
//!     value = current value of remaining position (if docalcs requested.  quote currency)
//!     net = unrealized profit/loss of remaining position (if docalcs requested.  quote currency, quote currency scale)
//!     misc = comma delimited list of miscellaneous info
//!     oflags = comma delimited list of order flags
//!         viqc = volume in quote currency
//!
//! - Note: Unless otherwise stated, costs, fees, prices, and volumes are in the asset pair's scale, not the currency's scale.
//!
std::string get_open_positions(const KAPI::Input& in) {
  kapi.private_method("OpenPositions", in);
}

//! *** //! Get ledgers info
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = comma delimited list of assets to restrict output to (optional.  default = all)
//! type = type of ledger to retrieve (optional):
//!     all (default)
//!     deposit
//!     withdrawal
//!     trade
//!     margin
//! start = starting unix timestamp or ledger id of results (optional.  exclusive)
//! end = ending unix timestamp or ledger id of results (optional.  inclusive)
//! ofs = result offset
//!
//! - Result: associative array of ledgers info
//! ledger_id = ledger info
//!     refid = reference id
//!     time = unx timestamp of ledger
//!     type = type of ledger entry
//!     aclass = asset class
//!     asset = asset
//!     amount = transaction amount
//!     fee = transaction fee
//!     balance = resulting balance
//!
//! - Note: Times given by ledger ids are more accurate than unix timestamps.
//!
std::string get_ledgers_info(const KAPI::Input& in) {
  kapi.private_method("Ledgers", in);
}

//! *** //! Query ledgers
//! //!
//! - Input:
//! id = comma delimited list of ledger ids to query info about (20 maximum)
//!
//! - Result: associative array of ledgers info
//! ledger_id = ledger info.  See
//!
//!
std::string query_ledgers(const KAPI::Input& in) {
  kapi.private_method("QueryLedgers", in);
}

//! *** //! Get trade volume
//! //!
//! - Input:
//! pair = comma delimited list of asset pairs to get fee info on (optional)
//! fee-info = whether or not to include fee info in results (optional)
//!
//! - Result: associative array
//! currency = volume currency
//! volume = current discount volume
//! fees = array of asset pairs and fee tier info (if requested)
//!     fee = current fee in percent
//!     minfee = minimum fee for pair (if not fixed fee)
//!     maxfee = maximum fee for pair (if not fixed fee)
//!     nextfee = next tier's fee for pair (if not fixed fee.  nil if at lowest fee tier)
//!     nextvolume = volume level of next tier (if not fixed fee.  nil if at lowest fee tier)
//!     tiervolume = volume level of current tier (if not fixed fee.  nil if at lowest fee tier)
//! fees_maker = array of asset pairs and maker fee tier info (if requested) for any pairs on maker/taker schedule
//!     fee = current fee in percent
//!     minfee = minimum fee for pair (if not fixed fee)
//!     maxfee = maximum fee for pair (if not fixed fee)
//!     nextfee = next tier's fee for pair (if not fixed fee.  nil if at lowest fee tier)
//!     nextvolume = volume level of next tier (if not fixed fee.  nil if at lowest fee tier)
//!     tiervolume = volume level of current tier (if not fixed fee.  nil if at lowest fee tier)
//!
//! - Note: If an asset pair is on a maker/taker fee schedule, the taker side
//! is given in "fees" and maker side in "fees_maker". For pairs not on
//! maker/taker, they will only be given in "fees".
//!
std::string get_trade_volume(const KAPI::Input& in) {
  kapi.private_method("TradeVolume", in);
}

//! //////////////////////////////////////////////////////////////////////////////////////////////////// ** id="private-user-trading" Private user trading
//! *** //! Add standard order
//! //!
//! - Input:
//! pair = asset pair
//! type = type of order (buy/sell)
//! ordertype = order type:
//!     market
//!     limit (price = limit price)
//!     stop-loss (price = stop loss price)
//!     take-profit (price = take profit price)
//!     stop-loss-profit (price = stop loss price, price2 = take profit price)
//!     stop-loss-profit-limit (price = stop loss price, price2 = take profit price)
//!     stop-loss-limit (price = stop loss trigger price, price2 = triggered limit price)
//!     take-profit-limit (price = take profit trigger price, price2 = triggered limit price)
//!     trailing-stop (price = trailing stop offset)
//!     trailing-stop-limit (price = trailing stop offset, price2 = triggered limit offset)
//!     stop-loss-and-limit (price = stop loss price, price2 = limit price)
//!     settle-position
//! price = price (optional.  dependent upon ordertype)
//! price2 = secondary price (optional.  dependent upon ordertype)
//! volume = order volume in lots
//! leverage = amount of leverage desired (optional.  default = none)
//! oflags = comma delimited list of order flags (optional):
//!     viqc = volume in quote currency (not available for leveraged orders)
//!     fcib = prefer fee in base currency
//!     fciq = prefer fee in quote currency
//!     nompp = no market price protection
//!     post = post only order (available when ordertype = limit)
//! starttm = scheduled start time (optional):
//!     0 = now (default)
//!     +n = schedule start time n seconds from now
//!     n = unix timestamp of start time
//! expiretm = expiration time (optional):
//!     0 = no expiration (default)
//!     +n = expire n seconds from now
//!     n = unix timestamp of expiration time
//! userref = user reference id.  32-bit signed number.  (optional)
//! validate = validate inputs only.  do not submit order (optional)
//!
//! optional closing order to add to system when order gets filled:
//!     close[ordertype] = order type
//!     close[price] = price
//!     close[price2] = secondary price
//!
//! - Result:
//! descr = order description info
//!     order = order description
//!     close = conditional close order description (if conditional close set)
//! txid = array of transaction ids for order (if order was added successfully)
//!
//! - Errors: errors include (but are not limited to):
//! EGeneral:Invalid arguments
//! EService:Unavailable
//! ETrade:Invalid request
//! EOrder:Cannot open position
//! EOrder:Cannot open opposing position
//! EOrder:Margin allowance exceeded
//! EOrder:Margin level too low
//! EOrder:Insufficient margin (exchange does not have sufficient funds to allow margin trading)
//! EOrder:Insufficient funds (insufficient user funds)
//! EOrder:Order minimum not met (volume too low)
//! EOrder:Orders limit exceeded
//! EOrder:Positions limit exceeded
//! EOrder:Rate limit exceeded
//! EOrder:Scheduled orders limit exceeded
//! EOrder:Unknown position
//!
//! - Note:
//!
std::string add_standard_order(const KAPI::Input in) {
  return kapi.private_method("AddOrder", in);
}

//! *** //! Cancel open order
//! //!
//! - Input:
//! txid = transaction id
//!
//! - Result:
//! count = number of orders canceled
//! pending = if set, order(s) is/are pending cancellation
//!
//! - Note: txid may be a user reference id.
//!
std::string cancel_open_order(const KAPI::Input& in) {
  KAPI::Input in;
  in.insert(make_pair("txid", txid));
  kapi.private_method("CancelOrder", in);
}

//! //////////////////////////////////////////////////////////////////////////////////////////////////// ** id="private-user-funding" Private user funding
//! - This is a tentative funding API and may be updated
//! in the future. Please refer to the main
//! *** //! Get deposit methods
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = asset being deposited
//!
//! - Result: associative array of deposit methods:
//! method = name of deposit method
//! limit = maximum net amount that can be deposited right now, or false if no limit
//! fee = amount of fees that will be paid
//! address-setup-fee = whether or not method has an address setup fee (optional)
//!
//!
std::string deposit_methods(const KAPI::Input& in) {
  kapi.private_method("DepositMethods", in);
}

//! *** //! Get deposit addresses
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = asset being deposited
//! method = name of the deposit method
//! new = whether or not to generate a new address (optional.  default = false)
//!
//! - Result: associative array of deposit addresses:
//! address = deposit address
//! expiretm = expiration time in unix timestamp, or 0 if not expiring
//! new = whether or not address has ever been used
//!
//!
std::string deposit_addresses(const KAPI::Input& in) {
  kapi.private_method("DepositAddresses", in);
}

//! *** //! Get status of recent deposits
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = asset being deposited
//! method = name of the deposit method
//!
//! - Result: array of array deposit status information:
//! method = name of the deposit method used
//! aclass = asset class
//! asset = asset X-ISO4217-A3 code
//! refid = reference id
//! txid = method transaction id
//! info = method transaction information
//! amount = amount deposited
//! fee = fees paid
//! time = unix timestamp when request was made
//! status = status of deposit
//! status-prop = additional status properties (if available)
//!     return = a return transaction initiated by Kraken
//!     onhold = deposit is on hold pending review
//!
//! For information about the status, please refer to the .
//!
std::string deposit_status(const KAPI::Input& in) {
  kapi.private_method("DepositStatus", in);
}

//! *** //! Get withdrawal information
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = asset being withdrawn
//! key = withdrawal key name, as set up on your account
//! amount = amount to withdraw
//!
//! - Result: associative array of withdrawal info:
//! method = name of the withdrawal method that will be used
//! limit = maximum net amount that can be withdrawn right now
//! fee = amount of fees that will be paid
//!
//!
std::string get_withdrawal_info(const KAPI::Input& in) {
  kapi.private_method("WithdrawInfo", in);
}

//! *** //! Withdraw funds
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = asset being withdrawn
//! key = withdrawal key name, as set up on your account
//! amount = amount to withdraw, including fees
//!
//! - Result: associative array of withdrawal transaction:
//! refid = reference id
//!
//!
std::string withdraw_funds(const KAPI::Input& in) {
  kapi.private_method("Withdraw", in);
}

//! *** //! Get status of recent withdrawals
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = asset being withdrawn
//! method = withdrawal method name (optional)
//!
//! - Result: array of array withdrawal status information:
//! method = name of the withdrawal method used
//! aclass = asset class
//! asset = asset X-ISO4217-A3 code
//! refid = reference id
//! txid = method transaction id
//! info = method transaction information
//! amount = amount withdrawn
//! fee = fees paid
//! time = unix timestamp when request was made
//! status = status of withdrawal
//! status-prop = additional status properties (if available)
//!     cancel-pending = cancelation requested
//!     canceled = canceled
//!     cancel-denied = cancelation requested but was denied
//!    return = a return transaction initiated by Kraken; it cannot be canceled
//!     onhold = withdrawal is on hold pending review
//!
//! For information about the status, please refer to the .
//!
std::string withdraw_status(const KAPI::Input& in) {
  kapi.private_method("WithdrawStatus", in);
}

//! *** //! Request withdrawal cancelation
//! //!
//! - Input:
//! aclass = asset class (optional):
//!     currency (default)
//! asset = asset being withdrawn
//! refid = withdrawal reference id
//!
//! - Result: true on success
//! - Note:  This will put
//! in a cancelation request. Depending upon how far along the withdrawal
//! process is, it may not be possible to cancel the withdrawal.
//!
//!
std::string withdraw_cancel(const KAPI::Input& in) {
  kapi.private_method("WithdrawCancel", in);
}
