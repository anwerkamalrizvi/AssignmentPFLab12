/*Write a program which perform following operations
 Dynamically allocate an array of integers of size n.
 Input values and calculate their sum.
 Reallocate the array to double its size and add n more values.
 Calculate the new sum.*/
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    int n; scanf("%d",&n);
    int* ptr = (int*)malloc(n*sizeof(int));
    if(ptr == NULL)
    {
        printf("\nMemory allocation failed ");
        return 1;
    }//end if
    int arr[n];
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter element[%d]: ",i+1);
        scanf("%d",&arr[i]);
        sum+= arr[i];
    }
    printf("\nThe total sum is %d ",sum);
    realloc(ptr,n*2);
    for (int i = n; i < n*2; i++)
    {
        printf("\nEnter element[%d]: ",i+1);
        scanf("%d",&arr[i]);
        sum+= arr[i];
    }
    printf("\nNow, The total sum is %d ",sum);
    return 0;
}//end main no way