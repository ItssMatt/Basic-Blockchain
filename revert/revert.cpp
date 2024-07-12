#include "revert.h"

CRevert::CRevert(std::string message, unsigned int code) : message(message), code(code) {

}

std::string CRevert::getMessage() {
	return this->message;
}

unsigned int CRevert::getCode() {
	return this->code;
}