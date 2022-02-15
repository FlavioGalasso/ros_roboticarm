#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>

#define SERVO1_PIN 5
#define SERVO2_PIN 7
#define SERVO3_PIN 11
#define SERVO4_PIN 10
#define OMEGA_SPEED 1

Servo l1;
Servo l2;
Servo l3;
Servo l4;

int L1 = 80;      //Shoulder to elbow length
int L2 = 80;      //Elbow to wrise length
int L3 = 68;      //Length from wrist to hand PLUS base centre to shoulder

int req_kq1 = 0;
int req_kq2 = 90;
int req_kq3 = 50;
int req_kq4 = 50;

int kq1 = 0;
int kq2 = 90;
int kq3 = 90;
int kq4 = 50;

void servo1_cb( const std_msgs::UInt16& cmd_msg){
  req_kq1 = cmd_msg.data;
}

void servo2_cb( const std_msgs::UInt16& cmd_msg){
  req_kq2 = cmd_msg.data;
}

void servo3_cb( const std_msgs::UInt16& cmd_msg){
  req_kq3 = cmd_msg.data;
}

void servo4_cb( const std_msgs::UInt16& cmd_msg){
  req_kq4 = cmd_msg.data;
}


void updateq1(int kin_ang){
  int s1 = 90-kin_ang;
  l1.write(s1);
}

void updateq2(int kin_ang){
  int s2 = 180-kin_ang;
  s2 = s2+s2*0.2;
  l2.write(s2);
}

void updateq3(int kin_ang){
  int s3 = 180-kin_ang;
  s3 = s3 + s3/6 - 35;
  l3.write(s3);
}

void updateq4(int kin_ang){
  int s4 = -0.35*kin_ang + 55;
  l4.write(s4);
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
}

void loop(){
  nh.spinOnce();
  if(req_kq1 > kq1) kq1 += OMEGA_SPEED;
  if(req_kq1 < kq1) kq1 -= OMEGA_SPEED;
  
  if(req_kq2 > kq2) kq2 += OMEGA_SPEED;
  if(req_kq2 < kq2) kq2 -= OMEGA_SPEED;
  
  if(req_kq3 > kq3) kq3 += OMEGA_SPEED;
  if(req_kq3 < kq3) kq3 -= OMEGA_SPEED;

  if(req_kq4 > kq4) kq4 += OMEGA_SPEED;
  if(req_kq4 < kq4) kq4 -= OMEGA_SPEED;

  updateq1(kq1);
  updateq2(kq2);
  updateq3(kq3);
  updateq4(kq4);
  
}
