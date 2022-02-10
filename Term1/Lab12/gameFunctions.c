#include "struct.h"

// Компаратор по имени
int compareByName(game record1, game record2)
{
    return strcmp(record1.name, record2.name);
}

// Компаратор по разработчику
int compareByDeveloper(game record1, game record2)
{
    return strcmp(record1.developer, record2.developer);
}

// Компаратор по издателю
int compareByPublisher(game record1, game record2)
{
    return strcmp(record1.publisher, record2.publisher);
}

// Компаратор по рейтингу
int compareByRating(game record1, game record2)
{
    return record1.rating > record2.rating;
}