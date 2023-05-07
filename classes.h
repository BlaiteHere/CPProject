#include <iostream>
using namespace std;

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
    int health, attack;   //max health
    Stats(){
        health=3, attack=1;
    }
    Stats(int hp, int att){
        health=hp, attack=att;
    }
    const int m_health=health;
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
        x=0, y=0;
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
    string name;
    Tile(){
        name="Unknown", solid=true, texture=name[0];
    }
    Tile(string tile_name, bool tile_solid, char tile_txt){
        name=tile_name, solid=tile_solid, texture=tile_txt;
    }
    virtual bool isSolid(){
        return solid;
    };
    virtual char getTxt(){
        return texture;
    };
    virtual string getName(){
        return name;
    };
};

struct Item{
    string name;    //item name
    char texture;   //basic item appearance
    int canBreak;   //what can item break
    Item(){
        name="Unknown", texture='E', canBreak=0;
    }
    Item(string item_name, char item_txt, int item_destroy){
        name=item_name, texture=item_txt, canBreak=item_destroy;
    }
    void use(){
        cout << "";        //IMPLEMENT THIS!
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
    void print(){           //prints inventory
        bool sel=false;     //bool sel(ected item)
        for(int i=0; i<3; i++){
            if(i==selected) sel=true;
            else sel=false;
            if(sel) cout << '>';
            else cout << '{';

            cout << array_quantity[i] << "x\t";

            if(array_types[i]==NULL) cout << '-';
            else cout << array_types[i]->name; 

            if(sel) cout << '<';
            else cout << '}';
            cout << "\n";
        }
    }
    void use(int index){    //"uses" item
        if(array_types[index]!=NULL){
            cout << "You used " << array_types[index]->name << ".\n";
            array_quantity[index]--;
            if(array_quantity[index]<0) {
                array_types[index]=NULL;
                array_quantity[index]=0;
            }
        }
    }
    void append(Item* &added_item, int quantity=1){
        for(int i=0; i<3; i++)  
            if(array_types[i]==NULL){
                array_types[i]=added_item;
                array_quantity[i]=quantity;
                return;     //adds an item to the inventory
            } else {
                if(array_types[i]==added_item){ 
                    array_quantity[i]++;
                    return;
                }
            }
        cout << "Your inventory is full!";
    }
};

struct Entity: Tile{
    bool solid;
    char texture;
    string name;
    Axis coords;
    Stats statistics;
    Inventory inv;
    Directions direction;
    Item* hand;
    Entity(){
        name="Dynamik", solid=true, texture=name[0], coords.x=0, coords.y=0;
    }
    Entity(string tile_name, char tile_txt, bool tile_solid=true, int x=1, int y=1){
        name=tile_name, texture=tile_txt, solid=tile_solid, coords.x=x, coords.y=y;
    }
    bool isSolid(){
        return solid;
    };
    char getTxt(){
        return texture;
    };
    string getName(){
        return name;
    };
};