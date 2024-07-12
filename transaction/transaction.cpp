#include "transaction.h"

std::vector<CTransaction> pendingTxs;

CTransaction::CTransaction() { }

CTransaction::CTransaction(std::string from, std::string to, unsigned long long value, unsigned long long incentive) : from(from), to(to), value(value), nonce(++nonces[getAddressFromString(from)]), incentive(incentive) {
	std::stringstream ss;
	ss << from << to << nonce;
	hash = getHashFromString(ss.str());
	tx["from"] = from;
	tx["to"] = to;
	tx["value"] = value;
	tx["nonce"] = nonce;
	tx["incentive"] = incentive;
	tx["hash"] = hash;
	tx["status"] = status = 0;
	pendingTxs.push_back(*this);
	std::cout << "Tx: " << hash << " (pending)\n";
}

CTransaction::CTransaction(std::string from, std::string to, unsigned long long value, unsigned long long incentive, unsigned long long nonce) : from(from), to(to), value(value), nonce(nonce), incentive(incentive) {
	std::stringstream ss;
	ss << from << to << nonce;
	hash = getHashFromString(ss.str());
	tx["hash"] = hash;
	tx["from"] = from;
	tx["to"] = to;
	tx["value"] = value;
	tx["incentive"] = incentive;
	tx["nonce"] = nonce;
	tx["status"] = status = 0;
	pendingTxs.push_back(*this);
	std::cout << "Tx: " << hash << " (pending)\n";
}

void CTransaction::loadTransactionFromJSON(nlohmann::json obj) {
	tx = obj;
	hash = obj["hash"];
	from = obj["from"];
	to = obj["to"];
	value = obj["value"];
	incentive = obj["incentive"];
	nonce = obj["nonce"];
	status = obj["status"];
	if (nonces[getAddressFromString(from)] < nonce)
		nonces[getAddressFromString(from)] = nonce;
}

bool CTransaction::executeTransaction() {
	pendingTxs.erase(std::remove(pendingTxs.begin(), pendingTxs.end(), *this), pendingTxs.end());
	if (this->tx["nonce"] < CAccount::getNonce(getAddressFromString(from)) || this->tx["incentive"] < 10)
		return false;
	if (this->tx["value"] == 0 || this->tx["to"] == this->tx["from"])
		return true;
	unsigned long long balanceFrom = CAccount::getBalance(this->tx["from"]);
	unsigned long long balanceTo = CAccount::getBalance(this->tx["to"]);
	try {
		CAccount::transfer(this->tx["from"], this->tx["to"], this->tx["value"]);
		balances[this->tx["from"]] = CSafeMath::sub(balances[this->tx["from"]], this->tx["incentive"]); // incentive for the miner
		return true;
	}
	catch (CRevert revert) {
		std::cout << "[CREVERT] Execution Reverted (" << revert.getMessage() << " Code: " << revert.getCode() << ")\n";
		CAccount::set(this->tx["from"], balanceFrom);
		CAccount::set(this->tx["to"], balanceTo);
		return false;
	}
}

bool CTransaction::simulateTransaction() {
	unsigned long long balanceFrom = CAccount::getBalance(this->tx["from"]);
	unsigned long long balanceTo = CAccount::getBalance(this->tx["to"]);
	bool status = executeTransaction();
	if (status) {
		CAccount::set(this->tx["from"], balanceFrom);
		CAccount::set(this->tx["to"], balanceTo);
	}
	return status;
}

bool CTransaction::operator==(const CTransaction& obj) {
	return this->tx == obj.tx;
}