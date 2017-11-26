#ifndef PUZZLE_H
#define PUZZLE_H

#include "assigment.h"
#include "tree.h"
#include "linkedlist.h"

void mark_valid(const linkedNode *linkedroot, const treeNode *treeroot);
void print_valid_words(const linkedNode *linkedroot);

#endif // PUZZLE_H
