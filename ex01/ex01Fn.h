//
// Created by skyle on 06/12/2021.
//

#ifndef LAB08_EX01FN_H
#define LAB08_EX01FN_H

#include <stdio.h>

void magicSquare(int n, char* outputFile);

//void magicSquareFill_r(int** matrix, int n, int** val);
//void magicSquareFill_r2(int** matrix, int n, int sum, int** val);

//int magicVal(int** valPtr,int index ,int sum);
//int findIndex(int* valPtr);

//int valTaken(int** valArray, int checkVal, int j, int n);
//void magicSquareFill_r3(int ** matrix, int n, int sum, int i, int** val);

//void magicSquareCheck_r(int** matrix, int n, int sum, int i , int j, int tmpSumV, int tmpSumH, int tmpSumD1,int tmpSumD2, int** val);

//void magicSquareCheck_r2(int*** matrix, int* n, int* sum, int* i , int* j, int* tmpSumV, int* tmpSumH, int* tmpSumD1,int* tmpSumD2, int** val);
void magicSquareFill_r4(int*** msq, int* n, int* sum, int* i, int* j, int** val, int* index);
void externalFill(int*** msq, int* n, int* sum, int* i, int* j, int** val);
void magicSquareCheck3(int*** matrix, int n, int sum, int** val, int* i, int* j);

void randValGen(int** valArray, int n);


#endif //LAB08_EX01FN_H
