#include "classes.h"
using namespace std;

const int tile_n=2;
Tile* t[tile_n]={     //Tiles
    new Tile("Wall", true, '#'),
    new Tile("Floor", false, '_')
};
Tile* e[]={     //Entities
    new Player("Player", 'P', 10, 5),
    new Entity("Zombie", 'Z', 5, 5)
};
Item* i[]={
    new Consumable("Apple", 'o', 5, "A red apple. Looks very delicious!")
};
Entity* player=(Entity*)e[0];