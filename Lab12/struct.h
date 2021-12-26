#ifndef _STRUCTURE_GAME
#define _STRUCTURE_GAME
#define MAX_SIZE 30

typedef struct game
{
    char name[MAX_SIZE];
    char developer[MAX_SIZE];
    char publisher[MAX_SIZE];
    int rating;
}game;

#endif
