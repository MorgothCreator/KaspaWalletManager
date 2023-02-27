// Copyright (c) 2017 Pieter Wuille
// Modified in 2023 for Kaspa coin by Iulian Gheorghiu
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php .

#include "bech32.h"

#include <string.h>

/** The Bech32 character set for encoding. */
const char* CHARSET = "qpzry9x8gf2tvdw0s3jn54khce6mua7l";
const int checksumLength = 8;

// For use in convertBits. Represents a number of bits to convert to or from and whether
// to add padding.
typedef struct {
    uint8_t fromBits;
    uint8_t toBits;
    bool pad;
}conversionType_t;

// Conversion types to use in convertBits.
conversionType_t fiveToEightBits = {.fromBits = 5, .toBits = 8, .pad = false};
conversionType_t eightToFiveBits = {.fromBits = 8, .toBits = 5, .pad = true};

/** Concatenate two byte arrays. */
bech32::data Cat(bech32::data x, const bech32::data& y) {
    bech32::data z = {0};
    x.insert(x.end(), z.begin(), z.end());
    x.insert(x.end(), y.begin(), y.end());
    return x;
}

/** Concatenate two byte arrays. */
bech32::data CatS(bech32::data x, const bech32::data& y) {
    x.insert(x.end(), y.begin(), y.end());
    return x;
}

uint64_t PolyMod(const bech32::data& v) {
    uint64_t c = 1;
    for (auto v_i : v) {
        uint8_t c0 = c >> 35;
        c = ((c & 0x07ffffffff) << 5) ^ v_i;
        if (c0 & 1)  c ^= 0x98f2bc8e61;
        if (c0 & 2)  c ^= 0x79b76d99e2;
        if (c0 & 4)  c ^= 0xf33e5fb3c4;
        if (c0 & 8)  c ^= 0xae2eabe2a8;
        if (c0 & 16) c ^= 0x1e4f43e470;
    }
    return c ^ 1;
}

/** Convert to lower case. */
inline unsigned char LowerCase(unsigned char c) {
    return (c >= 'A' && c <= 'Z') ? (c - 'A') + 'a' : c;
}

/** Expand a HRP for use in checksum computation. */
bech32::data ExpandHRP(const std::string& hrp) {
    bech32::data ret;
    ret.reserve(hrp.size() + 90);
    ret.resize(hrp.size());
    for (size_t i = 0; i < hrp.size(); ++i) {
        unsigned char c = hrp[i];
        ret[i] = c & 0x1f;
    }
    return ret;
}

/** Verify a checksum. */
bool VerifyChecksum(const std::string& hrp, const bech32::data& values) {
    uint64_t tmp = PolyMod(Cat(ExpandHRP(hrp), values));
    return tmp == 0;
}

/** Create a checksum. */
bech32::data CreateChecksum(const std::string& hrp, const bech32::data& values) {
    bech32::data enc = Cat(ExpandHRP(hrp), values);
    enc.resize(enc.size() + 8); // Append 8 zeroes
    uint64_t mod = PolyMod(enc);
    bech32::data ret(8);
    for (size_t i = 0; i < checksumLength; ++i) {
        // Convert the 5-bit groups in mod to checksum values.
        ret[i] = (mod >> (5 * (checksumLength - 1 - i))) & 31;
    }
    return ret;
}

// convertBits converts a byte slice where each byte is encoding fromBits bits,
// to a byte slice where each byte is encoding toBits bits.
bech32::data ConvertBits(bech32::data data, conversionType_t conversionType) {
    // The final bytes, each byte encoding toBits bits.
    bech32::data regrouped;
    // Keep track of the next byte we create and how many bits we have
    // added to it out of the toBits goal.
    uint8_t nextByte = 0;
    uint8_t filledBits = 0;
    for ( uint8_t b : data ) {
        // Discard unused bits.
        b = b << (8 - conversionType.fromBits);
        // How many bits remaining to extract from the input data.
        uint8_t remainingFromBits = conversionType.fromBits;
        for (; remainingFromBits > 0 ;) {
            // How many bits remaining to be added to the next byte.
            uint8_t remainingToBits = conversionType.toBits - filledBits;

            // The number of bytes to next extract is the minimum of
            // remainingFromBits and remainingToBits.
            uint8_t toExtract = remainingFromBits;
            if( remainingToBits < toExtract ) {
                toExtract = remainingToBits;
            }
            // Add the next bits to nextByte, shifting the already
            // added bits to the left.
            nextByte = (nextByte << toExtract) | (b >> (8 - toExtract));
            // Discard the bits we just extracted and get ready for
            // next iteration.
            b = b << toExtract;
            remainingFromBits -= toExtract;
            filledBits += toExtract;
            // If the nextByte is completely filled, we add it to
            // our regrouped bytes and start on the next byte.
            if( filledBits == conversionType.toBits ) {
                regrouped.insert(regrouped.end(), nextByte);
                filledBits = 0;
                nextByte = 0;
            }
        }
    }
    // We pad any unfinished group if specified.
    if( conversionType.pad && filledBits > 0 ) {
        nextByte = nextByte << (conversionType.toBits - filledBits);
        regrouped.insert(regrouped.end(), nextByte);
    }
    return regrouped;
}


/** Encode a Bech32 string. */
std::string bech32::Encode(const std::string& hrp, const bech32::data& values, uint8_t version) {
    bech32::data data(values.size() + 1);
    data.resize(1);
    data[0] = version;
    data.insert(data.end(), values.begin(), values.end());
    bech32::data  reverted = ConvertBits(data, eightToFiveBits);
    bech32::data checksum = CreateChecksum(hrp, reverted);
    bech32::data combined = CatS(reverted, checksum);
    std::string ret = hrp + ':';
    ret.reserve(ret.size() + combined.size());
    for (auto c : combined) {
        if (c >= 32) {
            return "";
        }
        ret += CHARSET[c];
    }
    return ret;
}

/** Decode a Bech32 string. */
bech32::decoded bech32::Decode(const std::string& str) {
    bool lower = false, upper = false;
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char c = str[i];
        if (c < 33 || c > 126)
            return {};
        if (c >= 'a' && c <= 'z') lower = true;
        if (c >= 'A' && c <= 'Z') upper = true;
    }
    if (lower && upper)
        return {};
    size_t pos = str.rfind(':');
    if (str.size() > 1023 || pos == str.npos || pos == 0 || pos + checksumLength + 1 > str.size())
        return {};
    bech32::data values(str.size() - 1 - pos);
    for (size_t i = 0; i < str.size() - 1 - pos; ++i) {
        unsigned char c = str[i + pos + 1];
        const char *rev = strchr(CHARSET, c);
        if (rev == nullptr)
            return {};
        values[i] = (uint8_t)(rev - CHARSET);
    }
    std::string hrp;
    for (size_t i = 0; i < pos; ++i)
        hrp += LowerCase(str[i]);
    if (!VerifyChecksum(hrp, values))
        return {};
    bech32::data converted = ConvertBits(bech32::data(values.begin(), values.end() - checksumLength), fiveToEightBits);
    uint8_t version = converted[0];
    bech32::data data;
    data.insert(data.end(), converted.begin() + 1, converted.end());
    return {{version, hrp}, data};
}

