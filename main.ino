// Boolean[8][8]    game
// int              x_dir   |-1 -> left| +1 -> right|
// int              y_dir   |-1 -> down| +1 -> Up|
// Boolean          is_speed_enable

// Boolean          can_snake_pass

// int[][]          food_loc
// int[][]          speed_loc
// int[][]          pass_loc

// Boolean          speed_on_game
// Boolean          pass_on_game
// LinkedList<Location> 

unsigned int game[8][8];
unsigned int prvX[8][8];
unsigned int prvY[8][8];

int xDir;
int yDir;

int xPos;
int yPos;

int snakeSize;

void setGame(){                   // Clear Game and make new snake

}

void setDirection(){           // Get input and set Direction 

}

void create_random_food(){     // generate random food on empty location

}

void create_random_item() {

}

void update_snake() {

}

bool eatFood() {
    return false;
}

void next() {
    setDirection();
    int tempX = xPos + xDir;
    int tempY = yPos + yDir;
    
    if(tempY > 7 || tempX > 7)
        return;
    
    game[tempX][tempY] = 1;
    prvX[tempX][tempY] = xPos;
    prvY[tempX][tempY] = yPos;

    xPos = tempX;
    yPos = tempY;

    if (eatFood()) {
        snakeSize++;
        return;
    }
        
    for (int i = 1; i < snakeSize; i++)
    {
        int x = prvX[tempX][tempY];
        int y = prvY[tempX][tempY];
        tempX = x;
        tempY = y;
    }

    prvX[tempX][tempY] = 0;
    prvY[tempX][tempY] = 0;
    game[tempX][tempY] = 0;


}