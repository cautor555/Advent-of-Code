#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int checkSurrounding(char *lines[200], int x, int y, char expected, int xDirection, int yDirection, int lineSize, int numLines);

int main(){
    FILE* fptr = fopen("data.txt", "r");

    if(!fptr){
        return 1;
    }

    int total = 0;
    char c;
    size_t len = 0;
    char *lines[200];
    int i = 0;

    int linecount = 0;
    int lineLength = 140;
    char* currentLine;

    while(lineLength != EOF){
        currentLine = malloc(sizeof(char)*200);
        
        if(getline(&currentLine, &len, fptr) == EOF){
            free(currentLine);
            break;
        }
        
        lines[i] = malloc(lineLength);
        lines[i] = currentLine;
        i++;
    }
    linecount = i;

    for(i = 1; i<linecount-1; i++){
        int j = 0;
        c = *(lines[i]+ j);

        while(c != '\0'){
            if(c == 'A'){
            char diagonal1[] = {*(lines[i-1] + j-1), *(lines[i+1] + j+1), '\0'};
            char diagonal2[] = {*(lines[i+1] + j-1), *(lines[i-1] + j+1), '\0'};

                if((!strcmp(diagonal1, "MS") || !strcmp(diagonal1, "SM")) 
                && (!strcmp(diagonal2, "MS") || !strcmp(diagonal2, "SM")))
                {
                    total++;
                }
            }

            c = *(lines[i]+ ++j);
        }
    }
    for(i = 0; i< linecount; i++){
        free(lines[i]);
    }

    printf("%d", total);
    return 0;
}