#include<stdio.h>


void bubbleSort(float arr[],int n){
    
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                float temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    
    printf("Sorted Array:\n");
    for(int i=0;i<n;i++){
        printf("%.2f  ",arr[i]);
    }
    printf("\n");
    
    int limit=(n<5)?n:5;
    
    printf("Largest elements are:");
        for(int i=n-1;i>n-limit;i--){
            printf("%.2f  ",arr[i]);
        }
    
}

void selectionSort(float arr[],int n){
    
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[min]){
                min=j;
            }
        }
        float temp=arr[min];
        arr[min]=arr[i];
        arr[i]=temp;
    }
    
    printf("Sorted Array:\n");
    for(int i=0;i<n;i++){
        printf("%.2f  ",arr[i]);
    }
    printf("\n");
    
    int limit=(n<5)?n:5;
    
    printf("Largest elements are:");
        for(int i=n-1;i>n-limit;i--){
            printf("%.2f  ",arr[i]);
        }
    
    
    
}

int main(){
    
    int n;
    int choice;
    printf("Enter size of array:");
    scanf("%d",&n);
    
    float arr[n];
    printf("Enter elements of array:\n");
    for(int i=0;i<n;i++){
        scanf("%f",&arr[i]);
    }
    
    printf("Unsorted array:\n");
    for(int i=0;i<n;i++){
        printf("%.2f\n",arr[i]);
    }
    
    do{
        printf("\n---------Sorting---------\n");
        printf("Select method\n");
        printf("1.Bubbl sort\n");
        printf("2.Selection sort\n");
        printf("3.Exit\n");
        
        
        
        printf("Enter Your choice:\n");
        scanf("%d",&choice);
        
        
        switch(choice){
            case 1:{
                printf("Sorting array using bubble sort\n");
                bubbleSort(arr,n);
                break;
            }
            case 2:{
                printf("Sorting array using selection sort\n");
                selectionSort(arr,n);
                break;
            }
            
            case 3:{
                printf("Exiting program-----\n");
                break;
            }
            
            default:
            printf("Invalid choice \n");
        }
    }while(choice!=3);
    return 0;
}