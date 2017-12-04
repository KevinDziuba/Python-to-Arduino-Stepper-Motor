#include <Wire.h>
#include <Stepper.h>

Stepper Left(200, 4, 3); // Dir = 4, Step = 3
Stepper Right(200, 9, 8); // Dir = 9, Step = 8

const byte buffSize = 40;
char inputBuffer[buffSize];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;

char motordirection[buffSize] = {0};
int steps = 0;

unsigned long curMillis;

unsigned long prevReplyToPCmillis = 0;
unsigned long replyToPCinterval = 1000;

// Set up the serial connection
void setup() {
  Left.setSpeed(45);
  Right.setSpeed(45);
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

// set up the loop of functions


// HOW TO READ DATA
void getDataFromPC() {

    // receive data from PC and save it into inputBuffer
    
  if(Serial.available() > 0) {

    char x = Serial.read();

      // the order of these IF clauses is significant
      
    if (x == endMarker) {
      readInProgress = false;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      parseData();
    }
    
    if(readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == buffSize) {
        bytesRecvd = buffSize - 1;
      }
    }

    if (x == startMarker) { 
      bytesRecvd = 0; 
      readInProgress = true;
    }
  }
}

// PARSING DATA
void parseData() {

    // split the data into its parts
    
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(inputBuffer,",");      // get the first part - the string
  strcpy(motordirection, strtokIndx); // copy it to messageFromPC
  
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  steps = atoi(strtokIndx);     // convert this part to an integer
}

void replyToPC() {

  if (newDataFromPC) {
    newDataFromPC = false;
    Serial.print("<Msg ");
    Serial.print(motordirection);
    Serial.print(" Amount of steps ");
    Serial.print(steps);
    Serial.print(" Time ");
    Serial.print(curMillis >> 9);
    Serial.println(">");
  }
}
// forward: +1 = left, -1 = right
// backward: -1 = left, +1 = right
// right: +1 = left, +1 = right
// left: -1 = left, - 1 = right

void RightTurn()
// Increment source: https://mathbits.com/MathBits/CompSci/looping/increment.htm
{
  if (steps != 0){
  for(int s = 0; s < steps; s++)
  {
    Right.step(1);
    Left.step(1);
  }
  }
  steps = 0;
}

void LeftTurn()
{
  if (steps != 0); {
  for(int s = 0; s < steps; s++)
  {
    Right.step(-1);
    Left.step(-1);
  }
  }
  steps = 0;
}

void Forward()
{
  if (steps != 0){
  for(int s = 0; s < steps; s++)
  {
    Right.step(-1);
    Left.step(1);
  }
  }
  steps = 0;
}

void Backward()
{
  if (steps != 0){
  for(int s = 0; s < steps; s++)
  {
    Right.step(1);
    Left.step(-1);
  }
  }
  steps = 0;
}

void motor()
{
  if (strcmp(motordirection, "Forward") == 0) {
     Forward();
  }
  if (strcmp(motordirection, "Left") == 0) {
     LeftTurn(); 
  }
  
  if (strcmp(motordirection, "Right") == 0) {
      RightTurn();
  }
  if (strcmp(motordirection, "Backward") == 0) {
      Backward();
  }
}

void loop() {
  curMillis = millis();
  getDataFromPC();
  replyToPC();
  motor();
}

