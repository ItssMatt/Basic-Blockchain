#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include "../nlohmann/json.hpp"
#include "../account/account.h"
#include "../utils/utils.h"

class CTransaction {
private:
	std::string from;
	std::string to;
	unsigned long long value;
	unsigned long long nonce;
	unsigned long long incentive;
public:
	std::string hash;
	nlohmann::json tx;
	unsigned short status;
	CTransaction();
	CTransaction(std::string from, std::string to, unsigned long long value, unsigned long long incentive);
	CTransaction(std::string from, std::string to, unsigned long long value, unsigned long long incentive, unsigned long long nonce);
	void loadTransactionFromJSON(nlohmann::json obj);
	bool executeTransaction();
	bool simulateTransaction();
	bool operator==(const CTransaction& obj);
};

extern std::vector<CTransaction> pendingTxs;


#endif