#ifndef BLOCK_H
#define BLOCK_H

#include <cstring>
#include <string>
#include <iostream>
#include <cstdlib>
#include "sha.h"

class Block {
    private:
        Block* prev;
        std::string transaction;
        std::string hash;
        std::string nonce;
    public:
        Block();

}

#endif