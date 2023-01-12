#include "cpu.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char**argv) {

    srand(time(NULL));   // Inicializacao da semente para os numeros aleatorios.

    if (argc != 3 && argc != 4) {
        printf("Numero de argumentos invalidos! Sao 3 ou 4.\n");
        printf("Linha de execucao: ./exe TIPO_INSTRUCAO [TAMANHO_RAM|ARQUIVO_DE_INSTRUCOES]\n");
        printf("\tExemplo 1 de execucao: ./exe random 10\n"); 
        printf("\tExemplo 2 de execucao: ./exe fibonacci 5 40\n");  //primeiro numero corresponde ao RamSize e o segundo o numero inicial
        printf("\tExemplo 3 de execucao: ./exe file arquivo_de_instrucoes.txt\n");
        printf("\tExemplo 4 de execucao: ./exe multiply 10 5\n");   //Primeiro numero corresponde ao tamanho da RAM e o segundo corresponde ao inicial
        printf("\tExemplo 5 de execucao: ./exe divide 40 8\n");     //Primeiro numero corresponde ao dividendo e o segundo ao divisor
        return 0;
    }

    int ramSize;
    Machine machine;
    Instruction *instructions;

    if (strcmp(argv[1], "random") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateRandomInstructions(ramSize);
    } else if (strcmp(argv[1], "multiply") == 0) {      //Multiplicacao
        ramSize = atoi(argv[2]) + 2;
        int multiplying = atoi(argv[3]);
        instructions = generateMultiplicationInstructions(ramSize, multiplying);
    } else if (strcmp(argv[1], "file") == 0) {
        instructions = readInstructions(argv[2], &ramSize);
    } else if (strcmp(argv[1], "fibonacci") == 0) {
        ramSize = atoi(argv[2]);
        int base = atoi(argv[3]);
        instructions = generateFibonacciInstructions(ramSize, base);
    } else if (strcmp(argv[1], "divide") == 0) {
        ramSize = 3;
        int dividend, divider;
        dividend = atoi(argv[2]);
        divider = atoi(argv[3]);
        instructions = generateDivisionInstructions(dividend, divider);
    } else if (strcmp(argv[1], "expo") == 0) {
        ramSize = 3;
        int base, exp;
        base = atoi(argv[2]);
        exp = atoi(argv[3]);
        instructions = generateExponetialInstructions(base, exp);
    }
    else {
        printf("Opcao invalida.\n");
        return 0;
    }
    
    printf("Iniciando a maquina...\n");
    start(&machine, instructions, ramSize);
    printRAM(&machine);
    run(&machine);
    printRAM(&machine);
    stop(&machine);
    printf("Finalizando a maquina...\n");
    return 0;
}