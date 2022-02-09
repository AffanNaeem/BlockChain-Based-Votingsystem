#include "votingbooth.hpp"

#include <ctime>
VotingBooth::VotingBooth() : bchain(new BlockChain) {
    std::vector<Block> blocks = IRecord::select<Block>();
    for (const auto &i : blocks) {
        bchain->addBlock(i);
        latestblockadded = i;
    }
}
void VotingBooth::verifychain() {
    if (!bchain->isChainValid())
        bchain->recalculatehashes();
}

void VotingBooth::castvote(const Person &p, const candidate &c) noexcept {
    time_t currenttime = std::time(nullptr);

    VoteTransaction newVote(std::to_string(p.getCNIC()),
                            std::to_string(c.getcnic()),
                            c.getcandidateVotekey(), ctime(&currenttime));
    Block newBlock(latestblockadded.getblocknumber() + 1,
                   latestblockadded.getblockhash(), newVote);
    verifychain();
    bchain->addAndInsert(newBlock);
    latestblockadded = newBlock;

    newBlock.displayblockdata();
}