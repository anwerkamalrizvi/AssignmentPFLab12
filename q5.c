/*
Create a program that dynamically allocates memory for a sparse matrix in compressed form (row,
column, value). Perform addition or multiplication of two such matrices.*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col, val;
} SparseElement;

typedef struct {
    int rows, cols, nz;
    SparseElement* elements;
} SparseMatrix;

SparseMatrix createMatrix(int rows, int cols, int nz) {
    SparseMatrix sm = {rows, cols, nz, malloc(nz * sizeof(SparseElement))};
    return sm;
}

SparseMatrix add(SparseMatrix a, SparseMatrix b) 
{
    if (a.rows != b.rows || a.cols != b.cols) exit(1);
    SparseMatrix res = createMatrix(a.rows, a.cols, a.nz + b.nz);
    int i = 0, j = 0, k = 0;
    while (i < a.nz && j < b.nz) {
        if (a.elements[i].row < b.elements[j].row || 
           (a.elements[i].row == b.elements[j].row && a.elements[i].col < b.elements[j].col)) 
            res.elements[k++] = a.elements[i++];
        else if (a.elements[i].row > b.elements[j].row || 
                (a.elements[i].row == b.elements[j].row && a.elements[i].col > b.elements[j].col)) 
            res.elements[k++] = b.elements[j++];
        else {
            res.elements[k] = a.elements[i];
            res.elements[k++].val = a.elements[i++].val + b.elements[j++].val;
        }
    }
    while (i < a.nz) res.elements[k++] = a.elements[i++];
    while (j < b.nz) res.elements[k++] = b.elements[j++];
    res.nz = k;
    return res;
}


SparseMatrix multiply(SparseMatrix a, SparseMatrix b) 
{
    if (a.cols != b.rows) exit(1);
    SparseMatrix res = createMatrix(a.rows, b.cols, a.nz * b.nz);
    int k = 0;
    for (int i = 0; i < a.nz; i++)

        for (int j = 0; j < b.nz; j++)


            if (a.elements[i].col == b.elements[j].row) 
            {
                
                 int found = 0;
             for (int p = 0; p < k; p++)
                            if (res.elements[p].row == a.elements[i].row && 
                       
                        res.elements[p].col == b.elements[j].col) 
                        {
                        res.elements[p].val += a.elements[i].val * b.elements[j].val;
                        found = 1;
                        break;
                    
                    }
                if (!found) 
                {
                    res.elements[k++] = (SparseElement){a.elements[i].row, b.elements[j].col, a.elements[i].val * b.elements[j].val};
                }
            }
    res.nz = k;
    return res;
}

void printMatrix(SparseMatrix sm) 
{
    printf("Row\tCol\tValue\n");
    for (int i = 0; i < sm.nz; i++)
        printf("%d\t%d\t%d\n", sm.elements[i].row, sm.elements[i].col, sm.elements[i].val);
}

void freeMatrix(SparseMatrix* sm) 
{
    if (sm->elements) free(sm->elements), sm->elements = NULL;
}

int main()
{
    int r1, c1; 
    int nz1, r2, c2, nz2;
    printf("Enter rows, cols, non-zero count for Matrix 1: ");
    scanf("%d %d %d", &r1, &c1, &nz1);
    SparseMatrix sm1 = createMatrix(r1, c1, nz1);
    for (int i = 0; i < nz1; i++) 
        scanf("%d %d %d", &sm1.elements[i].row, &sm1.elements[i].col, &sm1.elements[i].val);

    printf("Enter rows, cols, non-zero count for Matrix 2: ");
    scanf("%d %d %d", &r2, &c2, &nz2);
    SparseMatrix sm2 = createMatrix(r2, c2, nz2);
    for (int i = 0; i < nz2; i++) 
        scanf("%d %d %d", &sm2.elements[i].row, &sm2.elements[i].col, &sm2.elements[i].val);

    SparseMatrix sum = add(sm1, sm2);
    SparseMatrix product = multiply(sm1, sm2);

    printf("\nAddition Result:\n");
    printMatrix(sum);
    printf("\nMultiplication Result:\n");
    printMatrix(product);

    freeMatrix(&sm1), freeMatrix(&sm2), freeMatrix(&sum), freeMatrix(&product);
    return 0;
}
