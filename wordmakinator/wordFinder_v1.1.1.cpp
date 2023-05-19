#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#define FILE_ADDRESS "american-english.txt"

std::vector<std::string> wordDict;

void createDictVector(std::fstream& dictFile, int wordLength)
{
    while (!dictFile.eof()){
        std::string word;
        std::getline(dictFile, word);
        if (word.size() == wordLength)
            wordDict.push_back(word);
    }
}

void binarySearch(const std::string& word)
{
    int left = 0;
    int right = wordDict.size();

    while (right > left + 1){
        int middle = (right + left) / 2;
        if (word.compare(wordDict[middle]) > 0){
            left = middle;
        }
        else {
            right = middle;
        }
    }

    if (wordDict[right] == word){
        std::cout << word << "\n";
    }
}

void findWords (int wrdLength, const std::string& letters, std::string wrd)
{
    if (wrd.size() == wrdLength){
        binarySearch(wrd);
        return;
    }

    for (int i = 0; i < letters.size(); i++){        
        wrd += letters[i];

        findWords(wrdLength, letters, wrd);

        wrd.pop_back();
    }
}

void findWordsWithStencil(const std::string& stencil, int wrdLength, const std::string& letters, bool getContained, std::string& contains, std::string& wrd)
{
    if (wrd.size() == wrdLength){
        if (getContained){
            for (int i = 0; i < contains.size(); i++){
                bool found = false;
                for (int j = 0; j < wrdLength; j++){
                    if (wrd[j] == contains[i] && stencil[j] == '*'){
                        found = true;
                    }
                }
                if (!found){
                    return;
                }
            }
        }
        binarySearch(wrd);
        return;
    }

    if (stencil[wrd.size()] != '*'){
        wrd += stencil[wrd.size()];

        findWordsWithStencil(stencil, wrdLength, letters, getContained, contains, wrd);

        wrd.pop_back();
        return;
    }

    for (int i = 0; i < letters.size(); i++){        
        wrd += letters[i];

        findWordsWithStencil(stencil, wrdLength, letters, getContained, contains, wrd);

        wrd.pop_back();
    }
}

int addOption(int wordLength, const std::string& letters)
{
    std::cout << "Choose mode:\n\t0. Any word\n\t1. Words containing specific letters\n> ";
    int option;
    std::cin >> option;
    if (!option){
        return 0;
    }
    std::cout << "Enter the word (ex: **ce*** -> contains \"ce\" in third and fourth position. If all asterisks enter -1)\n> ";
    std::string stencil;
    std::cin >> stencil;
    if (stencil == "-1"){
        stencil = "";
        for (int i = 0; i < wordLength; i++){
            stencil += "*";
        }
    }
    while (stencil.size() != wordLength){
        std::cout << "Wrong input. Enter again: ";
        std::cin >> stencil;
    }
    std::string contains;
    std::cout << "Enter letters that appear but with unkown position (all together, enter -1 if there aren't any): ";
    std::cin >> contains;
    bool getContained = true;
    if (contains == "-1"){
        contains = "";
        getContained = false;
    }
    std::string word;
    findWordsWithStencil(stencil, wordLength, letters, getContained, contains, word);
    return 1;
}

bool hasLetter(char letterToCheck, char letterToRemove){
    return letterToCheck == letterToRemove;
}

void getLetters(std::string& letters)
{
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::cout << "1. Specify letters that can appear\n2. Specify letters that don't appear\n> ";
    int option;
    std::cin >> option;
    switch (option){
        case 1:
            std::cout << "Insert letters (lower case, all together): ";
            std::cin >> letters;
            break;
        case 2:
            std::cin >> letters;
            std::cout << "Insert letters (lower case, all together, -1 if all appear): ";
            if (letters != "-1"){
                for (int i = 0; i < letters.size(); i++){
                    alphabet.erase(remove(alphabet.begin(), alphabet.end(), letters[i]), alphabet.end());
                }
            }
            letters = alphabet;
    }
}

int main(int argc, char* argv[])
{
    int wrdLength;
    std::string letters;
    std::cout << "Enter word length: ";
    std::cin >> wrdLength;

    getLetters(letters);

    std::fstream dictionaryFile;
    dictionaryFile.open(FILE_ADDRESS,std::fstream::in);
    if (!dictionaryFile.is_open()){
        std::cout << "Error getting the dictionary file. Make shure you have it in the directory\n";
        return 1;
    }

    createDictVector(dictionaryFile, wrdLength);

    if(addOption(wrdLength, letters)){
        return 0;
    }

    findWords(wrdLength, letters, "");
}