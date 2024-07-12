#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "../transaction/transaction.h"

class CBlock {
private:
	unsigned long long blockId;
	std::string minerAddress;
public:
	std::string blockHash;
	std::vector<CTransaction> blockTxs;
	nlohmann::json blockData;
	static CBlock latest;
	static unsigned long long blockCount;
	CBlock();
	CBlock(std::vector<CTransaction> blockTxs, std::string minerAddress);
	void loadBlockFromJSON(nlohmann::json obj);
	void submitBlock();
};

extern std::vector<CBlock> blocks;


#endif