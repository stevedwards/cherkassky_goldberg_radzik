/***********************************************************/
/*                                                         */
/*               Executor of SP codes                      */
/*               (for network simplex)                     */
/*                                                         */
/***********************************************************/


#include <stdio.h>
#include <stdlib.h>

#define YES 1
#define NO  0
#define STATISTIC YES

/* statistical variables */
long n_scans;
long n_piv = 0;
long n_impr;


/* definitions of types: node & arc */

#include "types_simp.h"

/* parser for getting extended DIMACS format input and transforming the
   data to the internal representation */

#include "parsers/parser_dh.c"

/* function 'timer()' for mesuring processor time */

#include "utils/timer.c"

/* function for constructing shortest path tree */

#include "simp.c"


main ()

{

float t;
arc *arp, *ta;
node *ndp, *source, *k;
long n, m, nmin, i; 
char name[21];
double sum_d = 0;

 parse( &n, &m, &ndp, &arp, &source, &nmin, name );

/*
printf ( "%s\nn= %ld, m= %ld, nmin= %ld, source = %ld\n",
        name,
        n,m,nmin, (source-ndp)+nmin );

printf ("\nordered arcs:\n");
for ( k = ndp; k< ndp + n; k++ )
  { i = (k-ndp)+nmin;
    for ( ta=k -> first; ta != (k+1)-> first; ta++ )
      printf ( " %2ld %2ld %4ld\n",
               i, ((ta->head)-ndp)+nmin, ta->len
             );

  }
*/

t = timer();

simp ( n, ndp, source );

t = timer() - t;

for ( k= ndp; k< ndp + n; k++ )
  if ( k -> parent != (node*) NULL )
   sum_d += (double) (k -> dist);

printf ("\nNetwork simplex -> problem name: %s\n\n\
Nodes: %ld    Arcs: %ld\n\n\
Number of scans:        %10d\n\
Number of pivots:       %10d\n\
Number of improvements: %10d\n\n\
Sum of distances:       %.0f\n\
Running time:           %.2f\n\n",
         name, n, m, n_scans, n_piv, n_impr, sum_d, t ); 

/* 
#define nd(ptr) (int)(ptr-ndp+nmin)
 for ( k=ndp; k< ndp+n; k++ )
printf (" %d %d %d\n", nd(k), nd(k->parent), k->dist);
*/
}
