#include "blockchain.hpp"

constexpr size_t BlockChain::chainlen() const {
    return _chainlen;
}

void BlockChain::addAndInsert(const Block &b) noexcept {
    addBlock(b);
    b.insert();
    ++_chainlen;
}

void BlockChain::addBlock(const Block &b) noexcept {
    blockChain->pushback(b);
    ++_chainlen;
}

bool BlockChain::isChainValid() const {
    for (auto cur = blockChain->gethead()->next; cur != nullptr;
         cur = cur->next) {
        if (cur->data.getprevblockhash() != cur->back->data.getblockhash()) {
            return false;
        }
    }
    return true;
}

void BlockChain::recalculatehashes() {
    std::string freshhash;
    for (auto cur = blockChain->gethead(); cur != nullptr; cur = cur->next) {
        freshhash = cur->data.calculatehash();
        if (freshhash != cur->data.getblockhash()) {
        } else {
            cur->data.update();
        }
    }
}

void BlockChain::addGenesisBlock(const Block &b) noexcept {
    if (blockChain->empty()) {
        Genesisblock = b;
        blockChain->pushback(b);
    }
}