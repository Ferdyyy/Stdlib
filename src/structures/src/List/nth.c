/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


int nth( int n, ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now:
 * -  int n;
 * - list *elems;
 * -  int *__elems_rc;
 */
  list *ptr;
  int res;

  if( n<0)
    __SAC__Runtime_Error( "negative first arg of nth\n");

  ptr = elems;
  while( n>0) {
    ptr=ptr->rest;
    if( ptr->rest == NULL)
      __SAC__Runtime_Error( "first arg of nth %d larger than length of list\n", n);
    n--;
  }
  res = ptr->elem;

  if(--elems->rc == 0)
    free_list( elems);

  return( res);
}
