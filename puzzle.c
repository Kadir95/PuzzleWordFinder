#include <stdio.h>
#include "puzzle.h"

void mark_valid(const linkedNode *linkedroot, const treeNode *treeroot){
    if(!linkedroot){
        printf("Error at mark_valid: linkedroot is NULL\n");
        return;
    }
    if(!treeroot){
        printf("Error at mark_valid: treeroot is NULL\n");
        return;
    }

    linkedNode  *walker =   linkedroot;
    treeNode    *troot  =   treeroot;

    while(walker){
        if(is_it_a_valid_word(troot, walker->data)){
            IT_IS_VALID(walker);
        }
        walker = walker->next;
    }
}

void print_valid_words(const linkedNode *linkedroot){
    if(!linkedroot){
        printf("Error at print_valid_words: linkedroot is NULL\n");
        return;
    }

    linkedNode  *walker =   linkedroot;

    while(walker){
        if(walker->valid){
            printf("valid word : %6s\n",walker->data?walker->data:"DATA IS NULL!!");
        }

        walker = walker->next;
    }
}
