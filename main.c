#include <stdio.h>
#include <stdlib.h>
#include "assigment.h"
#include "linkedlist.h"
#include "tree.h"
#include <time.h>
#include "puzzle.h"

void random_char_array_filler(char puzzle[MAX_LENGTH][MAX_LENGTH]);
void print_char_array(char puzzle[MAX_LENGTH][MAX_LENGTH]);
void puzzle_word_finder(char puzzle[MAX_LENGTH][MAX_LENGTH], int x, int y, int **preCoor, char *preChar, linkedNode *tail, int depth);
void init_direction_additions();
int does_it_passed(int x, int y, int **array, int depth);
void add_file_to_tree(const treeNode *root, char *fileName);

int main()
{
    init_direction_additions();

    linkedNode *linkedroot = create_linkedNode();
    treeNode *treeroot = create_treeNode();

    add_file_to_tree(treeroot, "TurkishWords.txt");

    char puzzle[MAX_LENGTH][MAX_LENGTH];
    random_char_array_filler(puzzle);

    printf("\t<|-| PUZZLE |-|>\n");
    print_char_array(puzzle);
    printf("\t<|-| PUZZLE |-|>\n\n\n");

    printf("-> There will be some errors\n");
    linkedNode *tail = linkedroot;
    
    for(int i = 0; i < MAX_LENGTH; i++){
        for(int j = 0; j < MAX_LENGTH; j++){
            puzzle_word_finder(puzzle, i, j, NULL, NULL, tail, 0);
            tail = find_last_node(tail);
        }
    }

    mark_valid(linkedroot, treeroot);

    printf("\n\n\t>> VALID WORDS <<\n");
    print_valid_words(linkedroot);

    return 0;
}

void init_direction_additions(){
    int count = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            direction_additions[count][0] = j - 1;
            direction_additions[count][1] = i - 1;
            count++;
        }
    }
}

void random_char_array_filler(char puzzle[MAX_LENGTH][MAX_LENGTH]){
    srand(time(NULL));
    for(int i = 0; i < MAX_LENGTH; i++){
        for(int j = 0; j < MAX_LENGTH; j++){
            puzzle[i][j] = rand()%26 + 97;
        }
    }
}

void print_char_array(char puzzle[MAX_LENGTH][MAX_LENGTH]){
    for(int i = 0; i < MAX_LENGTH; i++){
        printf("\t  ");
        for(int j = 0; j < MAX_LENGTH; j++){
            printf("%c ",puzzle[i][j]);
        }
        printf("\n");
    }
}

void puzzle_word_finder(char puzzle[MAX_LENGTH][MAX_LENGTH], int x, int y, int **preCoor, char *preChar, linkedNode *tail, int depth){
    if((x < 0 || x == MAX_LENGTH) || (y < 0 || y == MAX_LENGTH)){
        return;
    }
    if(depth == MAX_CHAR){
        return;
    }

    int **newPreCoor = (int **) malloc(sizeof(int *) * MAX_CHAR);
    for(int i = 0; i < MAX_CHAR; i++){
        newPreCoor[i] = (int *) malloc(sizeof(int) * 2);
        if(i < depth){
            memcpy(newPreCoor[i], preCoor[i], sizeof(int) * 2);
        } else {
            newPreCoor[i][0] = -1;
            newPreCoor[i][1] = -1;
        }
    }
    newPreCoor[depth][0] = x;
    newPreCoor[depth][1] = y;

    char *newPreChar = (char *) malloc(sizeof(char) * MAX_CHAR);
    for(int i = 0; i < MAX_CHAR; i++){
        if(i < depth){
            newPreChar[i] = preChar[i];
        } else {
            newPreChar[i] = '\0';
        }
    }
    newPreChar[depth] = puzzle[x][y];

    set_linkedNode(tail, newPreChar);
    tail = add_linkedNode(tail);

    int a = 0;
    int b = 0;
    for(int i = 0; i < 9; i++){
        a = direction_additions[i][0];
        b = direction_additions[i][1];

        if(does_it_passed(x + a, y + b, newPreCoor, depth + 1)){
            continue;
        }

        tail = find_last_node(tail);

        puzzle_word_finder(puzzle, x + a, y + b, newPreCoor, newPreChar, tail, depth + 1);
    }

    #if TEST > 1
    printf("depth: %d | %s\n",depth, newPreChar);
    #endif // TEST

    free(newPreChar);
    for(int i = 0; i < MAX_CHAR; i++){
        free(newPreCoor[i]);
    }
    free(newPreCoor);
}

int does_it_passed(int x, int y, int **array, int depth){

    for(int i = 0; i < depth; i++){
        if(array[i][0] == x && array[i][1] == y){
            return 1;
        }
    }
    return 0;
}

void add_file_to_tree(const treeNode *root, char *fileName){
    if(!root){
        printf("Error at add_file_to_tree: root is NULL\n");
        return;
    }

    FILE *fp = fopen(fileName, "r");

    while(!feof(fp)){
        char temp[100];

        fscanf(fp, "%s\n",temp);

        char *result = (char *) malloc(sizeof(char) * (MAX_CHAR + 1));

        result[MAX_CHAR] = '\0';
        for(int i = 0; i < MAX_CHAR; i++){
            result[i] = temp[i];

            if(temp[i] == '\0' || temp[i] == '\n'){
                for(; i < MAX_CHAR; i++){
                    result[i] = '\0';
                }
            }
        }
        if(strlen(result) < MAX_CHAR + 1){
            #if TEST > 1
            printf(">> %s\n", result);
            #endif // TEST

            add_word_to_tree(root, result);
        }
        free(result);
    }
    fclose(fp);
}
