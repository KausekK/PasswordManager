#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <ctime>
#include <cstdlib>
#include "Timestamp.h"

#ifndef PASSWORDMANAGER_SZYFROWANIE_H
#define PASSWORDMANAGER_SZYFROWANIE_H


struct Szyfrowanie {

    Haslo haslo;

    int range(int &encrypted) {
        while (encrypted < 32 || encrypted > 122) {
            if (encrypted <= 32) {
                encrypted = 122 - (32 - encrypted - 1);
            } else if (encrypted >= 122) {
                encrypted = 32 + (encrypted - 122 - 1);
            }
        }

        return encrypted;
    }

    int szyfrowaniePliku(std::string password) {
        std::ifstream inputFile(haslo.path);
        std::ofstream outputFile("PlikZHaslamiTymczasowy.txt");

        if (!inputFile.is_open()) {
            std::cerr << "Blad otwarcia pliku wejsciowego." << std::endl;
            return 1; // lub inny sposób obsługi błędu
        }

        if (!outputFile.is_open()) {
            std::cerr << "Blad otwarcia pliku wyjsciowego." << std::endl;
            inputFile.close();
            return 1; // lub inny sposób obsługi błędu
        }

        char ch;
        size_t i = 0;
        auto encrypted = 33;
        auto lineNumber = 1;
        while (inputFile.get(ch)) {
            // Szyfrowanie znaku
            if (ch != '\n') {
                if (lineNumber == 1 || lineNumber == 11 || lineNumber == 21) {
                    outputFile << ch;
                } else {
                    if (password[i] % 4 == 0) {
                        encrypted = static_cast<int>(static_cast<unsigned char>(ch)) + password[i] + 14;
                        range(encrypted);
                        outputFile << static_cast<char>(encrypted);
                    } else if (password[i] % 2 == 0) {
                        encrypted = static_cast<int>(static_cast<unsigned char>(ch)) + password[i] + 7;
                        range(encrypted);
                        outputFile << static_cast<char>(encrypted);
                    } else {
                        encrypted = static_cast<int>(static_cast<unsigned char>(ch)) - password[i] - 11;
                        range(encrypted);
                        outputFile << static_cast<char>(encrypted);
                    }

                    // Przechodzenie do następnego znaku w haśle
                    i = (i + 1) % password.length();
                }
            } else {
                outputFile << ch;
                lineNumber++;
            }
        }

        inputFile.close();
        outputFile.close();

        std::remove(haslo.path);
        std::rename("PlikZHaslamiTymczasowy.txt", haslo.path);
    }

    int rozszyfrowaniePliku(std::string password) {
        std::ifstream inputFile(haslo.path);
        std::ofstream outputFile("PlikZHaslamiTymczasowy.txt");

        if (!inputFile.is_open()) {
            std::cerr << "Blad otwarcia pliku wejsciowego." << std::endl;
            return 1;
        }

        if (!outputFile.is_open()) {
            std::cerr << "Blad otwarcia pliku wyjsciowego." << std::endl;
            inputFile.close();
            return 1;
        }
        char ch;
        auto i = 0;
        auto lineNumber = 1;
        auto encrypted = 33;
        while (inputFile.get(ch)) {
            // Odszyfrowywanie znaku
            if (ch != '\n') {
                if (lineNumber == 1 || lineNumber == 11 || lineNumber == 21) {
                    outputFile << ch;
                } else {
                    if (password[i] % 4 == 0) {
                        encrypted = static_cast<int>(static_cast<unsigned char>(ch)) - password[i] - 14;
                        range(encrypted);
                        outputFile << static_cast<char>(encrypted);
                    } else if (password[i] % 2 == 0) {
                        encrypted = static_cast<int>(static_cast<unsigned char>(ch)) - password[i] - 7;
                        range(encrypted);
                        outputFile << static_cast<char>(encrypted);
                    } else {
                        encrypted = static_cast<int>(static_cast<unsigned char>(ch)) + password[i] + 11;
                        range(encrypted);;
                        outputFile << static_cast<char>(encrypted);
                    }

                    // Przechodzenie do następnego znaku w haśle
                    i = (i + 1) % password.length();
                }
            } else {
                outputFile << '\n';
                lineNumber++;
            }
        }

        inputFile.close();
        outputFile.close();

        std::remove(haslo.path);
        std::rename("PlikZHaslamiTymczasowy.txt", haslo.path);
        return 0;
    }
};


#endif //PASSWORDMANAGER_SZYFROWANIE_H
