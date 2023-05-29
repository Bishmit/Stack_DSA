#include <stdio.h>

#define STACK_SIZE 20

int top = -1; // top of stack
char stack[STACK_SIZE];

void push(char x) {
    if (top < STACK_SIZE - 1) {
        stack[++top] = x;
    } else {
        printf("Stack overflow\n");
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack underflow\n");
        return '\0'; // or any appropriate value to indicate the underflow condition
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^';
}

int priority(char x) {
    switch (x) {
        case '(': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
        case '^': return 4;
        default: return 0;
    }
}

int main() {
    char infix[20], postfix[20], x;
    int i = 0, j = 0;

    printf("Enter the infix expression: ");
    scanf("%s", &infix);

    while (infix[i] != '\0') {
           if (!isOperator(infix[i]) && infix[i] != ')' && infix[i] != '(') {
            postfix[j] = infix[i];
            j++;
            i++;
        } else if (infix[i] == '(') {
            push(infix[i]);
            i++;
        } else if (infix[i] == ')') {
            while ((x = pop()) != '(') {
                postfix[j] = x;
                j++;
            }
            i++;
        } else if (priority(infix[i]) <= priority(stack[top])) {
            while (top != -1 && priority(infix[i]) <= priority(stack[top])) {
                x = pop();
                postfix[j] = x;
                j++;
            }
            push(infix[i]);
            i++;
        } else {
            push(infix[i]);
            i++;
        }
    }

    while (top != -1) {
        x = pop();
        postfix[j] = x;
        j++;
    }

    postfix[j] = '\0';

    printf("The postfix expression is: %s\n", postfix);

    return 0;
}
