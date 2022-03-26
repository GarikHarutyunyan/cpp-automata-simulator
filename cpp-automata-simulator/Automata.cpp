#include <fstream>
#include <string>
#include <algorithm>
#include "Automata.h"

Automata::Automata(string fileName) {
    string content;
    ifstream configFile;
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
                string current = content.substr(0, content.find(","));

                if (current.length() == 1) {
                    this->inputAlphabet += current;
                    // Remove first 2 letters(first one is already added to input alphabet, second symbol is ',')
                    content.erase(0, 2);
                }
                else {
                    throw invalid_argument("Input Alphabet's element must contain only one symbol.");
                }
            }
        }
        // Check if output alphabet is not set yet
        else  if (this->outputAlphabet.length() == 0) {
            while (content.length()) {
                string current = content.substr(0, content.find(","));

                if (current.length() == 1) {
                    this->outputAlphabet += current;
                    content.erase(0, 2);
                }
                else {
                    throw invalid_argument("Output Alphabet's element must contain only one symbol.");
                }
            }
        }
        // Check if states are not set yet
        else  if (this->states.size() == 0) {
            while (content.length()) {
                // Get the substring from start till ','
                string current = content.substr(0, content.find(","));
                this->states.push_back(current);
                content.erase(0, current.length()+1);
            }

            int rows = this->states.size();
            this->functionResults.resize(rows);
            
            this->activeState = this->states[0];
        } 
        else {
            while (content.length()) {
                // Get the substring from start till '|'
                string current = content.substr(0, content.find("|"));
                this->functionResults[n].push_back(current);
                content.erase(0, current.length() + 1); // +1 for removing "|" character
            }
            n++;
        }
    }

    configFile.close();
}

string Automata::run(string input) {
    string output = "", functonResult, currentState;
    int rowIndex, colIndex;
    for (int i = 0; i < input.length();i++) {
        // Check if Input alphabet includes the current character
        if (this->inputAlphabet.find(input[i]) < this->inputAlphabet.length()) {
            // Get index of active state in states vector
            rowIndex = distance(this->states.begin(), find(this->states.begin(), this->states.end(),this->activeState));
            // Get index of current character in inputAlphabet string
            colIndex = this->inputAlphabet.find(input[i]);

            functonResult = this->functionResults[rowIndex][colIndex];

            // Get the substring from start till ','
            string outChar = functonResult.substr(0, functonResult.find(","));

            // Check if Output alphabet includes the current character
            if (outChar.length() == 1 && this->outputAlphabet.find(outChar) < this->outputAlphabet.length()) {
                output = output + outChar;
                currentState = functonResult.erase(0, 2);

                // Check if states vector includes the current state
                if (distance(this->states.begin(), find(this->states.begin(), this->states.end(), currentState)) < this->states.size()) {
                    this->activeState = currentState;
                }
                else {
                    throw invalid_argument("Current state does not exist: " + currentState);
                }
            }
            else {
                throw invalid_argument("Output Alphabet does not include the current character: " + outChar);
            }
        }
        else {
            throw invalid_argument("Input Alphabet does not include the current character: " + string(1,input[i]));
        }
    }

    return output;
}