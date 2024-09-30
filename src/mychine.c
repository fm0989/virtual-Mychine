#include "mychine.h"
int stack[256];
int registers[NUM_OF_REGISTERS] = {0,0,0,0,0,0,0,-1};
bool running = true;
//TODO add error check

void eval(int instr,int *program);
int get_line_PC(int *r,int counter);
void message_out(int *r,int counter,char *msg,bool error);

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
        printf("### MYCHINE V0.2 INIT ###\n###   PROGRAM START   ###\n#\n");
        while(running){
            eval(program[registers[PC]],program);
            registers[PC]++;
        }
    }else{
        printf("Launch the executable with the path to a 'Mychine program' as argument\n");
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
            if(registers[SP] == 255){
                message_out(rows,registers[PC],"Stack is full",false);
                return;
            }
            registers[SP]++;
            stack[registers[SP]] = program[++registers[PC]];
            break;
        case POP:// print last value in the stack
            if(registers[SP] == -1){
                message_out(rows,registers[PC],"Stack is empty",false);
                return;
            }
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
            if(reg < 0 || reg > NUM_OF_REGISTERS){
                message_out(rows,registers[PC],"Unknown register",false);
                return;
            }
            //check PC, SP mismatch
            if(reg == PC){
                int x = get_line_PC(rows,val);
                if(x==-1){
                    message_out(rows,registers[PC],"Program counter value set error",false);
                    return;
                }
                val = x;
            }
            if(reg == SP && (val<0 || val > registers[SP])){
                message_out(rows,registers[PC],"Stack pointer value out of bound",true);
                return;
            }
            registers[reg] = val;
            break;
        case MOV:// copy value of register 'a' to 'b'
            registers[PC]++;
            reg_A = program[registers[PC]++];
            reg_B = program[registers[PC]];
            //check PC, SP mismatch
            if(reg_B == PC){
                int x = get_line_PC(rows,registers[reg_A]);
                if(x==-1){
                    message_out(rows,registers[PC],"Program counter value set error",false);
                    return;
                }
                registers[reg_A] = x;
            }
            if(reg_B == SP && (registers[reg_A]<0 || registers[reg_A] > registers[SP])){
                message_out(rows,registers[PC],"Stack pointer value out of bound",true);
                return;
            }
            
            registers[reg_B] = registers[reg_A];
            break;
        case JMP:// goto x line of code
            registers[PC]++;
            registers[PC] = rows[program[registers[PC]]];
            registers[PC]--;// balancing PC increase
            break;
        default:
            printf("###    FATAL ERROR    ###\n###     SHUT DOWN     ###\n");
            running=false;
        break;
    }
}

int get_line_PC(int *r, int counter){
    int i;
    for(i=0;i<256;i++){
        if(r[i] > counter){
            return r[i-1]-1;// balancing PC increase
        }
        if(r[i] == counter){
            return r[i]-1;// balancing PC increase
        }
    }
    return -1;
}

void message_out(int *r,int counter,char *msg,bool error){
    int x;
    int i;
    for(i=0;i<256;i++){
        if(r[i] > counter){
            x = i;
            break;
        }
    }
    if(error){
    printf(ANSI_COLOR_RED "E:%d %s\n" ANSI_COLOR_RESET,x,msg);
    }else{
    printf(ANSI_COLOR_YELLOW "W:%d %s\n" ANSI_COLOR_RESET,x,msg);
    }
}