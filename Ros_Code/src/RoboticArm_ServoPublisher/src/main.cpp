
#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "tf/transform_broadcaster.h"

const double Pi = 3.14159265358979323846264; //constant expression
const double toRadian = Pi / 180;
const double toDegree = 180 / Pi;

const double q1Min = 0;
const double q1Max = 90;
const double q1Min2 = 270;
const double q1Max2 = 359;

const double q2Min = 20;
const double q2Max = 160;

const double q3Min = 0;
const double q3Max = 90;
const double q3Min2 = 315;
const double q3Max2 = 359;

const double q4Min = 0;
const double q4Max = 100;

const double h1 = 1.75;
const double l1 = 0.3;
const double l2 = 8.0;
const double l3 = 8.0;
const double le = 6.0;

void constrain(double &angle, double minangle,double maxangle){
  angle = angle > maxangle ? maxangle : angle;
  angle = angle < minangle ? minangle : angle;
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher servo1pub = n.advertise<std_msgs::UInt16>("servo1", 1000);
  ros::Publisher servo2pub = n.advertise<std_msgs::UInt16>("servo2", 1000);
  ros::Publisher servo3pub = n.advertise<std_msgs::UInt16>("servo3", 1000);
  ros::Publisher servo4pub = n.advertise<std_msgs::UInt16>("servo4", 1000);
  tf::TransformBroadcaster tfbroadcaster;
  ros::Rate loop_rate(10);

  double q1 = 0;
  double q2 = 0;
  double q3 = 0;
  double q4 = 0;
  double alpha1 = Pi/2;

  ROS_INFO("ROBOTARM CMD FOR JOINT TELE-OPERATION");
  ROS_INFO("Usage: first number for selecting the joint (eg: 1XXX)");
  ROS_INFO("last 3 numbers to select the joint angle (eg: first joint at 90° : 1090");



  while (ros::ok())
  {

    std_msgs::UInt16 msg;
    int servocmd = 0;
    ROS_INFO("Enter CMD:");
    std::cin >> servocmd;
    if(servocmd < 2000 && servocmd >= 1000){
        q1 = servocmd - 1000;
        
        if(q1 >= q1Min && q1 < q1Min2)
          constrain(q1,q1Min,q1Max);
        else if (q1 >= q1Min2)
          constrain(q1,q1Min2,q1Max2);

        msg.data = q1;
        servo1pub.publish(msg);
        ROS_INFO("%d sent to servo 1", msg.data);

        q1 = q1 * toRadian;
    }
    if(servocmd < 3000 && servocmd >= 2000){
        q2 = servocmd - 2000;

        constrain(q2,q2Min,q2Max);

        msg.data = q2;
        servo2pub.publish(msg);
        ROS_INFO("%d sent to servo 2", msg.data);

        q2 = q2* toRadian;

    }
    if(servocmd < 4000 && servocmd >= 3000){
        q3 = servocmd - 3000;
        
        if(q3 >= q3Min && q3 < q3Min2)
          constrain(q3,q3Min,q3Max);
        else if (q3 >= q3Min2)
          constrain(q3,q3Min2,q3Max2);
        
        msg.data=q3;
        servo3pub.publish(msg);
        ROS_INFO("%d sent to servo 3", msg.data);
    
        q3 = q3 * toRadian;

    }
        if(servocmd < 5000 && servocmd >= 4000){
        q4= servocmd - 4000;

        constrain(q4,q4Min,q4Max);

        msg.data = q4;
        servo4pub.publish(msg);
        ROS_INFO("%d sent to servo 4", msg.data);
    }


  
    tf::Transform tf1;
    tf::Transform tf2;
    tf::Transform tf3;
    tf::Transform tf4;

    tf1.setOrigin(tf::Vector3(0,0,0));
    tf::Quaternion quat1;
    quat1.setRPY(0,0,q1);
    tf1.setRotation(quat1);
    tfbroadcaster.sendTransform( tf::StampedTransform(tf1,ros::Time::now(), "/base_link", "/frame1"));

    tf2.setOrigin(tf::Vector3(l1,0,h1));
    tf::Quaternion quat2;
    quat2.setRPY(alpha1,-q2,0);
    tf2.setRotation(quat2);
    tfbroadcaster.sendTransform( tf::StampedTransform(tf2,ros::Time::now(), "/frame1", "/frame2"));

    tf3.setOrigin(tf::Vector3(l2,0,0));
    tf::Quaternion quat3;
    double q3d = -(q2+q3);
    quat3.setRPY(0,0,q3d);
    tf3.setRotation(quat3);
    tfbroadcaster.sendTransform( tf::StampedTransform(tf3,ros::Time::now(), "/frame2", "/frame3"));
    
    tf4.setOrigin(tf::Vector3(l3+le,0,0));
    tf::Quaternion quat4;
    quat4.setRPY(0,0,0);
    tf4.setRotation(quat4);
    tfbroadcaster.sendTransform( tf::StampedTransform(tf4,ros::Time::now(), "/frame3", "/frame4"));

    ROS_INFO("q1: %f, q2: %f, q3: %f, q3d: %f\n", q1,q2,q3,q3d);




    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
