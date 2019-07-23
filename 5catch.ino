#include <Wire.h>
#include <SoftwareSerial.h>
//发送部分的指令
#define FRAME_HEADER            0xFF   //帧头
#define CMD_SERVO_SPEED         0x01   //设置舵机速度
#define CMD_SERVO_PLACE         0x02   //设置舵机位置
#define CMD_ACTION_GROUP_RUN    0x09   //运行动作组
#define CMD_STOP_REFRESH        0x0b   //急停、恢复指令
#define GET_LOW_BYTE(A) (uint8_t)((A))     //宏函数 获得A的低八位
 #define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)     //宏函数 获得A的高八位
 
SoftwareSerial ServoSerial(19,18); // RX, TX 软串口
int old[6] = {30,138,157,162,82,45};//记录上一次舵机状态


void setup() {
  // put your setup code here, to run once:
  ServoSerial.begin(9600);
  Serial.begin(9600);
  servo_(164,0,20,135,180,65);//手爪下移到物块中间（手爪开）
 }
/************************************************
 函数名：moveServo
 功能：舵机运动控制 
 参数：servoID 舵机编号 Position：目标位置 Speed：移动速度
 ************************************************/
void moveServo(uint8_t servoID, uint16_t Position, uint16_t Speed)
{
  uint8_t buf[15];
//  if (servoID > 15 || !(Speed > 0)) { 
//    return;
//  }
  Position = Position*100/9+500;  
  buf[0] = FRAME_HEADER;                  
  buf[1] = CMD_SERVO_SPEED;
  buf[2] = servoID;                        
  buf[3] = GET_LOW_BYTE(Speed);              
  buf[4] = GET_HIGH_BYTE(Speed);            
  buf[5] = FRAME_HEADER;             
  buf[6] = CMD_SERVO_PLACE;          
  buf[7] = servoID;                    
  buf[8] = GET_LOW_BYTE(Position);        
  buf[9] = GET_HIGH_BYTE(Position);       
  ServoSerial.write(buf, 10);
}
/************************************************
 函数名：servo_
 功能：机械臂运动控制 
 参数：D1 D2 D3 D4 D5 D6   6个参数依次为6个舵机转动到的角度
 ************************************************/
void servo_(int D1, int D2, int D3, int D4, int D5, int D6) 
{
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
    moveServo(i, place[i], speed/2);
    t[i] = d[i] * 112 / speed;
    if (t[i] > t_max) 
    {
      t_max = t[i];
    }
  }
  delay(t_max);
}



/*************************************************
 函数名：grab_init()
 功能：机械臂初始状态
 *************************************************/
 void grab_init()
 {
  
 }


/*************************************************
 函数名：grab()
 功能：拽去一个物料
 *************************************************/
void grab()
{
  
}

/*************************************************
 函数名：put_down()
 功能：放下一个物料
 *************************************************/
void put_down()
{
  
}
void loop() {
  
  servo_(90,32,29,158,18,14);
  servo_(86,72,34,180,11,14);
  servo_(92,97,52,180,11,14);
  servo_(92,97,52,180,11,50);
}
