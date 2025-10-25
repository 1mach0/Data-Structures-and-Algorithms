//
// Created by machi on 10/23/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[20];
int top = -1;

char istack[20];
int itop = -1;

void push(char item) {
    stack[++top] = item;
}

char pop() {
    return stack[top--];
}

void ipush(int item) {
    istack[++itop] = item;
}

int ipop() {
    return istack[itop--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void infix_to_postfix(char* input, char* output) {
    int index = 0;
    int length = strlen(input);

    for (int i = 0; i < length; i++) {
        char curr = input[i];

        if ((curr >= '0' && curr <= '9') || (curr >= 'A' && curr <= 'Z') || (curr >= 'a' && curr <= 'z')) {
            output[index++] = curr;
        }
        else if (curr == '(') {
            push(curr);
        }
        else if (curr == ')') {
            while (top != -1 && stack[top] != '(') {
                output[index++] = pop();
            }
            if (top != -1 && stack[top] == '(') pop(); // remove '('
        }
        else if (is_operator(curr)) {
            while (top != -1 && precedence(stack[top]) >= precedence(curr) && stack[top] != '(') {
                output[index++] = pop();
            }
            push(curr);
        }
    }

    while (top != -1) {
        output[index++] = pop();
    }

    output[index] = '\0';
}

int postfix_evaluation(char* postfix) {
    // if number, push to stack
    // if operator, pop first two of stack, do operation and then push to stack
    int index = 0;
    char curr;
    while (postfix[index] != '\0') {
        curr = postfix[index];
        if (curr >= '0' && curr <= '9') {
            ipush(curr - '0');
        } else {
            int a = ipop(); int b = ipop();
            int pp = 0;
            if (curr == '+') {pp = (b+a);}
            if (curr == '-') {pp = (b-a);}
            if (curr == '*') {pp = (b*a);}
            if (curr == '/') {pp = (b/a);}
            if (curr == '^') {pp = (b^a);}
            ipush(pp);
        }
        index++;
    }
    int value = ipop();
    return value;
}

// infix to prefix
// prefix evaluation

int main() {
    char input[20] = "(1+2)*3+6-9/(2+1)";
    char* output = malloc(20 * sizeof(char));

    infix_to_postfix(input, output);
    printf("%s\n", output);

    printf("value = %d\n", postfix_evaluation(output));

    free(output);
    return 0;
}
