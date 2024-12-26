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
    
    while(lineLength != EOF){
        char* currentLine = malloc(sizeof(char)*200);

        if(getline(&currentLine, &len, fptr) == EOF){
            break;
        }
       
        lines[i] = realloc(currentLine, lineLength);
        i++;
    }
    linecount = i;

    for(i = 0; i<linecount; i++){
        int j = 0;
        c = *(lines[i]+ j);

        while(c != '\0'){
            if(c == 'X'){
                total += checkSurrounding(lines, j, i, 'X', 0, -1, lineLength, linecount)
                + checkSurrounding(lines, j, i, 'X', 0, 1, lineLength, linecount)
                + checkSurrounding(lines, j, i, 'X', -1, 0, lineLength, linecount)
                + checkSurrounding(lines, j, i, 'X', 1, 0, lineLength, linecount)
                + checkSurrounding(lines, j, i, 'X', 1, 1, lineLength, linecount)
                + checkSurrounding(lines, j, i, 'X', -1, -1, lineLength, linecount)
                + checkSurrounding(lines, j, i, 'X', 1, -1, lineLength, linecount)
                + checkSurrounding(lines, j, i, 'X', -1, 1, lineLength, linecount);
            }

            c = *(lines[i]+ ++j);
        }
    }

    for(i = 0; i<linecount; i++){
        free(lines[i]);
    }

    printf("\n%d", total);
    return 0;
}

int checkSurrounding(char *lines[200], int x, int y, char expected, int xDirection, int yDirection, int lineSize, int numLines){

    if(x >= lineSize || y >= numLines)
    {
        return 0;
    }
   
    char current = *(lines[y] + x);
    char next;

    if(current == expected){

        switch (current)
        {
            case 'S':
                return 1;
            case 'M':
                next = 'A';        
                break;
            case 'X':
                next = 'M';        
                break;
            case 'A':
                next = 'S';        
                break;
        }

        return checkSurrounding(lines, x+xDirection, y+yDirection, next, xDirection, yDirection, lineSize, numLines);
    }
    return 0;
}
