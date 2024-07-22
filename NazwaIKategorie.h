#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include "Haslo.h"


struct NazwaiKategorie {
     std::string name;
     std::string category;
    int lineNumber = 0;

    Haslo haslo;

    /**
    * @brief funkcja dodaje nazwę i kategorię które podaje użytkownik dla hasła i
    * zapisuje je w pliku tekstowym razem z hasłem
    * @param password String zawierający hasło, który ma byc zapisany do pliku
    *
    */
    auto dodajNazweHaslaIKategorie(const std::string& password) {
        lineNumber++;
        std::cout << "Podaj nazwe dla hasla: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Podaj kategorie" << std::endl;
        std::getline(std::cin, category);

        std::ofstream plikOut(haslo.path, std::ios::app);
        plikOut << '\n';
        if (!plikOut.is_open()) {
            std::cerr << "Blad: nie mozna otworzyc pliku do zapisu\n";
            return;
        }
        if  (lineNumber == 10 || lineNumber == 20) {
            plikOut << '\n';
        }
        plikOut << "    NAZWA: " << name << "; HASLO: " << password << "; KATEGORIA: " << category << ";" << '\n';
        plikOut.close();
    };


    int usunKategorie() {
        std::cout << "Podaj kategorie ktora chcesz usunac" << std::endl;

        std::string category;
        std::getline(std::cin, category);
        std::ifstream file(haslo.path, std::ios::in);
        std::string line;

        std::string searchCategory = "KATEGORIA: " + category + ";";

        if (file.is_open()) {
            auto categoryFound = false;
            while (std::getline(file, line)) {
                if (line.find(searchCategory) != std::string::npos) {
                    categoryFound = true;
                    break;
                }
            }
            file.close();

            if (!categoryFound) {
                std::cout << "Podana kategoria nie istnieje." << std::endl;
                return 0;
            }
        } else {
            std::cerr << "Nie mozna otworzyc pliku." << std::endl;
            return 0;
        }

        std::cout << R"(Czy na pewno chcesz usunac te kategorie? Odpowiedz "tak" lub "nie".)" << std::endl;
        std::string confirm;
        std::getline(std::cin, confirm);
        while (confirm != "nie" && confirm != "tak") {
            std::cerr << R"(Zla komenda, wpisz "tak" lub "nie".)" << std::endl;
            std::getline(std::cin, confirm);
        }

        if (confirm == "nie") {
            std::cout << "Kategoria nie zostanie usunieta." << std::endl;
        } else if (confirm == "tak") {
            std::ifstream file2(haslo.path);
            std::ofstream tempFile("PlikZHaslamiTymczasowy.txt");

            while (std::getline(file2, line)) {
                if (line.find(searchCategory) == std::string::npos) {
                    tempFile << line << std::endl;
                }
            }

            file2.close();
            tempFile.close();

            std::remove(haslo.path);
            std::rename("PlikZHaslamiTymczasowy.txt", haslo.path);

            std::cout << "Kategoria " << category << " zostala usuniete." << std::endl;

        }
    }


    /**
     * @brief Funkcja pyta uzytkownika jaka kategorie edytkowac,
     * uzytkownik podaje kategorie do edytowania i nowa jej nazwe za pomoca konsoli.
     * Plik szuka ciagu znakow "KATEGORIA: (nazwa kategorii) i przepisuje plik do nowego  pliku zmieniajac nazwe kategorii na nowa.
     * na koniec zastepuje stary plik nowym
     *
     */
    auto edytujKategorie() {
        std::cout << "Podaj kategorie ktore chcesz zmienic: " << std::endl;
        std::string oldCategory;

        std::ifstream file(haslo.path, std::ios::in);
        std::string line;
        getline(std::cin, oldCategory);
        std::string searchCategory = "KATEGORIA: " + oldCategory + ";";

        if (file.is_open()) {
            auto categoryFound = false;
            while (std::getline(file, line)) {
                if (line.find(searchCategory) != std::string::npos) {
                    categoryFound = true;
                    break;
                }
            }
            file.close();

            if (!categoryFound) {
                std::cout << "Podana kategoria nie istnieje." << std::endl;
                return 0;
            }

            std::string newCategory;
            std::cout << "Podaj nowa kategorie: " << std::endl;

            getline(std::cin, newCategory);

            std::ifstream inputFile(haslo.path);
            if (inputFile.is_open()) {
                std::ofstream outputFile("PlikZHaslamiTymczasowy.txt");

                if (outputFile.is_open()) {
                    std::string line;
                   

                    while (std::getline(inputFile, line)) {
                        if (line.find(searchCategory) != std::string::npos) {
                            std::string categoryReplaced = "KATEGORIA: " + newCategory + ";";
                            line.replace(line.find(searchCategory), searchCategory.length(), categoryReplaced);
                        }
                        outputFile << line << std::endl;
                    }
                    inputFile.close();
                    outputFile.close();

                    std::remove(haslo.path);
                    std::rename("PlikZHaslamiTymczasowy.txt", haslo.path);
                    std::cout << "Kategoria zostala zmieniona pomyslnie" << std::endl;
                }
            }
        }
    }
};

//bez tej deklaracji program nie dziala
//std::string NazwaiKategorie::name;
//std::string NazwaiKategorie::category;
