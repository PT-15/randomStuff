#include <stdio.h>
#include <string.h>

#define UNUSED __attribute__((unused))

FILE* src;
FILE* dest;

char* getTranslation(char instruction)
{
    switch (instruction){
        case '<':
            return "Ook? Ook. ";

        case '>':
            return "Ook. Ook? ";

        case '+':
            return "Ook. Ook. ";

        case '-':
            return "Ook! Ook! ";

        case '.':
            return "Ook! Ook. ";

        case ',':
            return "Ook. Ook! ";

        case '[':
            return "Ook! Ook? ";

        case ']':
            return "Ook? Ook! ";

        default:
            return "";
    }
}

void translateInstruction(char instruction)
{
    fprintf(dest, getTranslation(instruction));
}

int main(UNUSED int argc, char** argv)
{
    src = fopen(argv[1], "r");
    if (src == NULL){
        printf("Couldn't open file\n");
        return 1;
    }
    dest = fopen(argv[2], "w");

    char instruction;
    while((instruction = fgetc(src)) != EOF){
        translateInstruction(instruction);
    }

    fprintf(dest, "\n");
    fclose(src);
    fclose(dest);
}
