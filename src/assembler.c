#include "mychine.h"
char row[20];//Array current command line
int *rows;

int regcmp(char *reg);

int *compile(FILE *script, int i){
    int f_rows[i];
    int curr_instr = 0;
    int curr_row = 0;
    int *commands = (int *)malloc(i*sizeof(int));
    char *code_line = fgets(row,20,script);
    while(!feof(script))//until end of file
    {
        f_rows[curr_row] = curr_instr;
        curr_row++;
        
        if(strcmp(code_line,"\n")){
            char *instr = strtok(row," \n");
            if(strncmp(instr,"HLT",3)==0)
            { commands[curr_instr] = HLT; }
            else if(strncmp(instr,"PSH",3)==0)
            { commands[curr_instr] = PSH; }
            else if(strncmp(instr,"ADD",3)==0)
            { commands[curr_instr] = ADD; }
            else if(strncmp(instr,"SUB",3)==0)
            { commands[curr_instr] = SUB; }
            else if(strncmp(instr,"MUL",3)==0)
            { commands[curr_instr] = MUL; }
            else if(strncmp(instr,"DIV",3)==0)
            { commands[curr_instr] = DIV; }
            else if(strncmp(instr,"POP",3)==0)
            { commands[curr_instr] = POP; }
            else if(strncmp(instr,"SET",3)==0)
            {
                commands[curr_instr] = SET;
                curr_instr++;
                instr = strtok(NULL," \n");
                commands[curr_instr] = regcmp(instr);
            }
            else if(!strcmp(instr,"MOV"))
            {
                commands[curr_instr] = MOV;
                curr_instr++;
                instr = strtok(NULL," \n");
                commands[curr_instr] = regcmp(instr);

                curr_instr++;
                instr = strtok(NULL," \n");
                commands[curr_instr] = regcmp(instr);
            }
            else if(!strcmp(instr,"JMP"))
            { commands[curr_instr] = JMP; }
            else{
                commands[curr_instr] = NUM_OF_INSTRUCTIONS;
            }
            curr_instr++;
            instr = strtok(NULL," \n");
            while(instr != NULL){
                commands[curr_instr] = atoi(instr);
                instr = strtok(NULL," \n");
                curr_instr++;
            }
        }
        code_line = fgets(row,20,script);
    }
    rows = f_rows;
    return commands;
}

int regcmp(char *reg){
    if(strncmp(reg,"A",1)==0)
    { return A; }
    else if(strncmp(reg,"B",1)==0)
    { return B; }
    else if(strncmp(reg,"C",1)==0)
    { return C; }
    else if(strncmp(reg,"D",1)==0)
    { return D; }
    else if(strncmp(reg,"E",1)==0)
    { return E; }
    else if(strncmp(reg,"F",1)==0)
    { return F; }
    else if(strncmp(reg,"PC",2)==0)
    { return PC; }
    else if(strncmp(reg,"SP",2)==0)
    { return SP; }
    
    return 0;
}