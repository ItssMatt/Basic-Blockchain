#include "block.h"

CBlock CBlock::latest = CBlock();
unsigned long long CBlock::blockCount = 0;

std::vector<CBlock> blocks;

CBlock::CBlock() : blockHash("B_00"), minerAddress("W_0000000000000000000000000000000000000000"), blockId(0) { 
	blockData["hash"] = "B_00";
	blockData["miner"] = "W_0000000000000000000000000000000000000000";
	blockData["txcount"] = 0;
} // used for the default empty object

CBlock::CBlock(std::vector<CTransaction> blockTxs, std::string minerAddress) : blockTxs(blockTxs), minerAddress(minerAddress), blockId(0) {
	std::stringstream ss;
	ss << minerAddress << blockTxs.size() << nonces[minerAddress]++;
	blockHash = getHashFromString(ss.str());
	latest = *this;
	blockData["hash"] = blockHash;
	blockData["miner"] = minerAddress;
	blockData["txcount"] = blockTxs.size();
	unsigned short index = 0;
	for (auto& tx : blockTxs) {
		blockData["tx"][index++] = tx.tx;
	}
}

void CBlock::loadBlockFromJSON(nlohmann::json obj) {
	blockData = obj;
	blockHash = obj["hash"];
	minerAddress = obj["miner"];
	blockId = obj["id"];
	for (unsigned short i = 0; i < obj["txcount"]; i++) {
		CTransaction tx;
		tx.loadTransactionFromJSON(obj["tx"][i]);
		blockTxs.push_back(tx);
	}
}

void CBlock::submitBlock() {
	blockData["id"] = CBlock::blockCount;

	for (auto& tx : blockTxs) {
		bool status = tx.executeTransaction();
		tx.tx["status"] = tx.status = status;
		balances[blockData["miner"]] = CSafeMath::add(balances[blockData["miner"]], tx.tx["incentive"]);
		pendingTxs.erase(std::remove(pendingTxs.begin(), pendingTxs.end(), tx), pendingTxs.end());
	}
	std::stringstream ss;
	ss << Constants::blocksDirectory << "\\" << CBlock::blockCount++ << ".blk";
	std::ofstream outBlock(ss.str());
	outBlock << blockData.dump(4);
	outBlock.close();
	std::cout << "[CBLOCK] Block " << CBlock::blockCount - 1 << " submitted.\n";
	blocks.push_back(*this);
	latest = *this;
}