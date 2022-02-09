#include "candidate.hpp"

const std::string candidate::TableName = "candidate";

const std::string &candidate::insertColumns() const noexcept {
    static const std::string cols = "Cnic , TotalVotes , VoteKey ";
    return cols;
}

std::string candidate::insertValues() const noexcept {
    return build(cnic, _totalvotes, votekey);
}

std::string candidate::updateValues() const noexcept {
    static const std::vector<std::string> cols = {"TotalVotes"};
    return build(cols, _totalvotes);
}

std::string candidate::getTable() const noexcept {
    return "candidate";
}

std::vector<Condition> candidate::removeConditions() const noexcept {
    return {Condition::Impossible};
}
// yet to edit
std::vector<Condition> candidate::updateConditions() const noexcept {
    return {{"Cnic", cnic}};
}

int candidate::totalvotes() const {
    return _totalvotes;
}

ll candidate::getcnic() const noexcept {
    return cnic;
}

std::string candidate::getcandidateVotekey() const noexcept {
    return votekey;
}