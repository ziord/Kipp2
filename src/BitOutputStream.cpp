#include "BitOutputStream.h"


void BitOutputStream::writeBit(int bit) {
	setBit(buffer, bit, bPos++);
	if (bPos == CH_BITS) {  //successfully stored an octet byte(8bits) in buffer
		flushStream(); 
	}
}

void BitOutputStream::reset() {
	bPos = 0;
	buffer = 0;
}

void BitOutputStream::flushStream() {
	if (bPos == 0) return; //nothing to flush
	out.put(buffer);
	reset();
}

void BitOutputStream::writeBits(vector<int> bits) {
	for (auto bit : bits) {
		writeBit(bit);
	}
}


