#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    string content;

    ifstream configFile("Config.txt");
    int i = 0;
    while (getline(configFile, content)) {
        cout <<i++<<":" << content << endl;
    }

    configFile.close();
}