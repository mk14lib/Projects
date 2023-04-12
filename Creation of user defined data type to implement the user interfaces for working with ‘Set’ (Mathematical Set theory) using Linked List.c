/*
*  union_intersection.c
*  Created on: Dec 28, 2022
*  Author: Koona Maheswararao
*/

/* Creation of user defined data type to implement the user interfaces
*  for working with ‘Set’ (Mathematical Set theory i.e,. union and
*  intersection operations) using Linked List
*/

#include<stdio.h> //preprocessor directives for using scanf, printf,
#include<stdlib.h> //malloc,
#include<stdbool.h> //bool functions.

//declaration of single link list
struct Node{
    int data;
    struct Node* link;
};

//defined function prototype
void insert(struct Node**, int);

//boolean function prototype
bool check_if_exists(struct Node*, int);

//userdefined function prototype to find union of sets
struct Node* find_union(struct Node* head1, struct Node* head2);

//userdefined function prototype to find intersection of sets
struct Node* find_intersection(struct Node* head1, struct Node* head2);

//function prototype for printSet function
void printSet(struct Node*);



//program execution begins from here
int main()
{
    int a,i;
    // user defined dataType node variables declaration and initialization
    struct Node *head1 = NULL, *head2 = NULL, *intersection = NULL, *_union = NULL;

    //user input prompt 1
    printf("Enter 5 elements for Set A: \n");
    fflush(stdout);
    for(i=0; i<5; i++)
    {
        scanf("%d",&a);
        insert(&head1, a);
    }

    //user input prompt 1
    printf("Enter 5 elements for Set B: \n");
    fflush(stdout);
    for(i=0; i<5; i++)
    {
        scanf("%d",&a);
        insert(&head2, a);
    }

    //return values of find_union() and find_intersection are captured
    //by _union and intersection structs
    _union = find_union(head1, head2);
    intersection = find_intersection(head1, head2);

    //prints elements of corresponding sets to console
    printf("\nSet A elements: \n");
    printSet(head1);

    printf("\n\nSet B elements: \n");
    printSet(head2);

    printf("\n\nA union B: \n");
    printSet(_union);

    printf("\n\nA intersection B: \n");
    printSet(intersection);
    printf("\n");

    //return 0 after successfull execution
    return 0;
}



//user defined struct function to find duplicates and inserts each element
//only once to new set
struct Node* find_union(struct Node* head1, struct Node* head2)
{
    //new set 'uniq' stores the union set elements
    struct Node* uniq = NULL;
    struct Node *setA = head1, *setB = head2;

    //traverses through set A elements and insert them to 'uniq' set
    while (setA != NULL)
    {
        insert(&uniq, setA->data);
        setA = setA->link;
    }
    //traverses through set B elements, checks for existing elements
    //avoids them and inserts non-repetitive elements to 'uniq' set
    while (setB != NULL)
    {
        if (!check_if_exists(uniq, setB->data))
            insert(&uniq, setB->data);
        setB = setB->link;
    }
    return uniq;
}



//user defined struct function to find duplicates and insert elements
//to new set
struct Node* find_intersection(struct Node* head1, struct Node* head2)
{
    struct Node* common = NULL;
    struct Node* setA = head1;
    //compares sets A and B inserts commons elements to
    //new set 'common'
    while (setA != NULL)
    {
        if (check_if_exists(head2, setA->data))
            insert(&common, setA->data);
        setA = setA->link;
    }
    return common;
}



//function definition for insert operation
//inserts element by element when called
void insert(struct Node** headPointer, int data)
{
    //allocate memory of size struct node
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));

    //pushes input data received from main function to 'new' set
    new->data = data;

    //updates address to next location
    new->link = *headPointer;

    //data from new set copied to *headPointer set
    *headPointer = new;
}




//traverses through all elements and prints them to console
void printSet(struct Node* node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->link;
    }
}




//boolean function definition to check for duplicates elements
bool check_if_exists(struct Node* head, int data)
{
    struct Node* set = head;
    while (set != NULL)
    {
        if (set->data == data)
            return 1;
        set = set->link;
    }
    return 0;
}
