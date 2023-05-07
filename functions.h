#include "objects.h"
using namespace std;

void genFromInput(int maze_input[][5], Tile* maze_output[][5]){
    for(int y=0; y<5; y++){
        for(int x=0; x<5; x++) 
            switch(maze_input[y][x]){
                case 0:
                    //maze_output=;     WIP
                    break;
            };
    }
}

void nextTurn(){
    cout << "NEXT TURN!\n";
}

void genMap(Tile* dynmaze[][5], Tile* stamaze[][5], Tile* entmaze[]){
    for(int y=0; y<5; y++){
        for(int x=0; x<5; x++) dynmaze[y][x]=stamaze[y][x];
    }
    for(int y=0; y<1; y++) entmaze[0];
    nextTurn();
}
void renMap(Tile* this_maze[][5]){
    string ren_maze[5];
    for(int y=0; y<5; y++){
        for(int x=0; x<5; x++) cout << this_maze[y][x]->getTxt();
        cout << '\n';
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