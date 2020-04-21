#ifndef BOSTREAM_H
#define BOSTREAM_H
#include "common.h"
class BitOutputStream {
private:
	char buffer;
	int bPos;
	ostream& out;
public:
	explicit BitOutputStream(std::ostream& out): buffer(0), bPos(0), out(out){}
	~BitOutputStream() { flushStream(); }
	void writeBit(int bit);
	void writeBits(vector<int> bits);
	void reset();
	void flushStream();
	inline ostream& getOutputStream() const { return out; }

    static void setBit(char& buff, int val, int pos) {
        if (val == 1) {
            buff |= (val << pos); //set the bit on in buff
        }
    }
};


#endif