/*
 *  implementation of external standard module SysErr
 */


#include <stdio.h>
#include <string.h>

#include "icm2c.h"
#include "libsac.h"


/*****************************************************************/

extern char *strerror(int num);


/*****************************************************************/


char *SACstrerror(int num)
{
  char *buffer, *result;
  
  buffer=strerror(num);
  
  result=(char *)MALLOC(strlen(buffer)+1);
  strcpy(result, buffer);
  
  return(result);
}

/*****************************************************************/