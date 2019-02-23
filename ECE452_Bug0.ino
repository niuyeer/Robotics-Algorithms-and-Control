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

/*double angle(double L)
{
  double a=L/r;
  return a;
  }//返回 角度*/
  
 /*double len(double th)
  {
    double len=r*th;
    return len;
    }//返回*/


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
    lastPostion=postion;
    Serial.print(postion.getX());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getY());  // tab character
    Serial.print("\t");  // tab character
    Serial.print(postion.getZ());  // tab character
    Serial.print("\t");  // tab character
    }
  

void loop()
{
 accelerometer.read();
  if(abs( accelerometer.x)>1000)
  { 
   // lastLeft=lCount;
    //lastRight=rCount;
   // lCount=0;
   // rCount=0;
    buff=lCount;
     lCount = encoder.getTicks(LEFT);
     rCount = encoder.getTicks(RIGHT);
   //start towards GOAL
    if((center.read() < LINETHRESHOLD)&&(right.read() < LINETHRESHOLD)&&(left.read() < LINETHRESHOLD))  //white
    {
      Serial.print("Start 3 White To Goal");  // tab character
      Serial.print("\t");  // tab character
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
    //until go to GOAL
    while(distance(postion,goal)>1 )
   {
    
    /* Serial.print(lCount);  // tab character
     Serial.print("\t");  // tab character
   Serial.print(rCount);  // tab character
   Serial.print("\t");  // tab character*/

  /*  Serial.print((lCount)/(2*192)*(2.56*PI));  // tab character
   Serial.print("\t");  // tab character*/
 
  //   Serial.print(getAngle(postion,goal));  // tab character
  //   Serial.print("\t");  // tab character
 /*
   Serial.print("\t");  // tab character
   Serial.print((lCount)/(2*192)*(2.56*PI));  // tab character
   Serial.print("\t");  // tab character
    Serial.print((rCount)/(2*192)*(2.56*PI));  // tab character
   Serial.print("\t");  // tab character*/

 //3 sensors all sense white  
   if((center.read() < LINETHRESHOLD)&&(right.read() < LINETHRESHOLD)&&(left.read() < LINETHRESHOLD))  
  {
    //Position angle > Goal angle
    if(postion.getZ()>=goal.getZ())
    {
          //towards G
      if(getAngle(goal,postion)<(PI/2))//<90
      {
        while(abs(getAngle(postion,goal))>0.02)
        {
          turnRight();
          Serial.print("After Obtacle turn Right");  // tab character
          Serial.print("\t");  // tab character
          // stop our robot
   if(distance(postion,goal)<=1)
      {
      while(1){
      motors.brake();
      }
      }
          }
         goStraight();
          Serial.print("After Obtacle go Straight");  // tab character
          Serial.print("\t");  // tab character
       }
          //follow Line
      else{
           if(buffLeftSensor > LINETHRESHOLD)
             {
               turnLeft();
          Serial.print("After Obtacle turn Left");  // tab character
          Serial.print("\t");  // tab character
              }
              if(buffRightSensor > LINETHRESHOLD)
             {
               turnRight();
          Serial.print("After Obtacle turn Right");  // tab character
          Serial.print("\t");  // tab character
              }
           }
     }
     
       //Position angle < Goal angle
      if(postion.getZ()<goal.getZ())
      {
          //towards G
          if(getAngle(goal,postion)>(3*PI/2))
         {
           while(abs(2*PI-getAngle(postion,goal))>0.02)
             {
               turnRight();
          Serial.print("After obstacle towards Goal turn Right");  // tab character
          Serial.print("\t");  // tab character
          // stop our robot
   if(distance(postion,goal)<=1)
      {
      while(1){
      motors.brake();
      }
      }
              }
           goStraight();
          Serial.print("After Obtacle towards Goal go Straight");  // tab character
          Serial.print("\t");  // tab character
          }
            //follow LINE
          else{
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
        Serial.println("\n");      // prints another carriage return
     }
     // stop our robot
   if(distance(postion,goal)<=1)
      {
      while(1){
      motors.brake();
      }
      }
  }

   // stop our robot
   if(distance(postion,goal)<=1)
      {
      while(1){
      motors.brake();
      }
      }
 
   Serial.println("\n");      // prints another carriage return
  }  
 }
  

