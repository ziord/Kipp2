#ifndef HUFF_TREE_H
#define HUFF_TREE_H
#include "Chr.h"

 class HNode{
 public:
	int val;
	int freq;
	HNode* left;
	HNode* right;
	HNode* parent;
	HNode(int val, int freq, HNode* left, HNode* right, HNode* parent) :
		val(val), freq(freq), left(left), right(right), parent(parent) {}
	bool operator<(const HNode& rn);
};


 class HTreeCmp {
 public:
	 bool operator()(HNode* ln, HNode* rn) {
	     if (ln->freq != rn->freq)
		    return ln->freq > rn->freq;
	     else
	         return ln->val > rn->val;
	 }
 };

 class HTree {
 private:
	 Counter ch;
	 map<int, HNode*> hNodes;
	 void createTree();
	 HNode* root;

 public:
	 enum{ERR_ = -3, UND_ = -2, END_ = -1};
	 HTree():root(nullptr){}
	 explicit HTree(Counter& ch) :ch(ch) { root = nullptr; createTree(); }
	 ~HTree() { deleteAllNodes(root); }
	 void deleteAllNodes(HNode*);
	 void writeEncodingTable(ostream& out);
	 void readEncodingTable(istream& in);
	 vector<int> getCode(int ch);
	 int getChar(vector<int>& code) const;
};

#endif