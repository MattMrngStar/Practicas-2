#include <stdio.h>
#define MAX 100

void printArray(int *pdata,int n){

    printf("\n The array is: \n");

    for(int i = 0; i< n ;i++) {
        printf("data[%d]: %d\n",i,  *(pdata+i) );
    }
}

int main(){
    int n;
    int data[MAX];
    int position;

    printf("Enter the length of the array: ");
    scanf("%d", &n);
    printf("Enter %d elements of the array \n",n);

    for(int i = 0; i < n; i++){
        scanf("%d", &data[i]);
    }
    printArray(data, n);

    printf("\n Enter a position where you want to insert: ");
    scanf("%d", &position);
    position--;
    for(int i = n-1;i >= position; i--){
        data[i+1] = data[i];
    }
    printf("\nEnter the value: ");
    scanf("%d", &data[position]);

    printArray(data,n+1);
    return 0;
}