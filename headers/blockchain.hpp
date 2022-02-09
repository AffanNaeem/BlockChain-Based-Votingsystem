#ifndef __BLOCKCHAIN_HPP__
#define __BLOCKCHAIN_HPP__

#include "block.hpp"
#include "candidate.hpp"
#include "list.hpp"
class BlockChain {
    size_t _chainlen;
    list<Block> *blockChain;
    Block Genesisblock;

public:
    BlockChain() : _chainlen(0), blockChain(new list<Block>[10]) {
        // Adding Genesis Block (the very first block of blockChain)
    }
    void addGenesisBlock(const Block &) noexcept;
    constexpr size_t chainlen() const;
    void addBlock(const Block &) noexcept;
    bool isChainValid() const;
    void recalculatehashes();
    // void updateVotesforcands(std::vector<candidate> candidate);
    void addAndInsert(const Block &) noexcept;
};

#endif // __BLOCKCHAIN_HPP__
