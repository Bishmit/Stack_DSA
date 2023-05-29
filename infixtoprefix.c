#include <stdio.h>
#include <string.h>

#define STACK_CAPACITY 20

char stack[STACK_CAPACITY];
int top = -1;

void push(char x) {
    if (top < STACK_CAPACITY - 1) {
        stack[++top] = x;
    } else {
        printf("Stack overflow\n");
    }
}

char pop() {
    if (top < 0) {
        return '\0';
    } else {
        return stack[top--];
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^';
}

int priority(char x) {
    switch (x) {
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 4;
        default:
            return 0;
    }
}

char* reverseString(char* str) {
    int length = strlen(str);
    int i, j;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    return str;
}

char* infixToPrefix(char* infix, char* prefix) {
    int i = 0, j = 0;
    int length = strlen(infix);
    char x;

    while (i < length) {
        if (!isOperator(infix[i]) && infix[i] != ')' && infix[i] != '(') {
            prefix[j] = infix[i];
            j++;
            i++;
        } else if (infix[i] == '(') {
            push(infix[i]);
            i++;
        } else if (infix[i] == ')') {
            while ((x = pop()) != '(') {
                prefix[j] = x;
                j++;
            }
            i++;
        } else if (priority(infix[i]) <= priority(stack[top])) {
            while (top != -1 && priority(infix[i]) <= priority(stack[top])) {
                x = pop();
                prefix[j] = x;
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
        prefix[j] = x;
        j++;
    }

    prefix[j] = '\0';

    return reverseString(prefix);
}

int main() {
    char infix[20], prefix[20];

    printf("Enter the infix expression: ");
    scanf("%s", infix);

    char* prefixExpression = infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefixExpression);

    return 0;
}

