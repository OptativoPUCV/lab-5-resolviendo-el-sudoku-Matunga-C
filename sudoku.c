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

/*- No se repitan números en las filas
- No se repitan números en las columnas
- No se repitan números en las submatrices de 3x3*/

int is_valid(Node* n){
    int i,j,k;
    int row[9][10] = {0}; // filas
    int col[9][10] = {0}; // columnas
    int box[3][3][10] = {0}; // submatrices de 3x3
    for(i = 0; i < 9; i++) { // recorrer el sudoku
        for(j = 0; j < 9; j++) { // recorrer el sudoku
            if(n->sudo[i][j] != 0) { // si la celda no es 0, es decir, no es vacia
                k = n->sudo[i][j]; // asignar el valor de la celda a k
            }
          }    
    }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList(); // crear una nueva lista
    Node* aux; // crear un nuevo nodo
    int i, j, k; // variables para recorrer el sudoku
    for(i = 0; i < 9; i++) { // recorrer el sudoku
        for(j = 0; j < 9; j++) { // recorrer el sudoku
            if(n->sudo[i][j] == 0) { // si la celda es 0, es decir, vacia
                for(k = 1; k <= 9; k++) { // probar con los numeros del 1 al 9
                    aux = copy(n); // copiar el nodo actual
                    aux->sudo[i][j] = k; // asignar el nuevo valor
                    if(is_valid(aux)) { // si es valido, agregar a la lista
                        pushBack(list, aux); // agregar el nodo a la lista
                    }
                }
                return list; // retornar la lista
            }
        }
    }
    return list; // si no hay celdas vacias, retornar la lista vacia
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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