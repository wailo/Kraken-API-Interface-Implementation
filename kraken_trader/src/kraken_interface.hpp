#ifndef KRAKEN_INTERFACE_H
#define KRAKEN_INTERFACE_H

#include "order.hpp"
#include "../../krakenapi/kraken/kclient.hpp"

#include <unordered_map>
#include <boost/optional.hpp>

class kraken_interface
{
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
  kraken_interface& operator=(const kraken_interface &other) = default;

  //! Move assignment operator
  kraken_interface& operator=(kraken_interface &&other) = default;

    // convert to kraken map
  static Input order_to_kraken_order(const order& order_);

  // from kraken map
  static order from_kraken_order(Input &data);

  
  static const std::unordered_map<order::order_type, const std::string > order_types_to_string;
  static const std::unordered_map< std::string, const order::order_type> order_types_to_enum;
                                        
  static std::string order_side_to_string(order::side_t side);
  
  static order::side_t order_side_from_string(const std::string& side);



  // Kraken API Calls

  std::string get_server_time();

  std::string get_asset_info(const Input& in);

  std::string get_tradable_pairs(const Input& in);

  std::string get_ticker_info(const std::string& pair);

  std::string get_ohlc_data(const Input& in);

  std::string get_order_book(const std::string& pair,
                             const boost::optional<int>& count);

  std::string get_recent_trades(const std::string& pair,
                                const std::string& since);

  std::string get_recent_spread_data(const std::string& pair);

  std::string get_account_balance(const Input& in);

  std::string get_trade_balance(const std::string& aclass,
                                const std::string& asset);

  std::string get_open_orders(const std::string& trades,
                              const std::string& userref);  

  std::string get_closed_orders(const std::string& trades,
                                const std::string& userref,
                                const std::string& start,
                                const std::string& end,
                                const std::string& ofs,
                                const std::string& closetime);

  std::string query_orders_info(const std::string& trades,
                                const std::string& userref,
                                const std::string& txid);

  std::string get_trades_history(const Input& in);

  std::string query_trades_info(const Input& in);

  std::string get_open_positions(const Input& in);

  std::string get_ledgers_info(const Input& in);

  std::string query_ledgers(const Input& in);

  std::string get_trade_volume(const Input& in);

  std::string add_standard_order(const Input in);

  std::string cancel_open_order(const std::string& txid);

  std::string deposit_methods(const Input& in);

  std::string deposit_addresses(const Input& in);

  std::string deposit_status(const Input& in);

  std::string get_withdrawal_info(const Input& in);

  std::string withdraw_funds(const Input& in);

  std::string withdraw_status(const Input& in);

  std::string withdraw_cancel(const Input& in);
  
 protected:
 private:

  Kraken::KClient m_kapi;
};


#endif /* KRAKEN_INTERFACE_H */




/*

** id="general-usage" General Usage
-
- Public methods can use either GET or POST.
- Private methods must use POST and be set up as follows:
- HTTP header:
**** pre
API-Key = API key
API-Sign = Message signature using HMAC-SHA512 of (URI path + SHA256(nonce + POST data)) and base64 decoded secret API key

- POST data:
**** pre
nonce = always increasing unsigned 64 bit integer
otp = two-factor password (if two-factor enabled, otherwise not required)

- Note: There is no way to reset the nonce to a lower value so be sure to use a nonce generation method that won't generate
numbers less than the previous nonce. A persistent counter or the current time in hundredths of a second precision or higher is suggested.
Too many requests with nonces below the last valid nonce (EAPI:Invalid nonce) can result in temporary bans.
- Note: Sometimes requests can arrive out of order or NTP can cause your clock to rewind, resulting in nonce issues. If you encounter this issue, you can change the nonce window in your account API settings page. The amount to set it to depends upon how you increment the nonce. Depending on your connectivity, a setting that would accomodate 3-15 seconds of network issues is suggested.
- API calls that require currency assets can be referenced using their ISO4217-A3 names in the case of ISO registered names, their 3 letter commonly used names in the case of unregistered names, or their X-ISO4217-A3 code (see
- Responses are JSON encoded in the form of:
**** pre
error = array of error messages in the format of:
    &lt;char-severity code&gt;&lt;string-error category&gt;:&lt;string-error type&gt;[:&lt;string-extra info&gt;]
    severity code can be E for error or W for warning
result = result of API call (may not be present if errors occur)

- Note: Care should be taken when handling any numbers represented as strings, as these may overflow standard data types.
*** //! API call rate limit
void api-call-rate-limit() {
publicmethod("DoS attacks as well");
as order book manipulation caused by the rapid placing and canceling of
orders.
- Every user of our API has a &quot;call counter&quot; which starts at 0.
- Ledger/trade history calls increase the counter by 2.
- Place/cancel order calls do not affect the counter.
- All other API calls increase the counter by 1.
- The user's counter is reduced every couple of seconds, and if the
counter exceeds the user's maximum API access is suspended for 15 minutes.
Tier 2 users have a maximum of 15 and their count gets reduced by 1 every 3 seconds.
Tier 3 and 4 users have a maximum of 20; the count is reduced by 1 every 2 seconds for
tier 3 users, and is reduced by 1 every 1 second for tier 4 users.
- Although placing and cancelling orders does not increase the counter,
there are separate limits in place to prevent order book manipulation.
Only placing orders you intend to fill and keeping the rate down to 1
per second is generally enough to not hit this limit.
** id="public-market-data" Public market data
*** //! Get server time
void get-server-time() {
publicmethod("Time");
- Result: Server's time
**** pre
unixtime =  as unix timestamp
rfc1123 = as RFC 1123 time format

- Note: This is to aid in approximating the skew time between the server and client.
*** //! Get asset info
void get-asset-info() {
publicmethod("Assets");
- Input:
**** pre
info = info to retrieve (optional):
    info = all info (default)
aclass = asset class (optional):
    currency (default)
asset = comma delimited list of assets to get info on (optional.  default = all for given asset class)

- Result: array of asset names and their info
**** pre
&lt;asset_name&gt; = asset name
    altname = alternate name
    aclass = asset class
    decimals = scaling decimal places for record keeping
    display_decimals = scaling decimal places for output display

*** //! Get tradable asset pairs
void get-tradable-pairs() {
publicmethod("AssetPairs");
- Input:
**** pre
info = info to retrieve (optional):
    info = all info (default)
    leverage = leverage info
    fees = fees schedule
    margin = margin info
pair = comma delimited list of asset pairs to get info on (optional.  default = all)

- Result: array of pair names and their info
**** pre
&lt;pair_name&gt; = pair name
    altname = alternate pair name
    aclass_base = asset class of base component
    base = asset id of base component
    aclass_quote = asset class of quote component
    quote = asset id of quote component
    lot = volume lot size
    pair_decimals = scaling decimal places for pair
    lot_decimals = scaling decimal places for volume
    lot_multiplier = amount to multiply lot volume by to get currency volume
    leverage_buy = array of leverage amounts available when buying
    leverage_sell = array of leverage amounts available when selling
    fees = fee schedule array in [volume, percent fee] tuples
    fees_maker = maker fee schedule array in [volume, percent fee] tuples (if on maker/taker)
    fee_volume_currency = volume discount currency
    margin_call = margin call level
    margin_stop = stop-out/liquidation margin level

- Note: If an asset pair is on a maker/taker fee schedule, the taker side
is given in "fees" and maker side in "fees_maker". For pairs not on
maker/taker, they will only be given in "fees".
*** //! Get ticker information
void get-ticker-info() {
publicmethod("Ticker");
- Input:
**** pre
pair = comma delimited list of asset pairs to get info on

- Result: array of pair names and their ticker info
**** pre
&lt;pair_name&gt; = pair name
    a = ask array(&lt;price&gt;, &lt;whole lot volume&gt;, &lt;lot volume&gt;),
    b = bid array(&lt;price&gt;, &lt;whole lot volume&gt;, &lt;lot volume&gt;),
    c = last trade closed array(&lt;price&gt;, &lt;lot volume&gt;),
    v = volume array(&lt;today&gt;, &lt;last 24 hours&gt;),
    p = volume weighted average price array(&lt;today&gt;, &lt;last 24 hours&gt;),
    t = number of trades array(&lt;today&gt;, &lt;last 24 hours&gt;),
    l = low array(&lt;today&gt;, &lt;last 24 hours&gt;),
    h = high array(&lt;today&gt;, &lt;last 24 hours&gt;),
    o = today's opening price

- Note: Today's prices start at 00:00:00 UTC
*** //! Get OHLC data
void get-ohlc-data() {
publicmethod("OHLC");
- Input:
**** pre
pair = asset pair to get OHLC data for
interval = time frame interval in minutes (optional):
        1 (default), 5, 15, 30, 60, 240, 1440, 10080, 21600
since = return committed OHLC data since given id (optional.  exclusive)

- Result: array of pair name and OHLC data
**** pre
&lt;pair_name&gt; = pair name
    array of array entries(&lt;time&gt;, &lt;open&gt;, &lt;high&gt;, &lt;low&gt;, &lt;close&gt;, &lt;vwap&gt;, &lt;volume&gt;, &lt;count&gt;)
last = id to be used as since when polling for new, committed OHLC data

- Note: the last entry in the OHLC array is for the current, not-yet-committed frame and will always be present, regardless of the value of &quot;since&quot;.
*** //! Get order book
void get-order-book() {
publicmethod("Depth");
- Input:
**** pre
pair = asset pair to get market depth for
count = maximum number of asks/bids (optional)

- Result: array of pair name and market depth
**** pre
&lt;pair_name&gt; = pair name
    asks = ask side array of array entries(&lt;price&gt;, &lt;volume&gt;, &lt;timestamp&gt;)
    bids = bid side array of array entries(&lt;price&gt;, &lt;volume&gt;, &lt;timestamp&gt;)

*** //! Get recent trades
void get-recent-trades() {
publicmethod("Trades");
- Input:
**** pre
pair = asset pair to get trade data for
since = return trade data since given id (optional.  exclusive)

- Result: array of pair name and recent trade data
**** pre
&lt;pair_name&gt; = pair name
    array of array entries(&lt;price&gt;, &lt;volume&gt;, &lt;time&gt;, &lt;buy/sell&gt;, &lt;market/limit&gt;, &lt;miscellaneous&gt;)
last = id to be used as since when polling for new trade data

*** //! Get recent spread data
void get-recent-spread-data() {
publicmethod("Spread");
- Input:
**** pre
pair = asset pair to get spread data for
since = return spread data since given id (optional.  inclusive)

- Result: array of pair name and recent spread data
**** pre
&lt;pair_name&gt; = pair name
    array of array entries(&lt;time&gt;, &lt;bid&gt;, &lt;ask&gt;)
last = id to be used as since when polling for new spread data

- Note: &quot;since&quot; is inclusive so any returned data with the same time as the previous set should overwrite all of the previous set's entries at that time
** id="private-user-data" Private user data
*** //! Get account balance
void get-account-balance() {
publicmethod("Balance");
- Result: array of asset names and balance amount
*** //! Get trade balance
void get-trade-balance() {
publicmethod("TradeBalance");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = base asset used to determine balance (default = ZUSD)

- Result: array of trade balance info
**** pre
eb = equivalent balance (combined balance of all currencies)
tb = trade balance (combined balance of all equity currencies)
m = margin amount of open positions
n = unrealized net profit/loss of open positions
c = cost basis of open positions
v = current floating valuation of open positions
e = equity = trade balance + unrealized net profit/loss
mf = free margin = equity - initial margin (maximum margin available to open new positions)
ml = margin level = (equity / initial margin) * 100

- Note: Rates used for the floating valuation is the midpoint of the best bid and ask prices
*** //! Get open orders
void get-open-orders() {
publicmethod("OpenOrders");
- Input:
**** pre
trades = whether or not to include trades in output (optional.  default = false)
userref = restrict results to given user reference id (optional)

- Result: array of order info in open array with txid as the key
**** pre
refid = Referral order transaction id that created this order
userref = user reference id
status = status of order:
    pending = order pending book entry
    open = open order
    closed = closed order
    canceled = order canceled
    expired = order expired
opentm = unix timestamp of when order was placed
starttm = unix timestamp of order start time (or 0 if not set)
expiretm = unix timestamp of order end time (or 0 if not set)
descr = order description info
    pair = asset pair
    type = type of order (buy/sell)
    ordertype = order type (See )
    price = primary price
    price2 = secondary price
    leverage = amount of leverage
    order = order description
    close = conditional close order description (if conditional close set)
vol = volume of order (base currency unless viqc set in oflags)
vol_exec = volume executed (base currency unless viqc set in oflags)
cost = total cost (quote currency unless unless viqc set in oflags)
fee = total fee (quote currency)
price = average price (quote currency unless viqc set in oflags)
stopprice = stop price (quote currency, for trailing stops)
limitprice = triggered limit price (quote currency, when limit based order type triggered)
misc = comma delimited list of miscellaneous info
    stopped = triggered by stop price
    touched = triggered by touch price
    liquidated = liquidation
    partial = partial fill
oflags = comma delimited list of order flags
    viqc = volume in quote currency
    fcib = prefer fee in base currency (default if selling)
    fciq = prefer fee in quote currency (default if buying)
    nompp = no market price protection
trades = array of trade ids related to order (if trades info requested and data available)

- Note: Unless otherwise stated, costs, fees, prices, and volumes are in the asset pair's scale, not the currency's scale. For example, if the asset pair uses a lot size that has a scale of 8, the volume will use a scale of 8, even if the currency it represents only has a scale of 2. Similarly, if the asset pair's pricing scale is 5, the scale will remain as 5, even if the underlying currency has a scale of 8.
*** //! Get closed orders
void get-closed-orders() {
publicmethod("ClosedOrders");
- Input:
**** pre
trades = whether or not to include trades in output (optional.  default = false)
userref = restrict results to given user reference id (optional)
start = starting unix timestamp or order tx id of results (optional.  exclusive)
end = ending unix timestamp or order tx id of results (optional.  inclusive)
ofs = result offset
closetime = which time to use (optional)
    open
    close
    both (default)

- Result: array of order info
**** pre
closed = array of order info.  See .  Additional fields:
    closetm = unix timestamp of when order was closed
    reason = additional info on status (if any)
count = amount of available order info matching criteria

- Note: Times given by order tx ids are more accurate than unix timestamps. If an order tx id is given for the time, the order's open time is used
*** //! Query orders info
void query-orders-info() {
publicmethod("QueryOrders");
- Input:
**** pre
trades = whether or not to include trades in output (optional.  default = false)
userref = restrict results to given user reference id (optional)
txid = comma delimited list of transaction ids to query info about (20 maximum)

- Result: associative array of orders info
**** pre
&lt;order_txid&gt; = order info.  See

*** //! Get trades history
void get-trades-history() {
publicmethod("TradesHistory");
- Input:
**** pre
type = type of trade (optional)
    all = all types (default)
    any position = any position (open or closed)
    closed position = positions that have been closed
    closing position = any trade closing all or part of a position
    no position = non-positional trades
trades = whether or not to include trades related to position in output (optional.  default = false)
start = starting unix timestamp or trade tx id of results (optional.  exclusive)
end = ending unix timestamp or trade tx id of results (optional.  inclusive)
ofs = result offset

- Result: array of trade info
**** pre
trades = array of trade info with txid as the key
    ordertxid = order responsible for execution of trade
    pair = asset pair
    time = unix timestamp of trade
    type = type of order (buy/sell)
    ordertype = order type
    price = average price order was executed at (quote currency)
    cost = total cost of order (quote currency)
    fee = total fee (quote currency)
    vol = volume (base currency)
    margin = initial margin (quote currency)
    misc = comma delimited list of miscellaneous info
        closing = trade closes all or part of a position
count = amount of available trades info matching criteria

- If the trade opened a position, the follow fields are also present in the trade info:
**** pre
    posstatus = position status (open/closed)
    cprice = average price of closed portion of position (quote currency)
    ccost = total cost of closed portion of position (quote currency)
    cfee = total fee of closed portion of position (quote currency)
    cvol = total fee of closed portion of position (quote currency)
    cmargin = total margin freed in closed portion of position (quote currency)
    net = net profit/loss of closed portion of position (quote currency, quote currency scale)
    trades = list of closing trades for position (if available)

- Note:




*** //! Query trades info
void query-trades-info() {
publicmethod("QueryTrades");
- Input:
**** pre
txid = comma delimited list of transaction ids to query info about (20 maximum)
trades = whether or not to include trades related to position in output (optional.  default = false)

- Result: associative array of trades info
**** pre
&lt;trade_txid&gt; = trade info.  See

*** //! Get open positions
void get-open-positions() {
publicmethod("OpenPositions");
- Input:
**** pre
txid = comma delimited list of transaction ids to restrict output to
docalcs = whether or not to include profit/loss calculations (optional.  default = false)

- Result: associative array of open position info
**** pre
&lt;position_txid&gt; = open position info
    ordertxid = order responsible for execution of trade
    pair = asset pair
    time = unix timestamp of trade
    type = type of order used to open position (buy/sell)
    ordertype = order type used to open position
    cost = opening cost of position (quote currency unless viqc set in oflags)
    fee = opening fee of position (quote currency)
    vol = position volume (base currency unless viqc set in oflags)
    vol_closed = position volume closed (base currency unless viqc set in oflags)
    margin = initial margin (quote currency)
    value = current value of remaining position (if docalcs requested.  quote currency)
    net = unrealized profit/loss of remaining position (if docalcs requested.  quote currency, quote currency scale)
    misc = comma delimited list of miscellaneous info
    oflags = comma delimited list of order flags
        viqc = volume in quote currency

- Note: Unless otherwise stated, costs, fees, prices, and volumes are in the asset pair's scale, not the currency's scale.
*** //! Get ledgers info
void get-ledgers-info() {
publicmethod("Ledgers");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = comma delimited list of assets to restrict output to (optional.  default = all)
type = type of ledger to retrieve (optional):
    all (default)
    deposit
    withdrawal
    trade
    margin
start = starting unix timestamp or ledger id of results (optional.  exclusive)
end = ending unix timestamp or ledger id of results (optional.  inclusive)
ofs = result offset

- Result: associative array of ledgers info
**** pre
&lt;ledger_id&gt; = ledger info
    refid = reference id
    time = unx timestamp of ledger
    type = type of ledger entry
    aclass = asset class
    asset = asset
    amount = transaction amount
    fee = transaction fee
    balance = resulting balance

- Note: Times given by ledger ids are more accurate than unix timestamps.
*** //! Query ledgers
void query-ledgers() {
publicmethod("QueryLedgers");
- Input:
**** pre
id = comma delimited list of ledger ids to query info about (20 maximum)

- Result: associative array of ledgers info
**** pre
&lt;ledger_id&gt; = ledger info.  See

*** //! Get trade volume
void get-trade-volume() {
publicmethod("TradeVolume");
- Input:
**** pre
pair = comma delimited list of asset pairs to get fee info on (optional)
fee-info = whether or not to include fee info in results (optional)

- Result: associative array
**** pre
currency = volume currency
volume = current discount volume
fees = array of asset pairs and fee tier info (if requested)
    fee = current fee in percent
    minfee = minimum fee for pair (if not fixed fee)
    maxfee = maximum fee for pair (if not fixed fee)
    nextfee = next tier's fee for pair (if not fixed fee.  nil if at lowest fee tier)
    nextvolume = volume level of next tier (if not fixed fee.  nil if at lowest fee tier)
    tiervolume = volume level of current tier (if not fixed fee.  nil if at lowest fee tier)
fees_maker = array of asset pairs and maker fee tier info (if requested) for any pairs on maker/taker schedule
    fee = current fee in percent
    minfee = minimum fee for pair (if not fixed fee)
    maxfee = maximum fee for pair (if not fixed fee)
    nextfee = next tier's fee for pair (if not fixed fee.  nil if at lowest fee tier)
    nextvolume = volume level of next tier (if not fixed fee.  nil if at lowest fee tier)
    tiervolume = volume level of current tier (if not fixed fee.  nil if at lowest fee tier)

- Note: If an asset pair is on a maker/taker fee schedule, the taker side
is given in "fees" and maker side in "fees_maker". For pairs not on
maker/taker, they will only be given in "fees".
** id="private-user-trading" Private user trading
*** //! Add standard order
void add-standard-order() {
publicmethod("AddOrder");
- Input:
**** pre
pair = asset pair
type = type of order (buy/sell)
ordertype = order type:
    market
    limit (price = limit price)
    stop-loss (price = stop loss price)
    take-profit (price = take profit price)
    stop-loss-profit (price = stop loss price, price2 = take profit price)
    stop-loss-profit-limit (price = stop loss price, price2 = take profit price)
    stop-loss-limit (price = stop loss trigger price, price2 = triggered limit price)
    take-profit-limit (price = take profit trigger price, price2 = triggered limit price)
    trailing-stop (price = trailing stop offset)
    trailing-stop-limit (price = trailing stop offset, price2 = triggered limit offset)
    stop-loss-and-limit (price = stop loss price, price2 = limit price)
    settle-position
price = price (optional.  dependent upon ordertype)
price2 = secondary price (optional.  dependent upon ordertype)
volume = order volume in lots
leverage = amount of leverage desired (optional.  default = none)
oflags = comma delimited list of order flags (optional):
    viqc = volume in quote currency (not available for leveraged orders)
    fcib = prefer fee in base currency
    fciq = prefer fee in quote currency
    nompp = no market price protection
    post = post only order (available when ordertype = limit)
starttm = scheduled start time (optional):
    0 = now (default)
    +&lt;n&gt; = schedule start time &lt;n&gt; seconds from now
    &lt;n&gt; = unix timestamp of start time
expiretm = expiration time (optional):
    0 = no expiration (default)
    +&lt;n&gt; = expire &lt;n&gt; seconds from now
    &lt;n&gt; = unix timestamp of expiration time
userref = user reference id.  32-bit signed number.  (optional)
validate = validate inputs only.  do not submit order (optional)

optional closing order to add to system when order gets filled:
    close[ordertype] = order type
    close[price] = price
    close[price2] = secondary price

- Result:
**** pre
descr = order description info
    order = order description
    close = conditional close order description (if conditional close set)
txid = array of transaction ids for order (if order was added successfully)

- Errors: errors include (but are not limited to):
**** pre
EGeneral:Invalid arguments
EService:Unavailable
ETrade:Invalid request
EOrder:Cannot open position
EOrder:Cannot open opposing position
EOrder:Margin allowance exceeded
EOrder:Margin level too low
EOrder:Insufficient margin (exchange does not have sufficient funds to allow margin trading)
EOrder:Insufficient funds (insufficient user funds)
EOrder:Order minimum not met (volume too low)
EOrder:Orders limit exceeded
EOrder:Positions limit exceeded
EOrder:Rate limit exceeded
EOrder:Scheduled orders limit exceeded
EOrder:Unknown position

- Note:






*** //! Cancel open order
void cancel-open-order() {
publicmethod("CancelOrder");
- Input:
**** pre
txid = transaction id

- Result:
**** pre
count = number of orders canceled
pending = if set, order(s) is/are pending cancellation

- Note: txid may be a user reference id.
** id="private-user-funding" Private user funding
- This is a tentative funding API and may be updated
in the future. Please refer to the main
*** //! Get deposit methods
void deposit-methods() {
publicmethod("DepositMethods");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = asset being deposited

- Result: associative array of deposit methods:
**** pre
method = name of deposit method
limit = maximum net amount that can be deposited right now, or false if no limit
fee = amount of fees that will be paid
address-setup-fee = whether or not method has an address setup fee (optional)

*** //! Get deposit addresses
void deposit-addresses() {
publicmethod("DepositAddresses");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = asset being deposited
method = name of the deposit method
new = whether or not to generate a new address (optional.  default = false)

- Result: associative array of deposit addresses:
**** pre
address = deposit address
expiretm = expiration time in unix timestamp, or 0 if not expiring
new = whether or not address has ever been used

*** //! Get status of recent deposits
void deposit-status() {
publicmethod("DepositStatus");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = asset being deposited
method = name of the deposit method

- Result: array of array deposit status information:
**** pre
method = name of the deposit method used
aclass = asset class
asset = asset X-ISO4217-A3 code
refid = reference id
txid = method transaction id
info = method transaction information
amount = amount deposited
fee = fees paid
time = unix timestamp when request was made
status = status of deposit
status-prop = additional status properties (if available)
    return = a return transaction initiated by Kraken
    onhold = deposit is on hold pending review

For information about the status, please refer to the .
*** //! Get withdrawal information
void get-withdrawal-info() {
publicmethod("WithdrawInfo");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = asset being withdrawn
key = withdrawal key name, as set up on your account
amount = amount to withdraw

- Result: associative array of withdrawal info:
**** pre
method = name of the withdrawal method that will be used
limit = maximum net amount that can be withdrawn right now
fee = amount of fees that will be paid

*** //! Withdraw funds
void withdraw-funds() {
publicmethod("Withdraw");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = asset being withdrawn
key = withdrawal key name, as set up on your account
amount = amount to withdraw, including fees

- Result: associative array of withdrawal transaction:
**** pre
refid = reference id

*** //! Get status of recent withdrawals
void withdraw-status() {
publicmethod("WithdrawStatus");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = asset being withdrawn
method = withdrawal method name (optional)

- Result: array of array withdrawal status information:
**** pre
method = name of the withdrawal method used
aclass = asset class
asset = asset X-ISO4217-A3 code
refid = reference id
txid = method transaction id
info = method transaction information
amount = amount withdrawn
fee = fees paid
time = unix timestamp when request was made
status = status of withdrawal
status-prop = additional status properties (if available)
    cancel-pending = cancelation requested
    canceled = canceled
    cancel-denied = cancelation requested but was denied
    return = a return transaction initiated by Kraken; it cannot be canceled
    onhold = withdrawal is on hold pending review

For information about the status, please refer to the .
*** //! Request withdrawal cancelation
void withdraw-cancel() {
publicmethod("WithdrawCancel");
- Input:
**** pre
aclass = asset class (optional):
    currency (default)
asset = asset being withdrawn
refid = withdrawal reference id

- Result: true on success
- Note:  This will put
in a cancelation request. Depending upon how far along the withdrawal
process is, it may not be possible to cancel the withdrawal.


 */
