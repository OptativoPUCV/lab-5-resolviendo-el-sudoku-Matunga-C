#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i,j,k;
    int row[9][10] = {0};
    int col[9][10] = {0};
    int box[3][3][10] = {0};
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            if(n->sudo[i][j] != 0) {
                k = n->sudo[i][j];
                if(row[i][k] || col[j][k] || box[i/3][j/3][k]) {
                    return 0;
                }
            }
            if(n->sudo[i][j] != 0) {
                k = n->sudo[i][j];
                row[i][k] = 1;
                col[j][k] = 1;
                box[i/3][j/3][k] = 1;
            }
        }    
    }
    return 1;
}

List* get_adj_nodes(Node* n){
    List* list=createList();
    Node* aux;
    int i, j, k;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            if(n->sudo[i][j] == 0) {
                for(k = 1; k <= 9; k++) {
                    aux = copy(n);
                    aux->sudo[i][j] = k;
                    if(is_valid(aux)) {
                        pushBack(list, aux);
                    }
                }
                return list;
            }
        }
    }
    return list;
}

int is_final(Node* n){
    int i,j;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            if(n->sudo[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    List* stack = createStack();
    push(stack, initial);
    Node* current;
    while(!is_empty(stack)) {
        current = top(stack);
        pop(stack);
        (*cont)++;
        if(is_final(current)) {
            return current;
        }
        List* adj = get_adj_nodes(current);
        Node* aux;
        aux = first(adj);
        while(aux != NULL) {
            if(is_valid(aux)) {
                push(stack, aux);
            }
            aux = next(adj);
        }
        clean(adj);
    }
    return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/