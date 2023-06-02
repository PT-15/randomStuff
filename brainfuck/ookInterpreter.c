// BRAINFUCK INTERPRETER IN C
// Has cell array wrap (if you go left from the first cell you reach the last cell and viceversa)
// Has cell value wrap (it works with chars [bytes] and positive numbers. MIN_CELL_VALUE - 1 = MAX_CELL_VALUE and MAX_CELL_VALUE + 1 = MIN_CELL_VALUE)

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED __attribute__((unused))

#define MAX_MEMORY_SIZE 30000
#define MAX_STACK_SIZE 1000
#define MIN_CELL_VALUE 0
#define MAX_CELL_VALUE 127

struct stack {
    int top;
    char* stack[MAX_STACK_SIZE];
} loopTracker = {-1, {0}};

struct data {
    int currentCell;
    char cell[MAX_MEMORY_SIZE];
} dataMemory = {0, {0}};

int getFileDescriptor(char* fileName)
{
    int fd = open(fileName, O_RDONLY);

    if(fd < 0){
        printf("Error: couldn't get file descriptor\n");
        exit(1);
    }

    return fd;
}

void getFileStats(int fd, struct stat* fileInfo)
{
    if (fstat(fd, fileInfo) < 0){
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
    int error = munmap(memMap, fileSize);
    if(error != 0){
        printf("Error: couldn't unmap file\n");
        exit(1);
    }
}

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
    if (dataMemory.cell[dataMemory.currentCell] >= MAX_CELL_VALUE){
        dataMemory.cell[dataMemory.currentCell] = MIN_CELL_VALUE;
        return;
    }

    dataMemory.cell[dataMemory.currentCell]++;
}

void subtractFromCurrentCell()
{
    if (dataMemory.cell[dataMemory.currentCell] <= MIN_CELL_VALUE){
        dataMemory.cell[dataMemory.currentCell] = MAX_CELL_VALUE;
        return;
    }

    dataMemory.cell[dataMemory.currentCell]--;
}

void printCurrentCellValue ()
{
    printf("%c", dataMemory.cell[dataMemory.currentCell]);
}

void readToCurrentCell ()
{
    int cat;
    scanf("%d", &cat);
    if (cat > MAX_CELL_VALUE){
        cat = MAX_CELL_VALUE;
    }
    if (cat < MIN_CELL_VALUE){
        cat = MIN_CELL_VALUE;
    }

    dataMemory.cell[dataMemory.currentCell] = cat;
}

void startLoop (char* currInstruction)
{
    loopTracker.top++;
    loopTracker.stack[loopTracker.top] = currInstruction;
}

void loopEnd (char** currInstruction)
{
    if (dataMemory.cell[dataMemory.currentCell] == 0){
        loopTracker.top--;
        return;
    }

    *currInstruction = loopTracker.stack[loopTracker.top];
}

void getWholeInstruction(char* currInstruction, char* instruction)
{
    for (int i = 0; i < 9; i++){
        *(instruction+i) = *(currInstruction+i);
    }
    *(instruction+9) = '\0';
}

void executeInstruction(char** currInstruction)
{
    char instruction[10];
    getWholeInstruction(*currInstruction, instruction);

    if (!strcmp(instruction, "Ook. Ook?")){
        moveCurrentCellLeft();
        return;
    }
    if (!strcmp(instruction, "Ook? Ook.")){
        moveCurrentCellRight();
        return;
    }
    if (!strcmp(instruction, "Ook. Ook.")){
        addToCurrentCell();
        return;
    }
    if (!strcmp(instruction, "Ook! Ook!")){
        subtractFromCurrentCell();
        return;
    }
    if (!strcmp(instruction, "Ook! Ook.")){
        printCurrentCellValue();
        return;
    }
    if (!strcmp(instruction, "Ook. Ook!")){
        readToCurrentCell();
        return;
    }
    if (!strcmp(instruction, "Ook! Ook?")){
        startLoop(*currInstruction);
        return;
    }
    if (!strcmp(instruction, "Ook? Ook!")){
        loopEnd(currInstruction);
        return;
    }
    if (!strcmp(instruction, "Ook? Ook?")){ //Give the memory pointer a banana
        printf("\nOok! :)\n");
        return;
    }
}

int main(UNUSED int argc, char** argv)
{
    int programFileDescriptor = getFileDescriptor(argv[1]);

    struct stat programFileInfo;
    getFileStats(programFileDescriptor, &programFileInfo);

    char* firstInstruction = memoryMapFile(programFileInfo.st_size, programFileDescriptor);
    char* currInstruction = firstInstruction;

    while (currInstruction < firstInstruction+programFileInfo.st_size){
        if (*currInstruction != 'O')
            continue;

        executeInstruction(&currInstruction);
        currInstruction += 10;
    }

    unmap(firstInstruction, programFileInfo.st_size);

    return 0;
}
