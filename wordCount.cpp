#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <cctype>

void loadFile(std::ifstream&, std::map<std::string, int>&);
void  display(std::map<std::string, int>&);
void WordCount(std::string, std::map<std::string,int>&);


int main(int argc, char** argv) {

    std::map <std::string, int> wordMap;
    std::string fName;
    std::cout << "Enter file name including extension : ";
    std::getline(std::cin, fName);
    std::ifstream inputFile(fName);

    if (inputFile.is_open()) {
        std::cout << std::endl << "File loaded successfully!" << std::endl;
        loadFile(inputFile,wordMap);        
        inputFile.close();
        display(wordMap);
        std::cout << std::endl << fName << " has " << wordMap.size() << " words" << std::endl;
    }
    else
    {
    std::cout << "\nFile not found!\n" << std::endl;
    }
    return 0;
}

void loadFile(std::ifstream& fName, std::map<std::string,int>&wordMap) { 
        
    std::string line;
    while (getline(fName, line)) {
        size_t prev = 0, pos;

        while ((pos = line.find_first_of
        ("~`=!@#$%^&*)/\?-_|[,. }] (_-+{;':""></", prev)) != std::string::npos) {
            if (pos > prev) {
                WordCount(line.substr(prev, pos - prev),wordMap);
            }
            prev = pos + 1;
        }
        if (prev < line.length()) {
            WordCount(line.substr(prev, std::string::npos),wordMap);
        }
    }     
        
}

void WordCount(std::string str,std::map<std::string,int>& wordMap) {

    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c); });
    auto it = wordMap.find(str);

    if (it != wordMap.end()) {
        it->second = it->second + 1;
    }
    else {
        wordMap.insert(std::make_pair(str, 1));
    }
}

void display(std::map<std::string, int>&wordMap) {
    std::cout << "-----------------------------" << std::endl;
    for (auto word : wordMap) {
        std::cout << std::setw(20) <<std::left << word.first << " | " << std::setw(5) << word.second << "|" << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}
