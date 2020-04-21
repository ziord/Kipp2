#include "Chr.h"

void Counter::count() {  //input param
	char ch;
	while (!in.get(ch).eof()){
		charsDict[ch]++;
	}
}

void Counter::setFreq(char ch, int freq) {
	charsDict[ch] = freq;
}

int Counter::getFreq(char ch) const {
	auto itr = charsDict.find(ch);
	return itr != charsDict.end() ? itr->second : 0;
}
