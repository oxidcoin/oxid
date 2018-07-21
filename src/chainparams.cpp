// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2018 Oxid developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"
#include "chainparams.h"
#include "main.h"
#include "util.h"
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Create genesis block
//
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits)
{
    const char* pszTimestamp = "World Cup 2018 Final Result: France 4-2 Croatia";
    std::vector<CTxIn> vin;
    vin.resize(1);
    vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    std::vector<CTxOut> vout;
    vout.resize(1);
    vout[0].SetEmpty();
    CTransaction txNew(1, nTime, vin, vout, 0);

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock = 0;
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    genesis.nVersion = 1;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;

    return genesis;
}

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress>& vSeedsOut, const unsigned int* data, unsigned int count, int port)
{
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int k = 0; k < count; ++k) {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t = (i & 0x000000ff) << 24u | (i & 0x0000ff00) << 8u | (i & 0x00ff0000) >> 8u | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        pchMessageStart[0] = 0xa5;
        pchMessageStart[1] = 0xb6;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("04221c24f26fd0d091b3786855b368b911dff7e06d3e7eab9246960b9d4650de8e90bbf6f1f7eec5279880fc5df55e9b41c98c03983f2978e426564236d4dfe41c");
        nDefaultPort = 18932;
        nRPCPort = 18933;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        /*
        mainnet.genesis :
            CBlock(hash=00000ef8f68dfa24b1d004ea73b55f1a90ea1787a033bcd8ce84bdac7526cfc9, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=95c3dd755be8df88257a6f62fe1c19e76e07218bfc5171c23240a54a726b91b1, nTime=1532070000, nBits=1e0ffff0, nNonce=647464, vtx=1, vchBlockSig=)
          Coinbase(hash=95c3dd755be8df88257a6f62fe1c19e76e07218bfc5171c23240a54a726b91b1, nTime=1532070000, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a2f576f726c642043757020323031382046696e616c20526573756c743a204672616e636520342d322043726f61746961)
            CTxOut(empty)

          vMerkleTree:  95c3dd755be8df88257a6f62fe1c19e76e07218bfc5171c23240a54a726b91b1

        mainnet.genesis.GetHash():      00000ef8f68dfa24b1d004ea73b55f1a90ea1787a033bcd8ce84bdac7526cfc9
        mainnet.genesis.hashMerkleRoot: 95c3dd755be8df88257a6f62fe1c19e76e07218bfc5171c23240a54a726b91b1
        mainnet.genesis.nTime:          1532070000
        mainnet.genesis.nNonce:         647464
        */

        /**
         * uint32_t nTime
         * uint32_t nNonce// 647464
         * uint32_t nBits // 0x1e0ffff0
         */
        genesis = CreateGenesisBlock(1532070000, 647464, 0x1e0ffff0);

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000ef8f68dfa24b1d004ea73b55f1a90ea1787a033bcd8ce84bdac7526cfc9"));
        assert(genesis.hashMerkleRoot == uint256("0x95c3dd755be8df88257a6f62fe1c19e76e07218bfc5171c23240a54a726b91b1"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 115); // o
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 29);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 189);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 48);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("seed1", "seed1.oxid.io"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.oxid.io"));

        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "oRHCZZowbTQ3g9NHaCFVLEBJFhQZbXuf6v";
        nLastPOWBlock = 100000;
        nPOSStartBlock = 1001;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const
    {
        return vFixedSeeds;
    }

protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        pchMessageStart[0] = 0xa5;
        pchMessageStart[1] = 0xb6;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0xba;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        vAlertPubKey = ParseHex("04fc303535c7a2f696f1ed22dfadafc6ce7454462b52ff71c4b11df73a3c6fafd4e1a5eaf2b01e43cd4fa1359b3fb63259977963f93235b1e040195074bf0ab495");
        nDefaultPort = 18942;
        nRPCPort = 18943;
        strDataDir = "testnet";

        /*
        testnet.genesis :
            CBlock(hash=00000dc4c8fd63f9968d57fb64682fa966bcd914618cb1d1dc5d3cb7c1809d9e, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=9c7598dd90e0328bbf01130a7191325b50db7273d4e80e26ca26d68cab7e5090, nTime=1532070300, nBits=1e0ffff0, nNonce=4258358, vtx=1, vchBlockSig=)
          Coinbase(hash=9c7598dd90e0328bbf01130a7191325b50db7273d4e80e26ca26d68cab7e5090, nTime=1532070300, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a2f576f726c642043757020323031382046696e616c20526573756c743a204672616e636520342d322043726f61746961)
            CTxOut(empty)

          vMerkleTree:  9c7598dd90e0328bbf01130a7191325b50db7273d4e80e26ca26d68cab7e5090

        mainnet.genesis.GetHash():      00000dc4c8fd63f9968d57fb64682fa966bcd914618cb1d1dc5d3cb7c1809d9e
        mainnet.genesis.hashMerkleRoot: 9c7598dd90e0328bbf01130a7191325b50db7273d4e80e26ca26d68cab7e5090
        mainnet.genesis.nTime:          1532070300
        mainnet.genesis.nNonce:         4258358
        */
        genesis = CreateGenesisBlock(1532070300, 4258358, 0x1e0ffff0);

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000dc4c8fd63f9968d57fb64682fa966bcd914618cb1d1dc5d3cb7c1809d9e"));
        assert(genesis.hashMerkleRoot == uint256("0x9c7598dd90e0328bbf01130a7191325b50db7273d4e80e26ca26d68cab7e5090"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 177);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 59);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 120);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 100000;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams* pCurrentParams = &mainParams;

const CChainParams& Params()
{
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network)
{
    switch (network) {
    case CChainParams::MAIN:
        pCurrentParams = &mainParams;
        break;
    case CChainParams::TESTNET:
        pCurrentParams = &testNetParams;
        break;
    default:
        assert(false && "Unimplemented network");
        return;
    }
}

bool SelectParamsFromCommandLine()
{
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
