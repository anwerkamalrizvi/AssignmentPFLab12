/*Allocate memory dynamically for an array of structures.
 Use the array to store employee details (ID, name, salary).
 Sort employees by salary using pointer-based comparison.*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Employee
{
    int ID;
    char name[50];
    float salary;
}Emp;

float salarySort(const void* a, const void* b){
    Emp* Emp1 = (Emp*) a;
    Emp* Emp2 = (Emp*) b;
    return (Emp1->salary > Emp2->salary) - (Emp1->salary < Emp2->salary);
}

int main() 
{
    int n=2;
    Emp* data = (Emp*)calloc(n,sizeof(Emp));  //DMA
    if (data == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 1; i <= n; i++)
    {//start loooooooooooooooooooooooooooooooooooooop
        printf("\nEmployee %d: ",i);
        printf("\nEnter Employee's ID: ");
        scanf("%d",&data[i].ID);
        printf("\nEnter Employee's name: ");
        scanf("%s",&data[i].name);
        printf("\nEnter Employee's salary: ");
        scanf("%f",&data[i].salary);
    }//end for loop

    qsort(data, n, sizeof(Emp), salarySort);    //qsort is library buikdin func
    for (int i = 0; i < n; i++)
    {
        printf("Employee ID: %d\n ",data[i].ID );
        printf("Employee name: %s\n ", data[i].name);
        printf("Employee Salary: %.2f\n ", data[i].salary);
    }//end for loop

    free(data);
    return 0;
}