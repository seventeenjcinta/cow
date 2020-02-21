#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "util.h"
#include "log.h"

struct IntList
{
    int index;
    struct IntList *prev;
};

int /* bool */ hasError = 0; 
static char *fileName = "";
static int lineNum = 1;
static struct IntList *linePos = NULL;
int LogTokenPos = 0;
extern FILE *yyin;

static struct IntList *newIntList(int index, struct IntList *prev)
{
    struct IntList *result;

    result = malloc(sizeof(struct IntList));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> index = index;
    result -> prev = prev;

    return result;
}

void LogNewLine()
{
    lineNum ++;
    linePos = newIntList(LogTokenPos, linePos);
}

void LogError(int pos, char *message, ...)
{
    va_list ap;
    int num;
    struct IntList *intList;

    num = lineNum;
    intList = linePos;
    while(intList && intList -> index >= pos) {
        intList = intList -> prev;
        num --;
    }
    if(fileName) {
        fprintf(stderr, "%s: ", fileName);
    }
    if(intList) {
        fprintf(stderr, "%d.%d: ", num, pos - intList -> index);
    }
    va_start(ap, message);
    vfprintf(stderr, message, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}

void LogReset(char *newFileName)
{
    hasError = 0;
    fileName = newFileName;
    lineNum = 1;
    linePos = newIntList(0, NULL);
    yyin = fopen(newFileName, "r");
    if(!yyin) {
        LogError(0, "open failed!");
        exit(1);
    }
}

