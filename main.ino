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

void setGame(){                 	// Clear Game and make new snake
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            game[i][j] = 0;
            prvX[i][j] = 0;
            prvY[i][j] = 0;
        }
    }

    xDir = 1;
    yDir = 0;

    xPos = 3;
    yPos = 2;

    snakeSize = 3;

    game[3][2] = 1;
    prvX[3][2] = 2;
    prvY[3][2] = 2;

    game[2][2] = 1;
    prvX[2][2] = 1;
    prvY[2][2] = 2;

    game[1][2] = 1;
    
    
}

void removeLastSnakePart(int tempX, int tempY){
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


void setDirection(){        	  	// Get input and set Direction 

}

int score;

bool eatFood() {					// call when snake eats food
	if(game[xPos][yPos]==2){
		score++;
		create_random_food();
		return true;
	}
	return false;
}

bool is_effected[2];

void create_random_food(){    		// generate random food on empty location
	create_random(0,2)
}

void create_random_item(){			// generate random food on empty location
	if(is_effected)return;
	int tmp = random(0,2);
	create_random(0,3+tmp);
	is_effected[tmp]=1;
}

void delete_random_item(){
	creat_random(2,0)
	creat_random(3,0)
}

void create_random(int val1,int val2){		// put val2 instead of a random val1
	int init = random(0,64)
	bool flag = false;
	for(int i=init;i<64;i++){
		if(game[init/8][init%8]==val1){
			game[init/8][init%8]=val2;
			flag = true;
			break;
		}
	}
	if(!flag){
		for(int i=init;i>=0;i--){
			if(game[init/8][init%8]==val1){
			game[init/8][init%8]=val2;
			flag = true;
			break;
			}
		}
	}
}


void next() {
    setDirection();
    int tempX = xPos + xDir;
    int tempY = yPos + yDir;
	
	if(is_effected[1]){
		
	}
	// check for win or lose
	// ro khodesh bar nagarde
    
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
        
    removeLastSnakePart(tempX, tempY);
}