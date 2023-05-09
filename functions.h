#include "objects.h"
using namespace std;

void isNull(Tile* var){
    //for(int y=0; y<5; y++){
        //for(int x=0; x<5; x++){
        //    if(var[y][x]==NULL) cout << "NULL ";
        //    else cout << var[y][x] << ' ';
        //}
    //    cout << '\n';
    //}
    if(var==NULL) cout << "NULL\n";
}

Tile* findEntityByStr(string name){
    for(int i=0; i<sizeof(e)/sizeof(Entity);i++)
        if(e[i]->getName()==name) return e[i];
    return new Entity;
}

void genFromInput(int maze_input[5][5], Tile* (&maze_output)[5][5], const int maze_size){
    for(int y=0; y<maze_size; y++){
        for(int x=0; x<maze_size; x++){
            if(maze_input[y][x]<tile_n) maze_output[y][x]=t[maze_input[y][x]];
            else maze_output[y][x]=t[0];
        };
    }
}

void nextTurn(){
    cout << "|=== NEXT TURN! ===|\n";
}

void genMap(Tile* (&dynmaze)[5][5], Tile* stamaze[5][5], Tile* entmaze[]){
    const int maze_size=sizeof(dynmaze)/sizeof(dynmaze[0]), list_size=sizeof(entmaze)/sizeof(entmaze[0]);
    for(int y=0; y<maze_size; y++){
        for(int x=0; x<maze_size; x++) dynmaze[y][x]=stamaze[y][x];
    }
    for(int y=1; y<list_size; y++) dynmaze[entmaze[y]->coords.getCoords()][entmaze[y]coords.x];
    nextTurn();
}
void renMap(Tile* this_maze[][5], const int maze_size){
    string ren_maze[maze_size];
    for(int y=0; y<maze_size; y++){
        for(int x=0; x<maze_size; x++){ 
            ren_maze[y][x]=this_maze[y][x]->getTxt();
            cout << ren_maze[y][x];
        }
        cout  << '\n';
    }
}

void additional_ui(Entity* entity){
    entity->statistics.print_hp();
    cout << "\t\t";
    cout << "DIR: " << entity->direction.get_dir();
    cout << '\n';
    entity->statistics.print_att();
    cout << "\t\t";
    cout << "WEP: ";
    if(entity->hand==NULL) cout << "None.";
    else cout << entity->hand->name;
    cout << '\n';
}