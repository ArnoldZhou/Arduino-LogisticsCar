#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#define STOP      0
#define FORWARD   1
#define BACKWARD  2
#define TURNLEFT  3
#define TURNRIGHT 4
#define FRAME_HEADER            0xFF   //帧头
#define CMD_SERVO_SPEED         0x01   //设置舵机速度
#define CMD_SERVO_PLACE         0x02   //设置舵机位置
#define CMD_ACTION_GROUP_RUN    0x09   //运行动作组
#define CMD_STOP_REFRESH        0x0b   //急停、恢复指令
#define GET_LOW_BYTE(A) (uint8_t)((A))           //宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)     //宏函数 获得A的高八位
int leftMotor1 = 14;
int leftMotor2 = 15;
int rightMotor1 = 16;
int rightMotor2 = 17;//定义电机
int trac1 =11; 
int trac2 = 10; 
int trac3 = 9; 
int trac4 = 8; //定义前侧红外/从车头方向的最右边开始排序
int trac5 = 7;
int trac6 = 6;//定义右侧红外 
int inputPin =4;   // 定义超声波信号接收接口
int outputPin =5;  // 定义超声波信号发出接口
int leftPWM = 3;
int rightPWM = 2;//定义调速
int Flag_1 = 0; //取物料标志    
int Flag_2 = 0; //放物料标志    
int dis;
int q,w,e,r= 0;
int data[6];//定义红外读取数组
int i,j;
int Position=0;
char scanflag = ' ';
String SciString = " ";      
boolean flag_SetSeiDecMod = true;
boolean flag_StaDec = false;                   
unsigned char SetSeiDecMod[] = {0x07,0xC6,0x04,0x00,0xFF,0x8A,0x08,0xFD,0x9E};  
unsigned char StaDec[] = {0x04,0xE4,0x04,0x00,0xFF,0x14};     
SoftwareSerial mySerial(12,13);                // TX,RX
SoftwareSerial ServoSerial(19,18);             // RX, TX 软串口

void setup() 
{
  Serial.begin(9600);   //串口初始化
  ServoSerial.begin(9600);
  mySerial.begin(9600);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);  //测速引脚初始化
  pinMode(trac1, INPUT);
  pinMode(trac2, INPUT);
  pinMode(trac3, INPUT);
  pinMode(trac4, INPUT); 
  pinMode(trac5, INPUT);
  pinMode(trac6, INPUT);
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT); //超声波控制引脚初始化
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
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);
      break;
     case BACKWARD:
      Serial.println("BACKWARD"); //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2,HIGH );
      digitalWrite(rightMotor1,HIGH );
      digitalWrite(rightMotor2,LOW);
      break;
     case TURNLEFT:
      Serial.println("TURN LEFT"); //输出状态
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      break;
     case TURNRIGHT:
      Serial.println("TURN RIGHT"); //输出状态
       digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
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
  data[4] = digitalRead(7);
  data[5] = digitalRead(6);
   if((!data[0] && data[1] && data[2] && !data[3]))  
  {
    motorRun(FORWARD,255);
  }
  else if(data[0] && data[1] && data[2] && data[3])
  {
    motorRun(FORWARD,255);
  }
  else if(!data[0] && data[1] && data[2] && data[3])
  {
    motorRun(FORWARD,255);
  }
   else if(!data[0] && !data[1] && data[2] && data[3])
  {
    motorRun(TURNLEFT, 225);
  }
   else if(data[2] || data[3])
  {
    motorRun(TURNLEFT, 225);
  }
    else if(data[0] || data[1]) 
  {
    motorRun(TURNRIGHT, 225);
  }
}

void tracing2()
{
  data[0] = digitalRead(11);
  data[1] = digitalRead(10);
  data[2] = digitalRead(9);
  data[3] = digitalRead(8);
  data[4] = digitalRead(7);
  data[5] = digitalRead(6);
   if((!data[0] && data[1] && data[2] && !data[3]))  
  {
    motorRun(FORWARD,220);
  }
  else if(data[0] && data[1] && data[2] && data[3])
  {
    motorRun(FORWARD,220);
  }
  else if(!data[0] && data[1] && data[2] && data[3])
  {
    motorRun(FORWARD,220);
  }
  else if(data[0] && data[1] && data[2] && !data[3])
  {
    motorRun(FORWARD,220);
  }
  
  else if(data[0] && data[1] && !data[2] && !data[3])
  {
    motorRun(FORWARD,220);
  }
  
  else if(!data[0] && !data[1] && data[2] && data[3])
  {
    motorRun(TURNLEFT, 200);
  }
   else if( data[2] || data[3])
  {
    motorRun(TURNLEFT, 200);
  }
    else if(data[0] || data[1]) 
  {
    motorRun(TURNRIGHT, 200);
  }
}

void tracing3()
{
  data[0] = digitalRead(11);
  data[1] = digitalRead(10);
  data[2] = digitalRead(9);
  data[3] = digitalRead(8);
  data[4] = digitalRead(7);
  data[5] = digitalRead(6);
   if((data[1] && data[2]))  
  {
    motorRun(FORWARD,220);
  }
  else if( data[0] && data[1])
  {
    motorRun(FORWARD,220);
  }
   else if( data[1] && !data[2])
  {
    motorRun(TURNRIGHT, 180);
  }
    else if(!data[1] && data[2]) 
  {
    motorRun(TURNLEFT, 180);
  }
}

void moveServo(uint8_t servoID, uint16_t Position1, uint16_t Speed)
{
  uint8_t buf[15];
  Position1 = Position1*100/9+500;  
  buf[0] = FRAME_HEADER;                  
  buf[1] = CMD_SERVO_SPEED;
  buf[2] = servoID;                        
  buf[3] = GET_LOW_BYTE(Speed);              
  buf[4] = GET_HIGH_BYTE(Speed);            
  buf[5] = FRAME_HEADER;             
  buf[6] = CMD_SERVO_PLACE;          
  buf[7] = servoID;                    
  buf[8] = GET_LOW_BYTE(Position1);        
  buf[9] = GET_HIGH_BYTE(Position1);       
  ServoSerial.write(buf, 10);
}

void servo_(int D1, int D2, int D3, int D4, int D5, int D6) 
{
  int old[6] = {90,90,90,90,90,90};//初始位置
  int d[6];
  int t[6];
  int d_max = 0;
  int t_max = 0;
  int speed;
  int place[6] = {D1, D2, D3, D4, D5, D6 };

  for (int i = 0; i < 6; i++) 
  {
    d[i] = abs(place[i] - old[i]);
    if (d[i] > d_max) 
    {
      d_max = d[i];
    }
    old[i] = place[i];
  }

  for (int i = 0; i < 6; i++) 
  {
    if (d_max >= 60) 
    {
      speed = d[i] * 16 / d_max;
    }
    else 
    {
      speed = d[i] * 10 / d_max;
    }
    if ((d[i] > 140) && (i == 1))
    {
      speed = 20;
    } 
    if (speed > 20)
    {
      speed = 20;
    } 
    if (speed <= 5) 
    {
      speed = 5;
    }
    moveServo(i, place[i], speed*3/2);
    t[i] = d[i] * 112 / speed;
    if (t[i] > t_max) 
    {
      t_max = t[i];
    }
  }
  //delay(t_max);
}

char scan()
{
   char get_char = ' ';
   Position=0;
   if(flag_SetSeiDecMod == true)       //模块初始化功能
   {
      for(i = 0;i < sizeof(SetSeiDecMod);i++)
      {
        mySerial.write(SetSeiDecMod[i]);
        delay(1);
      }
      flag_SetSeiDecMod = 0;
      flag_StaDec = 1;
   }
   if(flag_StaDec == 1)     //模块扫码功能
   {
      for(i = 0;i < sizeof(StaDec);i++)
      {
         mySerial.write(StaDec[i]);
         delay(1);
       }
    }
   delay(10); 
   while(mySerial.available())    //所扫的字符串返回
   {
        char inChar = (char)mySerial.read();
        delay(5);
        SciString += inChar;
   }
   Position = SciString.indexOf('Z');  //找到字符Z的位置  
   if(Position != -1)   //字符'Z'找到
   {
      SciString = SciString.substring(Position,SciString.length());  //截取有效字符串 e.g    sdaaf,ZJGXDS01 --------->  ZJGXDS01
      //                        返回的字符串        截取到有效的字符串                                                              
      get_char = SciString.charAt(7);  // 返回第7位字符  e.g   ZJGXDS01  ---->    1
      SciString  = ""; //接受字符串清空 
      return get_char; //返回有效字符串的最后一位字符
   }
   else   //字符'Z'未能找到   
   {
      flag_SetSeiDecMod = 1;  //初始化标志位  方便第二次扫码
      flag_StaDec   = 0;
      SciString  = ""; //接受字符串清空 
      get_char = ' ';  //返回空字符
      return get_char;
    } 
}

void judgment1()                                                     
{ 
      switch(scanflag)
      {
        case '1':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 0, 15);
        delay(300);
        grab1();
        break;
        case '2':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 36, 15);
        delay(300);
        grab1();
        break;
        case '3' :                                                                                        //***************************抽签调整**********************************
        moveServo(6, 72, 15);
        delay(300);
        grab1();
        break;
        case '4':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 108, 15);
        delay(300);
        grab1();
        break;
        case '5':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 144, 15);
        delay(300);
        grab1();
        break;
        case '7' :                                                                                        //***************************抽签调整**********************************
        moveServo(6, 180, 15);
        delay(300);
        grab1();
        break;
      }
        Serial.println(scanflag);
        while(mySerial.read() >= 0){}
        /*while(mySerial.available()>0)
        mySerial.read();*/
}

void judgment2()                                                     
{ 
      switch(scanflag)
      {
        case '1':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 0, 15);
        delay(300);
        grab2();
        break;
        case '2':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 36, 15);
        delay(300);
        grab2();
        break;
        case '3' :                                                                                        //***************************抽签调整**********************************
        moveServo(6, 72, 15);
        delay(300);
        grab2();
        break;
        case '4':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 108, 15);
        delay(300);
        grab2();
        break;
        case '5':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 144, 15);
        delay(300);
        grab2();
        break;
        case '7' :                                                                                        //***************************抽签调整**********************************
        moveServo(6, 180, 15);
        delay(300);
        grab2();
        break;
      }
        initial_a();
        delay(500);
        Serial.println(scanflag);
        while(mySerial.read() >= 0){}
        /*while(mySerial.available()>0)
        mySerial.read();*/
        Flag_1=Flag_1+1;
        motorRun(FORWARD,200);
        delay(300);
}

void judgment3()                                                     
{ 
      switch(scanflag)
      {
        case '1':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 0, 15);
        delay(500);
        laydown();
        break;
        case '2':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 36, 15);
        delay(500);
        laydown();
        break;
        case '3' :                                                                                        //***************************抽签调整**********************************
        moveServo(6, 72, 15);
        delay(500);
        laydown();
        break;
        case '4' :                                                                                       //***************************抽签调整**********************************
        moveServo(6, 108, 15);
        delay(500);
        laydown();
        break;
        case '5':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 144, 15);
        delay(500);
        laydown();
        break;
        case '7' :                                                                                        //***************************抽签调整**********************************
        moveServo(6, 180, 15);
        delay(500);
        laydown();
        break;
      }
        Serial.println(scanflag);
        while(mySerial.read() >= 0){}
        /*while(mySerial.available()>0)
        mySerial.read();*/
}

void judgment4()                                                     
{ 
      switch(scanflag)
      {
        case '1':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 0, 15);
        delay(500);
        layup();
        break;
        case '2':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 36, 15);
        delay(500);
        layup();
        break;
        case '3' :                                                                                        //***************************抽签调整**********************************
        moveServo(6, 72, 15);
        delay(500);
        layup();
        break;
        case '4':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 108, 15);
        delay(500);
        layup();
        break;
        case '5':                                                                                         //***************************抽签调整**********************************
        moveServo(6, 144, 15);
        delay(500);
        layup();
        break;
        case '7' :                                                                                        //***************************抽签调整**********************************
        moveServo(6, 180, 15);
        delay(500);
        layup();
        break;
      }
        initial_b();
        delay(500);
        Serial.println(scanflag);
        while(mySerial.read() >= 0){}
        /*while(mySerial.available()>0)
        mySerial.read();*/
        Flag_2=Flag_2+1;
        motorRun(FORWARD,200);
        delay(300);
}

void initial_a()                    
{
servo_(129,70,108,161,91,65);
}

void initial_b()                    //下料扫码down位
{
servo_(128,106,50,124,91,65);
}

void grab1()
{
  e=e+1;
  servo_(129,61,99,146,93,75);
  delay(300);
  servo_(129,61,99,146,93,45);
  delay(300);
  servo_(129,77,99,146,93,45);
  delay(300);
  servo_(11,97,74,138,85,45);
  delay(1200);
  servo_(11,100,65,149,85,45);
  delay(300);
  servo_(11,86,65,149,85,45);
  delay(300);
  servo_(11,86,65,149,85,75);
  delay(300);
  servo_(11,95,70,140,93,75);
  delay(300);
  servo_(129,80,95,134,93,70);  
  delay(1200);
}

void grab2()
{
  e=e+1;
  servo_(129,57,92,120,93,70);
  delay(300);
  servo_(129,57,92,120,93,45);
  delay(300);
  servo_(129,86,92,117,93,45);
  delay(300);
  servo_(11,100,80,138,85,45);
  delay(1200);
  servo_(11,100,65,149,85,45);
  delay(300);
  servo_(11,95,52,140,85,45);
  delay(300);
  servo_(11,95,52,140,85,70);
  delay(300);
  servo_(11,100,74,137,85,70);
  delay(300);
}
void layup()
{
  e=e+1;
  servo_(13,90,90,162,85,70);
  delay(1200);
  servo_(13,68,92,162,85,70);
  delay(300);
  servo_(13,68,92,162,85,45);
  delay(300);
  servo_(13,92,92,162,85,45);
  delay(300);
  servo_(128,98,79,124,95,45);
  delay(1200);
  servo_(128,77,83,124,95,45);
  delay(300);
  servo_(128,77,83,130,95,67);
  delay(300);
  servo_(128,105,79,130,95,67);
  delay(300);
}
void laydown()
{
  e=e+1;
  servo_(128,106,90,124,91,65);
  delay(300);
  servo_(13,90,90,162,85,70);
  delay(1200);
  servo_(13,68,92,162,85,70);
  delay(300);
  servo_(13,68,92,162,85,45);
  delay(300);
  servo_(13,92,92,162,85,45);
  delay(300);
  servo_(128,90,79,162,90,45);
  delay(1200);
  servo_(128,120,79,162,90,45);
  delay(300);
  servo_(128,120,49,121,90,45);
  delay(300);
  servo_(128,91,49,110,90,45);
  delay(500);
   servo_(128,91,49,110,90,67);
  delay(500);
  servo_(128,117,38,110,90,67);
  delay(500);
}

void loop()
{
  //initial_b();
  //Flag_1=99;
  //Flag_2=1;
  initial_a();
  motorRun(FORWARD,255);
   delay(200);
  //Flag_1=8;
  while(Flag_1 == 0)
  {   
     tracing();//循迹
     if(data[0]&&data[1]&&data[2]&&data[3])
     {
      motorRun(FORWARD,255);
      delay(200);
      Flag_1= 1;
     }
  }

  while(Flag_1 == 1)                           //上坡十字调整
  {
    tracing3();
    if(data[0]&&data[1]&&!data[3])
    {Flag_1 = 2;}
  }

  while(Flag_1 == 2)
  {
    data[4] = digitalRead(7);
    motorRun(FORWARD,220);
    //tracing3();
    if(data[4])
    { Flag_1 = 3;}
  }
  
  while(Flag_1 == 3)                           //上料第一次停止
 {
      motorRun(BACKWARD,150);
      delay(410);                              //上料第一次急停调整
      motorRun(STOP,0);
      servo_(129,65,108,162,91,70);              //上料区第一次扫码1
      delay(300);
      q=162;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(129,65,108,q,91,70);
     }
     judgment1();
     servo_(129,63,95,134,91,70);              //上料区第一次扫码2
     delay(300);
     q=134;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(129,63,95,q,91,70);
     }
     judgment2();
 }
 
   while( Flag_1  ==  4)                         //上料第二次停止
  {  
       data[4] = digitalRead(7);
       r=0;
       motorRun(FORWARD,200);
       if(data[4])
     { 
      motorRun(BACKWARD,150);
      delay(110);                               //上料第二次急停调整  
      motorRun(STOP,0); 
      servo_(129,65,108,162,91,70);               //上料区第二次扫码1
      delay(300);
      q=162;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(129,65,108,q,91,70);
     }
     judgment1();
      servo_(129,63,95,134,91,70);                //上料区第二次扫码2
     delay(300);
     q=134;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
       servo_(129,63,95,q,91,70); 
     }
     judgment2();
     }
  }

  while( Flag_1 == 5)                           //上料第三次停止
  {
      r=0;
      motorRun(FORWARD,200);
      data[4] = digitalRead(7);
      if(data[4] )
      { 
      motorRun(BACKWARD,150);
      delay(200);                              //上料第三次急停调整  
      motorRun(STOP,0);
      servo_(129,65,108,162,91,70);             //上料区第三次扫码1
      delay(300);
      q=162;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
     servo_(129,65,108,q,91,70);
     }
     judgment1();
     servo_(129,63,95,134,91,70);               //上料区第三次扫码2
     delay(300);
     q=134;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(129,63,95,q,91,70);
     }
     judgment2();
      }
  }
  
while(Flag_1 == 6)                              //上料第四次停止
{
      if(e>=6)
      {
        Flag_1=8;
      }
      r=0;
      motorRun(FORWARD,200);
      data[4] = digitalRead(7);
      if(data[4])
      { 
      motorRun(BACKWARD,150);
      delay(245);                               //上料第四次急停调整  
      motorRun(STOP,0);
     servo_(129,65,108,162,91,70);              //上料区第四次扫码1
     delay(300);
      q=162;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(129,65,108,q,91,70);
     }
     judgment1();
     servo_(129,63,95,134,91,70);              //上料区第四次扫码2
     delay(300);
     q=134;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
     servo_(129,63,95,q,91,70); 
     }
     judgment2();
      }
  }

     while(Flag_1 == 7)                          //上料第五次停止
{
       if(e>=6)
      {
        Flag_1=8;
      }
       r=0;
       motorRun(FORWARD,200);
       data[5] = digitalRead(6);
       if(data[5])
      { 
      motorRun(BACKWARD,150); 
      delay(175);                                //上料第五次急停调整  
      motorRun(STOP,0);
      servo_(129,65,108,162,91,70);                //上料区第五次扫码1
      delay(300);
      q=162;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(129,65,108,q,91,70);
     }
     judgment1();
     servo_(129,63,95,134,91,70);                  //上料区第五次扫码2
     delay(300);
     q=134;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(129,63,95,q,91,70); 
     }
     judgment2();
      }
  }

//**************************************栅格**************************************
while(Flag_1 == 8)                            
  {  
     e=0;
     tracing2();//执行：前面4个巡线
     if(data[0] && data[1] && data[2] && data[3])
     {
      initial_b();
      Flag_1=9;
      Flag_2=1;
     }
  }
//**************************************栅格**************************************


/*
//**************************************减速带**********************************
  while(Flag_1 == 8)                            
  {  
     e=0;
     tracing2();//执行：前面4个巡线
     if(data[0] && data[1] && data[2] && data[3])
     {
      initial_b();
      Flag_1=9;
     }
  }
  while(Flag_1 == 9)                             //减速带
  {  
     tracing2();//执行：前面4个巡线
     data[5] = digitalRead(6);
     if(data[5])
     {
     Flag_1=10;
     }
  }
  while(Flag_1 == 10)
  {
    tracing2();
    data[4] = digitalRead(7);
    if(data[4])
      {
        motorRun(FORWARD,200);
        delay(1000);
        Flag_1=11;
        Flag_2=1;
       }
  }
//**************************************减速带**********************************
*/

  while(Flag_2 == 1)
  {   
       tracing2();
       if(data[0]&&data[1]&&!data[3])
       {       
        Flag_2 = 2;
       }
  }
       
  while(Flag_2 == 2)                             //下料第一次停止
 {
      r=0;
      motorRun(BACKWARD,150);
      delay(255);                                //下料第一次急停调整
      motorRun(STOP,0);
      servo_(128,106,50,124,91,65);           //下料区第一次扫码1 down
      q=124;
      while(mySerial.read() >= 0){}
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(300);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(128,106,50,q,91,65);                                
     }
     judgment3();
     servo_(128,97,82,132,91,65);              //下料区第一次扫码2 up
     delay(1000);
     q=132;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(128,97,82,q,91,65);
     }
     judgment4();
 }
    
   while( Flag_2  ==  3)                         //下料第二次停止
  {  
       r=0;
       motorRun(FORWARD,200);//直行
       data[4] = digitalRead(7);
       if(data[4] )
      { 
       motorRun(BACKWARD,150);
       delay(150);                               //下料第二次急停调整  
       motorRun(STOP,0);
        servo_(128,106,50,124,91,65);             //下料区第二次扫码1 down
       q=124;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
       servo_(128,106,50,q,91,65); 
     }
     judgment3();
       servo_(128,97,82,132,91,65);                //下料区第二次扫码2 up
     delay(1000);
     q=132;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
        servo_(128,97,82,q,91,65); 
     }
     judgment4();
     }
  }
  
  while( Flag_2 == 4)                           //下料第三次停止
  {
       r=0;
       motorRun(FORWARD,200);//直行
       data[4] = digitalRead(7);
       if(data[4] )
      { 
       motorRun(BACKWARD,150);
       delay(230);                              //下料第三次急停调整  
       motorRun(STOP,0);
     servo_(128,106,50,124,91,65);              //下料区第三次扫码1 down
      q=124;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
     servo_(128,106,50,q,91,65);  
     }
     judgment3();
     servo_(128,97,82,132,91,65);              //下料区第三次扫码2 up
     delay(1000);
     q=132;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
     servo_(128,97,82,q,91,65); 
     }
     judgment4();
     }
  }
   
while(Flag_2 == 5)                              //下料第四次停止
{
      if(e>=6)
      {
        Flag_1=7;
      }
     r=0;
     motorRun(FORWARD,150);//直行
     data[4] = digitalRead(7);
       if(data[4] )
      { 
      motorRun(BACKWARD,150);
      delay(245);                               //下料第四次急停调整  
      motorRun(STOP,0);
      servo_(128,106,50,124,91,65);           //下料区第四次扫码1 down
      q=124;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(128,106,50,q,91,65); 
     }
     judgment3();
     servo_(128,97,82,132,91,65);          //下料区第四次扫码2 up
     delay(1000);
     q=132;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
     servo_(128,97,82,q,91,65);
     }
     judgment4();
     }
  }

while(Flag_2 == 6)                              //下料第五次停止
{
      if(e>=6)
      {
        Flag_1=7;
      }
       r=0;
       motorRun(FORWARD,200);//直行
       data[5] = digitalRead(6);
       if(data[5] )
      { 
      motorRun(BACKWARD,150);
      delay(150);                               //下料第五次急停调整  
      motorRun(STOP,0); 
     servo_(128,106,50,124,91,65);            //下料区第五次扫码1 down
      q=124;
      while(r==0)
     {     
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
      servo_(128,106,50,q,91,65);
     }
     judgment3();
    servo_(128,97,82,132,91,65);               //下料区第五次扫码2 up
     delay(1000);
     q=132;
     while(r==1)
     {
      scanflag == ' ';
      scanflag = scan();
      Serial.println("scan");
      delay(200);
       if(scanflag != ' ')
      {
        r=r+1;
      }
      q=q-1;
     servo_(128,97,82,q,91,65);   
     }
     judgment4();
     }
  }

  while(Flag_2 == 7)
  {  
     tracing();
     if(!data[0] && !data[1] && !data[2] && !data[3])
     {
     motorRun(FORWARD,200);
     delay(300);
     motorRun(STOP,0);
     delay(5000);
     }
  }
}
