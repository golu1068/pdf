//// Linked list creation 

#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

void Display(struct Node *ptr)
{
    while(ptr != NULL)
    {
        printf("%x  ", ptr);
        printf("%d  ", ptr->data);
        printf("%x\n", ptr->next);
        ptr = ptr->next;
    }
}
struct Node *InsertionAtIndex(struct Node *head, int data, int index)
{
    int i=0;
    struct Node *node;
    struct Node *p = head;
    node = (struct Node *)malloc(sizeof(struct Node));
    while (1)
    {   
        if(i == index-1)
        {
            node->data = data;
            node->next = head->next;
            head->next = node;
            break;
        }
        else if(index == 0)
        {
            node->data = data;
            node->next = head;
            p = node;
            break;
        }
        i++;
        head = head->next;
    }
    return p;
}
struct Node *InsertionAtEnd(struct Node *head, int data)
{
    struct Node *node;
    struct Node *p = head;
    node = (struct Node *)malloc(sizeof(struct Node));
    while(head->next != NULL)
    {
        head = head->next;
    }  
    node->data = data;
    node->next = NULL;
    head->next = node;

    return p;
}
void main()
{
    struct Node *head;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;
    
    head = (struct Node *)malloc(1*sizeof(struct Node));
    second = (struct Node *)malloc(1*sizeof(struct Node));
    third = (struct Node *)malloc(1*sizeof(struct Node));
    fourth = (struct Node *)malloc(1*sizeof(struct Node));
    
    head->data = 10;
    head->next = second;
    second->data = 20;
    second->next = third;
    third->data = 30;
    third->next = fourth;
    fourth->data = 40;
    fourth->next = NULL;
    
    //// Insertion
    head = InsertionAtIndex(head, 25, 2);
    head = InsertionAtIndex(head, 5, 0);
    head = InsertionAtIndex(head, 27, 3);
    head = InsertionAtEnd(head, 45);
    head = InsertionAtIndex(head, 15, 1);
    head = InsertionAtEnd(head, 50);
    head = InsertionAtIndex(head, 2, 0);
    head = InsertionAtIndex(head, 15, 10);
    head = InsertionAtIndex(head, 0, 0);
    
    Display(head);


    free(head);
    free(second);
    free(third);
    free(fourth);
    // free(fiveth);
    
}

