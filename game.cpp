#include "functions.h"
using namespace std;

bool* blaite = NULL;        // Useless.
const int s=5, es=1;
int input_maze[s][s]={
    {0,0,0,0,0},
    {0,1,1,1,0},
    {0,1,0,1,0},
    {0,1,1,1,0},
    {0,0,0,0,0}
};
Tile* static_maze[s][s];
Tile* dynamic_maze[s][s];
Tile* entity_list[es]={e[1]};

int main(){
    delete(blaite);
    genFromInput(input_maze, static_maze, s);
    //additional_ui(player);
    genMap(dynamic_maze, static_maze, entity_list);
    renMap(dynamic_maze, s);
    return 0;
}