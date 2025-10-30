#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buff[]){
    char tokens[5][10] = {"if","else","while","do","for"};
    for(int i = 0 ; i < 5 ; i++){
        if(strcmp(buff , tokens[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void main() {
    int j = 0;
    char buff[20] , ch;
    FILE* fp = fopen("input.txt" , "r");

    while((ch = fgetc(fp)) != EOF){
        if(isalnum(ch)){
            buff[j] = ch;
            j++;
            continue;
        }else{
            ////////////////////
            if(j != 0){
                buff[j] = '\0';
                j = 0;
                if(isdigit(buff[0])){
                    printf("%s : number\n", buff);
                }else if(isKeyword(buff)){
                    printf("%s : keyword\n", buff);
                }else{
                    printf("%s : identifier\n", buff);
                }
            }
            //////////////////////
            if(ch == '/' || ch == '*' || ch == '+' || ch == '-' || ch == '%' || ch == '='){
                printf("%c : operator\n",ch);
            }else if(ch == '{' || ch == '}' || ch == ';' || ch == ','){
                 printf("%c : special\n",ch);
            }
        }
    }
}
