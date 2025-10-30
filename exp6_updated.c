#include <stdio.h>
#include <string.h>
char input[20] , stk[20];
int top = -1, idx = 0;

void push(char c){
    stk[++top] = c;
}

void pop(int n){
    while(n != 0){
        stk[top] = '\0';
        top--;
        n--;
    }
}

int reduce(){
    int reduced = 0;
    for(int i = 0 ; i < strlen(stk) ; i++){
        if(stk[i] == 'i' && stk[i + 1] == 'd'){
            printf("\n%-15s%-15s\tReduce by E -> id", stk , input + idx);
            pop(2);
            push('E');
            reduced = 1;
        }else if(stk[i] == 'E' && stk[i + 1] == '+' && stk[i + 2] == 'E'){
            printf("\n%-15s%-15s\tReduce by E -> E + E", stk , input + idx);
            pop(3);
            push('E');
            reduced = 1;
        }else if(stk[i] == 'E' && stk[i + 1] == '*' && stk[i + 2] == 'E'){
            printf("\n%-15s%-15s\tReduce by E -> E + E", stk , input + idx);
            pop(3);
            push('E');
            reduced = 1;
        }
    }
    return reduced;
}

void main(){
    printf("GRAMMAR:\nE -> E + E\nE -> E * E\nE -> id\n");
    
    printf("Enter string : ");
    scanf("%s" , input);
    
    printf("Stack\t\tInput\tAction\n");
    int len = strlen(input);
    while(idx < len){
        if(input[idx] == 'i' && input[idx + 1] == 'd'){
            printf("\n%-15s%-15s\tSHIFT id", stk , input + idx);
            push('i');
            push('d');
            idx+=2;
        }else{
            printf("\n%-15s%-15s\tSHIFT %c", stk , input + idx, input[idx]);
            push(input[idx]);
            idx++;
        }
        while(reduce());
    }
    if(top == 0 && stk[0] == 'E'){
        printf("\nE\t\t\t\t Accepted");
    }
}
