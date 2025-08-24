#include <stdio.h>
#include <stdlib.h>

// Structure for stack frame
typedef struct {
    int n;
    char src, aux, dest;
    int stage;  // to track progress
} Frame;

typedef struct {
    Frame data[100];
    int top;
} Stack;

void push(Stack *s, Frame f) {
    s->data[++s->top] = f;
}

Frame pop(Stack *s) {
    return s->data[s->top--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void hanoiIterative(int n, char src, char aux, char dest) {
    Stack s;
    s.top = -1;

    Frame f = {n, src, aux, dest, 0};
    push(&s, f);

    while (!isEmpty(&s)) {
        f = pop(&s);

        if (f.n == 1) {
            printf("Move disk 1 from %c to %c\n", f.src, f.dest);
            continue;
        }

        if (f.stage == 0) {
            // Stage 0: break into first recursive call
            f.stage = 1;
            push(&s, f);  // push current back with next stage
            push(&s, (Frame){f.n - 1, f.src, f.dest, f.aux, 0});
        } else if (f.stage == 1) {
            // Stage 1: print move and prepare for second call
            printf("Move disk %d from %c to %c\n", f.n, f.src, f.dest);
            push(&s, (Frame){f.n - 1, f.aux, f.src, f.dest, 0});
        }
    }
}

int main() {
    int n = 3;
    hanoiIterative(n, 'A', 'B', 'C');
    return 0;
}
