#include "miner.h"

CMiner::CMiner() : minerAddress("W_0000000000000000000000000000000000000000"), block(CBlock()) { }

CMiner::CMiner(std::string minerAddress, CBlock block) : minerAddress(minerAddress), block(block) { 
	
}

void CMiner::mineSelf() {
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    std::sort(pendingTxs.begin(), pendingTxs.end(), [](const CTransaction& a, const CTransaction& b) {
        return a.tx["incentive"] > b.tx["incentive"];
        });
    std::vector<CTransaction> transactions;
    unsigned short index = 0;
    for (auto& tx : pendingTxs) {
        index++;
        transactions.push_back(tx);
        if (index == Constants::MAX_TX_PER_BLOCK)
            break;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // ^^^ This part must be done by the miners

    CBlock newBlock = CBlock(transactions, "W_0000000000000000000000000000000000000000");
    newBlock.submitBlock();
}