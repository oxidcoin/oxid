// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2018 Oxid developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "checkpoints.h"
#include "main.h"
#include "txdb.h"
#include "uint256.h"
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
		(0, uint256("0x00000ef8f68dfa24b1d004ea73b55f1a90ea1787a033bcd8ce84bdac7526cfc9"))
    (5000, uint256("0x8f3e7db9fca7fa4dcc44425c509289ef66e1bbb42861fcf4687cd168ae5dafca"))
    (10000, uint256("0xd87e67c90eae992968f3ea6afd9f3892c37fccbcf2a621c0392bf4426ab3771f"))
    (15000, uint256("0x062280116ba847728d9982807bf1920375578b6509a01d38ac63caa3b9c6d939"))
    (20000, uint256("0x64695be47016651cd11fa724f86ac80a19557d7a966c5d21ba39154938eb9d7f"))
    (25000, uint256("0x6e5603fefcc56f039788770e925297608c99e8521a96da2df12f2b98321046f5"))
    (30000, uint256("0x7e76a1c493ad4dcdf9e37895ee79a0c0e8a3e41eec7943333f7219b9138216ab"))
    (35000, uint256("0xc9a49c372eda51e1d96d719a35e00b03f8e5686bb733f772d17646ee2b02fc1c"))
    (39285, uint256("0x8f58dfa24c768ffd8d8fbc56140312fc2d96422cc1ae7931102ebfc83ed22db6"))
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        //return checkpoints.rbegin()->first;
        return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                //return t->second;
                return NULL;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
