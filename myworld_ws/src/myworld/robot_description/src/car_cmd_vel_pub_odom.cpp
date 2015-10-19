#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "geometry_msgs/Twist.h"
#include <stdlib.h>
#include <time.h>
#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"
#include "gazebo_msgs/ModelStates.h"

ros::Publisher pub;
int vel_factor;
double  st_time;
double deltatime,ox,oy,nx,ny;

void cb(const gazebo_msgs::ModelStates::ConstPtr& current){

	deltatime=time(NULL)-st_time;
    if(deltatime<6*60) vel_factor=3;
    else if(deltatime<12*60) vel_factor=2;
    else if(deltatime<20*60) vel_factor=1;
    else vel_factor=0; 
ROS_INFO("deltatime=%lf  ",deltatime);

    ox=current->pose[2].position.x;
    oy=current->pose[2].position.y;
     
    nx=ox*0.707+oy*(-0.707);
    ny=ox*0.707+oy*0.707;
    ROS_INFO("ox=%lf oy=%lf nx=%lf ny=%lf\n",ox,oy,nx,ny);
    geometry_msgs::Twist msg;
    if(ox>=14.14){ //左半圆 || youbanyuan
	
	    msg.linear.x=25.0/6*(vel_factor/3.0),msg.linear.y=0,msg.linear.z=0;//正确速度应该是25/6
	    msg.angular.x=0,msg.angular.y=0,msg.angular.z=-msg.linear.x/20;
    }else if(ox<=-14.14){
	 msg.linear.x=25.0/6*(vel_factor/3.0),msg.linear.y=0,msg.linear.z=0;//正确速度应该是25/6
	    msg.angular.x=0,msg.angular.y=0,msg.angular.z=msg.linear.x/20;
    }else{
	    msg.linear.x=25.0/6*(vel_factor/3.0),msg.linear.y=0,msg.linear.z=0;
	    msg.angular.x=0,msg.angular.y=0,msg.angular.z=0;
    }
    //std::stringstream ss;
    //ss << " I am the example1_a node ";
    //msg.data = ss.str();
    //ROS_INFO("%s", msg.data.c_str());
    pub.publish(msg);
}
     
     
int main(int argc, char **argv)
{
  ros::init(argc, argv, "car_cmd_vel_pub_odom");
  ros::NodeHandle n;
  //ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  //ros::Rate loop_rate(10);
  st_time=time(NULL);
  ros::Subscriber sub = n.subscribe("/gazebo/model_states",1000,cb);
  ros::spin();
  //while (ros::ok())
  //{
    //geometry_msgs::Twist msg;
    //msg.linear.x=1,msg.linear.y=0,msg.linear.z=0;
    //msg.angular.x=0,msg.angular.y=0,msg.angular.z=0;
    //std::stringstream ss;
    //ss << " I am the example1_a node ";
    //msg.data = ss.str();
    //ROS_INFO("%s", msg.data.c_str());
    //pub.publish(msg);
    //ros::spinOnce();
    //loop_rate.sleep();
  //}
  return 0;
}
