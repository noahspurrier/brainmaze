#ifndef __HANDY
#define __HANDY 1

#define elif      else if        /* Three new control structures for C! */
#define loop      for (;;)       
#define until(a)  while (!(a))   /* Usage:  do { ... } until (boolean); */

typedef unsigned char   CHAR;
typedef unsigned char   UCHAR;
typedef unsigned int    UINT;
typedef unsigned long   ULONG;
typedef enum {FALSE, TRUE} BOOL;

#include <time.h>
#include <stdio.h> /* for NULL * */
#include <stdlib.h>
#define randomize() (srand((UINT)time( (time_t *)NULL )))
#define random(a) (rand()%(a))

#define MIN(a,b)  (((a) < (b)) ?  (a) : (b) )
#define MAX(a,b)  (((a) > (b)) ?  (a) : (b) )

#define ABS(a)    (((a) < 0  ) ? -(a) : (a) )
#define FABS(a)   (((a) < F 0) ? -(a) : (a) )
#define DABS(a)   (((a) < 0.0) ? -(a) : (a) )

#define SIGN(a)   (((a) < 0  ) ?   -1 :   1 )
#define FSIGN(a)  (((a) < F 0) ? F(-1): F 1 )
#define DSIGN(a)  (((a) < 0.0) ? -1.0 : 1.0 )

#endif

