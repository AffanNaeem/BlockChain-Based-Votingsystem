#include "admin.hpp"

#include <bits/stdc++.h>
#include <iostream>

int main() {
    Admin administrator;
    std::string username;
    std::string pass;
    std::cout << "\nEnter Username:";
    std::cin >> username;
    std::cout << "\nEnter Password:";
    std::cin >> pass;
    bool ended = false;
    administrator.Login(username, pass);
    int x;
    while (1) {
        std::cout << "\n1.Register Person";
        std::cout << "\n2.Register Vote";
        std::cout << "\n3.Diplay Votes for EveryCanddidate";
        std::cout << "\n4.End Elections";
        std::cout << "\n6.Display Citizens";
        std::cout << "\n7.Exit";
        std::cout << "\n8.Hack Block";
        administrator.checksecurity();
        std::cout << "\nEnter Choice";
        std::cin >> x;
        switch (x) {
            case 1:
                administrator.RegisterPerson();
                break;
            case 2:
                if (!ended)
                    administrator.CastVote();
                else
                    std::cout << "\nElections ended already";
                break;
            case 3:
                administrator.displayVotes();
                break;
            case 4:
                administrator.EndElection();
                ended = true;
                break;

            case 6:
                std::cout << "\n1.Karachi\n2.Hyderabad\n3.Sukkur\n4."
                             "Islamabad\n5.Lahore";
                std::cout << "\nEnter Choice:";
                std::cin >> x;
                administrator.DisplayCitizens(x - 1);
                break;
            case 7:
                exit(0);
                break;
            case 8:
                administrator.hackblock();
                break;
            default:
                std::cout << "\nInvalid Choice";
        }
    }
}
