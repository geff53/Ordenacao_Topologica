/*******************************************/
/* Aluno: Emanuel Gefferson Maciel Sampaio */
/* CES-11: Algoritmos para grafos          */
/* Turma T3                                */
/*******************************************/

#include "digraph.h"

int main() {
  DIGRAPH *digraph = digraph_read();
  topological_sort(digraph);
  digraph_destroy(digraph);
}
