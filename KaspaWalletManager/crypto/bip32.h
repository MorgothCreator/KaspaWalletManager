#ifndef HIERARCHICALDETERMINISTICWALLETS_HDWALLET_H
#define HIERARCHICALDETERMINISTICWALLETS_HDWALLET_H

#define SERIALIZED_KEY_BUFFER_LEN 112
#define VERSION_IDENTIFIER_LEN 4

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <openssl/ripemd.h>
#include <openssl/sha.h>

#ifdef __cplusplus
extern "C" {
#endif

// BIP32 Extended Key
typedef struct {
    uint8_t version[VERSION_IDENTIFIER_LEN];
    uint8_t depth;
    uint8_t parentFingerprint[4];
    uint8_t childNumber[4];
    uint8_t chainCode[32];
    uint8_t privateKey[32];
} __attribute__ ((packed)) BIP32_xkey_t;

typedef enum {
    BIP32_XKEY_TYPE_PUBLIC = 0,
    BIP32_XKEY_TYPE_PRIVATE = 1
} BIP32_XKEY_TYPE;

typedef enum {
    BIP32_XKEY_NET_MAINNET = 0,
    BIP32_XKEY_NET_TESTNET = 2,
    BIP32_XKEY_NET_DEVNET = 4,
    BIP32_XKEY_NET_SIMNET = 6
} BIP32_XKEY_NET;

/*
 * Contains the values of xkey version prefixes
 */
extern const uint8_t KEY_VERSIONS_VALUES[8][VERSION_IDENTIFIER_LEN];

/*
 * Generates the Master Node from a `seed` and puts it into `xkey`
 */
int BIP32_NewMaster(uint8_t *seed,
                             size_t seed_len,
                             BIP32_XKEY_NET net,
                             BIP32_xkey_t *key);

/*
 * Takes the `key` and turns it into a BIP32 compliant Base58 representation.
 * Outputs the string in a buffer of size `SERIALIZED_KEY_BUFFER_LEN`
 */
int BIP32_serialize_key(BIP32_xkey_t *key,
                      uint8_t *destination,
                      size_t *destination_len);

/*
 * Generates the extended public key from an extended private key
 * If provided private key is in fact public, the content pointed by `private_key` is copied to `public key`
 * Returns: 0 on failure
 *          1 on success
 */

int BIP32_derive_public(BIP32_xkey_t *private_key, BIP32_xkey_t *public_key);

/*
 * Derives a private child xkey
 * Returns: 0 on failure
 *          1 on success
 */
int BIP32_derive_private_child(BIP32_xkey_t *parent_key, BIP32_xkey_t *child_key, uint32_t index);

/*
 * Derives a public child xkey
 * Returns: 0 on failure
 *          1 on success
 */
int BIP32_derive_public_child(BIP32_xkey_t *parent_key, BIP32_xkey_t *child_key, uint32_t index);

/*
 * RIPEMD160 o SHA256
 * Returns: 0 on failure
 *          1 on success
 */
int BIP32_hash160(uint8_t *input,
                uint32_t input_len,
                uint8_t output[RIPEMD160_DIGEST_LENGTH]);

bool BIP32_is_xkey_hardened(BIP32_xkey_t *key);

int BIP32_double_SHA256(uint8_t *input,
                      uint32_t input_len,
                      uint8_t output[SHA256_DIGEST_LENGTH]);

int BIP32_hash160(uint8_t *input,
                uint32_t input_len,
                uint8_t output[RIPEMD160_DIGEST_LENGTH]);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //HIERARCHICALDETERMINISTICWALLETS_HDWALLET_H

