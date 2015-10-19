#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "car_cmd_vel_pub");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    geometry_msgs::Twist msg;
    msg.linear.x=1,msg.linear.y=0,msg.linear.z=0;
    msg.angular.x=0,msg.angular.y=0,msg.angular.z=0;
    //std::stringstream ss;
    //ss << " I am the example1_a node ";
    //msg.data = ss.str();
    //ROS_INFO("%s", msg.data.c_str());
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
