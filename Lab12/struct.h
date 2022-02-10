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

int compareByName(game record1, game record2);
int compareByDeveloper(game record1, game record2);
int compareByPublisher(game record1, game record2);
int compareByRating(game record1, game record2);

#endif
