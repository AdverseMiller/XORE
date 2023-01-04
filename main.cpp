#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <filesystem>
#include <sys/stat.h>
#include "functions.hpp"

namespace fs = std::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
    
    
    string file = "", pass = "", action = "", output = "";
    bool verbose = false, help = false, recurse = false;
    int i, hash = 0;
    for(i=1; i<argc; i++) {
        if(strcmp(argv[i],"-f")==0) file = argv[i+1];
        if(strcmp(argv[i],"-r")==0) recurse = true;
        if(strcmp(argv[i],"-p")==0) pass = argv[i+1];
        if(strcmp(argv[i],"-k")==0) pass = argv[i+1];
        if(strcmp(argv[i],"-a")==0) action = argv[i+1];
        if(strcmp(argv[i],"-o")==0) output = argv[i+1];
        if(strcmp(argv[i],"-v")==0) verbose = true;
        if(strcmp(argv[i],"-h")==0) help = true;
    }
    
    if(argc == 1) help = true;

    //help message
    if(help) {
        cout << 
        "help:\n"<<
        "Xore (XOR-Encrypt) is a program that uses a combination of XOR bitwise\n"<<
        "and ASCII shift to get Pretty Good Encryption with files.\n\n"<<
        "FLAGS\n"<<
        "   {-h} help\n"<<
        "   {-f} <file/directory>\n"<<
        "   {-r} recurse\n"<<
        "   {-p, -k} <password/key>\n"<<
        "   {-a} <encrypt/decrypt> <e/d>\n"<<
        "   {-o} <output>\n"<<
        "   {-v} verbosity\n\n"<<
        "ADDITIONAL INFO\n"<<
        "The output flag (-o) will create a file if it does not already exist, however,\n"<<
        "if a directory is the input, the given output must already exist.\n";
        ;
        return 0;
    }
    
    if(!fs::exists(file)) {
        cout << file << ": No such file or directory\n";
        return 1;
    }

    if(recurse) {
        if(!fs::is_directory(file)) {
            cout << file << ": Not a directory\n";
            return 1;
        }
        if(output.back() != '/') output=output+"/";
        if(output == "") {
            cout << "An output directory is required for recurse\n";
            return 1;
        }
        if(!fs::exists(output)) {
            cout << file << ": No such directory\n";
        }
        
    }

    if(pass == "") {
        cout << "Password is required\n"; 
        return 1;
    }

    //get password hash
    for(char& c : pass) {
          hash += (int)c;
    }   
    hash=hash*hash;


    cout << "Using password " << pass << " with hash value " << hash << endl;

    
    if(action == "encrypt" || action == "e") {
        if(recurse) {
            for (const auto & entry : fs::directory_iterator(file)) {
                if(fs::is_regular_file(entry.path())) {
                    encrypt(hash, entry.path(), output+entry.path().filename().string(), (int)pass.back());
                }
            }
        }
        else encrypt(hash, file, output, (int)pass.back());
    }
    else if(action == "decrypt" || action == "d") {
        if(recurse) {
            for (const auto & entry : fs::directory_iterator(file)) {
                if(fs::is_regular_file(entry.path())) {
                    decrypt(hash, entry.path(), output+entry.path().filename().string(), (int)pass.back());
                }
            }
        }
        else decrypt(hash, file, output, (int)pass.back());
    }
    else {cout << "Unknown action '" << action << "', -h for help" << endl; return 1;}
    
    return 0;
}