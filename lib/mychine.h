#ifndef MYCHINE_H
#define MYCHINE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

extern int *compile(FILE *s, int i);

extern int *rows;

typedef enum {
    HLT,
    PSH,
    ADD,
    SUB,
    MUL,
    DIV,
    POP,
    SET,
    MOV,
    JMP,
    NUM_OF_INSTRUCTIONS
} InstructionSet;

typedef enum {
    A, B, C, D, E, F, PC, SP,
    NUM_OF_REGISTERS
} Registers;
#endif