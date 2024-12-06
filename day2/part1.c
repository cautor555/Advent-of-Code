#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isIncreasing(int* a, int size);
int isDecreasing(int* a, int size);

int main(){
    FILE* fptr = fopen("data.txt", "r");


    if(!fptr){
        return 1;
    }
   
    int safecount = 0;
    char* line = malloc(sizeof(char)*20);
    int n;
    size_t len = 0;
    
    while(getline(&line, &len, fptr) != EOF){
        int i = 0;

        int* lineAsInt = malloc(sizeof(int)*10);
        char* token = strtok(line, " ");

        while(token!= NULL){
            *(lineAsInt+i) = atoi(token);

            token = strtok(NULL, " ");
            i++;
        }

        if(isIncreasing(lineAsInt, i) == 1
        || isDecreasing(lineAsInt, i) == 1){
            safecount++;
        }
    }
    printf("%d\n", safecount);
    return 1;
}

int isIncreasing(int* a, int size){
    int current = *a;
    int previous;


    for(int i = 1; i<size; i++){
        previous = current;
        current = *(a+i);


        if(current - previous > 3 || current - previous < 1){
            return 0;
        }
    }
    return 1;
}
int isDecreasing(int* a, int size){
    int previous;
    int current = *a;

    for(int i = 1; i<size; i++){
        previous = current;
        current = *(a+i);

        if(previous - current > 3 || previous - current < 1){
            return 0;
        }
    }
    return 1;
}