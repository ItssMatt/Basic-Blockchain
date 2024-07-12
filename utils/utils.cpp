#include "utils.h"

std::string getAddressFromString(std::string key) {
	std::uint8_t hash[Keccak256::ADDR_LEN];
	Keccak256::getAddrHash(std::vector<std::uint8_t>(key.c_str(), key.c_str() + std::strlen(key.c_str())).data(), key.length(), hash);
	std::stringstream ss;
	ss << "W_";
	for (int i = 0; i < Keccak256::ADDR_LEN; ++i) {
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
	}
	return ss.str();
}

std::string getHashFromString(std::string key) {
	std::uint8_t hash[Keccak256::HASH_LEN];
	Keccak256::getHash(std::vector<std::uint8_t>(key.c_str(), key.c_str() + std::strlen(key.c_str())).data(), key.length(), hash);
	std::stringstream ss;
	ss << "H_";
	for (int i = 0; i < Keccak256::HASH_LEN; ++i) {
		ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
	}
	return ss.str();
}