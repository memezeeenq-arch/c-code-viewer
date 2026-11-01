#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10

typedef struct{
    int key;
    char name[30];
    char phone[15];
    int occoupied;
}Client;

Client hashTable[MAX];

//hashTable initialization

void initTable(){
    for(int i=0;i<MAX;i++){
        hashTable[i].occoupied=0;
    }
}

//Primary hash function

int hashFunction(int key){
    return key%MAX;
}

//Secondary hash function
int hashFunction2(int key){
    return 7-(key%7);
}


//Insert using linear probing

void insertLinear(int key,char name[],char phone[]){
    int index=hashFunction(key);
    for(int i=0;i<MAX;i++){
        int pos=(index+i)%MAX;
        
        if(hashTable[pos].occoupied==0){
            hashTable[pos].key=key;
            strcpy(hashTable[pos].name,name);
            strcpy(hashTable[pos].phone,phone);
            hashTable[pos].occoupied=1;
            
            printf("Insterted at %d using Linear probing\n",pos);
            return;
        }
        
    }
    printf("Hash Table Full!!\n");
}






//Insert using Quadratic probing

void insertQuadratic(int key,char name[],char phone[]){
    int index=hashFunction(key);
    for(int i=0;i<MAX;i++){
        int pos=(index+i*i)%MAX;
        
        if(hashTable[pos].occoupied==0){
            hashTable[pos].key=key;
            strcpy(hashTable[pos].name,name);
            strcpy(hashTable[pos].phone,phone);
            hashTable[pos].occoupied=1;
            
            printf("Insterted at %d using Quadratic probing\n",pos);
            return;
        }
        
    }
    printf("Hash Table Full!!\n");
}


//Insert using Double hashing

void insertouble(int key,char name[],char phone[]){
    int index=hashFunction(key);
    int step=hashFunction2(key);
    for(int i=0;i<MAX;i++){
        int pos=(index+i*step)%MAX;
        
        if(hashTable[pos].occoupied==0){
            hashTable[pos].key=key;
            strcpy(hashTable[pos].name,name);
            strcpy(hashTable[pos].phone,phone);
            hashTable[pos].occoupied=1;
            
            printf("Insterted at %d using Double Hashing\n",pos);
            return;
        }
        
    }
    printf("Hash Table Full!!\n");
}

void search(int key){
    for(int i=0;i<MAX;i++){
        if(hashTable[i].occoupied && hashTable[i].key==key){
            printf("Client Found\n");
            printf("Name:%s\n",hashTable[i].name);
            printf("Phone:%s\n",hashTable[i].phone);
            printf("Index:%d\n",i);
            return;
            
        }
    }
    printf("Client Not found\n");
}


void display(){
    for(int i=0;i<MAX;i++){
        if(hashTable[i].occoupied){
            printf("Index %d: Key:%d Name: %s Phone:%s\n",
            i,hashTable[i].key,hashTable[i].name,hashTable[i].phone);
        }else{
            printf("Index %d is empty\n",i);
            
        }
    }
}


int main(){
    
    int choice;
    char name[30];
    char phone[15];
    int key;
    
    initTable();
    
    while(1){
        printf("\n===== TELEPHONE BOOK =====\n");
        printf("1. Insert using Linear Probing\n");
        printf("2. Insert using Quadratic Probing\n");
        printf("3. Insert using Double Hashing\n");
        printf("4. Search Client\n");
        printf("5. Display Table\n");
        printf("6. Exit\n");
        
        printf("Enter Your choice:\n");
        scanf("%d",&choice);
        
        switch(choice){
            case 1:{
            printf("Enter key: ");
            scanf("%d", &key);
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter phone: ");
            scanf("%s", phone);
            insertLinear(key, name, phone);
            break;
            }
            
            case 2:{
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phone: ");
                scanf("%s", phone);
                insertQuadratic(key, name, phone);
                break;
            }
            
            case 3:{
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phone: ");
                scanf("%s", phone);
                insertouble(key, name, phone);
                break;
            }
            
            case 4:{
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            }
            case 5:{
                display();
                break;
            }
            
            case 6:{
            printf("Exiting program...\n");
            exit(0);}
            default:{
            printf("Invalid choice!\n");}
        }
        
    }
    
    return 0;
}