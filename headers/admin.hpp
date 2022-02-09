#ifndef __ADMIN_HPP__
#define __ADMIN_HPP__

#include "Condition.hpp"
#include "PakistanTree.hpp"
#include "Person.hpp"
#include "SQLite.hpp"
#include "candidate.hpp"
#include "votingbooth.hpp"

#include <bits/stdc++.h>

enum class CityCodes {
    Karachi = 44300,
    Sukkur = 45504,
    Hydearabad = 42100,
    Islamabad = 32100,
    Lahore = 33100,
};

class Admin {
private:
    std::string username;
    std::string password;
    VotingBooth votingb;
    static std::vector<candidate> candidates;

public:
    PakistanTree<Person> pktree;
    static const std::string Tablename;
    Admin() {}
    Admin(const std::string &username, const std::string &password) :
        username(username), password(password) {}
    Admin(const std::vector<std::string> &v) :
        username(v.at(0)), password(v.at(1)) {}
    static std::vector<Admin> select(const std::vector<Condition> &);
    static Admin Login(const std::string &, const std::string &);
    void displayVotes() const;

    void CastVote();
    void RegisterPerson();
    ll generateCNIC(int) noexcept;
    int generatePassword() noexcept;
    int citycode(int) const;
    void DisplayCitizens(int x) const {
        pktree.DisplayCitizens(x);
    }
    void EndElection();
    // trying to alter data;
    void hackblock();
    void checksecurity();
};

#endif