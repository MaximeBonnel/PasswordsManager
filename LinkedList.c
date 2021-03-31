#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constants.h"

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-24 14:05:46
//  # Description: Initialisation of a new linked list
// **************************************************
struct linkedList * newLinkedList()
{
    struct linkedList * tmp;

    tmp = (struct linkedList *) malloc(sizeof(struct linkedList));

    if(tmp != NULL)
    {
        tmp->head = NULL;
        tmp->size = 0;
        tmp->tail = NULL;
    }

    return tmp;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-24 14:05:46
//  # Description: Creation of a new link
// **************************************************
struct link * newLink(char name[], char id[], char pwd[])
{
    struct link * tmp;

    tmp = (struct link *) malloc(sizeof(struct link));

    if(tmp != NULL)
    {
        strcpy(tmp->name, name);
        strcpy(tmp->id, id);
        strcpy(tmp->pwd, pwd);
        tmp->nextLink = NULL;
    }

    return tmp;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-24 17:50:27
//  # Description: Display the linked list
// **************************************************
int displayLinkedList(struct linkedList * LinkedList)
{
    if (LinkedList->head == NULL || LinkedList->tail == NULL || LinkedList->size < 0){return EXIT_FAILURE;}

    struct link * tmp = LinkedList->head;
    int count = 1;

    printf("\n--0--    %"CH_MAX_NAME_CHAR"s    %"CH_MAX_ID_CHAR"s    %"CH_MAX_PWD_CHAR"s", "--name--", "--id--", "--pwd--");

    while (tmp != NULL)
    {
        printf("\n--%d--    %"CH_MAX_NAME_CHAR"s    %"CH_MAX_ID_CHAR"s    %"CH_MAX_PWD_CHAR"s", count, tmp->name, tmp->id, tmp->pwd);
        count++;

        tmp = tmp->nextLink;
    }

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-24 14:05:46
//  # Description: Function to add a link at the end of the linked list
// **************************************************
int addLink(struct linkedList * LinkedList, struct link * Link)
{
    if (LinkedList == NULL || Link == NULL || LinkedList->size < 0){return EXIT_FAILURE;}
    
    if (LinkedList->head != NULL)
    {
        LinkedList->tail->nextLink = Link;
        LinkedList->tail = Link;
        LinkedList->size++;
    }
    else
    {
        LinkedList->head = Link;
        LinkedList->tail= Link;
        LinkedList->size = 1;
    }

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-24 14:05:46
//  # Description: Function to remove a link in a linked list
// **************************************************
int rmlink(struct linkedList * LinkedList, struct link * Link)
{
    if (LinkedList->head == NULL || LinkedList->tail == NULL || LinkedList->size <= 0 || Link == NULL){return EXIT_FAILURE;}

    // The link is alone
    if (Link == LinkedList->head && Link == LinkedList->tail)
    {
        free(Link);
        LinkedList->head = NULL;
        LinkedList->tail = NULL;
        LinkedList->size = 0;
        return EXIT_SUCCESS;
    }

    // The link is in first position
    if (Link == LinkedList->head)
    {
        LinkedList->head = Link->nextLink;
        LinkedList->size--;
        free(Link);
        return EXIT_SUCCESS;
    }

    // research of the link
    struct link * tmp = LinkedList->head;
    struct link * previous = NULL;
    while (tmp != Link && tmp != NULL)
    {
        previous = tmp;
        tmp = tmp->nextLink;
    } 

    // The link is the tail
    if (Link == LinkedList->tail)
    {
        LinkedList->tail = previous;
        LinkedList->tail->nextLink = NULL;
        free(Link);
        LinkedList->size--;
        return EXIT_SUCCESS;
    }

    // The link is in middle
    if (tmp == Link && previous != NULL && tmp->nextLink != NULL)
    {
        previous->nextLink = Link->nextLink;
        free(Link);
        LinkedList->size--;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-24 14:05:46
//  # Description: Function to switch two following link in the linked list
// **************************************************
int switchLink(struct linkedList * LinkedList, struct link * fLink, struct link * sLink)
{
    if (LinkedList == NULL || LinkedList->head == NULL || LinkedList->tail == NULL || LinkedList->size < 2 || fLink == NULL || sLink == NULL || sLink != fLink->nextLink){return EXIT_FAILURE;}

    // If the first link is the head and the second link is the tail
    if (fLink == LinkedList->head && sLink == LinkedList->tail)
    {
        sLink->nextLink = fLink;
        fLink->nextLink = NULL;
        LinkedList->head = sLink;
        LinkedList->tail = fLink;
        return EXIT_SUCCESS;
    }

    // If the first link is the head
    if (fLink == LinkedList->head)
    {
        fLink->nextLink = sLink->nextLink;
        sLink->nextLink = fLink;
        LinkedList->head = sLink;
        return EXIT_SUCCESS;
    }

    // If the second link is the tail
    if (sLink == LinkedList->tail)
    {
        struct link * previous = LinkedList->head;

        while (previous->nextLink != fLink && previous != NULL)
        {
            previous = previous->nextLink;
        }

        previous->nextLink = sLink;
        sLink->nextLink = fLink;
        fLink->nextLink = NULL;
        LinkedList->tail = fLink;
        return EXIT_SUCCESS;
    }

    // If both arstruct link * previous = LinkedList->head
    if (fLink != LinkedList->head && sLink != LinkedList->tail && fLink->nextLink == sLink)
    {
        struct link * previous = LinkedList->head;

        while (previous->nextLink != fLink && previous != NULL)
        {
            previous = previous->nextLink;
        }

        fLink->nextLink = sLink->nextLink;
        sLink->nextLink = fLink;
        previous->nextLink = sLink;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
