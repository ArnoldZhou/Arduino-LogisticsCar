# Arduino-Logistics-car
基于Arduino MEGA2560的智能物流小车(工程能力训练综合竞赛)

## 1.项目功能要求
去年暑假前报了某比赛（工程训练能力综合竞赛），比赛要求是做一个智能物流小车。项目要求小车实现的功能有—“赛道自主行走、物料扫码识别、规避障碍、跨越减速带和栅格、码垛和规避循迹的功能。”

![比赛地图](https://img-blog.csdnimg.cn/20190325183444568.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)

## 2.小车组成构架

![智能小车结构说明](https://img-blog.csdnimg.cn/20190325184116443.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)

a.==小车底盘设计==
小车底盘主要组成是：直流电机、电机支架、孔平板、联轴器、轮胎组成。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190325184441731.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)

b.==机械臂及抓取设计==
考虑到机械臂需要实现的功能以及机械臂与物料台之间的协调性，设计了6自由度的机械臂，并且用舵机来作为机械臂的关节。

![机械臂设计](https://img-blog.csdnimg.cn/20190325184640108.png)

抓取部件需要 — 咬合力大；结构简单切材料刚性好；接触点与物料之间的摩擦力大

![抓取设计](https://img-blog.csdnimg.cn/20190325184707986.png)

c.==物料台设计==
考虑到小车的车型，以及物料台和机械臂之间的距离，选择在小车旁边加一块小车铝合金板，在铝合金板上固定舵机，舵机上放通过金属舵盘和亚克力物料台固定，从而实现舵机对物料架的控制。

![物料台设计](https://img-blog.csdnimg.cn/20190325185021981.png)

d. ==小车主视图与左视图==

![主视图](https://img-blog.csdnimg.cn/2019032519074818.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190525103743326.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)

e.==小车爆炸图==

![爆炸图](https://img-blog.csdnimg.cn/20190325190834491.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)
## 3.主要零部件


| 名称 |  型号|
|--|--|
| 主控板 |MEGA2560及扩展板  |
|  灰度传感器|TCRT5000  |
|超声波|HC-SR04|
| 降压模块 |LM2596  |
|直流电机|JGB37-520|
|金属舵机|D3625MG/PDI6225MG|
|舵机板|16位舵机板|
|电池|9V电池|
## 4.程序流程图

![1](https://img-blog.csdnimg.cn/20190325191146264.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)

![2](https://img-blog.csdnimg.cn/20190325191201506.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)

## 5.成品展示
1.0初期版本(电线凌乱，布局混乱，物料架仅能放三个物体)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190325193527397.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zODAxNDY0MA==,size_16,color_FFFFFF,t_70)
2.0升级版本

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190325192927755.gif)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190325193011730.gif)
