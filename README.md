# KaspaWalletManager

Currently the code is in development, most of the UI is done.

It supports:

* Create wallet.
* Create accounts ( At this moment does not show the generated seed and verify it ).
* Fetch balances of addresses.
* Show seed.

## Generated addresses are not real they are derived from the seed but not the correct ones.

If in settings is TESTNET selected will connect to a localhost 127.0.0.1:16210 node, if MAINNET is selected will connect to 23.88.70.20:30110 node.

I managed to make gRPC work only on MacOs, there are included the Apple Silicon libs.

Anyway building for MacOs is good enough to advance the base code till Rusty with JSON API will be implemented.

The wallet is AES256 encrypted with a SHA256 of the password and contain no additional data beside the base58 encoded seed as JSON file.

There need more coding in Kaspa address generating, transaction picking/aggregating/signing.

My cryptography skills are limited to pretty much copy/paste and glue level especially when I talk about BIP32 stuff, if someone can take the work for that it will be highly appreciated.

There I implemented some code taken from Bitcoin core code and try to adapt with no success.

I prefer in time to translate the BIP32 and all wallet core code from Qt to pure C++ code to be able to implement the wallet on IOT devices.

The mainwindow.cpp file has implemented some testing code for fast check of the correctitude of some functions in project.

The project uses Qt 6.2.4 lib version, I prefer older to be compatible with older OS'es.

The code is little bit messy, but I usually create readable code..., as usually when the wallet will be functional the "cleanItUp()" human function will be activated :)
 
