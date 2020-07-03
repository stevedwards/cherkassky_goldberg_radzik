/***********************************************************/
/*                                                         */
/*               Executor of SP codes                      */
/*               (for Bellman-Ford)                      */
/*                                                         */
/***********************************************************/

#include <stdio.h>
#include <stdlib.h>

#define YES 1
#define NO 0
#define STATISTIC YES

/* statistical variables */
long n_scans;
long n_impr;

/* definitions of types: node & arc */
#include "../../data_structures/types_bf.h"

/* parser for getting extended DIMACS format input and transforming the
   data to the internal representation */
#include "../../parsers/parser_dh.c"

/* function 'timer()' for measuring processor time */
#include "../../utils/timer.c"

/* function for constructing shortest path tree */
#include "bf.c"

main()
{
  float t;
  arc *arp, *ta;
  node *ndp, *source, *k;
  long n, m, nmin, i;
  char name[21];
  double sum_d = 0;
  parse(&n, &m, &ndp, &arp, &source, &nmin, name);

  t = timer();

  bf(n, ndp, source);

  t = timer() - t;

  for (k = ndp; k < ndp + n; k++)
    if (k->parent != (node *)NULL)
      sum_d += (double)(k->dist);

  printf("\nNew Bellman-Ford -> problem name: %s\n\n\
Nodes: %ld    Arcs: %ld\n\
Number of scans: %ld\n\
Sum of distances: %.0f\n\n\
Running time of SP computation: %.2f\n\n",
         name, n, m, n_scans, sum_d, t);
}
