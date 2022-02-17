#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>

#define SERVO1_PIN 5
#define SERVO2_PIN 7
#define SERVO3_PIN 11
#define SERVO4_PIN 10
#define OMEGA_SPEED 1
#define LOOPTIME_MS 10

Servo l1;
Servo l2;
Servo l3;
Servo l4;

int L1 = 80;      //Shoulder to elbow length
int L2 = 80;      //Elbow to wrise length
int L3 = 68;      //Length from wrist to hand PLUS base centre to shoulder

int req_kq1 = 0;
int req_kq2 = 90;
int req_kq3 = 0;
int req_kq4 = 50;

int q1 = 0;
int q2 = 90;
int q3 = 0;
int q4 = 50;

bool wasConnected = false;

unsigned long looptime = 0;

void servo1_cb( const std_msgs::UInt16& cmd_msg){
  req_kq1 = cmd_msg.data;
   kq1_to_q1(req_kq1);
}

void servo2_cb( const std_msgs::UInt16& cmd_msg){
  req_kq2 = cmd_msg.data;
   kq2_to_q2(req_kq2);
}

void servo3_cb( const std_msgs::UInt16& cmd_msg){
  req_kq3 = cmd_msg.data;
   kq3_to_q3(req_kq3);
}

void servo4_cb( const std_msgs::UInt16& cmd_msg){
  req_kq4 = cmd_msg.data;
   kq4_to_q4(req_kq4);
}


void kq1_to_q1(int &kin_ang){
  if(kin_ang >= 270) kin_ang=kin_ang - 360;
  kin_ang = 90+kin_ang;
}

void kq2_to_q2(int &kin_ang){
  kin_ang = 180-kin_ang;
  kin_ang = kin_ang+kin_ang*0.2;
}

void kq3_to_q3(int &kin_ang){
  kin_ang = 180-kin_ang;
  kin_ang = kin_ang +kin_ang*0.13 -42;
}

void kq4_to_q4(int &kin_ang){
  kin_ang = -0.35*kin_ang + 55;
}

ros::NodeHandle  nh;
ros::Subscriber<std_msgs::UInt16> sub1("servo1", servo1_cb);
ros::Subscriber<std_msgs::UInt16> sub2("servo2", servo2_cb);
ros::Subscriber<std_msgs::UInt16> sub3("servo3", servo3_cb);
ros::Subscriber<std_msgs::UInt16> sub4("servo4", servo4_cb);


void setup(){
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  l1.attach(SERVO1_PIN);  
  l2.attach(SERVO2_PIN); 
  l3.attach(SERVO3_PIN); 
  l4.attach(SERVO4_PIN);

  kq1_to_q1(req_kq1);
  kq2_to_q2(req_kq2);
  kq3_to_q3(req_kq3);
  kq4_to_q4(req_kq4);

  q1 = req_kq1;
  q2 = req_kq2;
  q3 = req_kq3;
  q4=req_kq4;
}

void loop(){
  looptime = millis();

  if (!nh.connected()){
    req_kq1 = 0;
    req_kq2 = 90;
    req_kq3 = 70;
    req_kq4 = 50;
    kq1_to_q1(req_kq1);
    kq2_to_q2(req_kq2);
    kq3_to_q3(req_kq3);
    kq4_to_q4(req_kq4);
    wasConnected = false;
  }
  else if(wasConnected == false){
    wasConnected = true;
    req_kq1 = 0;
    req_kq2 = 90;
    req_kq3 = 0;
    req_kq4 = 50;
    kq1_to_q1(req_kq1);
    kq2_to_q2(req_kq2);
    kq3_to_q3(req_kq3);
    kq4_to_q4(req_kq4);
  }
  
  if(req_kq1 > q1) q1 += OMEGA_SPEED;
  if(req_kq1 < q1) q1 -= OMEGA_SPEED;
  
  if(req_kq2 > q2) q2 += OMEGA_SPEED;
  if(req_kq2 < q2) q2 -= OMEGA_SPEED;
  
  if(req_kq3 > q3) q3 += OMEGA_SPEED;
  if(req_kq3 < q3) q3 -= OMEGA_SPEED;

  if(req_kq4 > q4) q4 += OMEGA_SPEED;
  if(req_kq4 < q4) q4 -= OMEGA_SPEED;

  l1.write(q1);
  l2.write(q2);
  l3.write(q3);
  l4.write(q4);
  
  nh.spinOnce();
  while(millis() - looptime < LOOPTIME_MS);
  
  
}
