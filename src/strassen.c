#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int N;                  //N has to be a power of 2

/*Subtract two matrices
Requirements: 
    two square matrices of the same size
    matrix size
*/
int** add_matrix(int** A, int** B, int size){
    int** res = (int**)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) res[i] = (int*)malloc(size * sizeof(int)); 
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            res[i][j] = A[i][j] + B[i][j];
        }
    }
    return res;
}  

/*Add two matrices
Requirements: 
    two square matrices of the same size
    matrix size
*/
int** sub_matrix(int** A, int**B, int size){
    int** res = (int**)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) res[i] = (int*)malloc(size * sizeof(int)); 

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            res[i][j] = A[i][j] - B[i][j];
        }
    }

    return res;
}  

/*Multiply two matrices using the Strassen Algorithm
Requirements: 
    two square matrices of the same size
    matrix size
*/
int** mul_matrix(int** A, int** B, int size){
    int** res = (int**)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) res[i] = (int*)malloc(size * sizeof(int));
    if(size == 1){                              //base case for recursion
        res[0][0] = A[0][0] * B[0][0];
        return res;
    }

    int newSize = size/2;

    int** A0 = (int**)malloc(newSize * sizeof(int*));
    int** A1 = (int**)malloc(newSize * sizeof(int*));
    int** A2 = (int**)malloc(newSize * sizeof(int*));
    int** A3 = (int**)malloc(newSize * sizeof(int*));
    int** B0 = (int**)malloc(newSize * sizeof(int*));
    int** B1 = (int**)malloc(newSize * sizeof(int*));
    int** B2 = (int**)malloc(newSize * sizeof(int*));
    int** B3 = (int**)malloc(newSize * sizeof(int*));
    for(int i = 0; i < newSize; i++){
        A0[i] = (int*)malloc(newSize * sizeof(int));
        A1[i] = (int*)malloc(newSize * sizeof(int));
        A2[i] = (int*)malloc(newSize * sizeof(int));
        A3[i] = (int*)malloc(newSize * sizeof(int));
        B0[i] = (int*)malloc(newSize * sizeof(int));
        B1[i] = (int*)malloc(newSize * sizeof(int));
        B2[i] = (int*)malloc(newSize * sizeof(int));
        B3[i] = (int*)malloc(newSize * sizeof(int));
    }
    
    for(int i = 0; i < newSize; i++){                            //split matrices into quadrants
        for(int j = 0; j < newSize; j++){                        //each of size/2 by size/2
            A0[i][j] = A[i][j];
            A1[i][j] = A[i][(newSize) + j];
            A2[i][j] = A[(newSize) + i][j];
            A3[i][j] = A[(newSize) + i][(newSize) + j];
            B0[i][j] = B[i][j];
            B1[i][j] = B[i][(newSize) + j];
            B2[i][j] = B[(newSize) + i][j];
            B3[i][j] = B[(newSize) + i][(newSize) + j];
        }
    }
    
    int** M0 = mul_matrix(add_matrix(A0, A3, newSize), add_matrix(B0, B3, newSize), newSize);
    int** M1 = mul_matrix(add_matrix(A2, A3, newSize), B0, newSize);
    int** M2 = mul_matrix(A0, sub_matrix(B1, B3, newSize), newSize);
    int** M3 = mul_matrix(A3, sub_matrix(B2, B0, newSize), newSize);
    int** M4 = mul_matrix(add_matrix(A0, A1, newSize), B3, newSize);
    int** M5 = mul_matrix(sub_matrix(A2, A0, newSize), add_matrix(B0, B1, newSize), newSize);
    int** M6 = mul_matrix(sub_matrix(A1, A3, newSize), add_matrix(B2, B3, newSize), newSize);

    int** Q0 = sub_matrix(add_matrix(M0, M3, newSize), add_matrix(M4, M6, newSize), newSize);
    int** Q1 = add_matrix(M2, M4, newSize);
    int** Q2 = add_matrix(M1, M3, newSize);
    int** Q3 = add_matrix(sub_matrix(M0, M1, newSize), add_matrix(M2, M6, newSize), newSize);
    for(int i = 0; i < newSize; i++){                            //split matrices into quadrants
        for(int j = 0; j < newSize; j++){                        //each of size/2 by size/2
            res[i][j] = Q0[i][j];
            res[i][newSize + j] = Q1[i][j];
            res[newSize + i][j] = Q2[i][j];
            res[newSize + i][newSize + j] = Q3[i][j];
        }
    }
    for(int i = 0; i < newSize; i++){
        free(A0[i]);
        free(A1[i]);
        free(A2[i]);
        free(A3[i]);
        free(B0[i]);
        free(B1[i]);
        free(B2[i]);
        free(B3[i]);
    }
    free(A0);
    free(A1);
    free(A2);
    free(A3);
    free(B0);
    free(B1);
    free(B2);
    free(B3);
    
    return res;
} 

//Multiply matrix A and a transposed matrix B, assign result to matrix C
void** mat_multiply_strassen(int** A, int** B, int** C){
    int** res = mul_matrix(A, B, N);
    for(int i = 0; i < N; i++){               //show results
        for (int j = 0; j < N; j++){
            C[i][j] = res[i][j];
        }
    }
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
    mat_multiply_strassen(arrA, arrB, arrC);
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