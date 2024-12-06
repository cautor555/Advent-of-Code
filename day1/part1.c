#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int totalDiff = 0;
    FILE* fptr = fopen("data.txt", "r");

    if(!fptr){
        return 1;
    }
    
    int* ids = malloc(sizeof(int)*10000);
    int *idsStart = ids;
    int i = 0;
    fscanf(fptr, "%d", &(*(idsStart+i)));
    while(!feof(fptr)){
        i++;
        fscanf(fptr, "%d", &(*(idsStart+i)));
    }

    int length = ++i;
    i = 0;

    fclose(fptr);

    ids = realloc(ids, sizeof(int)*length);
    int* idsLeft = malloc(sizeof(int)*length/2);
    int* idsRight = malloc(sizeof(int)*length/2);

    while(i< length){
        if(i%2 == 0){
            *(idsLeft + i/2) = *(ids+i);
        }
        else{
            *(idsRight + i/2) = *(ids+i);
        }
        i++;
    }

    qsort(idsLeft, i/2, sizeof(int), compare);
    qsort(idsRight, i/2, sizeof(int), compare);

    i = 0;   
    while(i<length/2){
        printf("%d %d\n", *(idsLeft + i), *(idsRight + i));
        totalDiff+= abs(*(idsLeft + i) - *(idsRight + i));
        i++;
    }
    printf("%d\n", totalDiff);
    free(ids);
    free(idsLeft);
    free(idsRight);
}