#ifndef __MAZE
#define __MAZE 1
#include "handy.h"

/* You may reset these to special printer codes for BLOCKS and BLANKS */
#define BLOCK '#' /* ((char)0xdb) */
#define BLANK ' '

/* The Maze is always a square */
typedef struct MAZE_TAG * Maze;

/* This allocates all the area you need for your Maze.
It is assumed that the maze is square therefore you need only
pass the dimension of one side of the maze.
*/
Maze Create_Maze (int size);

/* This will get rid of a previously allocated Maze variable.
DO NOT SIMPLY USE free(maze)! This will only discard the pointer.
There is hidden data that most be disposed of properly. You will get
huge unreferenced allocated memory blocks if you don't use this destructor.
*/
void Destroy_Maze (Maze m);

/* Prints the maze to stdout using the characters defined as
BLOCK and BLANK. You may define these characters to whatever looks
pretty on your stdout device.
*/
void Print_Maze (Maze m);


/* This puts one of the basic elemental mazes into the Maze.
The elemental mazes are 3x3 in dimension. One of the possible
six is chosen at random and then copied into the Maze starting
at location (0,0).
*/
void Random_Basic_Element (Maze m);

/* This is the basic client interface function to the algorithm
which builds the maze using a DIVIDE-AND-CONQUER recursive fractal
technique. The Maze is taken and then filled by recursive quarterings
with a maze. The only prerequisite is that the Maze size be preset to
correspond with the number of levels of recursion you want this
algorithm to descend. That size is based on 4 to the power of the
number of recursive levels.
*/

void Build_Maze (Maze m);
/* This is used to combine four mazes into one Super_Maze(tm). */
void Combine_Submazes_Into_Maze(Maze m, Maze mq1, Maze mq2, Maze mq3, Maze mq4);

/* Get an element from the (x,y) coordinate of the Maze */
char Maze_Get (Maze m, int x, int y);

/* Put and element into the (x,y) coordinate of the Maze */
void Maze_Put (Maze m, int x, int y, char c);

/* Find out the dimension of one side of the square Maze */
int  Maze_Size (Maze m);
#endif

