#ifndef SHA_H
#define SHA_H
#include <iostream>
#include <cstring>
#include <string>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <bitset>

using namespace std;

string sha256(string str);

string hex_to_bin(char in);

string hex_to_bin(char in) {
    string out;
    switch(in){
        case '0':
            out = "0000";
            break;
        case '1':
            out = "0001";
            break;
        case '2':
            out = "0010";
            break;
        case '3':
            out = "0011";
            break;
        case '4':
            out = "0100";
            break;
        case '5':
            out = "0101";
            break;
        case '6':
            out = "0110";
            break;
        case '7':
            out = "0111";
            break;
        case '8':
            out = "1000";
            break;
        case '9':
            out = "1001";
            break;
        case 'a':
            out = "1010";
            break;
        case 'b':
            out = "1011";
            break;
        case 'c':
            out = "1100";
            break;
        case 'd':
            out = "1101";
            break;
        case 'e':
            out = "1110";
            break;
        case 'f':
            out = "1111";
            break;
    }
    return out;
}

string sha256(const string str) {
	// Implemented from a reference post at https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c/10632725 
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++){
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
    // unsigned n;
    // ss >> n;
    // bitset<256> b(n);
    // cout << b.to_string() << endl;
	return ss.str();
}

string string_hex_to_bin(string in) {
    string out = "";
    for(int i=0; i < (int)in.size(); i++) {
        out.append(hex_to_bin(in.at(i)));
    }
    return out;
}
#endif