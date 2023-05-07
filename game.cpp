#include "functions.h"
using namespace std;

Tile* static_maze[5][5]={
    {t[0], t[0], t[0], t[0], t[0]},
    {t[0], t[1], t[1], t[1], t[0]},
    {t[0], t[1], t[0], t[1], t[0]},
    {t[0], t[1], t[1], t[1], t[0]},
    {t[0], t[0], t[0], t[0], t[0]}
};
Tile* dynamic_maze[5][5];
Tile* entity_list[]={e[0]};

int main(){
    genMap(dynamic_maze, static_maze, entity_list);
    renMap(dynamic_maze);
}