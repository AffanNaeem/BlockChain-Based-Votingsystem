#ifndef __CANDIDATE_HPP__
#define __CANDIDATE_HPP__

#include "IRecord.hpp"
using ll = long long;

class candidate : public IRecord {
    IRecord_OVERRIDE;
    const ll cnic;
    std::string votekey;
    int _totalvotes;

public:
    static const std::string TableName;
    candidate(ll cnic) :
        cnic(cnic), _totalvotes(0), votekey((std::to_string(cnic)).substr(5)) {
        // insert();
    }
    candidate(const std::vector<std::string> &v) :
        cnic(std::stoll(v.at(0))), votekey(v.at(2)),
        _totalvotes(std::stoi(v.at(1))) {}
    ll getcnic() const noexcept;
    int totalvotes() const;
    void addvote() {
        _totalvotes++;
        candidate::update();
    }
    std::string getcandidateVotekey() const noexcept;
    // friend std::ostream &operator<<(std::ostream &out, const candidate &c) {
    //     out << "\nCandidate's VoteKey:" << c.getcandidateVotekey();
    //     return out;
    // }
};

#endif // __CANDIDATE_HPP__
