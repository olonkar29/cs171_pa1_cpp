#include <iostream>
#include <cstring>
#include <string>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "sha.h"


using namespace std;

int main() {
	cout << "hello" << endl;
	cout << sha256("hello") << endl;
	cout << string_hex_to_bin(sha256("hello")) << endl;
	return 0;
}
