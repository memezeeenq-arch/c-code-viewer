#include <stdio.h>
#define MAX 100

typedef struct {
    int id;
    char item[30];
} Order;

Order queue[MAX];
int front = -1, rear = -1, count = 0;
int M, nextId = 1;

int isFull() {
    return count == M;
}

int isEmpty() {
    return count == 0;
}

/* Add Order */
void enqueue() {
    if (isFull()) {
        printf("Queue Overflow!\n");
        return;
    }

    Order o;
    o.id = nextId++;

    printf("Enter pizza name: ");
    scanf("%29s", o.item);

    if (isEmpty())
        front = rear = 0;
    else
        rear = (rear + 1) % M;

    queue[rear] = o;
    count++;

    printf("Order %d accepted.\n", o.id);
}

/* Serve Order */
void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow!\n");
        return;
    }

    printf("Serving Order %d: %s\n",
           queue[front].id, queue[front].item);

    if (count == 1)
        front = rear = -1;
    else
        front = (front + 1) % M;

    count--;
}

/* Display Queue */
void display() {
    int i, idx;

    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nPending Orders:\n");

    for (i = 0, idx = front; i < count; i++) {
        printf("%d. Order %d - %s\n",
               i + 1, queue[idx].id, queue[idx].item);
        idx = (idx + 1) % M;
    }

    printf("Waiting: %d | Free slots: %d\n", count, M - count);
}

/* Main Function */
int main() {
    int choice;

    printf("Enter maximum orders: ");
    scanf("%d", &M);

    if (M < 1 || M > MAX) {
        printf("Invalid capacity!\n");
        return 1;
    }

    do {
        printf("\n1. Add Order\n");
        printf("2. Serve Order\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: display(); break;
            case 4: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}