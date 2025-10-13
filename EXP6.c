#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];       // stack
char input[MAX];       // input string
int top = -1;          // stack top

void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void pop(int n) {
    top -= n;
    stack[top + 1] = '\0';
}

// Check and reduce patterns
int reduce() {
    int reduced = 0;
    for (int i = 0; i <= top; i++) {
        // id -> E
        if (stack[i] == 'i' && stack[i + 1] == 'd') {
            stack[i] = 'E';
            // shift left remaining elements
            for (int j = i + 1; j < top; j++) stack[j] = stack[j + 1];
            top--;
            printf("\n$%s\t%s$\tREDUCE TO E", stack, input);
            reduced = 1;
        }
        // E+E -> E
        else if (stack[i] == 'E' && stack[i + 1] == '+' && stack[i + 2] == 'E') {
            stack[i] = 'E';
            for (int j = i + 1; j + 2 <= top; j++) stack[j] = stack[j + 2];
            top -= 2;
            printf("\n$%s\t%s$\tREDUCE TO E", stack, input);
            reduced = 1;
        }
        // E*E -> E
        else if (stack[i] == 'E' && stack[i + 1] == '*' && stack[i + 2] == 'E') {
            stack[i] = 'E';
            for (int j = i + 1; j + 2 <= top; j++) stack[j] = stack[j + 2];
            top -= 2;
            printf("\n$%s\t%s$\tREDUCE TO E", stack, input);
            reduced = 1;
        }
        // (E) -> E
        else if (stack[i] == '(' && stack[i + 1] == 'E' && stack[i + 2] == ')') {
            stack[i] = 'E';
            for (int j = i + 1; j + 2 <= top; j++) stack[j] = stack[j + 2];
            top -= 2;
            printf("\n$%s\t%s$\tREDUCE TO E", stack, input);
            reduced = 1;
        }
    }
    return reduced;
}

int main() {
    printf("GRAMMAR:\nE -> E + E\nE -> E * E\nE -> (E)\nE -> id\n");

    printf("Enter input string: ");
    scanf("%s", input);

    int len = strlen(input);
    printf("Stack\tInput\tAction\n");

    int i = 0;
    while (i < len) {
        // Shift
        if (input[i] == 'i' && input[i + 1] == 'd') {
            push('i');
            push('d');
            printf("\n$%s\t%s$\tSHIFT->id", stack, input + i);
            i += 2;
        } else {
            push(input[i]);
            printf("\n$%s\t%s$\tSHIFT->%c", stack, input + i, input[i]);
            i++;
        }

        // Try reducing as much as possible
        while (reduce());
    }

    if (top == 0 && stack[0] == 'E')
        printf("\nInput string is ACCEPTED\n");
    else
        printf("\nInput string is REJECTED\n");

    return 0;
}
