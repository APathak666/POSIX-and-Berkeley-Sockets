#include <stdlib.h>
#include <stdio.h>
  
// A linked list (LL) node to store a queue entry
 typedef struct node {
    int* cli_sock;
    struct node* next;
} node;

node* head = NULL;
node* tail = NULL;

void enqueue(int* client)
{
    node* newNode = malloc(sizeof(node));
    if (newNode == NULL) printf("malloc failed\n");
    //printf("%d\n", *client);

    newNode->cli_sock = client;
    newNode->next = NULL;

    if (head == NULL && tail == NULL)
    {
        head = newNode;
        //printf("tail was null\n");
    }

    else
    {
        //printf("tail was not null\n");
        tail->next = newNode;
    }

    tail = newNode;
    //printf("successfully enqueued\n");  
}

int* dequeue()
{
    if (head == NULL)
    {
        //printf("head was null\n");
        return NULL;
    }
    else
    {
        //printf("head not was null\n");
        int* res = head->cli_sock;
        node* temp = head;
        head = head->next;
        if (head == NULL)
            tail = NULL;

        free(temp);
        //if (res == NULL) printf("NULL return\n");
        return res;
    }
}

void printList()
{
    node* temp = head;
    //printf("printing list\n");
    if (head == NULL) printf("empty list\n");
    while (temp != NULL)
    {
        printf("%x ", temp->cli_sock);
        temp = temp->next;
    }

    printf("\n");
}

// int main()
// {
//     int arr[10];
//     for (int i = 0; i < 10; i++)
//     {
//         arr[i] = i;
//         enqueue(&arr[i]);
//         printList();
//         dequeue();
//     }

//     //printList();
// }