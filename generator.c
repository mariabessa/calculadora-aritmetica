#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

Instruction* generateRandomInstructions(int ramSize) {
    // 01|22|13|45 => isto é uma instrução
    // 02|33|12|01 => isto é outra instrução
            
    // 0 => salvar na memória
    // 1 => opcode => somar
    // 2 => opcode => subtrair
    //-1 => halt
    
    // 22 => significa um endereço da RAM (10 endereço) 
    // 13 => significa 2o endereço
    // 45 => significa 3o endereco
    //ramSize => ESTA FORA DO INTERVALO DE 0 A ramSize DA MEMÓRIA RAM

    Instruction* instructions = (Instruction*) malloc(10 * sizeof(Instruction));

    for (int i=0; i<9; i++){
        instructions[i].opcode = rand() % 5; //0, 1, 2, 3, 4
        instructions[i].info1 = rand() % ramSize; //0 ... RAM_SIZE
        do {
            instructions[i].info2 = rand() % ramSize; //0 ... RAM_SIZE
        } while (instructions[i].info1 == instructions[i].info2);
        instructions[i].info3 = rand() % ramSize; //0 ... RAM_SIZE
    }
    
    //inserindo a ultima instrucao do programa que nao faz nada que presta
    instructions[9].opcode =-1;
    instructions[9].info1 = -1;
    instructions[9].info2 = -1;
    instructions[9].info3 = -1;
    
    return instructions;
}

Instruction* readInstructions(char* fileName, int* ramSize) {
    printf("FILE -> %s\n", fileName);
    FILE* file = fopen(fileName, "r"); // Abrindo arquivo no modo leitura
    
    if (file == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    int n, i = 0;
    fscanf(file, "%d %d", ramSize, &n);
    Instruction* instructions = (Instruction*) malloc(n * sizeof(Instruction));
    while (i < n) {
        fscanf(file, "%d %d %d %d", &instructions[i].opcode, &instructions[i].info1, &instructions[i].info2, &instructions[i].info3);
        i++;
    }
    fclose(file); // Fechando o arquivo

    return instructions;
}

Instruction* generateMultiplicationInstructions(int multiplier, int multiplying){
    
    Instruction* instructions = (Instruction*) malloc((multiplier + 2) * sizeof(Instruction));
    
    //Three extra instructions:
    //  1 - Take multiplying to the memory
    //  2 - Putting zero in the position of the result in the RAM

    instructions[0].opcode = 0;
    instructions[0].info1 = multiplier;   //Content to be saved in RAM
    instructions[0].info2 = 0;   //RAM position
    
    instructions[1].opcode = 0;
    instructions[1].info1 = multiplying;  //Content
    instructions[1].info2 = 1;  //RAM Position

    instructions[2].opcode = 3;   //Opcode of multiplication
    instructions[2].info1 = 0;    //Position of multiplier
    instructions[2].info2 = 1;    //Position of multiplying
    instructions[2].info3 = 2;    //Position of multiplication result

    instructions[3].opcode = -1;
    instructions[3].info1 = -1;
    instructions[3].info2 = -1;
    instructions[3].info3 = -1;
     
    return instructions;
}

Instruction* generateFibonacciInstructions(int max, int base){
    
    Instruction* instructions = (Instruction*) malloc((2 + max) * sizeof(Instruction));
    
    //Three extra instructions:
    //  1 - Take base number to the memory
    //  2 - Putting zero in the position of the result in the RAM

    instructions[0].opcode = 0;
    instructions[0].info1 = 1;   //Content to be saved in RAM
    instructions[0].info2 = 0;   //RAM position
    
    instructions[1].opcode = 0;     //Save the number
    instructions[1].info1 = base;      //Initial number    
    instructions[1].info2 = 1;      //RAM position

    int position = 1;

    for (int i = 0; i < max; i++){    
        instructions[i+2].opcode = 4;   //Opcode of Fibonacci
        instructions[i+2].info1 = position-1;    //Position of multiplying
        instructions[i+2].info2 = position;    //Position of the number that will be part of the multiplication
        instructions[i+2].info3 = position+1;    //Position of multiplication result
        position++;
    }

    instructions[max].opcode = -1;
    instructions[max].info1 = -1;
    instructions[max].info2 = -1;
    instructions[max].info3 = -1;
     
    return instructions;
}

Instruction* generateDivisionInstructions(int dividend, int divider){
    
    Instruction* instructions = (Instruction*) malloc((4) * sizeof(Instruction));
    
    //Three extra instructions:
    //  1 - Take multiplying to the memory
    //  2 - Putting zero in the position of the result in the RAM

    instructions[0].opcode = 0;
    instructions[0].info1 = dividend;   //First number
    instructions[0].info2 = 0;   //RAM position
    
    instructions[1].opcode = 0;
    instructions[1].info1 = divider;  //Second number
    instructions[1].info2 = 1;  //RAM position

    
    instructions[2].opcode = 5;   //Opcode of division
    instructions[2].info1 = 0;    //Position of dividend
    instructions[2].info2 = 1;    //Position of divider
    instructions[2].info3 = 2;    //Position of division result
    

    //Signaling the end

    instructions[3].opcode = -1;
    instructions[3].info1 = -1;
    instructions[3].info2 = -1;
    instructions[3].info3 = -1;
     
    return instructions;
}

Instruction* generateExponentialInstructions(int base, int exp){

    Instruction* instructions = (Instruction*) malloc((4) * sizeof(Instruction));
    
    //Three extra instructions:
    //  1 - Take base numbers to the memory

    instructions[0].opcode = 0;
    instructions[0].info1 = base;   //First number
    instructions[0].info2 = 0;   //RAM position
    
    instructions[1].opcode = 0;
    instructions[1].info1 = exp;  //Second number
    instructions[1].info2 = 1;  //RAM position

    
    instructions[2].opcode = 6;   //Opcode of division
    instructions[2].info1 = 0;    //Position of dividend
    instructions[2].info2 = 1;    //Position of divider
    instructions[2].info3 = 2;    //Position of division result
    

    //Signaling the end

    instructions[3].opcode = -1;
    instructions[3].info1 = -1;
    instructions[3].info2 = -1;
    instructions[3].info3 = -1;
     
    return instructions;
}
