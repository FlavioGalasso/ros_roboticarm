/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo l1;
Servo l2;
Servo l3;
Servo l4;



int L1 = 80;      //Shoulder to elbow length
int L2 = 80;      //Elbow to wrise length
int L3 = 68;      //Length from wrist to hand PLUS base centre to shoulder

int increment = 1;
int loop_time_ms = 10; 
unsigned long last_loop_time_ms = 0;

int print_time_ms = 3000; 
unsigned long last_loop_printtime_ms = 0;

float pz = 0;

void update1(int kin_ang, int &s1){
  s1 = 90-kin_ang;
  l1.write(s1);
}

void update2(int kin_ang, int &s2){
  s2 = 180-kin_ang;
  s2 = s2+s2*0.2;
  l2.write(s2);
}

void update3(int kin_ang, int &s3){
  s3 = 180-kin_ang;
  s3 = s3 + s3/6 - 35;
  l3.write(s3);
}



void setup() {
  Serial.begin(9600);
  l1.attach(5);  
  l2.attach(7); 
  l3.attach(11); 
  //l4.attach(10);  
  }
int q1,q2,q3;
int kq1,kq2,kq3;
float krq1,krq2,krq3;
int state = 0;
float x,y,z;
float xd = 0;
float yd = 148;
float zd = 80;
float t = 0;
int sign = 1;
void loop() {
  delay(5);
  unsolve(krq1,krq2,krq3,x,y,z);
  
  if(sign == 1){
      xd = 0+ 30*cos(t);
      zd= 50+30*sin(t);
      t += 0.01;
      if(t >= 2*PI){
        t = 0;
        sign = 1;
      }
  }
//  else if(sign == -1){
//      zd = 80.0 - 60.0*t;
//      t += 0.008;
//      if(t >= 1){
//        t = 0;
//        sign = 1;
//      }
//  }


  solve(xd,yd,zd,krq1,krq2,krq3);
  kq1=krq1*RAD_TO_DEG;
  kq2=krq2*RAD_TO_DEG;
  kq3=-krq3*RAD_TO_DEG;

  update1(kq1,q1);
  update2(kq2,q2);
  update3(kq3,q3);
//  Serial.println("x: "+String(x) + " y: " + String(y) + " z: " + String(z)) ;
//  Serial.println("xd: "+String(xd) + " yd: " + String(yd) + " zd: " + String(zd)) ;
//  Serial.println("kq1: "+String(kq1) + " kq2: " + String(kq2) + " kq3: " + String(kq3)) ;
//  Serial.println("q1: "+String(q1) + " q2: " + String(q2) + " kq3: " + String(q3)) ;
// 
//  if(millis() - last_loop_printtime_ms > print_time_ms){
//    Serial.println("x: "+String(x) + " y: " + String(y) + " z: " + String(z)) ;
//    Serial.println("xd: "+String(xd) + " yd: " + String(yd) + " zd: " + String(zd)) ;
//    Serial.println("kq1: "+String(kq1) + " kq2: " + String(kq2) + " kq3: " + String(kq3)) ;
//    Serial.println("q1: "+String(q1) + " q2: " + String(q2) + " kq3: " + String(q3)) ;
//    
//    last_loop_printtime_ms = millis();
//  }
//  while(millis() - last_loop_time_ms < loop_time_ms);
//  last_loop_time_ms = millis();

}
