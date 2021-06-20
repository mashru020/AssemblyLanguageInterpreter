#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

#define LIMIT 255 ///12bit Data
#define LENGTH 8 ///12bit Data
#define MEMORYSIZE 8 ///8 Memory Slots

int Overflow=0;
int Underflow=0;

char Accumulator[LENGTH];
char Memory[MEMORYSIZE][LENGTH];

void EmptyAccumulator(){
    int i;
    for(i=0; i<LENGTH; i++)
        Accumulator[i]='0';
}

int ValidInput(int i){
    if(i>MEMORYSIZE){
        printf("Memory Location Cannot be Larger then The Memory Capacity\n");
        return 0;
    }
    if(i<0){
        printf("Memory Location Cannot be Negative\n");
        return 0;
    }
    return 1;
}

void Wait(){
    printf("\tPress Any Key to Continue...\n");
    getch();
    printf("\n");
}

char* toBinary(int Decimal){
    if(Decimal>LIMIT/2)
        Overflow=1;
    if(Decimal<LIMIT/-2)
        Underflow=1;
    int i;
    char Binary[LENGTH];
    if(Decimal<0){
        Decimal = (Decimal*-1);
        Binary[0] = '1';
    }
    else
        Binary[0] = '0';
    for(i=LENGTH-1; i>0; i--){
        if(Decimal > 0 && Decimal % 2 == 1)
            Binary[i] = '1';
        else
            Binary[i] = '0';
        Decimal = Decimal / 2;
    }
    return Binary;
}

int toDecimal(char *Binary){
    int i,Base=1,Decimal = 0;
    for (i=LENGTH-1; i>0; i--,Base*=2)
        if (Binary[i] == '0')
            Decimal += 0 * Base;
        else
            Decimal += 1 * Base;
    if(Binary[0]=='1')
        Decimal*=-1;
    return Decimal;
}

void GenerateMemory(){
    int i;
    srand(time(NULL));
    for(i=0; i< MEMORYSIZE; i++)
        strcpy(Memory[i],toBinary((rand() % LIMIT)-LIMIT/2));
}
/////////////////////////////////////////////////
void ShowMemoryFor(int i){
    int j;
    printf("Memory [%d]\t",i);
    printf("%d\t",toDecimal(Memory[i]));
    for(j=0; j<LENGTH; j++)
        printf("%c",Memory[i][j]);
    printf("\n");
}
void InputMemory(){
    char B[LENGTH];
    int l,D,c,i,j;
    printf("Input Memory Location[0 to %d]: ",MEMORYSIZE-1);
    scanf("%d",&l);
    if(!ValidInput(l))
        return;
    printf("Input '1' for Binary or '2' for Decimal: ");
    scanf("%d",&c);
    switch(c){
    case 1:
        printf("Input Binary Data[8 Bit with Mod Bit]: ");
        scanf("%s",B);
        if(strlen(B)!=LENGTH){
            printf("Invalid Input\n");
            return;
        }
        else{
            for(i=0; i<LENGTH; i++)
                if(B[i]!='0' && B[i]!='1'){
                    printf("Invalid Input\n");
                    return;
                }
        }
        for(j=0; j<LENGTH; j++)
            Memory[l][j]=B[j];
        printf("Location\tDecimal\tBinary\n--------------------------------\n");
        ShowMemoryFor(l);
        printf("Data Insertion Successful\n");
        break;
    case 2:
        printf("Input Decimal Data[%d to %d]: ",LIMIT/2*-1,LIMIT/2);
        scanf("%d",&D);
        if(D>LIMIT/2 || D<LIMIT/2*-1){
            printf("Invalid Input\n");
            return;
        }
        strcpy(B,toBinary(D));
        for(j=0; j<LENGTH; j++)
            Memory[l][j]=B[j];
        printf("Location\tDecimal\tBinary\n--------------------------------\n");
            ShowMemoryFor(l);
        printf("Data Insertion Successful\n");
        break;
    default:
        printf("Wrong Input\n");
        break;
    }
}

void ShowMemory(){
    int i,j;
    for(i=0; i< MEMORYSIZE; i++){
        printf("Memory [%d]\t",i);
        printf("%d\t",toDecimal(Memory[i]));
        for(j=0; j<LENGTH; j++)
            printf("%c",Memory[i][j]);
        printf("\n");
    }
}

/*void ShowMemoryFor(int i){
    int j;
    printf("Memory [%d]\t",i);
    printf("%d\t",toDecimal(Memory[i]));
    for(j=0; j<LENGTH; j++)
        printf("%c",Memory[i][j]);
    printf("\n");
}*/

void ShowAccumulator(){
    printf("Accumulator\t");
    printf("%d\t",toDecimal(Accumulator));
    printf("%s\n",Accumulator);
}

void Instruction(char *Opcode, int Operand){
    int i,j;
    if(!strcmp(Opcode,"ADD")){
        strcpy(Accumulator,toBinary(toDecimal(Accumulator)+toDecimal(Memory[Operand])));
    }
    else if(!strcmp(Opcode,"SUB")){
        strcpy(Accumulator,toBinary(toDecimal(Accumulator)-toDecimal(Memory[Operand])));
    }
    else if(!strcmp(Opcode,"MUL")){
        strcpy(Accumulator,toBinary(toDecimal(Accumulator)*toDecimal(Memory[Operand])));
    }
    else if(!strcmp(Opcode,"DIV")){
        strcpy(Accumulator,toBinary(toDecimal(Accumulator)/toDecimal(Memory[Operand])));
    }
    else if(!strcmp(Opcode,"AND")){
        for(i=0; i<LENGTH; i++)
            if((Accumulator[i]=='1')&&(Memory[Operand][i]=='1'))
                Accumulator[i]='1';
            else
                Accumulator[i]='0';
    }
    else if(!strcmp(Opcode,"NOT")){
        for(i=0; i<LENGTH; i++)
            if(Accumulator[i]=='0')
                Accumulator[i]='1';
            else
                Accumulator[i]='0';
    }
    else if(!strcmp(Opcode,"OR")){
        for(i=0; i<LENGTH; i++)
            if((Accumulator[i]=='0')&&(Memory[Operand][i]=='0'))
                Accumulator[i]='0';
            else
                Accumulator[i]='1';
    }
    else if(!strcmp(Opcode,"XOR")){
        for(i=0; i<LENGTH; i++)
            if((Accumulator[i] != Memory[Operand][i]))
                Accumulator[i]='1';
            else
                Accumulator[i]='0';
    }
    else if(!strcmp(Opcode,"LD")){
        for(j=0; j<LENGTH; j++)
            Accumulator[j] = Memory[Operand][j];
    }
    else if(!strcmp(Opcode,"ST")){
        for(j=0; j<LENGTH; j++)
            Memory[Operand][j] = Accumulator[j];
    }
    else{
        printf("Wrong Opcode\n");
        return;
    }
    if(Overflow){
        Overflow=0;
        printf("Overflow\n");
    }
    if(Underflow){
        Underflow=0;
        printf("Underflow\n");
    }
    printf("Assembly Instruction Execution Successful\n");
}

int main()
{
    char Opcode[5];
    int Operand,O;
    EmptyAccumulator();
    //GenerateMemory();
    while(1)
    {
        printf("\t\t\t\tInterpreter\n");
        printf("------------------------------------------------------------------------------\n");
        printf("1. View All Memory Contents\t\t");
        printf("6. Generate New Random Data for Memory\n");
        printf("2. View Accumulator Contents\t\t");
        printf("7. Empty Accumulator\n");
        printf("3. View Memory Contents of a Location\t");
        printf("8. Clear Screen\n");
        printf("4. Run Assembly Instruction\t\t");
        printf("9. Exit\n");
        printf("5. Insert Data to a Memory Location\n");
        printf("Enter Option: ");
        scanf("%d",&O);
        switch(O){
        case 1:
            printf("\tMemory View:\n");
            printf("Location\tDecimal\tBinary\n--------------------------------\n");
            ShowAccumulator();
            ShowMemory();
            Wait();
            break;
        case 2:
            printf("\tAccumulator View:\n");
            printf("Location\tDecimal\tBinary\n--------------------------------\n");
            ShowAccumulator();
            Wait();
            break;
        case 3:
            printf("\tSingle Memory View:\n");
            printf("Input Memory Location[0 to %d]: ",MEMORYSIZE-1);
            scanf("%d",&Operand);
            if(!ValidInput(Operand))
                break;
            printf("Location\tDecimal\tBinary\n--------------------------------\n");
            ShowMemoryFor(Operand);
            Wait();
            break;
        case 4:
            printf("\tAssembly Instruction:\n");
            printf("Enter Instruction: ");
            scanf("%s%d",Opcode,&Operand);
            if(!ValidInput(Operand))
                break;
            Instruction(Opcode,Operand);
            Wait();
            break;
        case 5:
            printf("\tInsert Data to Memory:\n");
            InputMemory();
            Wait();
            break;
        case 6:
            GenerateMemory();
            printf("\n\tMemory Generated\n\n");
            Wait();
            break;
        case 7:
            EmptyAccumulator();
            printf("\n\tAccumulator Emptied\n\n");
            Wait();
            break;
        case 8:
            system("CLS");
            break;
        case 9:
            return 0;
        default:
            printf("\n\tWrong Input\n\n");
            Wait();
            break;
        }
    }
    return 0;
}
