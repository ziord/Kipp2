#include "Compression.h"

void Compression::error(string msg){
    cerr<<msg<<endl;
    exit(EXIT_FAILURE);
}

bool Compression::compress(string& fn, string nfn, bool many_flag) {
//	string nfn = out;
	ifstream in(fn.c_str(), (ios::in | ios::binary));  //input
    ofstream b_out;
	if (many_flag)
	    b_out = ofstream(nfn.c_str(), (ios::out | ios::app)); //ouput -- write to
	else
        b_out = ofstream(nfn.c_str(), (ios::out | ios::binary)); //ouput -- write to

	Counter cc(in); //allow Counter do its thing
	HTree htree(cc); //create a tree using initialized Counter eob

	b_out << (magicmarker);
//	replace(fn.begin(), fn.end(), '\\', static_cast<char>(fs::path::preferred_separator));
	string a_f_name = fs::path(fn).filename().string();
	if (many_flag){
	    for (char & i : a_f_name){
            b_out << i;
	    }
	    b_out << '\0';
	}
	htree.writeEncodingTable(b_out);  //write the encoding table to output header
	in.clear(); in.seekg(0, ios::beg); //clear input stream, reset to beginning of file
	
	BitOutputStream bstream(b_out);  //create a bitoutputsream obj
	char ch;
	while (in.get(ch))
		bstream.writeBits(htree.getCode(ch & 0xff)); //write bits to output -- use a mask to prevent the high bits from being interpreted as a sign bit
	bstream.writeBits(htree.getCode(HTree::END_)); //sentinel
	in.close();
	if (!many_flag){
        uintmax_t c_size = fs::file_size(nfn);
        uintmax_t t_size = fs::file_size(fn);
        double rate = (static_cast<double>(t_size - c_size) / static_cast<double>(t_size)) * 100;
        cout<<"Compression complete.\n";
        cout<<"Original size of file: "<<t_size<<" bytes."<<endl;
        cout<<"Size of compressed file: "<<c_size<<" bytes."<<endl;
        cout<<"Compression Rate: "<<rate<<"%" << endl;
	}
	return true;
}

void Compression::uncompress(string& fn, string& fn2) {
    replace(fn.begin(), fn.end(), '\\', static_cast<char>(fs::path::preferred_separator));
    if (fs::path(fn).extension().string() != ".kipp"){
        error("Cannot uncompress :( -- Not a kipp file!");
    }
	ifstream b_in(fn.c_str(), (ios::in | ios::binary));
	ofstream out(fn2.c_str(), (ios::out | ios::binary));
	Counter cc;
	HTree htree;
	unsigned long long marker_;
	b_in >> marker_;
	if (marker_ != magicmarker){
	    error("Cannot uncompress :( -- Not a kipp file!");
	}
	htree.readEncodingTable(b_in);
	BitInputStream bistream(b_in);
	int bit = 0;
	int ch;
	vector<int> bits;
	for (;;) {
		bit = bistream.readBit();
		bits.push_back(bit);
		ch = htree.getChar(bits);
		if (ch == HTree::UND_) {
			continue;
		}else if (ch == HTree::ERR_) {
			error("error occurred while decoding file " + fn);
		}else if (ch == HTree::END_){
		    break;
		}else{
            out.put(static_cast<char>(ch));
            bits.resize(0);
		}
	}
	b_in.close();
    out.close();
//    return true;
	cout << "\nDone!\n";
	cout <<fn << " Uncompressed successfully\n";
	cout <<"Decompressed file size: "<<fs::file_size(fn2)<<" bytes."<<endl;
}

void Compression::compress_many(vector<string> files){
    if (files.empty())
        error("No files specified to be compressed.");
    string f = files[0];
    replace(f.begin(), f.end(), '\\', static_cast<char>(fs::path::preferred_separator));
    fs::path fp = f;
    fs::path comp_files_name;
    if (!fp.parent_path().empty())
        comp_files_name = fp.parent_path() / (fp.parent_path().filename().string() + ".kipp"); //par/dir/dir.kipp
    else
        comp_files_name = fs::current_path() / (fs::current_path().filename().string() + ".kipp"); //cwd/dir/dir.kipp
    uintmax_t t_size = 0;
    for (string& file : files){
        replace(file.begin(), file.end(), '\\', static_cast<char>(fs::path::preferred_separator));
        compress(file, comp_files_name, true);
        t_size += fs::file_size(file);
    }
    uintmax_t c_size = fs::file_size(comp_files_name);
    double rate = (static_cast<double>(t_size - c_size) / static_cast<double>(t_size)) * 100;
    cout<<"Compression complete.\n";
    cout<<"Total size of files: "<<t_size<<" bytes."<<endl;
    cout<<"Size of compressed file: "<<c_size<<" bytes."<<endl;
    cout<<"Compression Rate: "<<rate<<"%" << endl;
}

void Compression::uncompress_many(string& fn, string& folder_name){
    replace(fn.begin(), fn.end(), '\\', static_cast<char>(fs::path::preferred_separator));
    if (fs::path(fn).extension().string() != ".kipp"){
        error("Cannot uncompress :( -- Not a kipp file!");
    }
    ifstream b_in(fn.c_str(), (ios::in | ios::binary));

    unsigned long long marker_;
    b_in >> marker_;
    if (marker_ != magicmarker){
        error("Cannot uncompress :( -- Not a kipp file!");
    }
    fs::path pfn = fn;
    fs::path kipp_dir;
    if (!pfn.parent_path().empty())
        kipp_dir = pfn.parent_path() / folder_name; //par/fn/fn1...
    else
        kipp_dir = fs::current_path() / folder_name; //par/fn/fn1...
    create_directory(kipp_dir);
    while ( marker_ == magicmarker) {
        Counter cc;
        HTree htree;
        string file_name;
        char c;
        while ((c = b_in.get()) != '\0') {
            file_name += (c);
        }
        file_name.insert(0, (kipp_dir.string() + fs::path::preferred_separator));
        ofstream out(file_name.c_str(), (ios::out | ios::binary));
        htree.readEncodingTable(b_in);
        BitInputStream bistream(b_in);
        int bit = 0;
        int ch;
        vector<int> bits;
        for (;;) {
            bit = bistream.readBit();
            bits.push_back(bit);
            ch = htree.getChar(bits);
            if (ch == HTree::UND_) {
                continue;
            } else if (ch == HTree::ERR_) {
                error("error occurred while decoding file " + fn);
            } else if (ch == HTree::END_) {
                break;
            } else {
                out.put(static_cast<char>(ch));
                bits.resize(0);
            }
        }
        if (!b_in.eof()){
            b_in >> marker_;
            if (b_in.eof())
                marker_ = 0;
        }
    }
    cout << "\nDone!\n";
    cout <<fn << " Uncompressed successfully\n";
}

