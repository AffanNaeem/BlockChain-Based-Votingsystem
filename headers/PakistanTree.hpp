
#ifndef __PAKISTANTREE_HPP__
#define __PAKISTANTREE_HPP__

#include "IRecord.hpp"
#include "Person.hpp"

#include <bits/stdc++.h>
template <typename T>
class PakistanTree {
public:
    struct PersonNode {
        T data;
        PersonNode *left;
        PersonNode *right;
        size_t height;
        PersonNode(const T &data, PersonNode *left = nullptr,
                   PersonNode *right = nullptr) :
            height(1),
            data(data), right(right), left(left) {}
    };

    struct CityNode {
        PersonNode *root;
        size_t TotalCitizens; // size of Each city Node
        CityNode() : root(nullptr), TotalCitizens(0) {}
        PersonNode *getroot() const {
            return root;
        }
    };
    constexpr size_t PakistanPopulation() const {
        return Pakpop;
    };

    CityNode *Karachi;
    CityNode *Hyderabad;
    CityNode *Sukkur;
    CityNode *Islamabad;
    CityNode *Lahore;
    size_t Pakpop;

    // void insertinKarachi(const T &Persondata, PersonNode *cur) {}
    // void insertinHyderabad(const T &Persondata, PersonNode *cur) {}
    // void insertinSukkur(const T &Persondata, PersonNode *cur) {}
    // void insertinIslamabad(const T &Persondata, PersonNode *cur) {}
    // void insertinLahore(const T &Persondata, PersonNode *cur) {}

    // ALL Rotations

    PersonNode *LLRotation(PersonNode *&cur, PersonNode *&root) {
        auto cur2 = cur->left;
        auto cur2right = cur2->right;
        cur2->right = cur;
        cur->left = cur2right;
        cur->height = 1 + std::max(height(cur->left), height(cur->right));
        cur2->height = 1 + std::max(height(cur2->left), height(cur2->right));
        if (root == cur) {
            root = cur2;
        }
        return cur2;
    }
    PersonNode *RRRotation(PersonNode *&cur, PersonNode *&root) {
        auto cur2 = cur->right;
        auto cur2left = cur2->left;
        cur2->left = cur;
        cur->right = cur2left;
        cur->height = 1 + std::max(height(cur->left), height(cur->right));
        cur2->height = 1 + std::max(height(cur2->left), height(cur2->right));
        if (root == cur) {
            root = cur2;
        }
        return cur2;
    }
    PersonNode *LRRotation(PersonNode *&cur, PersonNode *&root) {
        auto cur2 = cur->left->right;
        cur->left->right = cur2->left;
        cur2->left = cur->left;
        cur->left = cur2->right;
        cur2->right = cur;
        cur->height = 1 + std::max(height(cur->left), height(cur->right));
        cur2->height = 1 + std::max(height(cur2->left), height(cur2->right));
        if (root == cur) {
            root = cur2;
        }
        return cur2;
    }
    PersonNode *RLRotation(PersonNode *&cur, PersonNode *&root) {
        auto cur2 = cur->right->left;
        cur->right->left = cur2->right;
        cur2->right = cur->right;
        cur->right = cur2->left;
        cur2->left = cur;
        cur->height = 1 + std::max(height(cur->left), height(cur->right));
        cur2->height = 1 + std::max(height(cur2->left), height(cur2->right));
        if (root == cur) {
            root = cur2;
        }
        return cur2;
    }

    void insertx(const T &Persondata, PersonNode *&cur, bool x) {
        PersonNode *reservedroot = nullptr;
        if (!x) {
            reservedroot = cur;
            x = true;
        }
        if (cur->data < Persondata) {
            if (cur->right != nullptr) {
                insertx(Persondata, cur->right, x);
            } else {
                cur->right = new PersonNode(Persondata);
            }
        } else {
            if (cur->left != nullptr) {
                insertx(Persondata, cur->left, x);
            } else {
                cur->left = new PersonNode(Persondata);
            }
        }
        cur->height = 1 + std::max(height(cur->left), height(cur->right));

        if (BFactor(cur) == 2) {
            if (BFactor(cur->left) == 1) {
                cur = LLRotation(cur, reservedroot);
            } else
                cur = LRRotation(cur, reservedroot);
        } else if (BFactor(cur) == -2) {
            if (BFactor(cur->right) == -1) {
                cur = RRRotation(cur, reservedroot);
            } else
                cur = RLRotation(cur, reservedroot);
        }
    }

    void DisplayCitizens(PersonNode *cur) const {
        if (cur != nullptr) {
            DisplayCitizens(cur->left);
            std::cout << cur->data << '\n';
            DisplayCitizens(cur->right);
        }
        return;
    }

    inline size_t height(PersonNode *cur) const {
        if (cur != nullptr) {
            return cur->height;
        }
        return 0;
    }
    inline int BFactor(PersonNode *cur) const {
        return height(cur->left) - height(cur->right);
    }

public:
    PakistanTree() :
        Karachi(new CityNode()), Hyderabad(new CityNode()),
        Sukkur(new CityNode()), Islamabad(new CityNode()),
        Lahore(new CityNode()) {
        std::vector<Person> persons = IRecord::select<Person>();
        for (auto i : persons) {
            insert(i, i.getcitycode()); //
        }
    }

    void insert(const T &Persondata, int cityc) {
        switch (cityc) {
            case 0:
                if (Karachi->getroot() == nullptr) {
                    Karachi->root = new PersonNode(Persondata);
                } else {
                    insertx(Persondata, Karachi->root, false);
                }
                Karachi->TotalCitizens++;
                break;
            case 1:
                if (Hyderabad->root == nullptr) {
                    Hyderabad->root = new PersonNode(Persondata);
                } else
                    insertx(Persondata, Hyderabad->root, false);
                Hyderabad->TotalCitizens++;
                break;
            case 2:
                if (Sukkur->root == nullptr) {
                    Sukkur->root = new PersonNode(Persondata);
                } else
                    insertx(Persondata, Sukkur->root, false);
                Sukkur->TotalCitizens++;
                break;
            case 3:
                if (Islamabad->root == nullptr)
                    Islamabad->root = new PersonNode(Persondata);
                else
                    insertx(Persondata, Islamabad->root, false);
                Islamabad->TotalCitizens++;
                break;

            case 4:
                if (Lahore->root == nullptr) {
                    Lahore->root = new PersonNode(Persondata);
                } else
                    insertx(Persondata, Lahore->root, false);
                Lahore->TotalCitizens++;
        } // default cases would be handled by admin

        ++Pakpop;
    }
    bool searchCitizen(ll cnic) const {
        int CityCodes[5] = {44300, 45504, 42100, 32100, 33100};
        return false;
    }
    void DisplayCitizens(int cityc) const {
        switch (cityc) {
            case 0:
                DisplayCitizens(Karachi->getroot());
                break;
            case 1:
                DisplayCitizens(Hyderabad->getroot());
                break;
            case 2:
                DisplayCitizens(Sukkur->getroot());
                break;
            case 3:
                DisplayCitizens(Islamabad->getroot());
                break;
            case 4:
                DisplayCitizens(Lahore->getroot());
                break;
        }
    }
};
#endif