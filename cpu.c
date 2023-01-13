#include "cpu.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

void start(Machine* machine, Instruction* instructions, int RAMSize) {
    machine->instructions = instructions;
    machine->RAM.items = (float*) malloc(sizeof(float) * RAMSize);
    machine->RAM.size = RAMSize;
    for (int i=0;i<RAMSize;i++)
        machine->RAM.items[i] = (float)rand() / RAND_MAX;
}

void stop(Machine* machine) {
    free(machine->instructions);
    free(machine->RAM.items);
}

void run(Machine* machine) {
    // Registradores
    int PC = 0; // Program Counter - Contador de programa
    int opcode = 0;
    int address1;
    int address2;
    float value;
    float result;
    float RAMContent1;
    float RAMContent2;
    int address3;
    while(opcode != -1) {
        Instruction instruction = machine->instructions[PC];
        opcode = instruction.opcode;
        switch (opcode) {
            case -1:
                printf("  > Finalizando a execucao.\n");
                break;
            case 0: // Levando informação para a RAM
                value = (float) instruction.info1;
                address1 = instruction.info2;
                machine->RAM.items[address1] = value;
                printf("  > Levando informacao (%f) para a RAM[%d].\n", value, address1);
                break;
            case 1: // Somando
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = RAMContent1 + RAMContent2;
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Somando RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
            case 2: // Subtraindo
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = RAMContent1-+ RAMContent2;
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Subtraindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
            case 3: // Multiplicacao
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = 0;
                for(int i = 0; i < RAMContent1; i++)
                    result = result + RAMContent2;        
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Multiplicando RAM[%d] (%.0f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
            case 4: // Fibonacci
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = RAMContent1 + RAMContent2;         //Problema ta aq
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Somando na sequencia de Fibonacci RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
            case 5: //Divisao
                address1 = instruction.info1;
                address2 = instruction.info2;
                RAMContent1 = machine->RAM.items[address1];
                RAMContent2 = machine->RAM.items[address2];
                result = 0;
                int soma = 0;
                for( ; ; ){
                    soma = soma + RAMContent2;
                    result++;
                    if(soma == RAMContent1)
                        break;
                        else if(soma > RAMContent1){
                            result -= 1;
                            soma = 0;
                            int RC2 = result;
                        //    for( ; ; )

                            break;
                        }
                }        
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  > Dividindo RAM[%d] (%.0f) com RAM[%d] (%.0f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
            case 6: //Exponenciacao
                address1 = instruction.info1;   
                address2 = instruction.info2;   
                RAMContent1 = machine->RAM.items[address1];     //basse
                RAMContent2 = machine->RAM.items[address2];     //expoente
                result = 0;
                float aux = RAMContent1;
                for(int i = 1; i < RAMContent2; i++){ 
                    result = 0;
                    for(int j = 0; j < RAMContent1; j++){
                        result = result + aux;
                        printf("\nresult = %f\n", result);
                    }
                    aux = result;
                    printf("\naux = %f\n", aux);
                }
        
                if(RAMContent2 == 1)
                    result = RAMContent1;
                address3 = instruction.info3;
                machine->RAM.items[address3] = result;
                printf("  >  RAM[%d] (%.0f) elevado por RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", 
                                address1, RAMContent1, address2, RAMContent2, address3, result);
                break;
        }
        PC++;
    }
}

void printRAM(Machine* machine) {
    printf("  > RAM");
    for (int i=0;i<machine->RAM.size;i++)
        printf("\t\t[%5d] : %f\n", i, machine->RAM.items[i]);
}
