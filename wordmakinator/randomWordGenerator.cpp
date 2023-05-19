#include <iostream>
#include <string>
#include <vector>

void generateWrds (int wrdLength, const std::string& letters, std::string wrd)
{
    if (wrd.size() == wrdLength){
        std::cout << wrd << "\n";
        return;
    }

    for (int i = 0; i < letters.size(); i++){        
        wrd += letters[i];

        generateWrds(wrdLength, letters, wrd);

        wrd.pop_back();
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3){
        std::cout << "Not enough arguments\n";
        return 1;
    }
    int wrdLength = *argv[1] - '0';
    std::string letters;
    for (int i = 2; i < argc; i++){
        letters += *argv[i];
    }
    
    generateWrds(wrdLength, letters, "");
}