#include <stdio.h>
#include "absyn.h"
#include "log.h"
#include "pabsyn.h"
#define INITINDENTNUM 4

extern int yyparse(void);
extern struct Exp *absynRoot;

void parse(char *fileName)
{
    LogReset(fileName);
    if(!yyparse()) {
        fprintf(stdout,"Parsing successful!\n");
    } else {
        fprintf(stdout,"Parsing failed\n");
    }
}

int main(int argc, char **argv)
{
    char *fileName;

    fileName = "cowOutput";
    parse(fileName);
    PExp(stdout, absynRoot, INITINDENTNUM);

    return 0;
}
