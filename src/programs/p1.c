#include<stdio.h>

int linearSearch(int arr[],int n,int key){
    for(int i=0;i<n;i++){
        if(arr[i]==key){
            return i;
        }
    }
    return -1;
}

int binarySearch(int arr[],int n,int key){
    int low=0;
    int high=n-1;

    while(low<=high){
        int mid=low+(high-low)/2;

        if(arr[mid]==key){
            return mid;
        }else if(arr[mid]<key){
            low=mid+1;
        }else{
            high=mid-1;
        }
    }
    return -1;
}

int main(){
    int n,key,choice;

    printf("Enter the number of students:");
    scanf("%d",&n);

    int arr[n];

    printf("Enter the roll numbers of students:");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

   

    do{
        
         printf("Enter roll number you want to search:\n");
    scanf("%d",&key);
    
        printf("-------Roll Number Search-----\n");
        printf("Select Method\n");
        printf("1.Linear search\n");
        printf("2.Binary Search\n");
        printf("3.Exit\n");

        printf("Enter Your choice:\n");
        scanf("%d",&choice);

        switch(choice){
            case 1:{
                int result1=linearSearch(arr,n,key);

                if(result1!=-1){
                    printf("Student attended program\n");
                }else{
                    printf("Student did not attended program\n");
                }
                break;
            }

            case 2:{
                int result2=binarySearch(arr,n,key);

                if(result2!=-1){
                    printf("Student attended program\n");
                }else{
                    printf("Student did not attended program\n");
                }
                break;
            }

            case 3:
                printf("Exiting program------\n");
                break;

            default:
                printf("Invalid Choice\n");
        }
    }while(choice!=3);

    return 0;
}