#include "global.h"

int main() {

    init();
    lookahead = lexan();

    printf("\nASSUME CS:CODE,DS:DATA\n");
    printf("CODE SEGMENT\n");
    printf("EXP PROC\n");


    Expression();

    printf("EXP ENDP\n");
    printf("CODE    ENDS\n");
    printf("DATA    SEGMENT\n\n");

    //accounts for some of the lowercase english characters (use only these when testing)

    printf("a       DW  ?\n");
    printf("b       DW  ?\n");
    printf("p       DW  ?\n");
    printf("c       DW  ?\n");
    printf("x       DW  ?\n");
    printf("y       DW  ?\n");
    printf("z       DW  ?\n\n");

    printf("DATA    ENDS\n");
    printf("        END EXP\n");

    exit(0);
}