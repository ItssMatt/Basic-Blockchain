#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "nlohmann/json.hpp"

namespace Constants {

	extern nlohmann::json configFile;
	extern std::string SYMBOL;
	extern std::string NAME;
	extern unsigned short BLOCK_TIME;
	extern unsigned short DECIMALS;
	extern unsigned long long TOTAL_SUPPLY;
	extern std::string blocksDirectory;

	const unsigned long long CEILING = 18446744073709551615;
	const unsigned short MAX_TX_PER_BLOCK = 10;

}

#endif