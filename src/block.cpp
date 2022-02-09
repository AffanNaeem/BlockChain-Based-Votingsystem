#include "block.hpp"

const std::string Block::TableName = "Block";
std::string Block::getTable() const noexcept {
    return TableName;
}

const std::string &Block::insertColumns() const noexcept {
    static const std::string cols =
        "block_number ,  prev_blockhash , blockhash , voter_cnic , "
        "cancidate_cnic , candidate_votekey,timestamp , nonce";
    return cols;
}

std::string Block::insertValues() const noexcept {
    return build(blocknumber, prevblockhash, blockhash, v.voterCnic,
                 v.candidateCnic, v.candidateVotekey, v.timestamp, nonce);
}

std::string Block::updateValues() const noexcept {
    static const std::vector<std::string> cols = {
        "block_number ,  prev_blockhash , blockhash , voter_cnic , "
        "cancidate_cnic , candidate_votekey,timestamp , nonce"};
    return build(cols, blocknumber, prevblockhash, blockhash, v.voterCnic,
                 v.candidateCnic, v.candidateVotekey, v.timestamp, nonce);
}
std::vector<Condition> Block::updateConditions() const noexcept {
    return {{"block_number", blocknumber}};
}
std::vector<Condition> Block::removeConditions() const noexcept {
    return {Condition::Impossible};
}

// Hash of each block is calculated here
std::string Block::calculatehash() const noexcept {
    SHA256 hashhelpr;
    std::string hash = std::to_string(blocknumber) + std::to_string(nonce) +
                       prevblockhash + v.voterCnic + v.candidateCnic +
                       v.candidateVotekey + v.timestamp;
    // Final Sha256 64 Bytes hash
    const std::string finalhash = hashhelpr(hash);
    return hash;
}

Block::Block(const std::vector<std::string> &v1) :
    blocknumber(std::stoi(v1.at(0))), prevblockhash(v1.at(1)),
    nonce(std::stoi(v1.at(7))), blockhash(v1.at(2)) {
    v.voterCnic = v1.at(3);
    v.candidateCnic = v1.at(4);
    v.candidateVotekey = v1.at(5);
    v.timestamp = v1.at(6);
}

void Block::sethash() noexcept {
    this->blockhash = calculatehash();
}

std::string Block::getblockhash() const noexcept {
    return this->blockhash;
}

unsigned Block::getblocknumber() const noexcept {
    return blocknumber;
}

std::string Block::getprevblockhash() const noexcept {
    return this->prevblockhash;
}

void Block::displayblockdata() const {
    std::cout << "\nVote Transaction:" << v << "\nBlock#:" << blocknumber
              << "\nBlock hash :" << blockhash
              << "\nPrevious Block Hash:" << prevblockhash;
}

// overload for displaying transactions data
std::ostream &operator<<(std::ostream &out, const VoteTransaction &v) {
    out << "\nVoter's Cnic:" << v.voterCnic
        << "\nCanditate's Cnic:" << v.candidateCnic
        << "\nCandaite's Votekey:" << v.candidateVotekey
        << "\nTimestamp of vote:" << v.timestamp;
    return out;
}