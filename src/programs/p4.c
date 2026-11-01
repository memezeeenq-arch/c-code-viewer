#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int prn;
    char name[30];
    struct node *next;
};

/* Create Node */
struct node* createNode() {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));

    printf("Enter PRN: ");
    scanf("%d", &newNode->prn);

    printf("Enter Name: ");
    scanf("%29s", newNode->name);

    newNode->next = NULL;
    return newNode;
}

/* Add President */
struct node* addPresident(struct node *head) {
    struct node *newNode = createNode();
    newNode->next = head;
    printf("President added.\n");
    return newNode;
}

/* Add Secretary */
struct node* addSecretary(struct node *head) {
    struct node *newNode = createNode(), *temp = head;

    if (head == NULL)
        return newNode;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    printf("Secretary added.\n");
    return head;
}

/* Add Member at Position */
struct node* addMember(struct node *head) {
    struct node *newNode = createNode(), *temp = head;
    int pos, i;

    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos <= 1 || head == NULL) {
        newNode->next = head;
        return newNode;
    }

    for (i = 1; i < pos - 1 && temp->next != NULL; i++)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;

    printf("Member added.\n");
    return head;
}

/* Delete President */
struct node* deletePresident(struct node *head) {
    struct node *temp;

    if (head == NULL) {
        printf("Club is empty.\n");
        return NULL;
    }

    temp = head;
    head = head->next;
    printf("Deleted President: %s\n", temp->name);
    free(temp);

    return head;
}

/* Delete Secretary */
struct node* deleteSecretary(struct node *head) {
    struct node *temp = head, *prev = NULL;

    if (head == NULL) {
        printf("Club is empty.\n");
        return NULL;
    }

    if (head->next == NULL) {
        printf("Deleted Secretary: %s\n", head->name);
        free(head);
        return NULL;
    }

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = NULL;
    printf("Deleted Secretary: %s\n", temp->name);
    free(temp);

    return head;
}

/* Delete Member at Position */
struct node* deleteMember(struct node *head) {
    struct node *temp = head, *prev = NULL;
    int pos, i;

    if (head == NULL) {
        printf("Club is empty.\n");
        return NULL;
    }

    printf("Enter position: ");
    scanf("%d", &pos);

    if (pos == 1)
        return deletePresident(head);

    if (pos < 1)
        return head;

    for (i = 1; i < pos && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position.\n");
        return head;
    }

    prev->next = temp->next;
    printf("Deleted member: %s\n", temp->name);
    free(temp);

    return head;
}

/* Count Members */
int countMembers(struct node *head) {
    int count = 0;

    while (head != NULL) {
        count++;
        head = head->next;
    }

    return count;
}

/* Display Members */
void display(struct node *head) {
    if (head == NULL) {
        printf("Club is empty.\n");
        return;
    }

    while (head != NULL) {
        printf("PRN: %d\tName: %s\n", head->prn, head->name);
        head = head->next;
    }
}

/* Concatenate Two Lists */
struct node* concatenate(struct node *head1, struct node *head2) {
    struct node *temp = head1;

    if (head1 == NULL)
        return head2;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = head2;
    return head1;
}

/* Main Function */
int main() {
    struct node *head1 = NULL, *head2 = NULL;
    int choice, division, count;

    do {
        printf("\n--- PINNACLE CLUB ---\n");
        printf("1.Add President  2.Add Member  3.Add Secretary\n");
        printf("4.Delete President  5.Delete Member  6.Delete Secretary\n");
        printf("7.Count Members  8.Display Members\n");
        printf("9.Concatenate Divisions  10.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 8) {
            printf("Enter Division (1 or 2): ");
            scanf("%d", &division);

            if (division != 1 && division != 2) {
                printf("Invalid division.\n");
                continue;
            }
        }

        struct node **head = (division == 1) ? &head1 : &head2;

        switch (choice) {
            case 1:
                *head = addPresident(*head);
                break;

            case 2:
                *head = addMember(*head);
                break;

            case 3:
                *head = addSecretary(*head);
                break;

            case 4:
                *head = deletePresident(*head);
                break;

            case 5:
                *head = deleteMember(*head);
                break;

            case 6:
                *head = deleteSecretary(*head);
                break;

            case 7:
                count = countMembers(*head);
                printf("Total members = %d\n", count);
                break;

            case 8:
                display(*head);
                break;

            case 9:
                head1 = concatenate(head1, head2);
                head2 = NULL;
                printf("Lists concatenated.\n");
                display(head1);
                break;

            case 10:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 10);

    return 0;
}