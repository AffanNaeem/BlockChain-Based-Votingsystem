#include "admin.hpp"

#include "SearchingTrees.cpp"

#include <bits/stdc++.h>
SearchTree cnictree;
SearchTree passtree;

std::vector<candidate> Admin::candidates = IRecord::select<candidate>();

const std::string Admin::Tablename = "admin";
std::vector<Admin> Admin::select(const std::vector<Condition> &conditions) {
    std::vector<Admin> ret;
    SQLite::run(
        "SELECT * FROM " + Admin::Tablename + " " +
            Condition::unpack(conditions) + ";",
        [](void *retPtr, int columnCount, char **columnValues, char **) {
            ((std::vector<Admin> *) retPtr)
                ->emplace_back(std::vector<std::string>(
                    columnValues, columnValues + columnCount));
            return 0;
        },
        &ret);
    return ret;
}

void Admin::CastVote() {
    ll cnic;
    int pass;
    std::string key;
    std::cout << "\nEnter Your Cnic:";
    std::cin >> cnic;
    std::cout << "\nEnter Password:";
    std::cin >> pass;
    std::vector<Person> p = IRecord::select<Person>(
        {{Condition({"Cnic", cnic}), Condition({"Password", pass})}});
    if (p.empty()) {
        throw std::invalid_argument("Invalid Cnic or Password");
    }
    std::cout << "\nLogin Succesful";
    if (p.at(0).voted())
        throw std::invalid_argument("\nThis Person has already Voted");
    std::cout << "\nSelect Your Candidate(This Decision cann't be changed) \n";
    std::cout << "keys:";
    for (auto i : candidates) {
        std::cout << i.getcandidateVotekey() << "\n\n";
    }
    std::cout << "Enter Correct key";
    std::cin >> key;
    std::vector<candidate> c =
        IRecord::select<candidate>({Condition("VoteKey", key)});
    if (c.empty()) {
        throw std::invalid_argument(
            "Invalid Key: Sorry Cant register ur vote try again");
    }
    votingb.castvote(p.at(0), c.at(0));
    p.at(0).setvoted(1);
    c.at(0).addvote();
}
Admin Admin::Login(const std::string &username, const std::string &password) {
    std::vector<Admin> all = select(
        {Condition("Username", username), Condition("Password", password)});
    if (all.empty())
        throw std::invalid_argument("Wrong Username Or Password");
    return all.at(0);
}

int Admin::citycode(int city) const {
    const int CnicCityCodes[5] = {
        int(CityCodes::Karachi), int(CityCodes::Hydearabad),
        int(CityCodes::Sukkur), int(CityCodes::Islamabad),
        int(CityCodes::Lahore)};
    return CnicCityCodes[city];
}
ll Admin::generateCNIC(int city) noexcept {
    long long num = 0;
    do {
        num = (rand() % (100000000)) + 10000000;
        if (num > 99999999) {
            num -= 9999999;
        }
    } while (cnictree.search(num));
    cnictree.insert(num);
    return std::stoll(std::to_string(citycode(city)) + std::to_string(num));
}

int Admin::generatePassword() noexcept {
    long long num = 0;
    do {
        num = rand() % 999999999 + 99999999;
    } while (passtree.search(num));
    passtree.insert(num);
    return num;
}

void Admin::RegisterPerson() {
    std::string name;
    std::string phoneNumber;
    int age;
    std::string fname;
    int city;
    std::cout << "\n1.Karachi\n2.Hyderabad\n3.Sukkur\n4.Islamabad\n5.Lahore";
    std::cout << "\nSelect City:";
    std::cin >> city;
    Expects(city <= 5 && city > 0, "Invalid Input");
    ll cnic = generateCNIC(city - 1);
    int password = generatePassword();
    Person p(cnic, password);
    fflush(stdin);
    std::cout << "Enter Name:";
    getline(std::cin, name);
    std::cout << "Enter Father's Name:";
    getline(std::cin, fname);
    std::cout << "Enter Age:";
    std::cin >> age;
    std::cout << "Enter MobileNumber:";
    std::cin >> phoneNumber;
    p.setName(name);
    p.setFname(fname);
    p.setAge(age);
    p.setMobileNum(phoneNumber);
    p.setvoted(0);
    // For inserting into database
    p.insert();
    // For inserting into Pakistan tree
    pktree.insert(p, city - 1);
    // std::cout << "\nPerson's Data:";
    // std::cout << p;
}

void Admin::displayVotes() const {
    for (auto const &can : candidates) {
        std::cout << can.getcandidateVotekey()
                  << " has votes: " << can.totalvotes() << '\n';
    }
}

void Admin::checksecurity() {
    votingb.verifychain();
}

void Admin::hackblock() {
    std::string cnictohack;
    std::cout << "Enter voter cnic of block to hack";
    std::cin >> cnictohack;
    std::vector<Block> blocktohack =
        IRecord::select<Block>({Condition("voter_cnic", cnictohack)});
    if (blocktohack.empty()) {
        std::cout << "\n No suck Block Exists";
    } else {
        blocktohack.at(0).changevote("Tiger");
        std::cout << "Vote Has been hacked and changed to key Tiger";
    }
}

void Admin::EndElection() {
    displayVotes();
}