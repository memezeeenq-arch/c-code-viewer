#include <stdio.h>
#include <ctype.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch) {
    stack[++top] = ch;
}

char pop() {
    return stack[top--];
}

int precedence(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

/* Infix to Postfix */
void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char ch;
    top = -1;

    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        if (isalnum(ch))
            postfix[j++] = ch;

        else if (ch == '(')
            push(ch);

        else if (ch == ')') {
            while (stack[top] != '(')
                postfix[j++] = pop();
            pop();
        }

        else {
            while (top != -1 && stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(ch))
                postfix[j++] = pop();

            push(ch);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

/* Evaluate Postfix */
int evaluatePostfix(char postfix[]) {
    int s[MAX], values[26] = {0};
    int top2 = -1, i, a, b;
    char ch;

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];

        if (isalpha(ch) && values[tolower(ch) - 'a'] == 0) {
            printf("Enter value of %c: ", ch);
            scanf("%d", &values[tolower(ch) - 'a']);
        }
    }

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];

        if (isalpha(ch))
            s[++top2] = values[tolower(ch) - 'a'];

        else if (isdigit(ch))
            s[++top2] = ch - '0';

        else {
            b = s[top2--];
            a = s[top2--];

            switch (ch) {
                case '+': s[++top2] = a + b; break;
                case '-': s[++top2] = a - b; break;
                case '*': s[++top2] = a * b; break;
                case '/': s[++top2] = a / b; break;
                case '^': {
                    int p = 1, k;
                    for (k = 0; k < b; k++) p *= a;
                    s[++top2] = p;
                    break;
                }
            }
        }
    }

    return s[top2];
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%99s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    printf("Result = %d\n", evaluatePostfix(postfix));

    return 0;
}