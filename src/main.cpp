#include "Compression.h"
#include <cstring>
#include <iostream>

using namespace std;
//Kipp -c f1
//Kipp -u f1 f2
//Kipp -cm f1 f2 ..fn
//Kipp -um f1

int main(int argc, char* argv[]) {
    if (argc >= 3){
        Compression c;
        string ifile;
        if (strcmp(argv[1], "-c") == 0){
             ifile = argv[2];
            c.compress(ifile, string(argv[2])+".kipp", false);
        }else if (strcmp(argv[1], "-uc") == 0){
            if (argc != 4)
                c.error("Not in the expected format: Kipp -uc file.kipp file.your_extension");
            ifile = argv[2];
            string ofile = argv[3];
            c.uncompress(ifile, ofile);
        }else if (strcmp(argv[1], "-cm")==0){
            vector<string> files;
            for (int i=2; i < argc; i++){
                cout<<argv[i]<<endl;
                files.emplace_back(argv[i]);
            }
            c.compress_many(files);
        }else if (strcmp(argv[1], "-um")==0){
            if (argc != 4)
                c.error("Not in the expected format: Kipp -um file.kipp folder_name");
            ifile = argv[2];
            string folder_name = argv[3];
            c.uncompress_many(ifile, folder_name);
        }
    }
    else{
        cerr<<"Expected formats\n"
              "Compression (single file): Kipp -c f\n"
              "Uncompression (single file): Kipp -uc f1 f2\n"<<
              "Compression (multiple files): Kipp -cm f1 f2 ..fn\n"
              "Uncompression (multiple files): Kipp -um f.kipp folder_name"<<endl;
        cerr<<"f - file to be compressed (single file compression)\n";
        cerr<<"f1 - file to be uncompressed\t f2  - name of output file (single file uncompression)\n"
            <<"f1 f2 ..fn (files to be compressed or uncompressed -- multiple file compression/decompression) "<<endl;
        exit(-1);
    }
}



