// Copyright (c) 2017 Pieter Wuille
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php .

// Bech32 is a string encoding format used in newer address types.
// The output consists of a human-readable part (alphanumeric), a
// separator character (1), and a base32 data section, the last
// 6 characters of which are a checksum.
//
// For more information, see BIP 173.

#ifndef BITCOIN_BECH32_H
#define BITCOIN_BECH32_H

#include <stdint.h>
#include <string>
#include <vector>


class bech32 {
public:
    typedef std::vector<uint8_t> data;
    typedef std::pair<std::pair<uint8_t, std::string>, data> decoded;
    /** Encode a Bech32 string. Returns the empty string in case of failure. */
    static std::string Encode(const std::string& hrp, const data& values, uint8_t version);

    /** Decode a Bech32 string. Returns (hrp, data). Empty hrp means failure. */
    static decoded Decode(const std::string& str);

}; // namespace bech32

#endif // BITCOIN_BECH32_H
