
#include "ros/ros.h"
#include "std_msgs/UInt16.h"

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher servo1pub = n.advertise<std_msgs::UInt16>("servo1", 1000);
  ros::Publisher servo2pub = n.advertise<std_msgs::UInt16>("servo2", 1000);
  ros::Publisher servo3pub = n.advertise<std_msgs::UInt16>("servo3", 1000);
  ros::Publisher servo4pub = n.advertise<std_msgs::UInt16>("servo4", 1000);
  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    std_msgs::UInt16 msg;
    int servocmd = 0;
    std::cin >> servocmd;
    if(servocmd <= 2000 && servocmd >= 0){
        msg.data = servocmd - 1000;
        servo1pub.publish(msg);
        ROS_INFO("%d sent to servo 1", msg.data);
    }
    if(servocmd <= 3000 && servocmd >= 2000){
        msg.data = servocmd - 2000;
        servo2pub.publish(msg);
        ROS_INFO("%d sent to servo 2", msg.data);
    }
    if(servocmd <= 4000 && servocmd >= 3000){
        msg.data = servocmd - 3000;
        servo3pub.publish(msg);
        ROS_INFO("%d sent to servo 3", msg.data);
    }
        if(servocmd <= 5000 && servocmd >= 4000){
        msg.data = servocmd - 4000;
        servo4pub.publish(msg);
        ROS_INFO("%d sent to servo 4", msg.data);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
