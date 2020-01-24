
//
// Created by sadra on 24January2020.
//



enum ItemType {
    SPEED,
    PASS,
};

typedef struct
{
    unsigned int x;
    unsigned int y;
}Location;


typedef struct
{
    Location loc;
    ItemType type;
}Item;

typedef struct
{
    //LinkedList<Location>    body;
    Location                direction;
    bool                    passEnable;
    bool                    fast;
    unsigned int            score;
}Snake;
