#include "LedControl.h"

LedControl lc=LedControl(12,10,11,2);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=200;  // Delay between Frames

int buzzerPin = 7;
int restartButton = 2;
int snake_speed = 20;
int snake_effected_time = 0;
byte numbers[10][5] {
  {0B111,
  0B101,
  0B101,
  0B101,
  0B111},

  {0B110,
  0B010,
  0B010,
  0B010,
  0B010},

  {0B111,
  0B001,
  0B111,
  0B100,
  0B111},

  {0B111,
  0B001,
  0B111,
  0B001,
  0B111},

  {0B101,
  0B101,
  0B111,
  0B001,
  0B001},

  {0B111,
  0B100,
  0B111,
  0B001,
  0B111},

  {0B111,
  0B100,
  0B111,
  0B101,
  0B111},

  {0B111,
  0B001,
  0B001,
  0B001,
  0B001},

  {0B111,
  0B101,
  0B111,
  0B101,
  0B111},

  {0B111,
  0B101,
  0B111,
  0B001,
  0B111}
  
};

unsigned int game[8][8];
unsigned int prvX[8][8];
unsigned int prvY[8][8];
bool is_effected[2];

int score = 0;
int xDir;
int yDir;

int xPos;
int yPos;

int snakeSize;

void showNumber(int number){
  int all[5];
  for(int i =0 ; i< 5; i+=1){
    all[i] = numbers[number/10][i]*32 + numbers[number%10][i];
  }
  for(int i = 0; i < 5;i+=1){
    lc.setRow(0,i,all[i]);
  }
    lc.setRow(0,5,0B00000000);
    lc.setRow(0,6,0B11111111);
    lc.setRow(0,7,0B11111111);  
}

void endGame(){
  showNumber(score);
  while(digitalRead(restartButton) == HIGH);
  setGame();
}

void create_random(int val1,int val2){    // put val2 instead of a random val1
  int init = random(0,64);
  bool flag = false;
  for(int i=init;i<64;i++){
    if(game[i/8][i%8]==val1){
      game[i/8][i%8]=val2;
      flag = true;
      break;
    }
  }
  if(!flag){
    for(int i=init;i>=0;i--){
      if(game[i/8][i%8]==val1){
      game[i/8][i%8]=val2;
      break;
      }
    }
  }
}

void create_random_item(){      // generate random food on empty location
  if(is_effected[0] || is_effected[1]) return;
  int tmp = random(0,2);
  create_random(0,3+tmp);
  
}

void delete_random_item(){
  create_random(3,0);
  create_random(4,0);
}

void create_random_food(){        // generate random food on empty location
  create_random(0,2);
}

bool eatFood(int x, int y) {          // call when snake eats food
  if(game[x][y]==2){
    Serial.print("eat\n");
    score++;
    create_random_food();
    return true;
  }
   Serial.print("noteat\n");
   
  return false;
}

void eatItem(int x, int y){
  if(game[x][y]==3){
    is_effected[0]=1;
  }
  if(game[x][y]==4){
    is_effected[1]=1;
  }
}

void setGame(){                   // Clear Game and make new snake
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

    snakeSize = 5;

    game[3][2] = 1;
    prvX[3][2] = 2;
    prvY[3][2] = 2;

    game[2][2] = 1;
    prvX[2][2] = 1;
    prvY[2][2] = 2;
/*
    game[1][2] = 1;
    prvX[1][2] = 0;
    prvY[2][2] = 2;
*/
    score = 0;
    is_effected[0] = 0;
    is_effected[1] = 0;
    snake_effected_time = 0;
    create_random_food();
}
char lastDirectionChange = 'N';

void setDirection(){           // Get input and set Direction 
    int mouse;
    mouse = analogRead(A0);  // read the input pin
    int lastXDir = xDir;
    int lastYDir = yDir;
    
    if(mouse > 768 && lastDirectionChange == 'N'){
      xDir = lastYDir;
      yDir = -lastXDir;
      lastDirectionChange = 'L';
    }
    if(mouse < 256 && lastDirectionChange == 'N'){  
      xDir = -lastYDir;
      yDir = lastXDir;
      lastDirectionChange = 'R';
    }
    if(mouse >= 256 && mouse <= 768){
      lastDirectionChange = 'N';
    }
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



void next() {
    int tempX = xPos + xDir;
    int tempY = yPos + yDir;
  
  if(game[tempX][tempY]==1){
    endGame();
    return;
  }
  if(is_effected[1]){
    tempX = (tempX+8)%8;
    tempY = (tempY+8)%8;
  }else{
    if(tempX > 7 || tempX < 0 || tempY > 7 || tempY < 0){
      endGame();
      return;
    }
  }
    if (eatFood(tempX, tempY)) {
        snakeSize++;
    }
    eatItem(tempX, tempY);
    
    game[tempX][tempY] = 1;
    prvX[tempX][tempY] = xPos;
    prvY[tempX][tempY] = yPos;

    xPos = tempX;
    yPos = tempY;

    
        
    removeLastSnakePart(tempX, tempY);
}





void setup()
{
  pinMode(buzzerPin, OUTPUT);    // sets the digital pin as output
  pinMode(restartButton, INPUT);    // sets the digital pin as output
  Serial.begin(9600);           //  setup serial

  digitalWrite(buzzerPin, LOW); // sets the LED on
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,5);  // Set intensity levels
  lc.setIntensity(1,5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);


  setGame();
}


int stepNumber = 0;
void showGame(){
  for(int i = 0; i < 8; i+=1){
    byte row = 0;
    int column = 1;
    for(int j = 0; j < 8; j+=1){
      switch(game[i][j]){
        case 0:
          row += 0;
          break;
         case 1:
          if(is_effected[1] == 0 || (stepNumber%5 < 2 && is_effected[1]))
            row += column;
          break;
         case 2:
          row += column;
          break;
         case 3:
          if(stepNumber%5 < 2){
            row += column;
          }
          break;
         case 4:
          if(stepNumber%10 < 2){
            row += column;
          }
          break;
      }
      column*=2;
    }
    lc.setRow(0,i,row);
  }
}



void loop()
{
  setDirection();
  if(snake_effected_time > 300){
    snake_effected_time = 0;
    is_effected[0] = 0;
    is_effected[1] = 0;
  }
  if(is_effected[0] || is_effected[1]){
    snake_effected_time+=1; 
  }
  if(stepNumber%(snake_speed - is_effected[0]*snake_speed/2) == 0){
    next();
  }
  if(stepNumber%400 == 0 && stepNumber > 400){
    create_random_item();
  }
  if(stepNumber%400 == 200){
    delete_random_item();
  }
  showGame();
  stepNumber += 1;
  delay(10);
}
