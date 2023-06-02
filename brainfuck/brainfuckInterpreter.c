// BRAINFUCK INTERPRETER IN C
// Has cell array wrap (if you go left from the first cell you reach the last cell and viceversa)
// Has cell value wrap (it works with chars [bytes] and positive numbers. 0 - 1 = 127 and 127 + 1 = 0)

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>

#define MAX_MEMORY_SIZE 30000
#define MAX_STACK_SIZE 1000
#define MIN_CELL_VALUE 0
#define MAX_CELL_VALUE 127

struct stack {
    int top;
    int stack[MAX_STACK_SIZE];
} loopTracker = {-1, {0}};

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

int openFile(char* fileName)
{
    int fd = open(fileName, O_RDONLY);

    if(fd < 0){
        printf("Error: couldn't get file descriptor\n");
        exit(1);
    }

    return fd;
}

void getFileStats(int fd, struct stat* info)
{
    if (fstat(fd, info) < 0){
        printf("Error: couldn't get file information\n");
        exit(1);
    }
}

char* memoryMapFile(int fileSize, int fd)
{
    char *pointerToMemory = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (pointerToMemory == MAP_FAILED){
        printf("Error: couldn't map file\n");
        exit(1);
    }
    return pointerToMemory;
}

void unmap(char* memMap, int fileSize)
{
    int err = munmap(memMap, fileSize);
    if(err != 0){
        printf("Error: couldn't unmap file\n");
        exit(1);
    }
}

int main(int argc, char** argv)
{
    int program_fd = openFile(argv[1]);

    struct stat info;
    getFileStats(program_fd, &info);

    printf("Size of file %ld\n", info.st_size);

    char* instruction = memoryMapFile(info.st_size, program_fd);

    char* it = instruction;
    for(int i = 0; i < info.st_size; i++){
        printf("%c", *it);
        it++;
    }
    printf("\nAnother way\n");
    for(it = instruction; it < instruction + info.st_size; it++){
        printf("%c", *it);
    }

    unmap(instruction, info.st_size);


    return 0;
}
