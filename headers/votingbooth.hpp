// this be for casting votes
// vote cast fun(peron& , candidate)
#ifndef __VOTINGBOOTH_HPP__
    #define __VOTINGBOOTH_HPP__
    #include "Person.hpp"
    #include "blockchain.hpp"
    #include "candidate.hpp"

class VotingBooth {
    BlockChain *bchain;
    Block latestblockadded;

public:
    VotingBooth();
    void castvote(const Person &, const candidate &) noexcept;
    void verifychain();
    void recalculatehashes();
};

#endif // __VOTINGBOOTH_HPP__

// ll obj