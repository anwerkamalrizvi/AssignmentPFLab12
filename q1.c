/*Q1. Write a program to reverse an array using pointers without using any additional arrays.*/
#include <stdio.h>

int main() {
    int arr[5];
    int* ptr = arr;
    for (int i = 0; i < 5; i++)
    {
        printf("\nEnter element[%d]: ",i+1);
        scanf("%d",&(*ptr));
        ptr++;
    }
        
    for (int i = 1; i <= 5; i++)
    {
        ptr--;
        printf("%d ", *ptr);
    }
    
    return 0;
}