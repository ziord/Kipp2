#ifndef COMPRESSION_H
#define COMPRESSION_H
#include "HuffTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include <string>
#include <experimental/filesystem>
namespace fs = experimental::filesystem;

#define magicmarker  0xface8200

class Compression {

public:
	explicit Compression()= default;
	bool compress(string& fn, string out, bool many_flag);
	void compress_many(vector<string> files);
	void uncompress(string& fn, string& fn2);
	void uncompress_many(string& files, string& folder_name);
	void error(string);
};
#endif // !COMPRESSION_H
