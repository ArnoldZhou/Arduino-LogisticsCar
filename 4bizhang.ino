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

int leftPWM = 2;
int rightPWM = 3;

Servo myServo;  //舵机

int inputPin=4;   // 定义超声波信号接收接口
int outputPin=5;  // 定义超声波信号发出接口

int dis;
float cm; 

void setup() {
  // put your setup code here, to run once:
  //串口初始化
  Serial.begin(9600); 
  //舵机引脚初始化
  myServo.attach(4);
  //测速引脚初始化
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  //超声波控制引脚初始化
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  avoidance();
}
void motorRun(int cmd,int value)
{
  analogWrite(leftPWM, value);  //设置PWM输出，即设置速度
  analogWrite(rightPWM, value);
  switch(cmd){
    case FORWARD:
     Serial.println("FORWARD"); //输出状态
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      break;
     case BACKWARD:
      Serial.println("BACKWARD"); //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);
      break;
     case TURNLEFT:
      Serial.println("TURN LEFT"); //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2,HIGH );
      digitalWrite(rightMotor1,HIGH );
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
void avoidance()
{
  motorRun(FORWARD,200);
  dis=getDistance(); //正前方距离
  Serial.print(dis);   
  Serial.println(); 
  if(dis<40)
  {
    motorRun(STOP,0);
    delay(1000);
    motorRun(TURNLEFT,255);
    delay(1100);
    motorRun(FORWARD,255);
    delay(1500);
    motorRun(TURNRIGHT,255);
    delay(1100);
    motorRun(FORWARD,255);
    delay(1800);
    motorRun(TURNRIGHT,255);
    delay(1100);
    motorRun(FORWARD,255);
    delay(1300);
    motorRun(TURNLEFT,255);
    delay(1100);
   }
}

int getDistance()
{
  digitalWrite(outputPin, LOW); // 使发出发出超声波信号接口低电平2μs
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW); // 保持发出超声波信号接口低电平
  
  int distance = pulseIn(inputPin, HIGH); // 读出脉冲时间
  distance= distance/58; // 将脉冲时间转化为距离（单位：厘米）
  Serial.println(distance); //输出距离值

 
  if (distance>180||distance<1)
  {
    //如果距离小于1大于180厘米返回数据
    return 180;
  }
  else
    return distance;
}
