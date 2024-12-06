#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

int parseStackForMult(char* a, int len);
int parseStackForEnableDisable(char* a, int len);

int main(){
    FILE* fptr = fopen("data.txt", "r");

    if(!fptr){
        return 1;
    }
   
    int total = 0;
    int enabled = 1;
    int tempEnabled;
    char* stackBase = malloc(sizeof(char)*200);
    int stackPointer = 0;
    char c;

    while((c = fgetc(fptr)) != EOF){
            if(stackPointer >= 100){
                stackPointer = 0;
            }
            else{
                *(stackBase + stackPointer) = c;
                stackPointer++;
            }
            if(c == ')'){

                if(enabled == 1){
                   
                    total += parseStackForMult(stackBase, stackPointer);
                }

                tempEnabled = parseStackForEnableDisable(stackBase, stackPointer);
                enabled = (tempEnabled != 0) ? tempEnabled : enabled;

                memset(stackBase, 0,200);
                stackPointer = 0;
            }
    }
    printf("%d", total);
    return 0;
}

int parseStackForMult(char* a, int len){
    regex_t regex;
    regmatch_t pmatch[1];
    const char* pattern = "mul\\([0-9]+,[0-9]+\\)";
    int num1, num2;
    char closeParen, comma, openParen, m, u, l;

    if(regcomp(&regex, pattern, REG_EXTENDED)){
        return 0;
    }
    if(regexec(&regex, a, 1, pmatch, 0)){
        return 0;
    }
    sscanf(&a[pmatch[0].rm_so], "%c%c%c%c%d%c%d", &m, &u, &l, &openParen, &num1, &comma, &num2 );

    return num1 * num2;
}

int parseStackForEnableDisable(char* a, int len){
    regex_t regex;
    regmatch_t pmatch[1];
    const char* patternDo = "do\\(\\)";
    const char* patternDont = "don't\\(\\)";

    regcomp(&regex, patternDo, REG_EXTENDED);
    if(regexec(&regex, a, 1, pmatch, 0 ) == 0){
        return 1;
    }

    regcomp(&regex, patternDont, REG_EXTENDED);
    if(regexec(&regex, a, 1, pmatch, 0) == 0){
        return -1;
    }

    return 0;
}
