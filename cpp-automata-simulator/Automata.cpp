#include <fstream>
#include <string>
#include <algorithm>
#include "Automata.h"
#include <utility>

Automata::Automata(std::string fileName) {
    std::string content;
    std::ifstream configFile;
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
                // Key is equals to concatination of state and input symbol
                std::string key = this->states[n] + this->inputAlphabet[i];
                // Get the substring from start till '|'
                std::string value = content.substr(0, content.find("|"));
                this->functionResults.insert({ key, value});
                content.erase(0, value.length() + 1); // +1 for removing "|" character
            }
            n++;
        }
    }

    configFile.close();
}

std::string Automata::run(std::string input) {
    std::string output = "", functonResult, currentState, key;

    this->activeState = this->states[0];

    for (int i = 0; i < input.length();i++) {
        // Check if Input alphabet includes the current character
        if (this->inputAlphabet.find(input[i]) < this->inputAlphabet.length()) {
            std::string inputSymbol(1, input[i]);
            key = this->activeState + inputSymbol;
            functonResult = this->functionResults[key];
            // Get the substring from start till ','
            std::string outChar = functonResult.substr(0, functonResult.find(","));

            // Check if Output alphabet includes the current character
            if (outChar.length() == 1 && this->outputAlphabet.find(outChar) < this->outputAlphabet.length()) {
                output = output + outChar;
                currentState = functonResult.erase(0, 2);
                
                // Check if states vector includes the current state
                if (distance(this->states.begin(), find(this->states.begin(), this->states.end(), currentState)) < this->states.size()) {
                    this->activeState = currentState;
                }
                else {
                    throw std::invalid_argument("Current state does not exist: " + currentState);
                }
            }
            else {
                throw std::invalid_argument("Output Alphabet does not include the current character: " + outChar);
            }
        }
        else {
            throw std::invalid_argument("Input Alphabet does not include the current character: " + std::string(1,input[i]));
        }
    }

    return output;
}