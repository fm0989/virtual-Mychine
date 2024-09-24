#include "mychine.h"
int stack[256];
int registers[NUM_OF_REGISTERS] = {0,0,0,0,0,0,0,-1};
bool running = true;
//TODO add error check

void eval(int instr,int *program);

int main (int argc, char *argv[]){
    if(argc == 2){
        //parse the program
        FILE *mychine_f;
        mychine_f=fopen(argv[1],"r");
        int *program = compile(mychine_f,256);
        /*DEBUG
        int loop;
        for(loop = 0; loop < 256; loop++)
            printf("%d ", program[loop]);
        */
        printf("### MYCHINE V0.1 INIT ###\n###   PROGRAM START   ###\n#\n");
        while(running){
            eval(program[registers[PC]],program);
            registers[PC]++;
        }
    }
    return 0;
}

void eval(int instr,int *program){
    int val_A,val_B,reg_A,reg_B;
    switch (instr){
        case HLT:// stop the machine
        printf("#\n###    PROGRAM END    ###\n");
            running=false;
            break;
        case PSH:// push a value in the stack
            registers[SP]++;
            stack[registers[SP]] = program[++registers[PC]];
            break;
        case POP:// print last value in the stack
            int val_pop = stack[registers[SP]];
            printf("# Value out %d\n",val_pop);
            registers[SP]--;
            break;
        case ADD:// addition op
            val_A = stack[registers[SP]--];
            val_B = stack[registers[SP]];
            stack[registers[SP]] = val_A + val_B;
            break;
        case SUB:// subtraction op
             val_A = stack[registers[SP]--];
             val_B = stack[registers[SP]];
            stack[registers[SP]] = val_B - val_A;
            break;
        case MUL:// multiplication op
             val_A = stack[registers[SP]--];
             val_B = stack[registers[SP]];
            stack[registers[SP]] = val_A * val_B;
            break;
        case DIV:// division op
             val_A = stack[registers[SP]--];
             val_B = stack[registers[SP]];
            stack[registers[SP]] = (int)round(val_B / val_A);
            break;
        case SET:// set value of a register
            registers[PC]++;
            int reg = program[registers[PC]++];
            int val = program[registers[PC]];
            //TODO check PC, SP mismatch
            registers[reg] = val;
            break;
        case MOV:// copy value of register 'a' to 'b'
            registers[PC]++;
            reg_A = program[registers[PC]++];
            reg_B = program[registers[PC]];
            //TODO check PC, SP mismatch
            registers[reg_B] = registers[reg_A];
            break;
        case JMP:// goto x line of code
            registers[PC]++;
            registers[PC] = rows[program[registers[PC]]];
            registers[PC]--;
            break;
        default:
            printf("###    FATAL ERROR    ###\n###     SHUT DOWN     ###\n");
            running=false;
        break;
    }
}