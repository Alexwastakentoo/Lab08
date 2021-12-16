#include <stdio.h>

#include "../../Lab05/StandardInputFn.h"
#include "ex01Fn.h"


int main(int argc, char** argv) {

    int n = 0;
    FILE *outputFile = NULL;

    checkargc(argc, 2, argv[0]);

    while(!n){
        printf("Input the magic square's size: "); fflush(stdout);
        if(scanf("%d", &n) == EOF){
            fprintf(stderr,"\nError size must be integer!\n"); fflush(stdout);
        }
    }


    magicSquare(n, argv[1]);

    return 0;
}
