#ifndef REVERT_H
#define REVERT_H

#include <string>

class CRevert {
private:
	std::string message;
	unsigned int code;
public:
	CRevert(std::string message, unsigned int code);
	std::string getMessage();
	unsigned int getCode();
};

#endif