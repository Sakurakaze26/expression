#include "global.h"
extern int lineno;

void error(m) char* m;
{
    fprintf(stderr, "line %d: %s\n", lineno, m);
    exit(1);
}

