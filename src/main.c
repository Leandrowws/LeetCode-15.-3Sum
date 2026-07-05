#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
void Merge(int vet[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int* esq = (int*)malloc(sizeof(int) * n1);
    int* dir = (int*)malloc(sizeof(int) * n2);

    for(i = 0; i < n1; i++) {
        esq[i] = vet[inicio + i];
    }

    for(j = 0; j < n2; j++) {
        dir[j] = vet[j + 1 + meio];
    }

    i = 0; j = 0; k = inicio;

    while(i < n1 && j < n2) {
        if(esq[i] < dir[j]) {
            vet[k++] = esq[i++];
        } else {
            vet[k++] = dir[j++];
        }
    }

    while(i < n1) {
        vet[k++] = esq[i++];
    }

    while(j < n2) {
        vet[k++] = dir[j++];
    }

    free(esq);
    free(dir);
}


void MergeSort(int vet[], int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        MergeSort(vet, inicio, meio);
        MergeSort(vet, meio + 1, fim);
        Merge(vet, inicio, meio, fim);
    }
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {

    MergeSort(nums, 0, numsSize - 1);

    int** resposta = (int**)malloc(sizeof(int*) * numsSize * numsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * numsSize * numsSize);

    *returnSize = 0;

    for(int i = 0; i < numsSize - 2; i++) {
        if(i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        int esq = i + 1;
        int dir = numsSize - 1;

        while(esq < dir) {
            int soma = nums[i] + nums[esq] + nums[dir];
            if(soma == 0) {

                resposta[*returnSize] = (int*)malloc(sizeof(int) * 3);
                resposta[*returnSize][0] = nums[i];
                resposta[*returnSize][1] = nums[esq];
                resposta[*returnSize][2] = nums[dir];

                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                esq++;
                dir--;

                while(esq < dir && nums[esq] == nums[esq - 1]) {
                    esq++;
                }
                while(esq < dir && nums[dir] == nums[dir + 1]) {
                    dir--;
                }

            } else if(soma < 0) {
                esq++;
            } else {
                dir--;
            }
        }
    }

    return resposta;
}

int main() {
    
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int tam = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* returnColumnSizes;

    printf("Vetor: ");
    for(int i = 0; i < tam; i++) {
        printf("%d ", nums[i]);
    }

    int** vet = threeSum(nums, tam, &returnSize, &returnColumnSizes);
   
    printf("\nSolucoes: ");
    for(int i = 0; i < returnSize; i++) {
        printf("[");
        for(int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", vet[i][j]);
            
        }
        printf("] ");
    }

    return 0;
}
