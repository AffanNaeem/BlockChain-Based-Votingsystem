#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__
#include "IRecord.hpp"
#include "Sha256.hpp"
#include "bits/stdc++.h"
enum block_validity
{
    Perfect,
    Prevblockhash_Mismatch,
};

struct VoteTransaction
{
    std::string voterCnic;
    std::string candidateCnic;
    std::string timestamp;
    std::string candidateVotekey;
    VoteTransaction() {}
    VoteTransaction(const std::string &vc, const std::string &cc,
                    const std::string &candivk, const std::string &ts) : voterCnic(vc),
                                                                         candidateCnic(cc), timestamp(ts), candidateVotekey(candivk) {}
    friend std::ostream &operator<<(std::ostream &, const VoteTransaction &);
};

class Block : public IRecord
{
    IRecord_OVERRIDE;
    unsigned blocknumber;
    std::string prevblockhash;
    std::string blockhash;
    int nonce;
    VoteTransaction v;

    void sethash() noexcept;

public:
    static const std::string TableName;
    Block() {}
    Block(unsigned blocknumber, const std::string &prevblockhash,
          const VoteTransaction &v, int nonce = 0) : blocknumber(blocknumber),
                                                     prevblockhash(prevblockhash), v(v), nonce(nonce)
    {
        sethash();
    }
    std::string calculatehash() const noexcept;
    std::string getprevblockhash() const noexcept;
    Block(const std::vector<std::string> &v);

    unsigned getblocknumber() const noexcept;
    std::string getblockhash() const noexcept;
    // this would be used for altering data of block

    void changevote(const std::string &votekee)
    {
        v.candidateVotekey = votekee;
    }

    std::string getcandidatecnic() const
    {
        return v.candidateCnic;
    }
    std::string getvotercnic() const
    {
        return v.voterCnic;
    }
    void displayblockdata() const;
    bool operator!=(const Block &other) const
    {
        return this->blockhash != other.blockhash;
    }
    bool operator==(const Block &other) const
    {
        return !(*this != other);
    }
};

#endif // __BLOCK_HPP__
