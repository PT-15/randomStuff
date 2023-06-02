#include <stdio.h>
#include <string.h>

#define UNUSED __attribute__((unused))

FILE* src;
FILE* dest;

void getWholeInstruction(char* instruction)
{
    *(instruction) = 'O';
    for (int i = 1; i < 9; i++){
        *(instruction+i) = fgetc(src);
    }
    *(instruction+9) = '\0';
}

char* getTranslation(char* instruction)
{
    if (!strcmp(instruction, "Ook. Ook?")){
        return ">";
    }
    if (!strcmp(instruction, "Ook? Ook.")){
        return "<";
    }
    if (!strcmp(instruction, "Ook. Ook.")){
        return "+";
    }
    if (!strcmp(instruction, "Ook! Ook!")){
        return "-";
    }
    if (!strcmp(instruction, "Ook! Ook.")){
        return ".";
    }
    if (!strcmp(instruction, "Ook. Ook!")){
        return ",";
    }
    if (!strcmp(instruction, "Ook! Ook?")){
        return "[";
    }
    if (!strcmp(instruction, "Ook? Ook!")){
        return "]";
    }
    return ""; //Banana received
}

void translateInstruction()
{
    char instruction[10];
    getWholeInstruction(instruction);

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
        if (instruction == 'O'){
            translateInstruction();
        }
    }

    fprintf(dest, "\n");
    fclose(src);
    fclose(dest);
}
