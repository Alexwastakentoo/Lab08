//
// Created by skyle on 06/12/2021.
//

#include "ex01Fn.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../Lab05/StandardInputFn.h"


#define DEBUG


void magicSquare(int n, char* fileName){

    int** msq = NULL, *val = NULL; // represent magic square in vector form
    int index_i = 0, index_j = 0, index_k = 0, sum = (n*((n*n) + 1)/2);

    msq = (int **) malloc(n * sizeof(int*)); // one slot for "sentinel" index
    if(checkMalloc(msq, "[magicSquare]")){
        // freeMem()
        exit(EXIT_FAILURE);
    }



    val = (int *) malloc(n*n * sizeof(int));
    if(checkMalloc(val, "[magicSquare]")){
        // freeMem()
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n*n; i++){
        val[i] = i + 1;
       // printf("val[%d] = %d", i, val[i]); fflush(stdout);
    }

    for(int i = 0; i < n; i++){
        msq[i] = (int*) malloc(n * sizeof(int));
        if(checkMalloc(msq[i], "[magicSquare]")){
            // freeMem()
            exit(EXIT_FAILURE);
        }

    }

#ifdef DEBUG1
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            msq[i][j] = 0;
            printf("msq[%d][%d] = %d @ %p\n", i, j, msq[i][j], &msq[i][j]); fflush(stdout);
        }
    }
    printf("msq @ %p\n", &msq); fflush(stdout);
#endif
    srand(time(NULL));
    randValGen(&val, n);
    magicSquareFill_r4(&msq, &n, &sum, &index_i, &index_j, &val, &index_k);

   // magicSquareFill_r3(&msq, n, (n*((n*n) + 1)/2), index, &val);

    //magicSquareFill_r2(&msq, n, (n*((n*n) + 1)/2), &val);

   // magicSquareFill_r(&msq, n, &val);

   FILE* outputFile =  fopen(fileName, "w");
    if(checkFile(outputFile, "[magicSquare]")){
        // freeMem()
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fprintf(outputFile, "%d ", msq[i][j]);
        }
        fprintf(outputFile,"\n\n");
    }

    fclose(outputFile);


}


void magicSquareFill_r4(int*** mat, int* n, int* sum, int* i, int* j, int** val, int* index){

    int** ptrMat = *mat;
    int* ptrVal = *val;
    int tmpSumH = 0;

    if(*i == *n){
        magicSquareCheck3(mat, *n, *sum, val, i, j);
        if(*i == *n){
            return;
        }
    }

    ptrMat[*i][*j] = ptrVal[*index];

#ifdef DEBUG

    printf("%d ", /*i, j,*/ ptrMat[*i][*j]/*, &ptrMat[i][j]*/); fflush(stdout);
    //  printf("next pointer: %p\n", &ptrMat[i][j+1]); fflush(stdout);
#endif

    if(*j == (*n) - 1){
        for (int k = 0; k < *n; k++) {
            tmpSumH += ptrMat[*i][k]; // i fixed
        }

        if(tmpSumH != *sum){
            printf("\n\n"); fflush(stdout);

            *i = 0, *j = -1, *index = -1;
            randValGen(val, *n);
        }
    }


    if(*j < (*n) - 1){
        (*j)++;
        (*index)++;
       return magicSquareFill_r4(mat, n, sum, i, j, val, index);
    } else{
        printf("\n"); fflush(stdout);
        (*i)++;
        (*j) = 0;
       return magicSquareFill_r4(mat, n, sum, i, j, val, index);
    }


}

void magicSquareCheck3(int*** matrix, int n, int sum, int** val, int* index_i, int* index_j){

    int** ptr = *matrix;
    int tmpSumV = 0, tmpSumH = 0, tmpSumD1 = 0, tmpSumD2 = 0, i, j;

        for( i = 0; i < n; i++){
            for( j = 0; j < n; j++){
                    tmpSumV += ptr[j][i]; // j fixed
                    tmpSumH += ptr[i][j]; // i fixed
            }

            if(tmpSumD2 != sum || tmpSumD1 != sum){
#ifdef DEBUG
                printf("\n"); fflush(stdout);
#endif
                *index_i = 0, *index_j = -1;
                return;
        }
}

    if(tmpSumH != sum || tmpSumV != sum) {
#ifdef DEBUG
        printf("\n"); fflush(stdout);
#endif

    }
    *index_i = 0, *index_j = -1;
    return;
}

void randValGen(int** valArray, int n){
    int temp, randIndex;
    int* array = *valArray;

    for(int i = 0; i < (n*n); i++){
        temp = array[i];
        randIndex = rand() % (n*n);
        array[i] = array[randIndex];
        array[randIndex] = temp;
    }

#ifdef DEBUG
    printf("\n");
    for(int i = 0; i < (n*n); i++){
        printf("val[%d] = %d ", i, array[i]); fflush(stdout);
    }
    printf("\n");
#endif
}



/*int valTaken(int** valArray, int checkVal, int j, int n){
    int* ptr = *valArray;

    if(j >= n){
        return 1;
    }

    if(ptr[checkVal-1] == 1){
        return 1;
    } else{
        ptr[checkVal-1] = 1;
        return 0;
    }
}
*/

/*
void magicSquareCheck_r2(int*** matrix, int* n, int* sum, int* i , int* j, int* tmpSumV, int* tmpSumH, int* tmpSumD1,int* tmpSumD2, int** val){

    int** ptr = *matrix;

    if(*i == *n || !valTaken(val, ptr[*i][*j], *j, *n)){
        *i = 0, *j = 0;
#ifdef DEBUG
        printf("\n"); fflush(stdout);
#endif
        magicSquareFill_r4(matrix, n, sum, i, j, val);
        return;
    }

    if(*j < *n){
        *tmpSumV += ptr[*j][*i]; // j fixed
        *tmpSumH += ptr[*i][*j]; // i fixed
        *tmpSumD1 += ptr[*j][*j];
        *tmpSumD2 += ptr[((*n)-1)- (*j)][*j];

        if(*tmpSumD2 != *sum || *tmpSumD1 != *sum) {

            for (int k = 0; k < ((*n) * (*n))-1; k++) {
                (*val)[k] = 0;
            }

            *tmpSumD2 = 0, *tmpSumD1 = 0, *tmpSumH= 0, *tmpSumV = 0;
            *i = 0, *j = 0;
#ifdef DEBUG
            printf("\n"); fflush(stdout);
#endif
            magicSquareFill_r4(matrix, n, sum, i, j, val);
            return;
        }

        (*j)++;
        magicSquareCheck_r2(matrix, n, sum, i, j, tmpSumV, tmpSumH, tmpSumD1, tmpSumD2, val);
        return;
    }

    if(*tmpSumD2 != *sum || *tmpSumD1 != *sum || *tmpSumH != *sum || *tmpSumV != *sum) {

        for (int k = 0; k < ((*n) * (*n))-1; k++) {
            (*val)[k] = 0;
        }

        *tmpSumD2 = 0, *tmpSumD1 = 0, *tmpSumH= 0, *tmpSumV = 0;
    }

    if(*i < *n){
        (*i)++;
        *j = 0;
        magicSquareCheck_r2(matrix, n, sum, i, j, tmpSumV, tmpSumH,tmpSumD1,tmpSumD2, val);
        return;
    }
}
 */

/*void magicSquareFill_r3(int ** mat, int n, int sum, int i, int** val){

    int** ptr = mat;

    if(i == n * n){
        return;
    }

    srand(1);

#ifdef DEBUG

    printf("*mat[%d] = %d @ %p\n", i, *ptr[0] + i, ptr[i]); fflush(stdout);
    printf("%p\n", ptr[i] + 1); fflush(stdout);
#endif

    *(ptr[0] + i) = (rand() % (n * n)) + 1;
    magicSquareFill_r3(ptr, n, sum, ++i, val);
    magicSquareCheck_r(ptr, n, sum, 0, 0, 0, 0, 0, 0, val);
}

void magicSquareCheck_r(int** matrix, int n, int sum, int i , int j, int tmpSumV, int tmpSumH, int tmpSumD1,int tmpSumD2, int**val){

    if((i * n) + j == n*n || !valTaken(val, *matrix[(i*n)+j]) || !valTaken(val, *matrix[(j*n)+i])
    || !valTaken(val, *matrix[i * (n+1)]) || !valTaken(val, *matrix[(i+1)*(n-1)])){
        return;
    }

    if(i < n){
        tmpSumV += *matrix[(i*n) + j]; // j fixed
        tmpSumH += *matrix[(j*n) + i]; // i should be fixed --> use j instead
        tmpSumD1 += *matrix[i * (n+1)];
        tmpSumD2 += *matrix[(i+1)*(n-1)];
        i++;
        magicSquareCheck_r(matrix, n, sum, i, j, tmpSumV, tmpSumH, tmpSumD1, tmpSumD2, val);
    }
    if(j < n){
        j++;
        magicSquareCheck_r(matrix, n, sum, i, j, tmpSumV, tmpSumH, tmpSumD1, tmpSumD2, val);
        return;
    }

    if(tmpSumD2 != sum || tmpSumD1 != sum || tmpSumH != sum || tmpSumV != sum){
        magicSquareFill_r3(matrix, n, sum, 0, val);
    }
}
















/*
void magicSquareFill_r2(int** mat,int n, int sum, int** val){

    int tmpVal;
    srand(1);

    if(mat == &mat[n*n]){
        return;
    }

    tmpVal = (rand() % (n*n)) +1;
    if(!valTaken(*val, tmpVal) && magicVal(*mat, findIndex(*mat), sum)){
        **mat = tmpVal;
        (*mat)++;
        magicSquareFill_r2(mat, n, sum, val);
    } else{
        magicSquareFill_r2(mat, n, sum, val);
    }

}




int magicVal(int** mat, int valIndex, int sum){



}

int findIndex(int* valPtr){
    int i = 0;
    while(*valPtr != -1){
     i++;

     valPtr--;
    }

    return i;
}
*/
/*
void magicSquareFill_r(int** matrix, int n, int** val){

    int sum = n*((n*n) + 1)/2; // optimal sum
    int tmpSumE, tmpSumS, rem, tmp = 0;

    if(**matrix == *matrix[n*(n-1)]){
        // end condition
    }

    (**matrix)++; // increment central node value (we move along the first clm)

    rem = sum - **matrix;

    while(!valTaken()){

    }

    tmpSumS = 0, tmpSumE = 0;
    for(int i = 0; i < n-1; i++){
        tmpSumE += *matrix[i];
        tmpSumS += *matrix[i*n];
    }

    if(tmpSumE != sum || tmpSumS != sum){ // either line is wrong
        magicSquareFill_r();
    }

   *matrix += n; // move to next element in first clm

}

int valTaken(int* valArray, int checkVal){
    for(int i = 0; valArray[i] != checkVal )
}*/