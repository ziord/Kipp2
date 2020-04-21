#ifndef CHR_H
#define CHR_H
#include "common.h"
class Counter {
private:
	istream& in;
	map<char, int> charsDict;
	void count();
public:
	explicit Counter(istream& in) : in(in) { count(); }
	explicit Counter(): in(cin){};
	void setFreq(char ch, int freq);
	[[nodiscard]] int getFreq(char ch) const;
};
#endif
