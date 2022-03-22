#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int N;

//Multiply matrix A and a transposed matrix B, assign result to matrix C
void mat_multiply_cached(int** A, int** B, int** C){
    int res;
    int** BTransposed = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        BTransposed[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++){
            BTransposed[i][j] = B[j][i];            
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            res = 0;
            for(int k = 0; k < N; k++){
                res += A[i][k]*B[j][k];
            }
            C[i][j] = res;
        }
    }

    //Free transposed matrix
    for(int i = 0; i < N; i++){
        free(BTransposed[i]);
    }
    free(BTransposed);

}

int main(){
    srand(time(0));

    printf("Input matrix size: ");
    scanf("%d", &N);                                        //input matrix size

    int** arrA = (int**)malloc(N * sizeof(int*));
    int** arrB = (int**)malloc(N * sizeof(int*));
    int** arrC = (int**)malloc(N * sizeof(int*));

    for(int i = 0; i < N; i++){
        arrA[i] = (int*)malloc(N * sizeof(int));            //ArrA and ArrB are factors with values ranging from -5 to 5
        arrB[i] = (int*)malloc(N * sizeof(int));            //ArrC is the resultant that is initially a null matrix
        arrC[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++){
            arrA[i][j] = (rand()%10)-5;            
            arrB[i][j] = (rand()%10)-5;
            arrC[i][j] = 0;
        }
    }

    //set up timer and run function
    clock_t start = clock();
    mat_multiply_cached(arrA, arrB, arrC);
    clock_t end = clock();
	double t = (double)(end - start) / CLOCKS_PER_SEC;

    /*
    for(int i = 0; i < N; i++){               //show results
        for (int j = 0; j < N; j++){
            printf("%3i ",arrC[i][j]);
        }
        printf("\n");
    }
    */

    printf("Process took %f seconds\n",t);
    for(int i = 0; i < N; i++){
        free(arrA[i]);
        free(arrB[i]);
        free(arrC[i]);
    }
    free(arrA);
    free(arrB);
    free(arrC);
    return 0;
}