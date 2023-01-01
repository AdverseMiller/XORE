#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include "functions.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    
    
    string file = "", pass = "", action = "", output = "";
    bool verbose = false, help = false;
    int i, hash = 0;
    for(i=1; i<argc; i++) {
        if(strcmp(argv[i],"-f")==0) file = argv[i+1];
        if(strcmp(argv[i],"-p")==0) pass = argv[i+1];
        if(strcmp(argv[i],"-k")==0) pass = argv[i+1];
        if(strcmp(argv[i],"-a")==0) action = argv[i+1];
        if(strcmp(argv[i],"-o")==0) output = argv[i+1];
        if(strcmp(argv[i],"-v")==0) verbose = true;
        if(strcmp(argv[i],"-h")==0) help = true;
    }
    
    //help message
    if(help) {
        cout << "help:\n"<<
        "Xore (XOR-Encrypt) is a program that uses a combination of XOR bitwise\n"<<
        "and ASCII shift to get Pretty Good Encryption with files.\n\n"<<
        "FLAGS\n"<<
        "   {-h} help\n"<<
        "   {-f} file\n"<<
        "   {-p, -k} password/key\n"<<
        "   {-a} encrypt/decrypt e/d\n"<<
        "   {-o} output file\n"<<
        "   {-v} verbosity\n";
        return 0;
    }


    //request password
    if(pass == "") {
        cout << "No password specified\nEnter Password: ";
        cin >> pass;
    }

    //get password hash
    for(char& c : pass) {
          hash += (int)c;
    }   
    hash=hash*hash;

    

    cout << "Using password " << pass << " with hash value " << hash << endl;

    if(action == "encrypt" || action == "e") encrypt(hash, file, output, (int)pass.back());
    else if(action == "decrypt" || action == "d") decrypt(hash, file, output, (int)pass.back());
    else {cout << "Unknown action '" << action << "', -h for help" << endl; return 1;}
    
    return 0;
}