#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isIncreasing(int* a, int size, int levelIgnored);
int isDecreasing(int* a, int size, int levelIgnored);
int* copyArrayMinusElement(int* a, int removeIndex, int size);

int main(){
    FILE* fptr = fopen("data.txt", "r");

    if(!fptr){
        return 1;
    }
   
    int safecount = 0;
    char* line = malloc(sizeof(char)*20);
    int* lineAsInt;
    size_t len = 0;
   
    while(getline(&line, &len, fptr) != EOF){
        int i = 0;

        lineAsInt = malloc(sizeof(int)*10);
        char* token = strtok(line, " ");

        while(token!= NULL){
            *(lineAsInt+i) = atoi(token);

            token = strtok(NULL, " ");
            i++;
        }

        if(isIncreasing(lineAsInt, i, 0) == 1
        || isDecreasing(lineAsInt, i, 0) == 1){
            safecount++;
        }
    }
    free(line);
    free(lineAsInt);
    printf("%d\n", safecount);
    return 0;
}

int isIncreasing(int* a, int size, int levelIgnored){
    int current = *a;
    int previous;

    for(int i = 1; i<size; i++){
        previous = current;
        current = *(a+i);

        if(current - previous > 3 || current - previous < 1){
             if(levelIgnored == 1){
                free(a);
                return 0;
            }
            return(isIncreasing(copyArrayMinusElement(a, i-1, size), size-1, 1)
            || isIncreasing(copyArrayMinusElement(a, i, size), size-1, 1));
        }
    }
    return 1;
}

int isDecreasing(int* a, int size, int levelIgnored){
    int previous;
    int current = *a;

    for(int i = 1; i<size; i++){
        previous = current;
        current = *(a+i);

        if(previous - current > 3 || previous - current < 1){
             if(levelIgnored == 1){
                free(a);
                return 0;
            }
            return(isDecreasing(copyArrayMinusElement(a, i-1, size), size-1, 1)
            || isDecreasing(copyArrayMinusElement(a, i, size), size-1, 1));
        }
    }
    return 1;
}

int* copyArrayMinusElement(int* a, int removeIndex, int size){
    int i = 0;
    int j = 0;
    int* copy = malloc(sizeof(int)*(size-1));
    
    while(i < size){
        if(i != removeIndex){
            *(copy+j) = *(a+i);
            j++;
        }
        i++;
    }
    return copy;
}
