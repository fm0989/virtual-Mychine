Virtual Mychine
Stack based machine
General purpose registers : A, B, C, D, E and F
Program counter register : PC
Stack pointer register : SP
9 operations : 
    - HLT > halt the machine
    - PSH x > push value on the stack
    - ADD > add last two numbers of the stack
    - SUB > subtraction between last two numbers of the stack
    - MUL > multiplication between last two numbers of the stack
    - DIV > division between last two numbers of the stack
    - POP > remove last value from the stack and print it in the console
    - SET reg x > set the value x to the given register
    - MOV reg_a reg_b > set the value of register b as register a
    - JMP pos_x > move the machine execution to the given instruction line of the program (starting from 0)
