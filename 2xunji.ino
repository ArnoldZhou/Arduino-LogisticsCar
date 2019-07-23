#include <Servo.h>

#define STOP      0
#define FORWARD   1
#define BACKWARD  2
#define TURNLEFT  3
#define TURNRIGHT 4

int leftMotor1 = 14;
int leftMotor2 = 15;
int rightMotor1 = 16;
int rightMotor2 = 17;

int trac1 = 11; //从车头方向的最右边开始排序
int trac2 = 10; 
int trac3 = 9; 
int trac4 = 8; 

int leftPWM = 3;
int rightPWM = 2;

int data[4];

void setup() {
  // put your setup code here, to run once:
  //串口初始化
  Serial.begin(9600); 
  //测速引脚初始化
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  //寻迹模块D0引脚初始化
  pinMode(trac1, INPUT);
  pinMode(trac2, INPUT);
  pinMode(trac3, INPUT);
  pinMode(trac4, INPUT);
}

void motorRun(int cmd,int value)
{
  analogWrite(leftPWM, value);  //设置PWM输出，即设置速度
  analogWrite(rightPWM, value);
  switch(cmd){
    case FORWARD:
     Serial.println("FORWARD"); //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);
      break;
      case BACKWARD:
      Serial.println("BACKWARD"); //输出状态
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      break;
     case TURNLEFT:
      Serial.println("TURN LEFT"); //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2,HIGH);
      digitalWrite(rightMotor1,HIGH);
      digitalWrite(rightMotor2,LOW);
      break;
     case TURNRIGHT:
      Serial.println("TURN RIGHT"); //输出状态
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);
      break;
     default:
      Serial.println("STOP"); //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
  }
}
void tracing()
{
  data[0] = digitalRead(11);
  data[1] = digitalRead(10);
  data[2] = digitalRead(9);
  data[3] = digitalRead(8);
   if((!data[0] && data[1] && data[2] & 4& !data[3]))  
  {
    motorRun(FORWARD,220);
  }
  
  else if(data[0] && data[1] && data[2] && data[3])
  {
    motorRun(FORWARD,220);
  }
  
  /*else if(!data[0] && data[1] && data[2] && data[3])
  {
    motorRun(TURNLEFT, 100,100);
  }   上坡微调*/ 

  else if(data[2] || data[3])  
  {
    motorRun(TURNLEFT,255);
  }

    else if(data[0] || data[1])  
  {
    motorRun(TURNRIGHT,255);
  }

  /* else if(!data[0] && !data[1] && data[2] &&!data[3])  
  {
    motorRun(TURNLEFT,220);
  }
   
   else if(!data[0] && !data[1] && data[2] && data[3])  
  {
    motorRun(TURNLEFT,220);
  }

  else if(!data[0] && !data[1] && !data[2] && data[3])  
  {
    motorRun(TURNLEFT,220);
  }

    else if(!data[0] && data[1] && !data[2] && !data[3])  
  {
    motorRun(TURNRIGHT,220);
  }

  else if(data[0] && data[1] && !data[2] && !data[3])  
  {
    motorRun(TURNRIGHT,220);
  }*/
  Serial.print(data[0]);
  Serial.print("---");
  Serial.print(data[1]);
  Serial.print("---");
  Serial.print(data[2]);
  Serial.print("---");
  Serial.print(data[3]);
  Serial.print("---");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  tracing();
}
