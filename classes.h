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
    Axis getCoords(){
        return Axis(x, y);
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
    string desc;    //item description
    Item(){
        name="Unknown", texture='E', 
        desc="This is a default item. Enjoy!";
    }
    Item(string item_name, char item_txt, string description){
        name=item_name, texture=item_txt, desc=description;
    }
    virtual void description(){
        cout << desc;
    }
    virtual void use(){
        description();      //IMPLEMENT THIS!
    }
};

struct Consumable: Item{
    string name;    //item name
    char texture;   //basic item appearance
    int heal;       //amount of healing
    string desc;
    Consumable(){
        name="Goo", texture='E', heal=-1,
        desc="Gross!";
    }
    Consumable(string item_name, char item_txt, int item_heal,
    string description){
        name=item_name, texture=item_txt, heal=item_heal,
        desc=description;
    }
    void description(){
        cout << desc;
    }
    void use(int &health){
        cout << "You used the" << name << " and ";
        if(heal>0) cout << "it healed you " << heal << "HP.";
        else{
            if(heal<0) cout << "you lost " << heal << " of HP.";
            if(heal>0) cout << "it did nothing. It was a good shot though.";
        }
        health=-heal;
    };
};

struct Tool: Item{
    string name;    //item name
    char texture;   //basic item appearance
    Tile* canBreak; //what can item break
    string desc;    //item description
    Tool(){
        name="Broken tool", texture='E', canBreak=NULL,
        desc="Looks very broken. And useless.";
    }
    Tool(string item_name, char item_txt, Tile* item_destroy,
    string description){
        name=item_name, texture=item_txt, canBreak=item_destroy,
        desc=description;
    }
    void description(){
        cout << desc;
    }
    void use(Directions looking_at, Axis where_its){
        bool one=looking_at.one, two=looking_at.two;

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
            array_types[index]->use();
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
    Directions direction;
    Item* hand=NULL;
    Entity(){
        name="Entity", solid=true, texture=name[0], coords.x=0, coords.y=0;
    }
    Entity(string tile_name, char tile_txt, int hp, int ap, 
    int x=0, int y=0, bool tile_solid=true){
        name=tile_name, texture=tile_txt, solid=tile_solid,
        coords.x=x, coords.y=y, statistics.attack=ap,
        statistics.health=hp;
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
    virtual void moveEntity(){
        cout << ">>> " << name << " as been moved!\n";
    }
};

struct Player: Entity{
    bool solid;
    char texture;
    string name;
    Axis coords;
    Stats statistics;
    Inventory inv;
    Directions direction;
    Item* hand=NULL;
    Player(){
        name="player", solid=true, texture=name[0], coords.x=0, coords.y=0;
    }
    Player(string tile_name, char tile_txt, int hp, int ap, 
    int x=0, int y=0, bool tile_solid=true, bool starterpack=false){
        name=tile_name, texture=tile_txt, solid=tile_solid,
        coords.x=x, coords.y=y, statistics.attack=ap,
        statistics.health=hp;
        if(starterpack) cout << ">>> " << name << " HAS ACTIVATED STARTER PACK ON!"; //inv.append();
        else;
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
    void moveEntity(){      //got bored optimising, time to deoptimise :>
        if(direction.get_dir()=="UP") coords.y--; else{
            if(direction.get_dir()=="DOWN") coords.y++; else{
                if(direction.get_dir()=="LEFT") coords.x--; else{
                    if(direction.get_dir()=="RIGHT") coords.x++;
                    else cout << "what.\n";
                }
            }
        }
    }
};

struct Monster: Entity{
    bool solid;
    char texture;
    int stage, ai;
    string name;
    Axis coords;
    Stats statistics;
    Directions direction;
    Item* hand=NULL;
    Monster(){
        name="Monster", solid=true, texture=name[0], coords.x=0, coords.y=0,
        ai=0;
    }
    Monster(string tile_name, char tile_txt, int hp, int ap, 
    int ai=0, int x=0, int y=0, bool tile_solid=true){
        name=tile_name, texture=tile_txt, solid=tile_solid,
        coords.x=x, coords.y=y, statistics.attack=ap,
        statistics.health=hp, this->ai=ai;
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
    virtual void moveEntity(){
        switch(ai){
            case 1:     //zombie
                if(stage<2);
                else{;}
                if(stage>7) stage=0;
                else stage++;
                break;
            case 2:     //lazy ghost
                if(stage==0){solid=true; stage++;}
                else{solid=false; stage=0;}
                break;
        }
    }
};