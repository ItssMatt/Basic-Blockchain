#ifndef MINER_H
#define MINER_H

#include <string>

#include "../block/block.h"
#include "../nlohmann/json.hpp"


class CMiner {
public:
	std::string minerAddress;
	CBlock block;
	static void mineSelf();
	CMiner();
	CMiner(std::string minerAddress, CBlock block);
};

#endif