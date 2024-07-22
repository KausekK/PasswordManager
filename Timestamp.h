#include <string>
#include <iostream>
#include <vector>

#ifndef PASSWORDMANAGER_TIMESTAMP_H
#define PASSWORDMANAGER_TIMESTAMP_H


 struct Timestamp {

    Haslo haslo;

    std::string randomCharacters() {
        srand(time(nullptr));
        std::string characters = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string randomCharacters = "";
        for (int i = 0; i < 50; i++) {
            int index = rand() % characters.length();
            randomCharacters += characters[index];
        }
        return randomCharacters;
    }

    auto timestamp() {

        std::time_t time = std::time(nullptr);
        std::tm *now = std::localtime(&time);

        std::string hour = std::to_string(now->tm_hour);
        std::string minute = std::to_string(now->tm_min);
        std::string second = std::to_string(now->tm_sec);

        std::ifstream inputFile(haslo.path);
        if (!inputFile) {
            std::cerr << "Nie mozna otworzyc pliku." << std::endl;
            return;
        }

        std::string characters1 = randomCharacters();
        std::string characters2 = randomCharacters();
        std::string characters3 = randomCharacters();


        std::vector<std::string> lines;
        std::string line;
        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }
        inputFile.close();


        if (lines.size() >= 21) {
            lines[0] = " ";
            lines[10] = " ";
            lines[20] = " ";
            if (lines[0][0] >= '0' && lines[0][0] <= '9' && lines[0][1] >= '0' && lines[0][1] <= '9') {
                lines[0] = hour + lines[0].substr(2) + " " + characters1;
            } else {
                lines[0] = hour + lines[0] + " " + characters1;
            }
            if (lines[10][0] >= '0' && lines[10][0] <= '9' && lines[10][1] >= '0' && lines[10][1] <= '9') {
                lines[10] = minute + lines[10].substr(2) + " " + characters2;
            } else {
                lines[10] = minute + lines[10] + " " + characters2;
            }
            if (lines[20][0] >= '0' && lines[20][0] <= '9' && lines[20][1] >= '0' && lines[20][1] <= '9') {
                lines[20] = second + lines[20].substr(2) + " " + characters3;
                characters3 = "";
            } else {
                lines[20] = second + lines[20] + " " + characters3;
            }

        } else {
            lines[0] = hour + " " + minute + " " + second + " " + lines[0].substr(9);
        }

        std::ofstream outputFile(haslo.path);
        if (!outputFile) {
            std::cerr << "Nie mozna otworzyc pliku do zapisu." << std::endl;
            return;
        }
        for (auto line: lines) {
            outputFile << line << std::endl;
        }
        outputFile.close();


    }
};


#endif //PASSWORD-MANAGER_TIMESTAMP_H
