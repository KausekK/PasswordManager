#include <string>

#include "Haslo.h"
#include "NazwaIKategorie.h"
#include "Szyfrowanie.h"
#include "Timestamp.h"

auto main() -> int {

    std::string password = "1234";
    std::string userPassword;
    auto logged = false;
    Haslo haslo;
    NazwaiKategorie nazwaiKategorie;
    std::string command;
    Szyfrowanie szyfrowanie;
    Timestamp timestamp;

//C:\Users\Admin\Desktop\Hasla.txt

//    std::string answer;
//    std::cout << "Chcesz uzyc jednego z plikow znajdujacych sie w folderze czy absolutnej sciezki do pliku? ";
//    std::getline(std::cin, answer);
//
//    if (answer == "sciezka") {
//        std::cout << "Podaj absolutna sciezke do pliku: "<<std::endl;
//        std::getline(std::cin,haslo.path);
//    }
//
//    std::ofstream officialFile(haslo.path.c_str(), std::ios::app);

//    if (officialFile.is_open()) {
//        std::cout << "Podaj haslo aby rozszyfrowac hasla" << std::endl;

        while (!logged) {

            std::cin >> userPassword;
            if (userPassword == password) {
                logged = true;
                szyfrowanie.rozszyfrowaniePliku(password);
                std::cout << R"(Witaj w menadzerze hasel. Do wyboru masz takie komendy: "dodaj haslo", "wyszukaj haslo", "posortuj hasla",
"edytuj haslo", "usun haslo" ,"dodaj kategorie", "usun kategorie" i "wyjscie". Z ktorej chcesz teraz skorzystac?)"
                          << std::endl;
                std::cin.ignore();
                do {
                    std::cout << "Jaka komende chcesz uzyc? " << std::endl;
                    std::getline(std::cin, command);
                    if (command == "dodaj haslo") {
                        haslo.dodajHaslo();
                    } else if (command == "usun kategorie") {
                        nazwaiKategorie.usunKategorie();
                    } else if (command == "edytuj kategorie") {
                        nazwaiKategorie.edytujKategorie();
                    } else if (command == "usun haslo") {
                        haslo.usunHaslo(haslo.path.c_str());
                    } else if (command == "wyszukaj haslo") {
                        haslo.wyszukajHaslo();
                    } else if (command == "edytuj haslo") {
                        haslo.edytujHaslo();
                    } else if (command == "posortuj hasla") {
                        haslo.sortowaniePoNazwieHasla();
                    }

                } while (command != "wyjscie");

            } else {
                std::cerr << "Zle haslo, sprobuj ponownie" << std::endl;
                timestamp.timestamp(haslo.path.c_str());
            }
        }

        szyfrowanie.szyfrowaniePliku(password);

//    else{
//        std::cerr << "Nie udalo sie otworzyc pliku." << std::endl;
//    }

//    officialFile.close();

    return 0;

}
