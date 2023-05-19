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

void findWordsWithStencil(const std::string& stencil, int wrdLength, const std::string& letters, std::string wrd)
{
    if (wrd.size() == wrdLength){
        binarySearch(wrd);
        return;
    }

    if (stencil[wrd.size()] != '*'){
        wrd += stencil[wrd.size()];

        findWordsWithStencil(stencil, wrdLength, letters, wrd);

        wrd.pop_back();
        return;
    }

    for (int i = 0; i < letters.size(); i++){        
        wrd += letters[i];

        findWordsWithStencil(stencil, wrdLength, letters, wrd);

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
    std::cout << "Enter the word (ex: **ce*** -> contains \"ce\" in third and fourth position)\n> ";
    std::string stencil;
    std::cin >> stencil;
    while (stencil.size() != wordLength){
        std::cout << "Wrong input. Enter again: ";
        std::cin >> stencil;
    }

    findWordsWithStencil(stencil, wordLength, letters, "");
    return 1;
}

bool hasLetter(char letterToCheck, char letterToRemove){
    return letterToCheck == letterToRemove;
}

void getLetters(std::string& letters)
{
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::cout << "1. Specify letters that appear\n2. Specify letters that don't appear\n> ";
    int option;
    std::cin >> option;
    std::cout << "Insert letters (lower case, -1 if all appear): ";
    switch (option){
        case 1:
            std::cin >> letters;
            break;
        case 2:
            std::cin >> letters;
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