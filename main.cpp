
#include <fstream>
#include <filesystem>
#include <string>

#include "constants.h"

#include "account/account.h"
#include "block/block.h"
#include "utils/utils.h"

#include "thread/thread.h"

int main(int argc, char* argv[]) {
	std::filesystem::path exePath = std::filesystem::canonical(argv[0]).parent_path();
	std::filesystem::path configPath = exePath / "config.json";
	std::ifstream ifs(configPath.string());
	if (!ifs.is_open()) {
		std::cerr << "[CONFIG] Unable to open config.json!\n";
		return 0;
	}
	ifs >> Constants::configFile;
	
	Constants::SYMBOL = (std::string)Constants::configFile["symbol"];
	Constants::NAME = (std::string)Constants::configFile["name"];
	Constants::DECIMALS = (unsigned short)Constants::configFile["decimals"];
	Constants::BLOCK_TIME = (unsigned short)Constants::configFile["block_time"];
	Constants::TOTAL_SUPPLY = (unsigned long long)Constants::configFile["total_supply"];

	std::cout << "Name: " << Constants::NAME << " ($" << Constants::SYMBOL << ")\n\n\n";

	for (unsigned short i = 0; i < Constants::configFile["accounts"].size(); i++) {
		CAccount::set(getAddressFromString(Constants::configFile["accounts"][i]["key"]), Constants::configFile["accounts"][i]["amount"]);
	}

	try {
		std::filesystem::path blocksDirectory = exePath / "blocks";
		Constants::blocksDirectory = blocksDirectory.string();
		for (const auto& entry : std::filesystem::directory_iterator(blocksDirectory)) {
			if (!strstr(entry.path().filename().string().c_str(), ".blk"))
				continue;
			CBlock block;
			std::ifstream blockFile(entry.path().string());
			blockFile >> block.blockData;
			blockFile.close();
			block.loadBlockFromJSON(block.blockData);

			if (strcmp(block.blockHash.c_str(), "B_00") == 0)
				continue;

			block.submitBlock();
		}
		if (!CBlock::blockCount)
			std::cout << "[CBLOCK] No blocks found.\n";
		else 
			std::cout << "[CBLOCK] " << CBlock::blockCount << " block" << (CBlock::blockCount != 1 ? "s" : "") << " found.\n";
	}
	catch (int e) {
		(void)e; // suppress unused variable warning 
		std::cout << "[CBLOCK] An error occured while loading blocks. Make sure the folder exists and the blocks are valid!";
	}

	if (balances.size() > 0) {
		std::cout << "[CACCOUNT] Loaded accounts: " << balances.size() << "\n";
		std::cout << "\n==================================================\n";
		unsigned short index = 1;
		for (const auto& account : balances) {
			std::cout << "(" << index++ << ") " << account.first << ": " << account.second << " " << Constants::SYMBOL << "\n";
		}
		std::cout << "==================================================\n\n";
	}
	else std::cout << "[CACCOUNT] Loaded accounts: 0\n";
	
	CThread mineThread = CThread(&mineThreadFn, "Mine Thread");

	//CTransaction tr = CTransaction(getAddressFromString(Constants::configFile["accounts"][0]["key"]), getAddressFromString(Constants::configFile["accounts"][1]["key"]), 100, 20);

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	return 1;
}