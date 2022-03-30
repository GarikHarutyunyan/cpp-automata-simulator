#include <fstream>
#include <string>
#include <algorithm>
#include "Automata.h"

Automata::Automata(std::string fileName) {
    std::string content;
    std::ifstream configFile;
    std::pair<std::string, char> key, value;
    configFile.open(fileName);
    int n = 0;

    // Reading file line by line
    while (getline(configFile, content)) {
        // Remove spaces
        content.erase(remove_if(content.begin(), content.end(), isspace), content.end());

        if (content.length() == 0) continue;

        // Check if input alphabet is not set yet
        if (this->inputAlphabet.length() == 0) {
            while (content.length()) {
                // Get the substring from start till ','
                std::string current = content.substr(0, content.find(","));

                if (current.length() == 1) {
                    this->inputAlphabet += current;
                    // Remove first 2 letters(first one is already added to input alphabet, second symbol is ',')
                    content.erase(0, 2);
                }
                else {
                    throw std::invalid_argument("Input Alphabet's element must contain only one symbol.");
                }
            }
        }
        // Check if output alphabet is not set yet
        else  if (this->outputAlphabet.length() == 0) {
            while (content.length()) {
                std::string current = content.substr(0, content.find(","));

                if (current.length() == 1) {
                    this->outputAlphabet += current;
                    content.erase(0, 2);
                }
                else {
                    throw std::invalid_argument("Output Alphabet's element must contain only one symbol.");
                }
            }
        }
        // Check if states are not set yet
        else  if (this->states.size() == 0) {
            while (content.length()) {
                // Get the substring from start till ','
                std::string current = content.substr(0, content.find(","));
                this->states.push_back(current);
                content.erase(0, current.length()+1);
            }
        } 
        else {
            for (int i = 0; content.length(); i++) {
                // Get the substring from start till '|'
                std::string valueString = content.substr(0, content.find("|"));

                char outChar = valueString[0];
                std::string nextState = valueString.substr(valueString.find(",")+1, valueString.length()-1);
                bool isOutCharValid = this->outputAlphabet.find(outChar) < this->outputAlphabet.length();
                bool isStateValid = distance(this->states.begin(), find(this->states.begin(), this->states.end(), nextState)) < this->states.size();
                // Check if Output alphabet includes the current character
                if (!isOutCharValid) {
                    throw std::invalid_argument("Output Alphabet does not include the current character: " + outChar);
                }
                // Check if states vector includes the current state
                if (!isStateValid) {
                    throw std::invalid_argument("Current state does not exist: " + nextState);
                }

                // Create key for map
                std::string state = this->states[n];
                char inputChar = this->inputAlphabet[i];
                key = std::make_pair(state, inputChar);

                // Create value for map
                value = std::make_pair(nextState, outChar);

                this->functionResults.insert({ key, value});
                content.erase(0, valueString.length() + 1); // +1 for removing "|" character
            }
            n++;
        }
    }

    configFile.close();
}

std::string Automata::run(std::string input) {
    char outChar;
    std::string nextState, output = "";
    std::pair<std::string, char> key, functonResult;

    this->activeState = this->states[0];

    for (int i = 0; i < input.length();i++) {
        std::string inputSymbol(1, input[i]);
        // Check if Input alphabet includes the current character
        if (this->inputAlphabet.find(input[i]) < this->inputAlphabet.length()) {
            key = std::make_pair(this->activeState, input[i]);
            functonResult = this->functionResults[key];
            // Get the substring from start till ','
            outChar = functonResult.second;
            output = output + outChar;

            nextState = functonResult.first;
            this->activeState = nextState;
        }
        else {
            throw std::invalid_argument("Input Alphabet does not include the current character: " + inputSymbol);
        }
    }

    return output;
}