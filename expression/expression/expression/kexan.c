#include "global.h"

char lexbuf[BSIZE];
extern int tokenval = NONE;
extern struct entry symtable[SYMMAX];
int lineno = 1;
int lexan() {
    int t;
    while (1) {
        int t = getchar();
        if (isdigit(t)) {
            ungetc(t, stdin);
            scanf_s("%d", &tokenval);
            return NUM;
        }
        else if (isalpha(t)) {
            int p, b = 0;
            while (isalnum(t)) {
                lexbuf[b] = t;
                t = getchar();
                b = b + 1;
                if (b == BSIZE)
                    error("compiler error");
            }
            lexbuf[b] = EOS;
            if (t != EOF)
                ungetc(t, stdin);
            p = lookup(lexbuf);
            if (p == 0)
                p = insert(lexbuf, ID);
            tokenval = p;
            return symtable[p].token;
        }
        else if (t == EOF) {
            return DONE;
        }
        else {
            tokenval = NONE;
            return t;
        }
    }
}
