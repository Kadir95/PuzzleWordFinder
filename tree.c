#include "assigment.h"
#include "tree.h"
#include <stdlib.h>

treeNode * create_treeNode(){
    treeNode *created = (treeNode *) malloc(sizeof(treeNode));
    created->child_num = 0;
    created->data = '\0';
    created->nextNodeList = NULL;
    created->valid = FALSE;
    return created;
}

treeNode * add_treeNode(treeNode *target){
    if(!target){
        printf("Error at add_treeNode: target is NULL\n");
        return NULL;
    }

    if(target->child_num == 0){
        target->nextNodeList = (treeNode **) malloc(sizeof(treeNode *) * (target->child_num + 1));
    }else{
        treeNode **temp;
        if(!(temp = (treeNode **) realloc(target->nextNodeList, sizeof(treeNode *) * (target->child_num + 1)))){
            temp = (treeNode **) malloc(sizeof(treeNode *) * (target->child_num + 1));
            for(register int i = 0; i < target->child_num; i++){
                temp[i] = target->nextNodeList[i];
            }
            free(target->nextNodeList);

        }
        target->nextNodeList = temp;
    }

    target->nextNodeList[target->child_num] = create_treeNode();
    return target->nextNodeList[target->child_num++];
}

treeNode * find_treeNode(treeNode *target, char finding_char){
    if(!target){
        printf("Error at find_treeNode: target is NULL\n");
        return NULL;
    }

    treeNode *temp = target;
    treeNode *walker;

    for(int i = 0; i < target->child_num; i++){
        walker = temp->nextNodeList[i];
        if(walker->data == finding_char){
            return walker;
        }
    }
    return NULL;
}

treeNode * go_to_treeNode(treeNode *target, int *road, int size){
    if(!target){
        printf("Error at go_to_treeNode: target is NULL\n");
        return NULL;
    }
    if(!road){
        printf("Error at go_to_treeNode: road is NULL\n");
        return NULL;
    }

    treeNode *walker = target;

    for(int i = 0; i < size; i++){
        if(walker->child_num > road[i]){
            walker = walker->nextNodeList[road[i]];
        }else{
            return NULL;
        }
    }

    return walker;
}

void add_word_to_tree(const treeNode *root, char *word){
    if(!root){
        printf("Error at add_word_to_tree: root is NULL\n");
        return;
    }
    if(!word){
        printf("Error at add_word_to_tree: word is NULL\n");
        return;
    }

    treeNode *walker = root;
    char *ch = word;
    while(*ch){
        treeNode *temp = find_treeNode(walker, *ch);
        if(temp){
            walker = temp;
        } else {
            temp = add_treeNode(walker);
            temp->data = *ch;
            walker = temp;
        }
        if(!*(++ch)){
            walker->valid = 1;
        }
    }
}

void print_child_nodes(treeNode *target){
    if(!target){
        printf("Error at print_child_nodes: target is NULL\n");
        return;
    }

    treeNode *walker = target;
    for(register int i = 0; i < walker->child_num; i++){
        printf("<%c%c> ", walker->nextNodeList[i]->data, walker->nextNodeList[i]->valid?'+':'-');
    }
    printf("\n");
}

char * create_a_word(treeNode *target, int *road, int size){
    if(!target){
        printf("Error at create_a_word: target is NULL\n");
        return NULL;
    }
    if(!road){
        printf("Error at create_a_word: road is NULL\n");
        return NULL;
    }

    char *result = (char *) malloc(sizeof(char) * size);
    treeNode *walker = target;

    for(int i = 0; i < size; i++){
        if(walker->child_num > road[i]){
            walker = walker->nextNodeList[road[i]];
        }else{
            return NULL;
        }
        result[i] = walker->data;
    }

    return result;
}

int is_it_a_valid_word(const treeNode *root, char *word){
    if(!root){
        printf("Error at is_it_a_valid_word: root is NULL\n");
        return 0;
    }
    if(!word){
        printf("Error at is_it_a_valid_word: word is NULL\n");
        return 0;
    }

    treeNode *walker = root;
    for(int i = 0; i < strlen(word); i++){
        treeNode *temp;
        if(temp = find_treeNode(walker, word[i])){
            walker = temp;
        }else{
            return 0;
        }
    }

    return walker->valid?1:0;
}
