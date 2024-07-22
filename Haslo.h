#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include "NazwaIKategorie.h"
#include "Timestamp.h"

struct Haslo {

    NazwaIKategorie nazwaiKategorie;
    std::string path = "\"PlikZHaslami.txt\"";

private:
    std::string password;

    /**
     * @brief funkcja sprawdza czy haslo zawiera duze litery
     *
     * @param str String który jest sprawdzany na wypadek wystepowania duzych liter
     * @return Zwraca True lub False w zależności czy przekazany do niej string zawiera co najmniej jedną dużą literę.
     */
    static bool containsUppercase(const std::string &str)//sprawdza czy haslo zawiera duze litery
    {
        return std::any_of(str.begin(), str.end(), [](char c) { return std::isupper(c); });
    }

    /**
     *@brief funkcja sprawdza czy haslo zawiera znaki specjalne
     *
     * @param str String który jest sprawdzany na wypadek wystepowania znakow specjalnych
     * @return Zwraca True lub False w zależności czy przekazany do niej string zawiera co najmniej jeden znak specjalny.
     */
    static bool containsSpecialCharacters(const std::string &str)//sprawdza czy haslo zawiera znaki specjalne
    {
        return std::any_of(str.begin(), str.end(), [](char c) { return std::ispunct(c); });
    }


    /**
     * @brief Generuje losowe hasło w zależności od tego co wpisze użytkownik w konsoli.
     * Użytkownik wybiera długość hasła wygenerowanego oraz to czy zawiera duże litery i znaki specjalne
     *
     *  Wypisuje wygenerowane haslo w konsoli oraz zapisuje je do pliku tekstowego
     */
    auto generatePassword() { //generuje losowe haslo
        password = "";
        srand(time(nullptr));  // Inicjalizacja generatora liczb pseudolosowych
        auto length = 0;
        std::cout << "Ile znakow ma miec haslo?" << std::endl;
        while (!(std::cin >> length)) {
            std::cout << "To nie jest liczba. Podaj liczbe: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n'); // ignorowanie niepoprawnych znaków
        }

        std::string answer;
        do {
            std::cout << R"(Czy haslo ma zawierac zarowno wielkie jak i male litery? Wpisz "tak" lub "nie": )";
            std::cin >> answer;
        } while (answer != "tak" && answer != "nie");

        std::string characters = "abcdefghijklmnopqrstuvwxyz1234567890"; // Lista dostępnych znaków
        if (answer == "tak") {
            characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }

        std::string answer2;
        do {
            std::cout << R"(Czy haslo ma zawierac znaki specjalne? Wpisz "tak" lub "nie": )";
            std::cin >> answer2;
        } while (answer2 != "tak" && answer2 != "nie");

        if (answer2 == "tak") {
            characters += "!@#$%^&*+_-?<>"; // Dodaj znaki specjalne
        }

        // Wygeneruj hasło
        for (int i = 0; i < length; i++) {
            int index = rand() % characters.length();
            password += characters[index];

        }
    }


/**
 * @brief W zaelznosci od opcji ktora wybierze uzytkownik albo wygeneruje haslo i zapisze do pliku przy uzyciu funkcji "generatePassword".
 * Lub da mozliwosc stworzenia swojego hasla uzytkownikow.
 * Oceni siłe hasla, jesli bedzie niska da szanse poprawienia hasla i zapisze je do pliku tekstowego
 *
 */
public:
    void dodajHaslo() {

        std::string whichPassword;
        std::string changePassword;
        auto wrongAnswer = true;
        std::cout << "Chcesz wygenerowane haslo czy swoje?" << std::endl;
        std::cin >> whichPassword;

        do {
            if (whichPassword == "wygenerowane") {
                generatePassword();
                wrongAnswer = false;
            } else if (whichPassword == "swoje") {
                std::cout << "Podaj Haslo" << std::endl;
                std::cin >> password;
                wrongAnswer = false;
                if (password.length() > 10 && containsUppercase(password) && containsSpecialCharacters(password)) {
                    std::cout << "Silne haslo!" << std::endl;
                } else if (password.length() > 8 && containsUppercase(password) ||
                           containsSpecialCharacters(password)) {
                    std::cout << "Srednie haslo!" << std::endl;
                } else {
                    std::cout << "Slabe Haslo" << std::endl;

                    wrongAnswer = true;
                    do {
                        std::cout << "Czy chcesz je zmienic?" << std::endl;
                        std::cin >> changePassword;
                        if (changePassword == "tak") {
                            std::cout << "Podaj nowe haslo" << std::endl;
                            std::cin >> password;
                            wrongAnswer = false;
                        } else if (changePassword != "nie") {
                            std::cerr << "Odpowiedz tak lub nie" << std::endl;
                        } else {
                            wrongAnswer = false;
                        }
                    } while (wrongAnswer);
                }

            } else {
                std::cout << R"(Odpowiedz "wygenerowane" lub "swoje")" << std::endl;
                std::cin >> whichPassword;
            }
        } while (wrongAnswer);
        nazwaiKategorie.dodajNazweHaslaIKategorie(password);
    }

    void usunHaslo(const char *string) {
        std::cout << "Podaj haslo ktore chcesz usunac" << std::endl;
        password = "";
        std::getline(std::cin, password);
        std::ifstream file(path, std::ios::in);
        std::string line;
        int counter = 0;

        std::string searchPassword = "HASLO: " + password + "; ";

        if (file.is_open()) {
            while (getline(file, line)) {
                if (line.find(searchPassword) != std::string::npos) {
                    counter++;
                }
            }
            file.close();
        }
        std::cout << "Counter: " << counter << std::endl;
        if (counter == 0) {
            std::cout << "Nie ma takiego hasla." << std::endl;
            return;
        }

        std::cout << "Haslo '" << password << "' wystepuje " << counter << " razy." << std::endl;

        std::cout << R"(Czy na pewno chcesz usunac te haslo? Odpowiedz "tak" lub "nie".)" << std::endl;
        std::string confirm;
        std::getline(std::cin, confirm);

        if (confirm == "nie") {
            std::cout << "Haslo nie zostanie usuniete." << std::endl;
        } else if (confirm == "tak") {
            std::ifstream file2(path);
            std::ofstream tempFile("PlikZHaslamiTymczasowy.txt");

            while (std::getline(file2, line)) {
                if (line.find(searchPassword) == std::string::npos) {
                    tempFile << line << std::endl;
                }
            }
            file2.close();
            tempFile.close();

            std::remove(path.c_str());
            std::rename("PlikZHaslamiTymczasowy.txt", path.c_str());

            std::cout << "Haslo: " << password << " zostalo usuniete." << std::endl;
        }
    }

    auto wyszukajHaslo() -> void {
        std::string word;
        std::string line;
        auto counter = 0;
        std::cout << "Podaj szukane haslo lub katalog lub nazwe: " << std::endl;
        std::cin >> word;

        std::ifstream inputFile(path);
        std::cin.ignore();
        while (std::getline(inputFile, line)) {
            if (line.find(word) != std::string::npos) {
                std::cout << line << std::endl;
                counter++;
            }
        }
        if (counter == 0) {
            std::cout << "Nie znaleziono żadnej wartości dla " << word << std::endl;
        }

        inputFile.close();
    }


    int edytujHaslo() {
        std::cout << "Podaj haslo ktore chcesz zmienic: " << std::endl;
        std::string oldPassword;

        std::ifstream file(path, std::ios::in);
        std::string line;
        getline(std::cin, oldPassword);
        std::string searchPassword = "HASLO: " + oldPassword + ";";

        if (file.is_open()) {
            auto passwordFound = false;
            while (std::getline(file, line)) {
                if (line.find(searchPassword) != std::string::npos) {
                    passwordFound = true;
                    break;
                }
            }
            file.close();

            if (!passwordFound) {
                std::cout << "Podane haslo nie istnieje." << std::endl;
                return 0;
            }

            std::string newPassword;
            std::cout << "Podaj nowe haslo: " << std::endl;

            getline(std::cin, newPassword);

            std::ifstream inputFile(path);
            if (inputFile.is_open()) {
                std::ofstream outputFile("PlikZHaslamiTymczasowy.txt");

                if (outputFile.is_open()) {
                    std::string line;

                    while (std::getline(inputFile, line)) {
                        if (line.find(searchPassword) != std::string::npos) {
                            std::string passwordReplaced = "HASLO: " + newPassword + ";";
                            line.replace(line.find(searchPassword), searchPassword.length(), passwordReplaced);
                        }
                        outputFile << line << std::endl;
                    }
                    inputFile.close();
                    outputFile.close();

                    std::remove(path.c_str());
                    std::rename("PlikZHaslamiTymczasowy.txt", path.c_str());
                    std::cout << "Haslo zostalo zmienione pomyslnie" << std::endl;
                }
            }
        }
    }

    auto sortowaniePoNazwieHasla() -> void {
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Nie mozna otworzyc pliku do zapisu." << std::endl;
            return;
        }
        std::vector<std::string> lines;
        std::string line;
        auto counter = 0;
        if (inputFile.is_open()) {
            while (std::getline(inputFile, line)) {
                counter++;
                if (counter != 1 && counter != 11 && counter != 21) {
                    lines.push_back(line);
                }
                if (line.empty()) {
                    break;
                }
            }
        }
        std::sort(lines.begin(), lines.end());

        inputFile.close();

        std::ofstream outputFile(path);

        if (!outputFile) {
            std::cerr << "Nie mozna otworzyc pliku do zapisu." << std::endl;
            return;
        }

        counter = 0;
        for (const auto &item: lines) {
            counter++;
            if (counter == 1 || counter == 11 || counter == 21) {
                outputFile << '\n';
            } else {
                outputFile << item << std::endl;
            }
        }

        outputFile.close();

        std::cout << "Plik zostal posortowany wzgledem nazw" << std::endl;
        Timestamp timestamp;
        timestamp.timestamp(path);
    }
};