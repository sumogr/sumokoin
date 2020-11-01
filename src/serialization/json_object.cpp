// Copyright (c) 2016-2020, The Monero Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "json_object.h"

#include <boost/range/adaptor/transformed.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <limits>
#include <type_traits>

<<<<<<< HEAD
#include "cryptonote_basic/cryptonote_basic_impl.h"

=======
>>>>>>> origin/android-wallet
// drop macro from windows.h
#ifdef GetObject
  #undef GetObject
#endif

namespace cryptonote
{

namespace json
{

namespace
{
  template<typename Source, typename Destination>
  constexpr bool precision_loss()
  {
    return
      std::numeric_limits<Destination>::is_signed != std::numeric_limits<Source>::is_signed ||
      std::numeric_limits<Destination>::min() > std::numeric_limits<Source>::min() ||
      std::numeric_limits<Destination>::max() < std::numeric_limits<Source>::max();
  }

  template<typename Source, typename Type>
  void convert_numeric(Source source, Type& i)
  {
    static_assert(
      (std::is_same<Type, char>() && std::is_same<Source, int>()) ||
      std::numeric_limits<Source>::is_signed == std::numeric_limits<Type>::is_signed,
      "comparisons below may have undefined behavior"
    );
    if (source < std::numeric_limits<Type>::min())
    {
      throw WRONG_TYPE{"numeric underflow"};
    }
    if (std::numeric_limits<Type>::max() < source)
    {
      throw WRONG_TYPE{"numeric overflow"};
    }
    i = Type(source);
  }

  template<typename Type>
  void to_int(const rapidjson::Value& val, Type& i)
  {
    if (!val.IsInt())
    {
      throw WRONG_TYPE{"integer"};
    }
    convert_numeric(val.GetInt(), i);
  }
  template<typename Type>
  void to_int64(const rapidjson::Value& val, Type& i)
  {
    if (!val.IsInt64())
    {
      throw WRONG_TYPE{"integer"};
    }
    convert_numeric(val.GetInt64(), i);
  }

  template<typename Type>
  void to_uint(const rapidjson::Value& val, Type& i)
  {
    if (!val.IsUint())
    {
      throw WRONG_TYPE{"unsigned integer"};
    }
    convert_numeric(val.GetUint(), i);
  }
  template<typename Type>
  void to_uint64(const rapidjson::Value& val, Type& i)
  {
    if (!val.IsUint64())
    {
      throw WRONG_TYPE{"unsigned integer"};
    }
    convert_numeric(val.GetUint64(), i);
  }
}

void read_hex(const rapidjson::Value& val, epee::span<std::uint8_t> dest)
{
  if (!val.IsString())
  {
    throw WRONG_TYPE("string");
  }

<<<<<<< HEAD
  if (!epee::from_hex::to_buffer(dest, {val.GetString(), val.GetStringLength()}))
=======
  if (!epee::from_hex::to_buffer(dest, {val.GetString(), val.Size()}))
>>>>>>> origin/android-wallet
  {
    throw BAD_INPUT();
  }
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const rapidjson::Value& src)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const rapidjson::Value& src)
>>>>>>> origin/android-wallet
{
  src.Accept(dest);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const boost::string_ref i)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const boost::string_ref i)
>>>>>>> origin/android-wallet
{
  dest.String(i.data(), i.size());
}

void fromJsonValue(const rapidjson::Value& val, std::string& str)
{
  if (!val.IsString())
  {
    throw WRONG_TYPE("string");
  }

  str = val.GetString();
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const std::vector<std::uint8_t>& src)
{
  const std::string hex = epee::to_hex::string(epee::to_span(src));
  dest.String(hex.data(), hex.size());
}

void fromJsonValue(const rapidjson::Value& val, std::vector<std::uint8_t>& dest)
{
  if (!val.IsString())
  {
    throw WRONG_TYPE("string");
  }

  dest.resize(val.GetStringLength() / 2);
  if ((val.GetStringLength() % 2) != 0 || !epee::from_hex::to_buffer(epee::to_mut_span(dest), {val.GetString(), val.GetStringLength()}))
  {
    throw BAD_INPUT();
  }
}

void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, bool i)
{
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, bool i)
{
>>>>>>> origin/android-wallet
  dest.Bool(i);
}

void fromJsonValue(const rapidjson::Value& val, bool& b)
{
  if (!val.IsBool())
  {
    throw WRONG_TYPE("boolean");
  }
  b = val.GetBool();
}

void fromJsonValue(const rapidjson::Value& val, unsigned char& i)
{
  to_uint(val, i);
}

void fromJsonValue(const rapidjson::Value& val, char& i)
{
  to_int(val, i);
}

void fromJsonValue(const rapidjson::Value& val, signed char& i)
{
  to_int(val, i);
}

void fromJsonValue(const rapidjson::Value& val, unsigned short& i)
{
  to_uint(val, i);
}

void fromJsonValue(const rapidjson::Value& val, short& i)
{
  to_int(val, i);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const unsigned int i)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const unsigned int i)
>>>>>>> origin/android-wallet
{
  dest.Uint(i);
}

void fromJsonValue(const rapidjson::Value& val, unsigned int& i)
{
  to_uint(val, i);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const int i)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const int i)
>>>>>>> origin/android-wallet
{
  dest.Int(i);
}

void fromJsonValue(const rapidjson::Value& val, int& i)
{
  to_int(val, i);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const unsigned long long i)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const unsigned long long i)
>>>>>>> origin/android-wallet
{
  static_assert(!precision_loss<unsigned long long, std::uint64_t>(), "bad uint64 conversion");
  dest.Uint64(i);
}

void fromJsonValue(const rapidjson::Value& val, unsigned long long& i)
{
  to_uint64(val, i);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const long long i)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const long long i)
>>>>>>> origin/android-wallet
{
  static_assert(!precision_loss<long long, std::int64_t>(), "bad int64 conversion");
  dest.Int64(i);
}

void fromJsonValue(const rapidjson::Value& val, long long& i)
{
  to_int64(val, i);
}

void fromJsonValue(const rapidjson::Value& val, unsigned long& i)
{
  to_uint64(val, i);
}

void fromJsonValue(const rapidjson::Value& val, long& i)
{
  to_int64(val, i);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::transaction& tx)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::transaction& tx)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, version, tx.version);
  INSERT_INTO_JSON_OBJECT(dest, unlock_time, tx.unlock_time);
  INSERT_INTO_JSON_OBJECT(dest, inputs, tx.vin);
  INSERT_INTO_JSON_OBJECT(dest, outputs, tx.vout);
  INSERT_INTO_JSON_OBJECT(dest, extra, tx.extra);
<<<<<<< HEAD
  if (!tx.pruned)
  {
    INSERT_INTO_JSON_OBJECT(dest, signatures, tx.signatures);
  }
=======
  INSERT_INTO_JSON_OBJECT(dest, signatures, tx.signatures);
>>>>>>> origin/android-wallet
  INSERT_INTO_JSON_OBJECT(dest, ringct, tx.rct_signatures);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::transaction& tx)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, tx.version, version);
  GET_FROM_JSON_OBJECT(val, tx.unlock_time, unlock_time);
  GET_FROM_JSON_OBJECT(val, tx.vin, inputs);
  GET_FROM_JSON_OBJECT(val, tx.vout, outputs);
  GET_FROM_JSON_OBJECT(val, tx.extra, extra);
  GET_FROM_JSON_OBJECT(val, tx.rct_signatures, ringct);

  const auto& sigs = val.FindMember("signatures");
  if (sigs != val.MemberEnd())
  {
    fromJsonValue(sigs->value, tx.signatures);
  }

  const auto& rsig = tx.rct_signatures;
  if (!cryptonote::is_coinbase(tx) && rsig.p.bulletproofs.empty() && rsig.p.rangeSigs.empty() && rsig.p.MGs.empty() && rsig.get_pseudo_outs().empty() && sigs == val.MemberEnd())
    tx.pruned = true;
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::block& b)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, major_version, b.major_version);
  INSERT_INTO_JSON_OBJECT(dest, minor_version, b.minor_version);
  INSERT_INTO_JSON_OBJECT(dest, timestamp, b.timestamp);
  INSERT_INTO_JSON_OBJECT(dest, prev_id, b.prev_id);
  INSERT_INTO_JSON_OBJECT(dest, nonce, b.nonce);
  INSERT_INTO_JSON_OBJECT(dest, miner_tx, b.miner_tx);
  INSERT_INTO_JSON_OBJECT(dest, tx_hashes, b.tx_hashes);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::block& b)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, major_version, b.major_version);
  INSERT_INTO_JSON_OBJECT(dest, minor_version, b.minor_version);
  INSERT_INTO_JSON_OBJECT(dest, timestamp, b.timestamp);
  INSERT_INTO_JSON_OBJECT(dest, prev_id, b.prev_id);
  INSERT_INTO_JSON_OBJECT(dest, nonce, b.nonce);
  INSERT_INTO_JSON_OBJECT(dest, miner_tx, b.miner_tx);
  INSERT_INTO_JSON_OBJECT(dest, tx_hashes, b.tx_hashes);

>>>>>>> origin/android-wallet
  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::block& b)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, b.major_version, major_version);
  GET_FROM_JSON_OBJECT(val, b.minor_version, minor_version);
  GET_FROM_JSON_OBJECT(val, b.timestamp, timestamp);
  GET_FROM_JSON_OBJECT(val, b.prev_id, prev_id);
  GET_FROM_JSON_OBJECT(val, b.nonce, nonce);
  GET_FROM_JSON_OBJECT(val, b.miner_tx, miner_tx);
  GET_FROM_JSON_OBJECT(val, b.tx_hashes, tx_hashes);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::txin_v& txin)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::txin_v& txin)
>>>>>>> origin/android-wallet
{
  dest.StartObject();
  struct add_input
  {
    using result_type = void;

<<<<<<< HEAD
    rapidjson::Writer<epee::byte_stream>& dest;
=======
    rapidjson::Writer<rapidjson::StringBuffer>& dest;
>>>>>>> origin/android-wallet

    void operator()(cryptonote::txin_to_key const& input) const
    {
      INSERT_INTO_JSON_OBJECT(dest, to_key, input);
    }
    void operator()(cryptonote::txin_gen const& input) const
    {
      INSERT_INTO_JSON_OBJECT(dest, gen, input);
    }
    void operator()(cryptonote::txin_to_script const& input) const
    {
      INSERT_INTO_JSON_OBJECT(dest, to_script, input);
    }
    void operator()(cryptonote::txin_to_scripthash const& input) const
    {
      INSERT_INTO_JSON_OBJECT(dest, to_scripthash, input);
    }
  };
  boost::apply_visitor(add_input{dest}, txin);
  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::txin_v& txin)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  if (val.MemberCount() != 1)
  {
    throw MISSING_KEY("Invalid input object");
  }

  for (auto const& elem : val.GetObject())
  {
    if (elem.name == "to_key")
    {
      cryptonote::txin_to_key tmpVal;
      fromJsonValue(elem.value, tmpVal);
      txin = std::move(tmpVal);
    }
    else if (elem.name == "gen")
    {
      cryptonote::txin_gen tmpVal;
      fromJsonValue(elem.value, tmpVal);
      txin = std::move(tmpVal);
    }
    else if (elem.name == "to_script")
    {
      cryptonote::txin_to_script tmpVal;
      fromJsonValue(elem.value, tmpVal);
      txin = std::move(tmpVal);
    }
    else if (elem.name == "to_scripthash")
    {
      cryptonote::txin_to_scripthash tmpVal;
      fromJsonValue(elem.value, tmpVal);
      txin = std::move(tmpVal);
    }
  }
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::txin_gen& txin)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::txin_gen& txin)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, height, txin.height);

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::txin_gen& txin)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, txin.height, height);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::txin_to_script& txin)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, prev, txin.prev);
  INSERT_INTO_JSON_OBJECT(dest, prevout, txin.prevout);
  INSERT_INTO_JSON_OBJECT(dest, sigset, txin.sigset);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::txin_to_script& txin)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, prev, txin.prev);
  INSERT_INTO_JSON_OBJECT(dest, prevout, txin.prevout);
  INSERT_INTO_JSON_OBJECT(dest, sigset, txin.sigset);

>>>>>>> origin/android-wallet
  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::txin_to_script& txin)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, txin.prev, prev);
  GET_FROM_JSON_OBJECT(val, txin.prevout, prevout);
  GET_FROM_JSON_OBJECT(val, txin.sigset, sigset);
}


<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::txin_to_scripthash& txin)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, prev, txin.prev);
  INSERT_INTO_JSON_OBJECT(dest, prevout, txin.prevout);
  INSERT_INTO_JSON_OBJECT(dest, script, txin.script);
  INSERT_INTO_JSON_OBJECT(dest, sigset, txin.sigset);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::txin_to_scripthash& txin)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, prev, txin.prev);
  INSERT_INTO_JSON_OBJECT(dest, prevout, txin.prevout);
  INSERT_INTO_JSON_OBJECT(dest, script, txin.script);
  INSERT_INTO_JSON_OBJECT(dest, sigset, txin.sigset);

>>>>>>> origin/android-wallet
  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::txin_to_scripthash& txin)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, txin.prev, prev);
  GET_FROM_JSON_OBJECT(val, txin.prevout, prevout);
  GET_FROM_JSON_OBJECT(val, txin.script, script);
  GET_FROM_JSON_OBJECT(val, txin.sigset, sigset);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::txin_to_key& txin)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::txin_to_key& txin)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, amount, txin.amount);
  INSERT_INTO_JSON_OBJECT(dest, key_offsets, txin.key_offsets);
  INSERT_INTO_JSON_OBJECT(dest, key_image, txin.k_image);

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::txin_to_key& txin)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, txin.amount, amount);
  GET_FROM_JSON_OBJECT(val, txin.key_offsets, key_offsets);
  GET_FROM_JSON_OBJECT(val, txin.k_image, key_image);
}


<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::txout_to_script& txout)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::txout_to_script& txout)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, keys, txout.keys);
  INSERT_INTO_JSON_OBJECT(dest, script, txout.script);

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::txout_to_script& txout)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, txout.keys, keys);
  GET_FROM_JSON_OBJECT(val, txout.script, script);
}


<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::txout_to_scripthash& txout)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::txout_to_scripthash& txout)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, hash, txout.hash);

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::txout_to_scripthash& txout)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, txout.hash, hash);
}


<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::txout_to_key& txout)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::txout_to_key& txout)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, key, txout.key);

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::txout_to_key& txout)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, txout.key, key);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::tx_out& txout)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::tx_out& txout)
>>>>>>> origin/android-wallet
{
  dest.StartObject();
  INSERT_INTO_JSON_OBJECT(dest, amount, txout.amount);

  struct add_output
  {
    using result_type = void;

<<<<<<< HEAD
    rapidjson::Writer<epee::byte_stream>& dest;
=======
    rapidjson::Writer<rapidjson::StringBuffer>& dest;
>>>>>>> origin/android-wallet

    void operator()(cryptonote::txout_to_key const& output) const
    {
      INSERT_INTO_JSON_OBJECT(dest, to_key, output);
    }
    void operator()(cryptonote::txout_to_script const& output) const
    {
      INSERT_INTO_JSON_OBJECT(dest, to_script, output);
    }
    void operator()(cryptonote::txout_to_scripthash const& output) const
    {
      INSERT_INTO_JSON_OBJECT(dest, to_scripthash, output);
    }
  };
  boost::apply_visitor(add_output{dest}, txout.target);
   dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::tx_out& txout)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  if (val.MemberCount() != 2)
  {
    throw MISSING_KEY("Invalid input object");
  }

  for (auto const& elem : val.GetObject())
  {
    if (elem.name == "amount")
    {
      fromJsonValue(elem.value, txout.amount);
    }

    if (elem.name == "to_key")
    {
      cryptonote::txout_to_key tmpVal;
      fromJsonValue(elem.value, tmpVal);
      txout.target = std::move(tmpVal);
    }
    else if (elem.name == "to_script")
    {
      cryptonote::txout_to_script tmpVal;
      fromJsonValue(elem.value, tmpVal);
      txout.target = std::move(tmpVal);
    }
    else if (elem.name == "to_scripthash")
    {
      cryptonote::txout_to_scripthash tmpVal;
      fromJsonValue(elem.value, tmpVal);
      txout.target = std::move(tmpVal);
    }
  }
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::connection_info& info)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, incoming, info.incoming);
  INSERT_INTO_JSON_OBJECT(dest, localhost, info.localhost);
  INSERT_INTO_JSON_OBJECT(dest, local_ip, info.local_ip);
  INSERT_INTO_JSON_OBJECT(dest, address_type, info.address_type);

  INSERT_INTO_JSON_OBJECT(dest, ip, info.ip);
  INSERT_INTO_JSON_OBJECT(dest, port, info.port);
  INSERT_INTO_JSON_OBJECT(dest, rpc_port, info.rpc_port);
  INSERT_INTO_JSON_OBJECT(dest, rpc_credits_per_hash, info.rpc_credits_per_hash);

  INSERT_INTO_JSON_OBJECT(dest, peer_id, info.peer_id);

  INSERT_INTO_JSON_OBJECT(dest, recv_count, info.recv_count);
  INSERT_INTO_JSON_OBJECT(dest, recv_idle_time, info.recv_idle_time);

  INSERT_INTO_JSON_OBJECT(dest, send_count, info.send_count);
  INSERT_INTO_JSON_OBJECT(dest, send_idle_time, info.send_idle_time);

  INSERT_INTO_JSON_OBJECT(dest, state, info.state);

  INSERT_INTO_JSON_OBJECT(dest, live_time, info.live_time);

  INSERT_INTO_JSON_OBJECT(dest, avg_download, info.avg_download);
  INSERT_INTO_JSON_OBJECT(dest, current_download, info.current_download);

  INSERT_INTO_JSON_OBJECT(dest, avg_upload, info.avg_upload);
  INSERT_INTO_JSON_OBJECT(dest, current_upload, info.current_upload);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::connection_info& info)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, incoming, info.incoming);
  INSERT_INTO_JSON_OBJECT(dest, localhost, info.localhost);
  INSERT_INTO_JSON_OBJECT(dest, local_ip, info.local_ip);
  INSERT_INTO_JSON_OBJECT(dest, address_type, info.address_type);

  INSERT_INTO_JSON_OBJECT(dest, ip, info.ip);
  INSERT_INTO_JSON_OBJECT(dest, port, info.port);
  INSERT_INTO_JSON_OBJECT(dest, rpc_port, info.rpc_port);
  INSERT_INTO_JSON_OBJECT(dest, rpc_credits_per_hash, info.rpc_credits_per_hash);

  INSERT_INTO_JSON_OBJECT(dest, peer_id, info.peer_id);

  INSERT_INTO_JSON_OBJECT(dest, recv_count, info.recv_count);
  INSERT_INTO_JSON_OBJECT(dest, recv_idle_time, info.recv_idle_time);

  INSERT_INTO_JSON_OBJECT(dest, send_count, info.send_count);
  INSERT_INTO_JSON_OBJECT(dest, send_idle_time, info.send_idle_time);

  INSERT_INTO_JSON_OBJECT(dest, state, info.state);

  INSERT_INTO_JSON_OBJECT(dest, live_time, info.live_time);

  INSERT_INTO_JSON_OBJECT(dest, avg_download, info.avg_download);
  INSERT_INTO_JSON_OBJECT(dest, current_download, info.current_download);

  INSERT_INTO_JSON_OBJECT(dest, avg_upload, info.avg_upload);
  INSERT_INTO_JSON_OBJECT(dest, current_upload, info.current_upload);

>>>>>>> origin/android-wallet
  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::connection_info& info)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, info.incoming, incoming);
  GET_FROM_JSON_OBJECT(val, info.localhost, localhost);
  GET_FROM_JSON_OBJECT(val, info.local_ip, local_ip);
  GET_FROM_JSON_OBJECT(val, info.address_type, address_type);

  GET_FROM_JSON_OBJECT(val, info.ip, ip);
  GET_FROM_JSON_OBJECT(val, info.port, port);
  GET_FROM_JSON_OBJECT(val, info.rpc_port, rpc_port);
  GET_FROM_JSON_OBJECT(val, info.rpc_credits_per_hash, rpc_credits_per_hash);

  GET_FROM_JSON_OBJECT(val, info.peer_id, peer_id);

  GET_FROM_JSON_OBJECT(val, info.recv_count, recv_count);
  GET_FROM_JSON_OBJECT(val, info.recv_idle_time, recv_idle_time);

  GET_FROM_JSON_OBJECT(val, info.send_count, send_count);
  GET_FROM_JSON_OBJECT(val, info.send_idle_time, send_idle_time);

  GET_FROM_JSON_OBJECT(val, info.state, state);

  GET_FROM_JSON_OBJECT(val, info.live_time, live_time);

  GET_FROM_JSON_OBJECT(val, info.avg_download, avg_download);
  GET_FROM_JSON_OBJECT(val, info.current_download, current_download);

  GET_FROM_JSON_OBJECT(val, info.avg_upload, avg_upload);
  GET_FROM_JSON_OBJECT(val, info.current_upload, current_upload);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::tx_blob_entry& tx)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, blob, tx.blob);
  INSERT_INTO_JSON_OBJECT(dest, prunable_hash, tx.prunable_hash);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::tx_blob_entry& tx)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, blob, tx.blob);
  INSERT_INTO_JSON_OBJECT(dest, prunable_hash, tx.prunable_hash);

>>>>>>> origin/android-wallet
  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::tx_blob_entry& tx)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, tx.blob, blob);
  GET_FROM_JSON_OBJECT(val, tx.prunable_hash, prunable_hash);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::block_complete_entry& blk)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::block_complete_entry& blk)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, block, blk.block);
  INSERT_INTO_JSON_OBJECT(dest, transactions, blk.txs);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::block_complete_entry& blk)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, blk.block, block);
  GET_FROM_JSON_OBJECT(val, blk.txs, transactions);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::block_with_transactions& blk)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::block_with_transactions& blk)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, block, blk.block);
  INSERT_INTO_JSON_OBJECT(dest, transactions, blk.transactions);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::block_with_transactions& blk)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, blk.block, block);
  GET_FROM_JSON_OBJECT(val, blk.transactions, transactions);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::transaction_info& tx_info)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::transaction_info& tx_info)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, height, tx_info.height);
  INSERT_INTO_JSON_OBJECT(dest, in_pool, tx_info.in_pool);
  INSERT_INTO_JSON_OBJECT(dest, transaction, tx_info.transaction);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::transaction_info& tx_info)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, tx_info.height, height);
  GET_FROM_JSON_OBJECT(val, tx_info.in_pool, in_pool);
  GET_FROM_JSON_OBJECT(val, tx_info.transaction, transaction);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::output_key_and_amount_index& out)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::output_key_and_amount_index& out)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, amount_index, out.amount_index);
  INSERT_INTO_JSON_OBJECT(dest, key, out.key);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::output_key_and_amount_index& out)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, out.amount_index, amount_index);
  GET_FROM_JSON_OBJECT(val, out.key, key);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::amount_with_random_outputs& out)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::amount_with_random_outputs& out)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, amount, out.amount);
  INSERT_INTO_JSON_OBJECT(dest, outputs, out.outputs);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::amount_with_random_outputs& out)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, out.amount, amount);
  GET_FROM_JSON_OBJECT(val, out.outputs, outputs);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::peer& peer)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::peer& peer)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, id, peer.id);
  INSERT_INTO_JSON_OBJECT(dest, ip, peer.ip);
  INSERT_INTO_JSON_OBJECT(dest, port, peer.port);
  INSERT_INTO_JSON_OBJECT(dest, rpc_port, peer.rpc_port);
  INSERT_INTO_JSON_OBJECT(dest, rpc_credits_per_hash, peer.rpc_credits_per_hash);
  INSERT_INTO_JSON_OBJECT(dest, last_seen, peer.last_seen);
  INSERT_INTO_JSON_OBJECT(dest, pruning_seed, peer.pruning_seed);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::peer& peer)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, peer.id, id);
  GET_FROM_JSON_OBJECT(val, peer.ip, ip);
  GET_FROM_JSON_OBJECT(val, peer.port, port);
  GET_FROM_JSON_OBJECT(val, peer.rpc_port, rpc_port);
  GET_FROM_JSON_OBJECT(val, peer.rpc_credits_per_hash, rpc_credits_per_hash);
  GET_FROM_JSON_OBJECT(val, peer.last_seen, last_seen);
  GET_FROM_JSON_OBJECT(val, peer.pruning_seed, pruning_seed);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::tx_in_pool& tx)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::tx_in_pool& tx)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, tx, tx.tx);
  INSERT_INTO_JSON_OBJECT(dest, tx_hash, tx.tx_hash);
  INSERT_INTO_JSON_OBJECT(dest, blob_size, tx.blob_size);
  INSERT_INTO_JSON_OBJECT(dest, weight, tx.weight);
  INSERT_INTO_JSON_OBJECT(dest, fee, tx.fee);
  INSERT_INTO_JSON_OBJECT(dest, max_used_block_hash, tx.max_used_block_hash);
  INSERT_INTO_JSON_OBJECT(dest, max_used_block_height, tx.max_used_block_height);
  INSERT_INTO_JSON_OBJECT(dest, kept_by_block, tx.kept_by_block);
  INSERT_INTO_JSON_OBJECT(dest, last_failed_block_hash, tx.last_failed_block_hash);
  INSERT_INTO_JSON_OBJECT(dest, last_failed_block_height, tx.last_failed_block_height);
  INSERT_INTO_JSON_OBJECT(dest, receive_time, tx.receive_time);
  INSERT_INTO_JSON_OBJECT(dest, last_relayed_time, tx.last_relayed_time);
  INSERT_INTO_JSON_OBJECT(dest, relayed, tx.relayed);
  INSERT_INTO_JSON_OBJECT(dest, do_not_relay, tx.do_not_relay);
  INSERT_INTO_JSON_OBJECT(dest, double_spend_seen, tx.double_spend_seen);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::tx_in_pool& tx)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, tx.tx, tx);
  GET_FROM_JSON_OBJECT(val, tx.blob_size, blob_size);
  GET_FROM_JSON_OBJECT(val, tx.weight, weight);
  GET_FROM_JSON_OBJECT(val, tx.fee, fee);
  GET_FROM_JSON_OBJECT(val, tx.max_used_block_hash, max_used_block_hash);
  GET_FROM_JSON_OBJECT(val, tx.max_used_block_height, max_used_block_height);
  GET_FROM_JSON_OBJECT(val, tx.kept_by_block, kept_by_block);
  GET_FROM_JSON_OBJECT(val, tx.last_failed_block_hash, last_failed_block_hash);
  GET_FROM_JSON_OBJECT(val, tx.last_failed_block_height, last_failed_block_height);
  GET_FROM_JSON_OBJECT(val, tx.receive_time, receive_time);
  GET_FROM_JSON_OBJECT(val, tx.last_relayed_time, last_relayed_time);
  GET_FROM_JSON_OBJECT(val, tx.relayed, relayed);
  GET_FROM_JSON_OBJECT(val, tx.do_not_relay, do_not_relay);
  GET_FROM_JSON_OBJECT(val, tx.double_spend_seen, double_spend_seen);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::hard_fork_info& info)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::hard_fork_info& info)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, version, info.version);
  INSERT_INTO_JSON_OBJECT(dest, enabled, info.enabled);
  INSERT_INTO_JSON_OBJECT(dest, window, info.window);
  INSERT_INTO_JSON_OBJECT(dest, votes, info.votes);
  INSERT_INTO_JSON_OBJECT(dest, threshold, info.threshold);
  INSERT_INTO_JSON_OBJECT(dest, voting, info.voting);
  INSERT_INTO_JSON_OBJECT(dest, state, info.state);
  INSERT_INTO_JSON_OBJECT(dest, earliest_height, info.earliest_height);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::hard_fork_info& info)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, info.version, version);
  GET_FROM_JSON_OBJECT(val, info.enabled, enabled);
  GET_FROM_JSON_OBJECT(val, info.window, window);
  GET_FROM_JSON_OBJECT(val, info.votes, votes);
  GET_FROM_JSON_OBJECT(val, info.threshold, threshold);
  GET_FROM_JSON_OBJECT(val, info.voting, voting);
  GET_FROM_JSON_OBJECT(val, info.state, state);
  GET_FROM_JSON_OBJECT(val, info.earliest_height, earliest_height);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::output_amount_count& out)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::output_amount_count& out)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, amount, out.amount);
  INSERT_INTO_JSON_OBJECT(dest, total_count, out.total_count);
  INSERT_INTO_JSON_OBJECT(dest, unlocked_count, out.unlocked_count);
  INSERT_INTO_JSON_OBJECT(dest, recent_count, out.recent_count);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::output_amount_count& out)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, out.amount, amount);
  GET_FROM_JSON_OBJECT(val, out.total_count, total_count);
  GET_FROM_JSON_OBJECT(val, out.unlocked_count, unlocked_count);
  GET_FROM_JSON_OBJECT(val, out.recent_count, recent_count);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::output_amount_and_index& out)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::output_amount_and_index& out)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, amount, out.amount);
  INSERT_INTO_JSON_OBJECT(dest, index, out.index);

  dest.EndObject();
}


void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::output_amount_and_index& out)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, out.amount, amount);
  GET_FROM_JSON_OBJECT(val, out.index, index);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::output_key_mask_unlocked& out)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, key, out.key);
  INSERT_INTO_JSON_OBJECT(dest, mask, out.mask);
  INSERT_INTO_JSON_OBJECT(dest, unlocked, out.unlocked);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::output_key_mask_unlocked& out)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, key, out.key);
  INSERT_INTO_JSON_OBJECT(dest, mask, out.mask);
  INSERT_INTO_JSON_OBJECT(dest, unlocked, out.unlocked);

>>>>>>> origin/android-wallet
  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::output_key_mask_unlocked& out)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, out.key, key);
  GET_FROM_JSON_OBJECT(val, out.mask, mask);
  GET_FROM_JSON_OBJECT(val, out.unlocked, unlocked);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::error& err)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, code, err.code);
  INSERT_INTO_JSON_OBJECT(dest, error_str, err.error_str);
  INSERT_INTO_JSON_OBJECT(dest, message, err.message);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::error& err)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, code, err.code);
  INSERT_INTO_JSON_OBJECT(dest, error_str, err.error_str);
  INSERT_INTO_JSON_OBJECT(dest, message, err.message);

>>>>>>> origin/android-wallet
  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::error& error)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, error.code, code);
  GET_FROM_JSON_OBJECT(val, error.error_str, error_str);
  GET_FROM_JSON_OBJECT(val, error.message, message);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::BlockHeaderResponse& response)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::BlockHeaderResponse& response)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, major_version, response.major_version);
  INSERT_INTO_JSON_OBJECT(dest, minor_version, response.minor_version);
  INSERT_INTO_JSON_OBJECT(dest, timestamp, response.timestamp);
  INSERT_INTO_JSON_OBJECT(dest, prev_id, response.prev_id);
  INSERT_INTO_JSON_OBJECT(dest, nonce, response.nonce);
  INSERT_INTO_JSON_OBJECT(dest, height, response.height);
  INSERT_INTO_JSON_OBJECT(dest, depth, response.depth);
  INSERT_INTO_JSON_OBJECT(dest, hash, response.hash);
  INSERT_INTO_JSON_OBJECT(dest, difficulty, response.difficulty);
  INSERT_INTO_JSON_OBJECT(dest, reward, response.reward);

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::BlockHeaderResponse& response)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, response.major_version, major_version);
  GET_FROM_JSON_OBJECT(val, response.minor_version, minor_version);
  GET_FROM_JSON_OBJECT(val, response.timestamp, timestamp);
  GET_FROM_JSON_OBJECT(val, response.prev_id, prev_id);
  GET_FROM_JSON_OBJECT(val, response.nonce, nonce);
  GET_FROM_JSON_OBJECT(val, response.height, height);
  GET_FROM_JSON_OBJECT(val, response.depth, depth);
  GET_FROM_JSON_OBJECT(val, response.hash, hash);
  GET_FROM_JSON_OBJECT(val, response.difficulty, difficulty);
  GET_FROM_JSON_OBJECT(val, response.reward, reward);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const rct::rctSig& sig)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const rct::rctSig& sig)
>>>>>>> origin/android-wallet
{
  using boost::adaptors::transform;

  dest.StartObject();

  const auto just_mask = [] (rct::ctkey const& key) -> rct::key const&
  {
    return key.mask;
  };

  INSERT_INTO_JSON_OBJECT(dest, type, sig.type);
  INSERT_INTO_JSON_OBJECT(dest, encrypted, sig.ecdhInfo);
  INSERT_INTO_JSON_OBJECT(dest, commitments, transform(sig.outPk, just_mask));
  INSERT_INTO_JSON_OBJECT(dest, fee, sig.txnFee);

  // prunable
  if (!sig.p.bulletproofs.empty() || !sig.p.rangeSigs.empty() || !sig.p.MGs.empty() || !sig.get_pseudo_outs().empty())
  {
    dest.Key("prunable");
    dest.StartObject();

    INSERT_INTO_JSON_OBJECT(dest, range_proofs, sig.p.rangeSigs);
    INSERT_INTO_JSON_OBJECT(dest, bulletproofs, sig.p.bulletproofs);
    INSERT_INTO_JSON_OBJECT(dest, mlsags, sig.p.MGs);
    INSERT_INTO_JSON_OBJECT(dest, pseudo_outs, sig.get_pseudo_outs());

    dest.EndObject();
  }

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, rct::rctSig& sig)
{
  using boost::adaptors::transform;

  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }


  GET_FROM_JSON_OBJECT(val, sig.type, type);
  GET_FROM_JSON_OBJECT(val, sig.ecdhInfo, encrypted);
  GET_FROM_JSON_OBJECT(val, sig.outPk, commitments);
  GET_FROM_JSON_OBJECT(val, sig.txnFee, fee);

  // prunable
  const auto prunable = val.FindMember("prunable");
  if (prunable != val.MemberEnd())
  {
    rct::keyV pseudo_outs = std::move(sig.get_pseudo_outs());

    GET_FROM_JSON_OBJECT(prunable->value, sig.p.rangeSigs, range_proofs);
    GET_FROM_JSON_OBJECT(prunable->value, sig.p.bulletproofs, bulletproofs);
    GET_FROM_JSON_OBJECT(prunable->value, sig.p.MGs, mlsags);
    GET_FROM_JSON_OBJECT(prunable->value, pseudo_outs, pseudo_outs);

    sig.get_pseudo_outs() = std::move(pseudo_outs);
  }
  else
  {
    sig.p.rangeSigs.clear();
    sig.p.bulletproofs.clear();
    sig.p.MGs.clear();
    sig.get_pseudo_outs().clear();
  }
}

<<<<<<< HEAD
void fromJsonValue(const rapidjson::Value& val, rct::ctkey& key)
{
  key.dest = {};
  fromJsonValue(val, key.mask);
}

void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const rct::ecdhTuple& tuple)
{
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const rct::ecdhTuple& tuple)
{
>>>>>>> origin/android-wallet
  dest.StartObject();
  INSERT_INTO_JSON_OBJECT(dest, mask, tuple.mask);
  INSERT_INTO_JSON_OBJECT(dest, amount, tuple.amount);
  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, rct::ecdhTuple& tuple)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, tuple.mask, mask);
  GET_FROM_JSON_OBJECT(val, tuple.amount, amount);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const rct::rangeSig& sig)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const rct::rangeSig& sig)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, asig, sig.asig);
  INSERT_INTO_JSON_OBJECT(dest, Ci, epee::span<const rct::key>{sig.Ci});

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, rct::rangeSig& sig)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  const auto ci = val.FindMember("Ci");
  if (ci == val.MemberEnd())
  {
    throw MISSING_KEY("Ci");
  }

  GET_FROM_JSON_OBJECT(val, sig.asig, asig);

  std::vector<rct::key> keyVector;
  cryptonote::json::fromJsonValue(ci->value, keyVector);
  if (!(keyVector.size() == 64))
  {
    throw WRONG_TYPE("key64 (rct::key[64])");
  }
  for (size_t i=0; i < 64; i++)
  {
    sig.Ci[i] = keyVector[i];
  }
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const rct::Bulletproof& p)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, V, p.V);
  INSERT_INTO_JSON_OBJECT(dest, A, p.A);
  INSERT_INTO_JSON_OBJECT(dest, S, p.S);
  INSERT_INTO_JSON_OBJECT(dest, T1, p.T1);
  INSERT_INTO_JSON_OBJECT(dest, T2, p.T2);
  INSERT_INTO_JSON_OBJECT(dest, taux, p.taux);
  INSERT_INTO_JSON_OBJECT(dest, mu, p.mu);
  INSERT_INTO_JSON_OBJECT(dest, L, p.L);
  INSERT_INTO_JSON_OBJECT(dest, R, p.R);
  INSERT_INTO_JSON_OBJECT(dest, a, p.a);
  INSERT_INTO_JSON_OBJECT(dest, b, p.b);
  INSERT_INTO_JSON_OBJECT(dest, t, p.t);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const rct::Bulletproof& p)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, V, p.V);
  INSERT_INTO_JSON_OBJECT(dest, A, p.A);
  INSERT_INTO_JSON_OBJECT(dest, S, p.S);
  INSERT_INTO_JSON_OBJECT(dest, T1, p.T1);
  INSERT_INTO_JSON_OBJECT(dest, T2, p.T2);
  INSERT_INTO_JSON_OBJECT(dest, taux, p.taux);
  INSERT_INTO_JSON_OBJECT(dest, mu, p.mu);
  INSERT_INTO_JSON_OBJECT(dest, L, p.L);
  INSERT_INTO_JSON_OBJECT(dest, R, p.R);
  INSERT_INTO_JSON_OBJECT(dest, a, p.a);
  INSERT_INTO_JSON_OBJECT(dest, b, p.b);
  INSERT_INTO_JSON_OBJECT(dest, t, p.t);

>>>>>>> origin/android-wallet
  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, rct::Bulletproof& p)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, p.V, V);
  GET_FROM_JSON_OBJECT(val, p.A, A);
  GET_FROM_JSON_OBJECT(val, p.S, S);
  GET_FROM_JSON_OBJECT(val, p.T1, T1);
  GET_FROM_JSON_OBJECT(val, p.T2, T2);
  GET_FROM_JSON_OBJECT(val, p.taux, taux);
  GET_FROM_JSON_OBJECT(val, p.mu, mu);
  GET_FROM_JSON_OBJECT(val, p.L, L);
  GET_FROM_JSON_OBJECT(val, p.R, R);
  GET_FROM_JSON_OBJECT(val, p.a, a);
  GET_FROM_JSON_OBJECT(val, p.b, b);
  GET_FROM_JSON_OBJECT(val, p.t, t);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const rct::boroSig& sig)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, s0, epee::span<const rct::key>{sig.s0});
  INSERT_INTO_JSON_OBJECT(dest, s1, epee::span<const rct::key>{sig.s1});
  INSERT_INTO_JSON_OBJECT(dest, ee, sig.ee);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const rct::boroSig& sig)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, s0, epee::span<const rct::key>{sig.s0});
  INSERT_INTO_JSON_OBJECT(dest, s1, epee::span<const rct::key>{sig.s1});
  INSERT_INTO_JSON_OBJECT(dest, ee, sig.ee);

>>>>>>> origin/android-wallet
  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, rct::boroSig& sig)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  OBJECT_HAS_MEMBER_OR_THROW(val, "s0")
  std::vector<rct::key> keyVector;
  cryptonote::json::fromJsonValue(val["s0"], keyVector);
  if (!(keyVector.size() == 64))
  {
    throw WRONG_TYPE("key64 (rct::key[64])");
  }
  for (size_t i=0; i < 64; i++)
  {
    sig.s0[i] = keyVector[i];
  }

  OBJECT_HAS_MEMBER_OR_THROW(val, "s1")
  keyVector.clear();
  cryptonote::json::fromJsonValue(val["s1"], keyVector);
  if (!(keyVector.size() == 64))
  {
    throw WRONG_TYPE("key64 (rct::key[64])");
  }
  for (size_t i=0; i < 64; i++)
  {
    sig.s1[i] = keyVector[i];
  }

  GET_FROM_JSON_OBJECT(val, sig.ee, ee);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const rct::mgSig& sig)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, ss, sig.ss);
  INSERT_INTO_JSON_OBJECT(dest, cc, sig.cc);

=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const rct::mgSig& sig)
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, ss, sig.ss);
  INSERT_INTO_JSON_OBJECT(dest, cc, sig.cc);

>>>>>>> origin/android-wallet
  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, rct::mgSig& sig)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("key64 (rct::key[64])");
  }

  GET_FROM_JSON_OBJECT(val, sig.ss, ss);
  GET_FROM_JSON_OBJECT(val, sig.cc, cc);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::DaemonInfo& info)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::DaemonInfo& info)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, height, info.height);
  INSERT_INTO_JSON_OBJECT(dest, target_height, info.target_height);
  INSERT_INTO_JSON_OBJECT(dest, difficulty, info.difficulty);
  INSERT_INTO_JSON_OBJECT(dest, target, info.target);
  INSERT_INTO_JSON_OBJECT(dest, tx_count, info.tx_count);
  INSERT_INTO_JSON_OBJECT(dest, tx_pool_size, info.tx_pool_size);
  INSERT_INTO_JSON_OBJECT(dest, alt_blocks_count, info.alt_blocks_count);
  INSERT_INTO_JSON_OBJECT(dest, outgoing_connections_count, info.outgoing_connections_count);
  INSERT_INTO_JSON_OBJECT(dest, incoming_connections_count, info.incoming_connections_count);
  INSERT_INTO_JSON_OBJECT(dest, white_peerlist_size, info.white_peerlist_size);
  INSERT_INTO_JSON_OBJECT(dest, grey_peerlist_size, info.grey_peerlist_size);
  INSERT_INTO_JSON_OBJECT(dest, mainnet, info.mainnet);
  INSERT_INTO_JSON_OBJECT(dest, testnet, info.testnet);
  INSERT_INTO_JSON_OBJECT(dest, stagenet, info.stagenet);
  INSERT_INTO_JSON_OBJECT(dest, nettype, info.nettype);
  INSERT_INTO_JSON_OBJECT(dest, top_block_hash, info.top_block_hash);
  INSERT_INTO_JSON_OBJECT(dest, cumulative_difficulty, info.cumulative_difficulty);
  INSERT_INTO_JSON_OBJECT(dest, block_size_limit, info.block_size_limit);
  INSERT_INTO_JSON_OBJECT(dest, block_weight_limit, info.block_weight_limit);
  INSERT_INTO_JSON_OBJECT(dest, block_size_median, info.block_size_median);
  INSERT_INTO_JSON_OBJECT(dest, block_weight_median, info.block_weight_median);
<<<<<<< HEAD
  INSERT_INTO_JSON_OBJECT(dest, adjusted_time, info.adjusted_time);
=======
>>>>>>> origin/android-wallet
  INSERT_INTO_JSON_OBJECT(dest, start_time, info.start_time);

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::DaemonInfo& info)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, info.height, height);
  GET_FROM_JSON_OBJECT(val, info.target_height, target_height);
  GET_FROM_JSON_OBJECT(val, info.difficulty, difficulty);
  GET_FROM_JSON_OBJECT(val, info.target, target);
  GET_FROM_JSON_OBJECT(val, info.tx_count, tx_count);
  GET_FROM_JSON_OBJECT(val, info.tx_pool_size, tx_pool_size);
  GET_FROM_JSON_OBJECT(val, info.alt_blocks_count, alt_blocks_count);
  GET_FROM_JSON_OBJECT(val, info.outgoing_connections_count, outgoing_connections_count);
  GET_FROM_JSON_OBJECT(val, info.incoming_connections_count, incoming_connections_count);
  GET_FROM_JSON_OBJECT(val, info.white_peerlist_size, white_peerlist_size);
  GET_FROM_JSON_OBJECT(val, info.grey_peerlist_size, grey_peerlist_size);
  GET_FROM_JSON_OBJECT(val, info.mainnet, mainnet);
  GET_FROM_JSON_OBJECT(val, info.testnet, testnet);
  GET_FROM_JSON_OBJECT(val, info.stagenet, stagenet);
  GET_FROM_JSON_OBJECT(val, info.nettype, nettype);
  GET_FROM_JSON_OBJECT(val, info.top_block_hash, top_block_hash);
  GET_FROM_JSON_OBJECT(val, info.cumulative_difficulty, cumulative_difficulty);
  GET_FROM_JSON_OBJECT(val, info.block_size_limit, block_size_limit);
  GET_FROM_JSON_OBJECT(val, info.block_weight_limit, block_weight_limit);
  GET_FROM_JSON_OBJECT(val, info.block_size_median, block_size_median);
  GET_FROM_JSON_OBJECT(val, info.block_weight_median, block_weight_median);
  GET_FROM_JSON_OBJECT(val, info.adjusted_time, adjusted_time);
  GET_FROM_JSON_OBJECT(val, info.start_time, start_time);
}

<<<<<<< HEAD
void toJsonValue(rapidjson::Writer<epee::byte_stream>& dest, const cryptonote::rpc::output_distribution& dist)
=======
void toJsonValue(rapidjson::Writer<rapidjson::StringBuffer>& dest, const cryptonote::rpc::output_distribution& dist)
>>>>>>> origin/android-wallet
{
  dest.StartObject();

  INSERT_INTO_JSON_OBJECT(dest, distribution, dist.data.distribution);
  INSERT_INTO_JSON_OBJECT(dest, amount, dist.amount);
  INSERT_INTO_JSON_OBJECT(dest, start_height, dist.data.start_height);
  INSERT_INTO_JSON_OBJECT(dest, base, dist.data.base);

  dest.EndObject();
}

void fromJsonValue(const rapidjson::Value& val, cryptonote::rpc::output_distribution& dist)
{
  if (!val.IsObject())
  {
    throw WRONG_TYPE("json object");
  }

  GET_FROM_JSON_OBJECT(val, dist.data.distribution, distribution);
  GET_FROM_JSON_OBJECT(val, dist.amount, amount);
  GET_FROM_JSON_OBJECT(val, dist.data.start_height, start_height);
  GET_FROM_JSON_OBJECT(val, dist.data.base, base);
}

}  // namespace json

}  // namespace cryptonote
