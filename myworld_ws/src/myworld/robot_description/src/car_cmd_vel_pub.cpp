#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "geometry_msgs/Twist.h"
#include <stdlib.h>
#include <time.h>
#include "tf/transform_listener.h"
#include "tf/transform_broadcaster.h"
#include "nav_msgs/Odometry.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "car_cmd_vel_pub");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000); //100 or 1000?
  ros::Rate loop_rate(10);

  tf::TransformListener listener;
  tf::StampedTransform transform,t2;
  //tf::TransformBroadcaster br; 

  geometry_msgs::Twist msg;

  int vel_factor;
  //double st_time=clock();
  double  st_time=time(NULL);
  double difftime;

  double ox,oy,nx,ny;

  while (ros::ok())
  {
    //double difftime=(clock()-st_time)/CLOCKS_PER_SEC; //temporal speed
    difftime=time(NULL)-st_time;
    if(difftime<6*60) vel_factor=3;
    else if(difftime<12*60) vel_factor=2;
    else if(difftime<20*60) vel_factor=1;
    else vel_factor=0;      
				//temporal odom
	ROS_INFO("difftime=%lf  ",difftime);

	//t2.setOrigin( tf::Vector3(0.0, 0.0, 0.0) ); // must here?
        //t2.setRotation( tf::Quaternion( 0.0, 0.0, -0.383, 0.924) );// -pi/4
        //br.sendTransform( tf::StampedTransform(t2, ros::Time::now(), "odom", "world_fixed") );
	

	try{
          listener.waitForTransform( "odom", "base_footprint",ros::Time(0), ros::Duration(10.0) );  //?? tf listener tutorial学到的
	 listener.lookupTransform( "odom","base_footprint",
		                  ros::Time(0), transform); //谁前谁后有讲究
	}
	catch (tf::TransformException &ex) {
	 ROS_ERROR("erro occurs! %s\n",ex.what());
	 //ros::Duration(1.0).sleep();
	 //continue;
	}
	
    ox=transform.getOrigin().x();
    oy=transform.getOrigin().y();
     
    nx=ox*0.707+oy*(-0.707);
    ny=ox*0.707+oy*0.707;
    ROS_INFO("ox=%lf oy=%lf nx=%lf ny=%lf\n",ox,oy,nx,ny);
    
    if(nx>=14.14||nx<=-14.14){ //左半圆 || youbanyuan
	
	    msg.linear.x=5.0/6*(vel_factor/3.0),msg.linear.y=0,msg.linear.z=0;
	    msg.angular.x=0,msg.angular.y=0,msg.angular.z=-msg.linear.x/20;
    }else{
	    msg.linear.x=5.0/6*(vel_factor/3.0),msg.linear.y=0,msg.linear.z=0;
	    msg.angular.x=0,msg.angular.y=0,msg.angular.z=0;
    }
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
