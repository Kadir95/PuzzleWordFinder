#include "assigment.h"
#include "linkedlist.h"
#include <stdio.h>
#include <string.h>

linkedNode * find_last_node(linkedNode *baseNode){
    if(!baseNode){
        printf("Error at find_last_node: baseNode is NULL\n");
        return NULL;
    }

    linkedNode *walker = baseNode;

    while(NEXT_NODE(walker)){
        walker = NEXT_NODE(walker);
    }

    return walker;
}

void set_linkedNode(linkedNode *target, char *word){
    if(!target){
        printf("Error at set_linkedNode: target is NULL\n");
        if(!word){
            printf("Error at set_linkedNode: word is NULL\n");
        }
        return;
    }

    target->data = (char *) malloc(strlen(word));

    strcpy(target->data, word);
}

linkedNode * add_linkedNode(linkedNode *target){
    if(NEXT_NODE(target)){
        printf("Error at add_linkedNode: target already has next node\n");
    }

    return NEXT_NODE(target) = create_linkedNode();
}

linkedNode * create_linkedNode(){
    linkedNode *created = (linkedNode *) malloc(sizeof(linkedNode));
    NEXT_NODE(created) = NULL;
    created->data = NULL;
    IT_IS_NOT_VALID(created);
    return created;
}

void print_linkedList(linkedNode *root){
    if(!root){
        printf("Error at print_linkedList: root is NULL\n");
        return;
    }

    linkedNode *walker = root;

    while(walker){
        printf("%s -> ",walker->data);
        walker = walker->next;
    }
}

char * get_word(linkedNode *target){
    if(!target){
        printf("Error at get_word: target is NULL\n");
        return "Error\n";
    }
    if(!target->data){
        printf("Error at get_word: target's data is NULL\n");
        return "Error\n";
    }

    char *newChar = (char *) malloc(sizeof(char) * strlen(target->data));
    strcpy(newChar, target->data);

    return newChar;
}
