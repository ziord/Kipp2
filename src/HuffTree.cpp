#include "HuffTree.h"


void HTree::createTree() {
	priority_queue<HNode*, vector<HNode*>, HTreeCmp> pq;
	for (int i = 0; i < CH_MAX; i++) {
		auto freq = ch.getFreq(i);
		if (freq > 0) {
			auto cur = new HNode(i, freq, nullptr, nullptr, nullptr);
			hNodes[i] = cur;
			pq.push(cur);
		}
	}
	//set END_ for decoding sentinel
	auto end_ = new HNode(END_, 1, nullptr, nullptr, nullptr);
	hNodes[END_] = end_;
	pq.push(end_);
	while (pq.size() > 1) {
		HNode* ln = pq.top(); pq.pop();
        HNode* rn = pq.top(); pq.pop();
        auto par = new HNode(UND_, (ln->freq + rn->freq), ln, rn, nullptr);
		ln->parent = rn->parent = par;
		pq.push(par);
	}
	if (!pq.empty()) {
		root = pq.top();
	}
}

vector<int> HTree::getCode(int ch) {
	vector<int> code;
	auto itr= hNodes.find(ch);
	if (itr == hNodes.end())
		return vector<int>();
	HNode* cur = itr->second; 
	//walk up the tree
	HNode* parent = cur->parent;
	while (parent) {
		if (parent->left == cur)
			code.push_back(0);
		else
			code.push_back(1);
		cur = cur->parent;
		parent = cur->parent;
	}
	reverse(code.begin(), code.end()); //reverse the vector to obtain the code in the right order
	return code;
}

int HTree::getChar(vector<int>& code)const {
	HNode* cur = root;

	for (int i = 0; cur && i < code.size(); i++) {
		if (code[i] == 0)
			cur = cur->left;
		else if (code[i] == 1)
			cur = cur->right;
	}

	if (!cur)
		return ERR_;
	return (*cur).val;
}

void HTree::writeEncodingTable(ostream& out) {
	for (int i = 0; i < CH_MAX; i++) {
		int f = ch.getFreq((char)i);
		if (f > 0) { //filter out unused characters
			out << static_cast<char>(i) << f << '\n';
		}
	}
	out << '\0' << 0 << '\n'; //stopper/sentinel for encoding table
}

void HTree::readEncodingTable(istream& in) {
	for (int i = 0; i < CH_MAX; i++)
		ch.setFreq((char)i, 0);
	char c, nl;
	int f;
	while(!in.eof()) {
		in.get(c);
		in >> f;
		in.get(nl);
		if (f == 0)
			break;
		ch.setFreq(c, f);
	}
	createTree();
}

void HTree::deleteAllNodes(HNode* node) {
	HNode* cur = node;
	while (cur) {
        if (cur->left) {
            deleteAllNodes(cur->left);
        }
        if (cur->right) {
            deleteAllNodes(cur->right);
        }
        delete cur;
        cur = nullptr;
    }
}

bool HNode::operator<(const HNode& hn) {
	return freq > hn.freq;
}