
#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "tf/transform_broadcaster.h"

const double Pi = 3.14159265358979323846264; //constant expression
const double toRadian = Pi / 180;
const double toDegree = 180 / Pi;

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

  double l1 = 1;
  double l2 = 2;
  double l3 = 2;
  double le = 1;
  double q1 = 0;
  double q2 = 0;
  double q3 = 0;
  double q4 = 0;
  double alpha1 = Pi/2;


  while (ros::ok())
  {

    std_msgs::UInt16 msg;
    int servocmd = 0;
    std::cin >> servocmd;
    if(servocmd <= 2000 && servocmd >= 0){
        msg.data = servocmd - 1000;
        servo1pub.publish(msg);
        q1 = msg.data * toRadian;
        ROS_INFO("%d sent to servo 1", msg.data);
    }
    if(servocmd <= 3000 && servocmd >= 2000){
        msg.data = servocmd - 2000;
        servo2pub.publish(msg);
        q2 = msg.data * toRadian;
        ROS_INFO("%d sent to servo 2", msg.data);
    }
    if(servocmd <= 4000 && servocmd >= 3000){
        msg.data = servocmd - 3000;
        servo3pub.publish(msg);
        q3 = msg.data * toRadian;
        ROS_INFO("%d sent to servo 3", msg.data);
    }
        if(servocmd <= 5000 && servocmd >= 4000){
        msg.data = servocmd - 4000;
        servo4pub.publish(msg);
        q4 = msg.data;
        ROS_INFO("%d sent to servo 4", msg.data);
    }


  
    tf::Transform tf1;
    tf::Transform tf2;
    tf::Transform tf3;
    tf::Transform tf4;

    tf1.setOrigin(tf::Vector3(l1,0,0));
    tf::Quaternion quat1;
    quat1.setRPY(alpha1,0,q1);
    tf1.setRotation(quat1);
    tfbroadcaster.sendTransform( tf::StampedTransform(tf1,ros::Time::now(), "/base_link", "/frame1"));

    tf2.setOrigin(tf::Vector3(l2,0,0));
    tf::Quaternion quat2;
    quat2.setRPY(0,0,q2);
    tf2.setRotation(quat2);
    tfbroadcaster.sendTransform( tf::StampedTransform(tf2,ros::Time::now(), "/frame1", "/frame2"));

    tf3.setOrigin(tf::Vector3(l3+le,0,0));
    tf::Quaternion quat3;
    q3 = -(q2+q3);
    quat3.setRPY(0,0,q3);
    tf3.setRotation(quat3);
    tfbroadcaster.sendTransform( tf::StampedTransform(tf3,ros::Time::now(), "/frame2", "/frame3"));




    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
