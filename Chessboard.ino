#include <SpeedyStepper.h>
#include "board.h"
#include "Pair.h"
#include "mux.h"

// Important - Currently, this program assumes two things. One: Human always plays whites, and Two: The user always promotes to Queen

// Motors
#define X_STEP_PIN 54  //A0
#define X_DIR_PIN 55  //A1
#define X_ENABLE_PIN 38

#define Y_STEP_PIN 60  
#define Y_DIR_PIN 61 
#define Y_ENABLE_PIN 56

// Electromagnet
#define ELECTROMAGNET_PIN 2

// Limit switches
#define Y_LIMIT_SWITCH 14
#define X_LIMIT_SWITCH 3

// Units are in mm
const int tileSize = 40;
const double tileCenter = tileSize/2;
const int boardSize = 320;
const int x_max_pos = 280;
const int y_max_pos = 288;

// Stepper driver and motor specs
const int unsigned MAX_MICROSTEP = 16;
const int unsigned stepsPerRevolution = 200*16; // 1.8 degrees per step according to motor specifications multiplied by microstepping
const int unsigned stepperSpeed = 12;
const int unsigned motorSpeed = 80;
const int unsigned homingSpeed = 40;

SpeedyStepper x_motor;
SpeedyStepper y_motor;

board chessboard;

bool runOnce = false;

// ----- Fuction Declarations
void home();
void turnOffMotors();
void turnOnMotors();
void moveDiagonal(unsigned int direction);
void movePiece(chessPiece piece);
void capturePiece(chessPiece piece);
void detect_human_movement();
void goTo(chessPiece piece);
void dropPiece();
void grabPiece();
int charToInt(char character);
bool checkXinBounds();
bool checkYinBounds();


void setup() {
  Serial.begin(115200);

  chessboard.printBoard();
  
  x_motor.connectToPins(X_STEP_PIN, X_DIR_PIN);
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW);

  y_motor.connectToPins(Y_STEP_PIN, Y_DIR_PIN);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN, LOW);

  pinMode(ELECTROMAGNET_PIN, OUTPUT);
  pinMode(Y_LIMIT_SWITCH, INPUT);
  pinMode(X_LIMIT_SWITCH, INPUT);
  digitalWrite(ELECTROMAGNET_PIN, LOW);

  x_motor.setStepsPerMillimeter(80);
  x_motor.setAccelerationInMillimetersPerSecondPerSecond(25);
  x_motor.setSpeedInMillimetersPerSecond(motorSpeed);

  y_motor.setStepsPerMillimeter(80);
  y_motor.setAccelerationInMillimetersPerSecondPerSecond(25);
  y_motor.setSpeedInMillimetersPerSecond(motorSpeed);

  home();
  goTo(5, 'E');
  grabPiece();
  home();
  dropPiece();
  goTo(8, 'B');
  
}

void loop() {

  if (runOnce == false){
    runOnce = true;
    turnOffMotors();
  }
}

void home(){
  turnOnMotors();

  x_motor.setSpeedInMillimetersPerSecond(homingSpeed);
  x_motor.setupMoveInMillimeters(-x_max_pos); // negative to move right (Towards motor)

  y_motor.setSpeedInMillimetersPerSecond(homingSpeed);
  y_motor.setupMoveInMillimeters(y_max_pos);

  while ( ((!x_motor.motionComplete()) || (!y_motor.motionComplete()))){
    if (digitalRead(X_LIMIT_SWITCH) == 0 && digitalRead(Y_LIMIT_SWITCH) == 0){
      break;
    }

    if(digitalRead(X_LIMIT_SWITCH) == 1){
      x_motor.processMovement();
    }
    
    if(digitalRead(Y_LIMIT_SWITCH) == 1){
      y_motor.processMovement();
    }
  }

  x_motor.setCurrentPositionInMillimeters(0);
  y_motor.setCurrentPositionInMillimeters(0);

  turnOffMotors();

  return;
}

void turnOffMotors(){
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);

  return;
}

void turnOnMotors(){
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);

  return;
}

/*
  Moves x-carriage diagonally.
  Direction:
  1: Right top corner
  2: Right bottom corner
  3: Left top corner
  4: Left bottom Corner
*/
void moveDiagonal(unsigned int direction){
  turnOnMotors();

  if (direction == 1 || direction == 2){
    x_motor.setupRelativeMoveInMillimeters(-tileCenter);
  } else{
    x_motor.setupRelativeMoveInMillimeters(tileCenter);
  }

  if (direction == 1 || direction == 3){
    y_motor.setupRelativeMoveInMillimeters(tileCenter);
  } else{
    y_motor.setupRelativeMoveInMillimeters(-tileCenter); // Move down
  }
  
  while ( ((!x_motor.motionComplete()) || (!y_motor.motionComplete()))){
    // Ensure we do not exceed bounds!
    if( checkXinBounds() ){
      x_motor.processMovement();
    }
    if( checkYinBounds() ){
      y_motor.processMovement();
    }
  }

  turnOffMotors();
  return;
}

/*
  Move piece from orginal place to new place.
  Arguments:
  - ChessPiece
  - designation (col and row)
  This function will actively try to ignore tiles that are currently occupied whilst moving
*/
void movePiece(chessPiece Piece, char col, unsigned int row){
  


  return;
}

/*
  Capture chess piece by going to it's location, and depending on its color, go to a line before it and move it to one side of the board.
  Arguments:
  - chessPiece
*/
void capturePiece(chessPiece piece){
  goTo(piece); // Go to the chess Piece
  grabPiece(); // Grab the piece

  turnOnMotors();
  // If the chess piece currently capturing is black, move it upwards and to the right (Black is on y-axis motor side)
  if (piece.getColour() == 'B')
  {
    y_motor.moveRelativeInMillimeters(tileSize/2);
    x_motor.moveRelativeInMillimeters(0);
  }else{ // White piece, move it downwards and to the left of the board.
    y_motor.moveRelativeInMillimeters(-tileSize/2);
    x_motor.moveRelativeInMillimeters(x_max_pos);
  }
  turnOffMotors();

  return;
}

// Move to the specified tile
void goTo(int row, char column)
{
  turnOnMotors();

  x_motor.setSpeedInMillimetersPerSecond(motorSpeed);
  y_motor.setSpeedInMillimetersPerSecond(motorSpeed);

  // Determine distance to some tile.
  double distance_X = -1*(tileSize *  charToInt(column)); // We home at H8, therefore, subtract by H to get overall distance to travel.
  double distance_Y = (tileSize * (8-row));

  Serial.println(distance_Y);

  x_motor.setupMoveInMillimeters(distance_X);
  y_motor.setupMoveInMillimeters(-distance_Y);

  while( !x_motor.motionComplete() || !y_motor.motionComplete() ){
    if ( checkXinBounds() ){
      x_motor.processMovement();
    }

    if ( checkYinBounds() ){
      y_motor.processMovement();
    }
  }
  
  turnOffMotors();
  return;
}

// Turn of electromagnet
void grabPiece(){
  digitalWrite(ELECTROMAGNET_PIN, HIGH);
  return;
}

// Turn off electromagnet
void dropPiece(){
  digitalWrite(ELECTROMAGNET_PIN, LOW);
  return;
}

// Convert a column letter to its corresponding integer.
int charToInt(char character){
  return int(character) - 72; // Eg, 'A' = 97. 97 - 96 = 1 (column 1)
}

// Check if the carriage is currently in the playable area.
bool checkXinBounds(){
  if (x_motor.getCurrentPositionInMillimeters() < x_max_pos && x_motor.getCurrentPositionInMillimeters() >= 0 ){
    return true;
  }
  return false;
}

// Check if the carriage is currently in the playable area.
bool checkYinBounds(){
  if (y_motor.getCurrentPositionInMillimeters() < y_max_pos && y_motor.getCurrentPositionInMillimeters() <= 0 ){ // <= 0 due to moving opposite direction
    return true;
  }
  return false;
}
