/*  
 *  Start to move when tapping on the accelerometer.
 *  Follow the path.
 *  Stop when the traveled distance from the start point is 50''.
 *  Send the traveled distance to the PC continuously.
 *  
 */
#include <RedBot.h>
RedBotSensor left = RedBotSensor(A3);  // initialize a left sensor object on A3 
RedBotSensor center = RedBotSensor(A6); // initialize a center sensor object on A6
RedBotSensor right = RedBotSensor(A7);  // initialize a right sensor object on A7
/*
 * constants that are used in the code. LINETHRESHOLD is the level to detect 
 * if the sensor is on the line or not. If the sensor value is greater than this 
 * the sensor is above a DARK line.
*/
#define LINETHRESHOLD 700  //threshold
#define SPEED 60   // sets the nominal speed.

RedBotAccel accelerometer;
RedBotMotors motors;

RedBotEncoder encoder = RedBotEncoder(A2, 10); 

int buttonPin = 12; // variable used to store the pin number of tht button
int countsPerRev = 192;  
int leftSpeed;  // variable used to store the leftMotor speed 
int rightSpeed;  // variable used to store the leftMotor speed
int i=0;
int k=0;
float lCount;
float rCount;

void turnLeft()// turn left
{
  leftSpeed = -(SPEED-50);
  rightSpeed = SPEED + 50;
  motors.rightMotor(rightSpeed);
  motors.leftMotor(leftSpeed);
  }
void turnRight() // turn right
{
  leftSpeed = -(SPEED + 50);
  rightSpeed = SPEED-50;
  motors.rightMotor(rightSpeed);
  motors.leftMotor(leftSpeed);
  }
void goStraight() //go straight
{
   leftSpeed = -SPEED; 
    rightSpeed = SPEED;
    motors.rightMotor(rightSpeed);
    motors.leftMotor(leftSpeed);
  }


void setup()
{ 
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Welcome to Project 1");
  Serial.println("------------------------------------------");
  delay(20);
  Serial.println("IR Sensor Readings: ");
  delay(10);
}

void loop()
{
  accelerometer.read();
  if(abs( accelerometer.x)>1000)
  k++;
  if(k>0)
  {
    if(i==0)
    {
      encoder.clearEnc(BOTH); 
      i++;
      }

  Serial.print(left.read()); // print out left sensor
  Serial.print("\t");  // tab character
  Serial.print(center.read()); // print out center sensor
  Serial.print("\t");  // tab character
  Serial.print(right.read()); // print out right sensor
  Serial.print("\t");  // tab character
  
 // compare the sensor value with the LINETHRESHOLD
 //go straight
 if((center.read() > LINETHRESHOLD)&&(right.read() < LINETHRESHOLD)&&(left.read() < LINETHRESHOLD))
  {
   goStraight();
  }
 
  //turn right
  else if((center.read() < LINETHRESHOLD)&&(right.read() > LINETHRESHOLD)&&(left.read() < LINETHRESHOLD))
  {
    turnRight();
  }

 //turn left
  else if((center.read() < LINETHRESHOLD)&&(right.read() < LINETHRESHOLD)&&(left.read() > LINETHRESHOLD))
  {
    turnLeft();
  }
 
  //go straight
  if((center.read() > LINETHRESHOLD)&&(right.read() > LINETHRESHOLD)&&(left.read() > LINETHRESHOLD))
  {
    goStraight();
  }
 
   //STOP
    if((center.read() < LINETHRESHOLD)&&(right.read() < LINETHRESHOLD)&&(left.read() < LINETHRESHOLD))
  {
    leftSpeed = 0; 
    rightSpeed = 0;
  }
 
 //turn left
  else if((center.read() > LINETHRESHOLD)&&(right.read() < LINETHRESHOLD)&&(left.read() > LINETHRESHOLD))
  {
   turnLeft();
  }
 
  //turn right
  else if((center.read() > LINETHRESHOLD)&&(right.read() > LINETHRESHOLD)&&(left.read() < LINETHRESHOLD))
  {
   turnRight();
  }

 
 //s delay(0);
 
    lCount = encoder.getTicks(LEFT);
    rCount = encoder.getTicks(RIGHT);
    float j=(lCount+rCount)/(2*192)*(2.56*PI);
  if ((lCount+rCount)/(2*192)*(2.56*PI)>=50)
  {
    motors.brake();
  }
  int l=j;//tpe conversion
  Serial.print(l);
  Serial.println();
  }
}

