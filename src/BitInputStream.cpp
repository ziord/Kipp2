#include "BitInputStream.h"

int BitInputStream::getBit(char buff, int pos) {
	return  (buff & (1 << pos)) ? 1 : 0;   //use a mask to obtain the bit at offset pos
}

int BitInputStream::readBit() {
	if (bPos == CH_BITS) {
		in.get(buffer);  //get a byte for a new set of bits
		if (in.eof()) return EOF;  //check for eof
		bPos = 0; 
	}
	return getBit(buffer, bPos++);
}
