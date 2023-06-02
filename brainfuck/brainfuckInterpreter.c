// BRAINFUCK INTERPRETER IN C
// Has cell array wrap (if you go left from the first cell you reach the last cell and viceversa)
// Has cell value wrap (it works with chars [bytes] and positive numbers. 0 - 1 = 127 and 127 + 1 = 0)

#include <stdio.h>

#define MAX_MEMORY_SIZE 30000
#define MAX_STACK_SIZE 1000
#define MIN_CELL_VALUE 0
#define MAX_CELL_VALUE 127

struct stack {
    int top;
    int stack[MAX_STACK_SIZE];
} loopTracker = {-1, {0}};

struct list {
    int lastInstruction;
    char instruction[MAX_MEMORY_SIZE];
} instructionMemory = {-1, {0}};

struct data {
    int currentCell;
    char memory[MAX_MEMORY_SIZE];
} dataMemory = {0, {0}};

void moveCurrentCellRight ()
{
    if(dataMemory.currentCell >= MAX_MEMORY_SIZE - 1){
        dataMemory.currentCell = 0;
        return;
    }

    dataMemory.currentCell++;
}

void moveCurrentCellLeft()
{
    if (dataMemory.currentCell <= 0){
        dataMemory.currentCell = MAX_MEMORY_SIZE - 1;
        return;
    }

    dataMemory.currentCell--;
}

void addToCurrentCell()
{
    if (dataMemory.memory[dataMemory.currentCell] >= MAX_CELL_VALUE){
        dataMemory.memory[dataMemory.currentCell] = MIN_CELL_VALUE;
        return;
    }

    dataMemory.memory[dataMemory.currentCell]++;
}

void subtractFromCurrentCell()
{
    if (dataMemory.memory[dataMemory.currentCell] <= MIN_CELL_VALUE){
        dataMemory.memory[dataMemory.currentCell] = MAX_CELL_VALUE;
        return;
    }

    dataMemory.memory[dataMemory.currentCell]--;
}

void printCurrentCellValue ()
{
    printf("Instruction received\n");
    printf("%c", dataMemory.memory[dataMemory.currentCell]);
}

void readToCurrentCell ()
{
    printf("Instruction received\n");
    char cat;
    scanf("%c", &cat);
    printf("Input was %c\n", cat);
    //scanf("%c", &dataMemory.memory[dataMemory.currentCell]);
}

void executeInstruction(char instruction)
{
    switch (instruction){
        case '<':
            moveCurrentCellLeft();
            break;

        case '>':
            moveCurrentCellRight();
            break;

        case '+':
            addToCurrentCell();
            break;

        case '-':
            subtractFromCurrentCell();
            break;

        case '.':
            printCurrentCellValue();
            break;

        case ',':
            readToCurrentCell();
            break;

        case '[':
            startLoop();
            break;

        case ']':
            loopEnd();
            break;

        default:
            break;
    }
}

void startLoop ()
{

}

void loopEnd ()
{

}

void readProgram ()
{
    for(char instruction = getchar(); instruction != EOF; instruction = getchar()){
        if (instruction == '<' || instruction == '>' ||
            instruction == '+' || instruction == '-' ||
            instruction == '.' || instruction == ',' ||
            instruction == '[' || instruction == ']')
        {
            instructionMemory.lastInstruction++;
            instructionMemory.instruction[instructionMemory.lastInstruction] = instruction;
        }
    }
}

int main()
{
    readProgram();

    

    return 0;
}
