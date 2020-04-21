#ifndef BISTREAM_H
#define BISTREAM_H
#include "common.h"


class BitInputStream {
private:
	char buffer;
	int bPos;
	istream& in;

public:
	explicit BitInputStream(istream& is):buffer(0), bPos(CH_BITS), in(is){}
	int readBit();
	int getBit(char buff, int pos);
	inline istream& getInputStream() const { return in; }
	
};


#endif BISTREAM_H
