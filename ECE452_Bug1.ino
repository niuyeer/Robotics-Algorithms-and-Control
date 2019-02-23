#include <RedBot.h>

RedBotSensor left = RedBotSensor(A3);   
RedBotSensor center = RedBotSensor(A6); 
RedBotSensor right = RedBotSensor(A7); 
RedBotAccel accelerometer;
#define LINETHRESHOLD 700
#define SPEED 60 

class CPoint  //point
{  
private:  
    double x;  // 横坐标  
    double y;  // 纵坐标  
    double z;  //车头角度
public:  
    CPoint(double xx=0,double yy=0,double zz=0):x(xx),y(yy),z(zz){};  
    double getX(){return x;}  
    double getY(){return y;}  
    double getZ(){return z;}  //空间朝向
   // double setP(double xx,double yy){x=xx;y=yy;}
    double setX(double xx){x=xx;}
    double setY(double yy){y=yy;}
    double setZ(double zz){z=zz;}
    //
};  

  
double distance(CPoint p1,CPoint p2)  
{  
    double d;  
    d=sqrt((p1.getX()-p2.getX())*(p1.getX()-p2.getX())+(p1.getY()-p2.getY())*(p1.getY()-p2.getY()));  
    return d;  
}  
double getAngle(CPoint p1,CPoint p2)
{
  return p2.getZ()-p1.getZ();
  }

RedBotMotors motors;
RedBotEncoder encoder = RedBotEncoder(A2, 10); 
int buttonPin = 12;
int countsPerRev = 192;  
int leftSpeed;   
int rightSpeed; 
float lCount;
float rCount;
double buff=0;
double pX=0,pY=0; //get postion x,y
CPoint start(0,0,0);  
CPoint lastPostion(0,0,0); 
CPoint postion(0,0,0);
CPoint goal(-30,30,PI/4); 
//double theat=0;//小车转向角度
double buffLeftSensor;
double buffRightSensor;
float minLength=0;
float totalLength=0;
float minDistance;
CPoint buffPoint(0,0,0);
CPoint pHit(0,0,0);
int flag=0;



void setup()
{ 
   encoder.clearEnc(BOTH); 
 // pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Welcome to Project_2");
  // Serial.println(start.getX());
 // Serial.println(start.getY());
  Serial.println("------------------------------------------");
  delay(20);
  Serial.println("IR Sensor Readings: ");
  delay(10);
  minDistance = distance(postion,goal);
}

 
void turnLeft()
  {
    leftSpeed = SPEED;
    rightSpeed = SPEED;
    motors.rightMotor(rightSpeed);
    motors.leftMotor(leftSpeed);
     postion.setZ((buff-lCount)/(2*192)*(2.56*PI)*2/3.125+lastPostion.getZ());
    Serial.print(buff);  
    Serial.print("\t"); 
   Serial.print(lCount);  
    Serial.print("\t"); 
    Serial.print(lastPostion.getZ());  
    Serial.print("\t"); 
    Serial.print((buff-lCount)/(2*192)*(2.56*PI)*2/3.125); 
    Serial.print("\t"); 
    
     if(postion.getZ()>=2*PI)
     {
       postion.setZ(postion.getZ()-2*PI);
      } 
     if(postion.getZ()<0)
     {
       postion.setZ(postion.getZ()+2*PI);
      }     
      lastPostion=postion;
    Serial.print(postion.getX());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getY());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getZ());  // tab character
    Serial.print("\t");  // tab character
    }
    
void turnRight()
  {
    
    leftSpeed = -SPEED;
    rightSpeed = -SPEED;
    motors.rightMotor(rightSpeed);
    motors.leftMotor(leftSpeed);
     postion.setZ((buff-lCount)/(2*192)*(2.56*PI)*2/3.125+lastPostion.getZ());
     if(postion.getZ()>=2*PI)
     {
       postion.setZ(postion.getZ()-2*PI);
      }
     
      lastPostion=postion;
    Serial.print(postion.getX());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getY());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getZ());  // tab character
    Serial.print("\t");  // tab character
    }
  
  void goStraight()
  {
   leftSpeed = -SPEED;
    rightSpeed = SPEED;
    motors.rightMotor(rightSpeed);
    motors.leftMotor(leftSpeed); 
    postion.setX((buff-lCount)/(2*192)*(2.56*PI)*(-sin(postion.getZ()))+lastPostion.getX());
    postion.setY((buff-lCount)/(2*192)*(2.56*PI)*cos(postion.getZ())+lastPostion.getY());
     totalLength += (buff-lCount)/(2*192)*(2.56*PI);
   
    if(distance(postion,goal)<minDistance){
      minDistance=distance(postion,goal);
      buffPoint=postion;
      minLength=totalLength;   
    }
    lastPostion = postion;
    Serial.print(postion.getX());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getY());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getZ());  // tab character
    Serial.print("\t");  // tab character
    }
  
void followLineL()
{
    //sense 3 white
   if((left.read() > LINETHRESHOLD) || ((right.read() > LINETHRESHOLD) || (center.read() > LINETHRESHOLD)))
   {
      if(buffLeftSensor > LINETHRESHOLD)
      {
         turnLeft();
        Serial.print("After Obtacle towards Goal turn Left");  // tab character
         Serial.print("\t");  // tab character
      }
     if(buffRightSensor > LINETHRESHOLD)
       {
      turnRight();
      Serial.print("After Obtacle towards Goal turn Right");  // tab character
       Serial.print("\t");  // tab character
        }
      }

       //Left white
    if((left.read() < LINETHRESHOLD)&&((right.read() > LINETHRESHOLD)||(center.read() > LINETHRESHOLD)))  
    {
       buffLeftSensor=left.read();
      buffRightSensor=right.read();
      Serial.print("Sense Left white");  // tab character
      Serial.print("\t");  // tab character
        goStraight();
       Serial.print("Left white go Straight");  // tab character
       Serial.print("\t");  // tab character
      }
      //left black
     if(left.read() > LINETHRESHOLD)  
      {
       buffLeftSensor=left.read();
       buffRightSensor=right.read();
      Serial.print("Sense Left black");  // tab character
      Serial.print("\t");  // tab character
      turnLeft();
      Serial.print("Left black turn Left");  // tab character
      Serial.print("\t");  // tab character
      }
 }
void followLineR()
{
    //sense 3 white
   if((left.read() > LINETHRESHOLD) || ((right.read() > LINETHRESHOLD) || (center.read() > LINETHRESHOLD)))
   {
      if(buffLeftSensor > LINETHRESHOLD)
      {
         turnLeft();
        Serial.print("After Obtacle towards Goal turn Left");  // tab character
         Serial.print("\t");  // tab character
      }
     if(buffRightSensor > LINETHRESHOLD)
       {
      turnRight();
      Serial.print("After Obtacle towards Goal turn Right");  // tab character
       Serial.print("\t");  // tab character
        }
      }

       //Right white
    if((right.read() < LINETHRESHOLD)&&((left.read() > LINETHRESHOLD)||(center.read() > LINETHRESHOLD)))  
    {
       buffLeftSensor=left.read();
      buffRightSensor=right.read();
      Serial.print("Sense Left white");  // tab character
      Serial.print("\t");  // tab character
        goStraight();
       Serial.print("Left white go Straight");  // tab character
       Serial.print("\t");  // tab character
      }
      //Right black
     if(right.read() > LINETHRESHOLD)  
      {
       buffLeftSensor=left.read();
       buffRightSensor=right.read();
      Serial.print("Sense Left black");  // tab character
      Serial.print("\t");  // tab character
      turnRight();
      Serial.print("Left black turn Left");  // tab character
      Serial.print("\t");  // tab character
      }
 }

void loop()
{
 accelerometer.read();
  if(abs( accelerometer.x)>1000)
  { 
   
    buff=lCount;
     lCount = encoder.getTicks(LEFT);
     rCount = encoder.getTicks(RIGHT);

     
     
   //start towards GOAL
    if(((center.read() < LINETHRESHOLD)&&(right.read() < LINETHRESHOLD)&&(left.read() < LINETHRESHOLD))||((abs(distance(postion,goal)-minDistance)<3)&&flag==1)) 
    {
//     Serial.print("Start 3 White To Goal");  // tab character
//     Serial.print("\t");  // tab character
 //     Serial.print((lCount)/(2*192)*(2.56*PI));  // tab character
 //     Serial.print("\t");  // tab character
 //     Serial.print((rCount)/(2*192)*(2.56*PI));  // tab character
 //     Serial.print("\t");  // tab character*/
   
   // Serial.print(getAngle(start,postion));  // tab character
  // Serial.print("\t");  // tab character*/
   // Serial.print(getAngle(start,goal));  // tab character
  // Serial.print("\t");  // tab character*/
   // if(-(lCount)/(2*192)*(2.56*PI)==(getAngle(start,goal)*3.125/2)) /// 
   

   if((getAngle(postion,goal)>PI)||(getAngle(postion,goal)<-0.03))
   {
    turnRight();
    Serial.print("Start turn Right");  // tab character
    Serial.print("\t");  // tab character
    }
    if((getAngle(postion,goal)<=PI)&&(getAngle(postion,goal)>0.03))
   {
    turnLeft();
     Serial.print("Start turn Left");  // tab character
     Serial.print("\t");  // tab character
    }
     if(abs(getAngle(postion,goal))<=0.02)
   {
   Serial.print("Start Go Straight");  // tab character
   Serial.print("\t");  // tab character
     goStraight();
    }
  }

//when it hit obtacle(LINE) then follow Line(turn around obstacle)
  if((center.read() > LINETHRESHOLD)||(right.read() > LINETHRESHOLD)||(left.read() > LINETHRESHOLD))
  {
    pHit=postion;
    turnLeft();
    //until go to GOAL
   while(!(distance(pHit,postion)<3&&totalLength>20))
    {
      followLineL();
    }
  //
    Serial.print("\n");
    Serial.print("****************** 1 Square ****************");
    Serial.print(postion.getX());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getY());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getZ());  // tab character
    Serial.print("\t");  // tab character  
  if(minLength<totalLength*1/2)
    {
     turnLeft();
     while(distance(buffPoint,postion)>3)
        {
          followLineL();
        }
    flag=1;
    Serial.print("\n");
    Serial.print("******************Pleave****************");  
    Serial.print(postion.getX());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getY());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getZ());  // tab character
    Serial.print("\t");  // tab character
    }
  else
  {
      turnRight();
      while(distance(buffPoint,postion)>3)
      {
      followLineR();
      }
    flag=1;
    Serial.print("\n");
    Serial.print("******************Pleave****************");  
    Serial.print(postion.getX());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getY());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getZ());  // tab character
    Serial.print("\t");  // tab character
   
  }
   
    //


   // stop our robot
   if(distance(postion,goal)<=5)
      {
      while(1){
         motors.stop();
         delay(500);}
      }
  
  }  
  }
     Serial.println("\n");      // prints another carriage return

  }

