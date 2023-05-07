#include "classes.h"
using namespace std;

Tile* t[]={
    new Tile("Wall", true, '#'),
    new Tile("Floor", false, '_')
};
Tile* e[]={
    new Entity("Zombie", 'Z')
};