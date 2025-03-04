#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lookahead;
int tokenval;
extern struct entry symtable[SYMMAX];

void Expression(void);
void MoreTerms(void);
void Term(void);
void MoreFactors(void);
void Factor(void);
void match(int tok);

void Expression(void) {
    Term();
    MoreTerms();
}

void MoreTerms(void) {
    while (lookahead == '+' || lookahead == '-') {
        int op = lookahead;
        match(lookahead);
        printf("PUSH AX\n");
        Term();
        printf("POP BX\n");
        if (op == '+') {
            printf("ADD AX, BX\n");
        }
        else {
            printf("SUB BX, AX\n");
            printf("MOV AX, BX\n");
        }
    }
}

void Term(void) {
    Factor();
    MoreFactors();
}

void MoreFactors(void) {
    while (lookahead == '*' || lookahead == '/') {
        int op = lookahead;
        match(lookahead);
        printf("PUSH AX\n");
        Factor();
        printf("POP BX\n");
        if (op == '*') {
            printf("IMUL BX\n");
        }
        else {
            printf("MOV DX, 0\n");  // Clear DX for division
            printf("XCHG AX, BX\n"); // Exchange BX and AX
            printf("IDIV BX\n");
        }
    }
}

void Factor(void) {
    if (lookahead == '(') {
        match('(');
        Expression();
        match(')');
    }
    else if (lookahead == ID) {
        printf("MOV AX, %s\n", symtable[tokenval].lexptr);
        match(ID);
    }
    else if (lookahead == NUM) {
        printf("MOV AX, %d\n", tokenval);
        match(NUM);
    }
    else {
        error("Unexpected token in Factor");
    }
}

void match(int tok) {
    if (tok == lookahead) {
        lookahead = lexan();
    }
    else {
        error("Syntax error: token mismatch");
    }
}