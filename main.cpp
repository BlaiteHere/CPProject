/*By BlaiteHere#8818 DC: https://discord.gg/CcHYxcSctv

    TO-DO:
     - CHESTS
     - MORE AI
    
    I    CAN      IMPLEMENT   BY: 
     - VIRTUAL FUNCTION (HARD)
     > CHEST ENTITY & DYNAMIC AND 
       'STATIC ARRAYS' (EASY)
*/
#include <iostream>
using namespace std;
//----------------------------------------------------
struct Directions{  //boolean direction (00=up, 01=right, 10=down, 11=left)
    bool one, two;
    Directions(){
        one=false, two=false;
    }
    Directions(bool eins, bool zwei){
        one=eins, two=zwei;
    }
    string get_dir(){
        if(!one && !two) return "UP";
        if(!one && two) return "RIGHT";
        if(one && !two) return "DOWN";
        if(one && two) return "LEFT";
        return "ERROR";
    };
};
struct Stats{
    int health, attack, m_health;   //max health
    Stats(){
        health=3, attack=1, m_health=health;
    }
    Stats(int hp, int att){
        health=hp, attack=att, m_health=hp;
    }
    void print_hp(){
        cout << "HP: " << health << '/' << m_health;
    }
    void print_att(){
        cout << "ATK: " << attack;
    }
};
struct Axis{
    int x, y;
    Axis(){
        x=5, y=5;
    }
    Axis(int x, int y){
        this->x = x, this->y = y;
    }
    void print(){
        cout << "[x: " << x << ", y: " << y << "]";
    }
};
struct Tile{
    bool solid;     //true=solid tile, eg. wall; false=you can walk on it, eg. floor
    char texture;   //how it should be rendered
    Tile(){
        solid=true, texture=' ';
    }
    Tile(bool tile_solid, char tile_txt){
        solid=tile_solid, texture=tile_txt;
    }
    virtual void open(){
        cout << "THIS DOESN'T WORK";
    }
    virtual char getTile(){
        return texture;
    }
    virtual bool isSolid(){
        return solid;
    }
};
struct Item{
    bool weapon;    //true=the item is a weapon; false=the item is NOT a weapon
    string name;    //item name
    char texture;   //basic item appearance
    int canBreak;   //what can item break
    Item(){
        name="Unknown", texture='E', canBreak=0, weapon=false;
    }
    Item(string item_name, char item_txt, int item_destroy, bool item_weapon=false){
        name=item_name, texture=item_txt, canBreak=item_destroy, weapon=item_weapon;
    }
    void use(){
        cout << "";
    }
};
struct Inventory{
    int selected=0;
    int array_quantity[3];
    Item* array_types[3];
    Inventory(){
        for(int i=0; i<3; i++){
            array_quantity[i]=0;
            array_types[i]=NULL;
        }
    }
    Inventory(Item* an_array[3]){
        for(int i=0; i<3; i++){
            array_quantity[i]=1;
            array_types[i]=an_array[i];
        }
    }
    Inventory(Item* an_array[3], int amounts[3]){
        for(int i=0; i<3; i++){
            array_quantity[i]=amounts[i];
            array_types[i]=an_array[i];
        }
    }
    void print(){           //prints inventory
        bool sel=false;
        for(int i=0; i<3; i++){
            if(i==selected) sel=true;
            else sel=false;
            if(sel) cout << '>';
            else cout << '{';

            cout << array_quantity[i] << "x\t";

            if(array_types[i]==NULL) cout << "Nothing";
            else cout << array_types[i]->name; 

            if(sel) cout << '<';
            else cout << '}';
            cout << "\n";
        }
    }
    void use(int index){    //using item
        if(array_types[index]!=NULL){
            cout << "You used " << array_types[index]->name << ".\n";
            array_quantity[index]--;
            if(array_quantity[index]<0) array_types[index]=NULL;
        }                   //"uses" item
    }
    void append(Item &added_item, int quantity=1){
        for(int i=0; i<3; i++)
            if(array_types[i]==NULL){
                array_types[i]=&added_item;
                array_quantity[i]=quantity;
                return;     //adds an item to the inventory
            }
        cout << "Your inventory is full!";
    }
};
struct Entity: Tile{
    bool solid=true;
    char texture;
    int ai=0, stage=0;
    Axis coords;
    Stats statistics;
    Inventory inv;
    Directions direction;
    Item* hand;
    Entity(){
        texture='E';
        coords=Axis();
        hand=NULL;
        solid=false;
        ai=0;

    }           //type1, 0 args: default
    Entity(char entity_txt, Item entity_hand, int moves, Stats statz=Stats()){
        texture=entity_txt, hand=&entity_hand, ai=moves, statistics=statz;
    }           //type2, 3-4 args: txt, hand, ai, stats=d
    Entity(char entity_txt, Axis entity_coords, int moves, Stats statz, Item &entity_hand, Inventory bagpack=Inventory());
    virtual void move(bool one, bool two);
    virtual void make_move();
};
struct Chest: Tile{
    bool solid=false;
    Item* inside;
    Chest(){
        inside=NULL;
    }
    Chest(Item* chest_inside){
        inside=chest_inside;
    }
    void open(Entity* pointer){
        pointer->inv.append(*inside);
        delete(this);
    };
    char getTile(){
        return 'A';
    }
    bool isSolid(){
        return solid;
    }
};
Item items[]={                          //  ITEMS PROGRAMMED IN:
    Item(),                             //UNKNOWN
    Item("Axe", 'T', 3, true),          //AXE
    Item("Money", 'm', 0, 0)
};
Tile* blocks[]={             //  TILES PROGRAMMED IN:
    new Tile(),                 //ERROR BLOCK           0
    new Tile(true, '-'),        //WALL                  1
    new Tile(false, ' '),       //FLOOR                 2
    new Tile(true, '`'),        //WOOD                  3
    new Chest(&items[2])        //CHEST                 4
};
Item* myArray[3]={&items[1], &items[0]};                    //HEREEEE
Item* pointy=NULL;
Entity temp[]={             //  MONSTERS PROGRAMMED IN:
    Entity('Z', items[0], 1)       //ZOMBIE
};
Entity::Entity(char entity_txt, Axis entity_coords, int moves, Stats statz, Item &entity_hand, Inventory backpack){
    texture=entity_txt, coords=entity_coords, ai=moves, statistics=statz, hand=&entity_hand, inv=backpack;
}           //type3, 3-6 args: txt, axis, ai, stats=d, hand=d, inv=d;
Entity dynamic_maze[]={
    Entity('P', Axis(1,1), 0, Stats(6, 2), *pointy, Inventory(myArray)),
    Entity('Z', Axis(3, 3), 1, Stats(), items[0])
};
//------------------------------------------------------
bool mode=1;                //true=maze, false=inventory
Entity* player = &dynamic_maze[0];
const int h=7, w=14;         //height, width (of the maze);
string maze_input[h]={       //You can change this to whatever you want! anything that
    "WWW_WCWW",              // won't be recognised in generateMaze() will be just a
    "____W__W",              //                      solid wall.
    "W_W_WW_W",              
    "W_____________",              //              W: WALL, _: FLOOR, C: CHEST.
    "W/WWWW_W",
    "W______W",
    "W_"
};
Tile* static_maze[h][w];
string current_render[h];
char* blaite = NULL;        // Useless.
//------------------------------------------------------
void Entity::move(bool one, bool two){
    direction.one=one, direction.two=two;
    if(!direction.one && !direction.two && !static_maze[coords.y-1][coords.x]->solid){          //up
        coords.y--;         //boolean movement (00=up, 01=right, 10=down, 11=left)
    } else if(direction.one && !direction.two && !static_maze[coords.y+1][coords.x]->solid){    //down
        coords.y++;         //&& (collision)
    } else if(!direction.one && direction.two && !static_maze[coords.y][coords.x+1]->solid){    //right
        coords.x++;
    } else if(direction.one && direction.two && !static_maze[coords.y][coords.x-1]->solid){     //left
        coords.x--;
    }
}
void Entity::make_move(){
    //cout << stage << '\t';
    if(!static_maze[coords.y][coords.x]->solid){
        switch(ai){
            case 1:     //(simple ai)
                if(stage<2){
                    move(false, false);//up
                } else if(stage==2 || stage==3){
                    move(false, true);//right
                }
                else if(stage==4 || stage==5){
                    move(true, false);//down
                }
                else if(stage>5){
                    move(true, true);//left
                }
                if(stage>6) stage=0;
                else stage++;
                break;
        }
    }
}
//void loadMaze();
void input(bool input_mode){    //player (for maze) input
    char listener;
    cout << "\n>>> ";
    cin >> listener;
    if(mode)
        switch(listener){
            case 'w':           //(collision & movement/input)
                if(player->coords.y-1 >= 0 && !static_maze[player->coords.y-1][player->coords.x]->solid)
                    player->coords.y--;
                    player->direction.one=false, player->direction.two=false;
                break;
            case 's':
                if(player->coords.y+1 < h && !static_maze[player->coords.y+1][player->coords.x]->solid)
                    player->coords.y++;
                    player->direction.one=true, player->direction.two=false;
                break;
            case 'a':
                if(player->coords.x-1 >= 0 && !static_maze[player->coords.y][player->coords.x-1]->solid)
                    player->coords.x--;
                    player->direction.one=true, player->direction.two=true;
                break;
            case 'd':
                if(player->coords.x+1 < w && !static_maze[player->coords.y][player->coords.x+1]->solid)
                    player->coords.x++;
                    player->direction.one=false, player->direction.two=true;
                break;
            case 'e':           //inventory
                mode=!mode;     //switch
                break;
            case 'q':           //interact
                if(static_maze[player->coords.y][player->coords.x]==blocks[4])
                    static_maze[player->coords.y][player->coords.x]->open();
                
                break;
        }
    else
        switch(listener){
            case 'e':
                mode=!mode;     //switch
                break;
            case 's':
                if(player->inv.selected==2) player->inv.selected=0;
                else player->inv.selected++;
                break;
            case 'w':
                if(player->inv.selected==0) player->inv.selected=2;
                else player->inv.selected--;
                break;
            case 'q':           //check if item exists, then if item is a weapon
                if(player->inv.array_types[player->inv.selected] != NULL){
                    if(player->inv.array_types[player->inv.selected]->weapon){
                        cout << "Equipped " <<player->inv.array_types[player->inv.selected]->name << ".\n";
                        player->hand = player->inv.array_types[player->inv.selected];
                    } else {
                        player->inv.use(player->inv.selected);
                        player->inv.array_types[player->inv.selected] = NULL;
                    }}
                break;
        }
}
void moveEntities(){
    int ELS=sizeof(dynamic_maze)/sizeof(Entity);
    for(int i=1; i<ELS; i++) dynamic_maze[i].make_move();
}
void setTile(Axis block_axis, Tile* block){
    static_maze[block_axis.y][block_axis.x] = block;
}
void generateMaze(){;
	for(int y=0; y<h; y++)
		for(int x=0; x<w; x++)
            switch(maze_input[y][x]){
                default:
                    setTile(Axis(x, y), blocks[1]);
                    break;
                case '_':
                    setTile(Axis(x, y), blocks[2]);
                    break;
                case '/':
                    setTile(Axis(x, y), blocks[3]);
                    break;
                case 'C':
                    setTile(Axis(x, y), blocks[4]);
                    break;
            };
}
void renderMaze(){      //renders maze  from  static_maze  and  dynamic maze
    int y_start, y_end; //from pointers/objects to strings, then prints them
    if(player->coords.y<3) y_end=5, y_start=0;
    else {
        if(player->coords.y>h-3) y_end=h, y_start=h-5;
        else y_end=player->coords.y+3, y_start=player->coords.y-2;
    }
    int x_start, x_end;
    if(player->coords.x<3) x_end=5, x_start=0;
    else {
        if(player->coords.x>w-3) x_end=w, x_start=w-5;
        else x_end=player->coords.x+3, x_start=player->coords.x-2;
    }
    int ELS=sizeof(dynamic_maze)/sizeof(Entity);
    for(int y=0; y<h; y++){ //maze render
		for(int x=0; x<w; x++){
            Tile* wall=blocks[1];
            if(static_maze[y][x] == wall)
                if(x>0 && static_maze[y][x-1]==wall){
                    if(x<w && static_maze[y][x+1]==wall) current_render[y][x] = '-';
                    else current_render[y][x] = '+';
                } else {
                    if(y<h && static_maze[y+1][x]==wall && y>0 && static_maze[y-1][x]==wall) 
                            current_render[y][x] = '|';
                        else current_render[y][x] = '+';
                }
            else current_render[y][x] = static_maze[y][x]->getTile();
        }
	}
    for(int i=0; i<ELS; i++){ //entity render
		if(dynamic_maze[i].solid) 
            current_render[dynamic_maze[i].coords.y][dynamic_maze[i].coords.x] = dynamic_maze[i].texture;
	}
	for(int y=y_start; y<y_end; y++){ //whole render renderer
        cout << '\t';
		for(int x=x_start; x<x_end; x++) cout << current_render[y][x]; //<< current_render[y][x];
        cout << '\n';
	}
}
void additional_ui(){
    player->statistics.print_hp();
    cout << "\t\t";
    cout << "DIR: " << player->direction.get_dir();
    cout << '\n';
    player->statistics.print_att();
    cout << "\t\t";
    cout << "WEP: ";
    if(player->hand==NULL) cout << "None.";
    else cout << player->hand->name;
    cout << '\n';
}
//------------------------------------------------------
int main(){
    //loadMaze();
    cout << "Znak skrzyni: " << blocks[4]->getTile() << ".\n";
    delete(blaite);
    generateMaze();
    while(true){
        if(mode) renderMaze();
        else player->inv.print();
        cout << '\n';
        additional_ui();
        input(mode);
        if(mode) moveEntities();
    }
    return mode;
}